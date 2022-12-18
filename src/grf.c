#include "grf.h"
#include "windowsx.h"

#define CLASS_NAME L"GameRoom"
#define WIN_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)

void dummyOnDraw(HDC hdc, LPPAINTSTRUCT ps) {}
void dummyCallback() {}
void dummyOnMouseButton(int button, int x, int y) {}
void dummyOnMouseMove(int x, int y) {}
void dummyOnKey(int key) {}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static DrawCallback callbackOnDraw = &dummyOnDraw;
static CommonCallback callbackOnLoad = &dummyCallback;
static CommonCallback callbackOnExit = &dummyCallback;
static MouseButtonCallback callbackOnMouseDown = &dummyOnMouseButton;
static MouseButtonCallback callbackOnMouseUp = &dummyOnMouseButton;
static MouseMoveCallback callbackOnMouseMove = &dummyOnMouseMove;
static KeyboardCallback callbackOnKeyDown = &dummyOnKey;
static KeyboardCallback callbackOnKeyUp = &dummyOnKey;

static int isLoaded = 0;
static HBRUSH backgroundBrush;
static uint8_t bgrR = 0;
static uint8_t bgrG = 0;
static uint8_t bgrB = 0;
static HINSTANCE hInst;
static HWND hWindow;

static HDC backbufferHdc;
static HBITMAP backbufferBitmap;
static RECT backbufferRect;
static int clientWidth;
static int clientHeight;

static HDC imageHdc;
static RECT paintRect;
static int isDrawing = 0;

static void CreateBackbufferImage(HDC mainHdc, int width, int height) {
    if (backbufferBitmap) {
        DeleteObject(backbufferBitmap);
    }
    backbufferBitmap = CreateCompatibleBitmap(mainHdc, width, height);
    backbufferRect.right = width;
    backbufferRect.bottom = height;
    SelectObject(backbufferHdc, backbufferBitmap);
    FillRect(backbufferHdc, &backbufferRect, backgroundBrush);
}

static void InitBackbuffer(HDC mainHdc, int width, int height) {
    backbufferRect.left = 0;
    backbufferRect.top = 0;
    backbufferHdc = CreateCompatibleDC(mainHdc);
    imageHdc = CreateCompatibleDC(mainHdc);
    CreateBackbufferImage(mainHdc, width, height);
}

static void FreeBackbuffer() {
    DeleteObject(backbufferBitmap);
    DeleteDC(backbufferHdc);
    DeleteDC(imageHdc);
}

void appSetClbDraw(DrawCallback draw_callback) {
    callbackOnDraw = draw_callback;
}

void grfSetOnLoad(CommonCallback load_callback) {
    callbackOnLoad = load_callback;
}

void grfSetOnExit(CommonCallback exit_callback) {
    callbackOnExit = exit_callback;
}

void grfSetOnMouseDown(MouseButtonCallback mouse_callback) {
    callbackOnMouseDown = mouse_callback;
}

void grfSetOnMouseUp(MouseButtonCallback mouse_callback) {
    callbackOnMouseUp = mouse_callback;
}

void grfSetOnMouseMove(MouseMoveCallback mouse_callback) {
    callbackOnMouseMove = mouse_callback;
}

void grfSetOnKeyDown(KeyboardCallback key_callback) {
    callbackOnKeyDown = key_callback;
}

void grfSetOnKeyUp(KeyboardCallback key_callback) {
    callbackOnKeyUp = key_callback;
}

void grfSetFillColor(uint8_t r, uint8_t g, uint8_t b) {
    if (isLoaded) {
        DeleteObject(backgroundBrush);
        backgroundBrush = CreateSolidBrush(RGB(r, g, b));
    } else {
        bgrR = r;
        bgrG = g;
        bgrB = b;
    }
}

static GRFImage __grfLoadImage(const wchar_t* filename, int fromRes) {
    GRFImage result = (GRFImage)malloc(sizeof(__GRFImageData));
    if (fromRes) {
        result->bitmap = (HBITMAP)LoadImage(hInst, filename, IMAGE_BITMAP, 0, 0, 0);
    } else {
        result->bitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }

    BITMAP bitmap;
    GetObject(result->bitmap, sizeof(bitmap), &bitmap);
    result->width = bitmap.bmWidth;
    result->height = bitmap.bmHeight;

    return result;
}

GRFImage grfLoadImageFromRes(const wchar_t* filename) {
    return __grfLoadImage(filename, 1);
}

GRFImage grfLoadImageFromFile(const wchar_t* filename) {
    return __grfLoadImage(filename, 0);
}

void grfFreeImage(GRFImage image) {
    DeleteObject(image->bitmap);
    free(image);
}

int grfStart(HINSTANCE hInstance, const wchar_t* title, int width, int height) {
    SetProcessDPIAware();

    hInst = hInstance;
    clientWidth = width;
    clientHeight = height;

    WNDCLASSEX wc;
    SIZE screenSize;
    LONG winX, winY;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // Create widow class

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(hInstance, L"icMain");
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbWndExtra = 0;
    wc.cbClsExtra = 0;
    wc.lpszMenuName = NULL;

    if (!RegisterClassEx(&wc)) {
        return -1;
    }

    // Calculate window geometry

    screenSize.cx = GetSystemMetrics(SM_CXSCREEN);
    screenSize.cy = GetSystemMetrics(SM_CYSCREEN);

    winX = (screenSize.cx - width) / 2;
    winY = (screenSize.cy - height) / 2;

    RECT winRect = {
        .left = winX,
        .top = winY,
        .right = winX + width,
        .bottom = winY + height};

    AdjustWindowRectEx(&winRect, WIN_STYLE, FALSE, WS_EX_OVERLAPPEDWINDOW);

    // Create the window.

    hWindow = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,  // Optional window styles.
        CLASS_NAME,              // Window class
        title,                   // Window text
        WIN_STYLE,               // Window style

        // Size and position
        winRect.left, winRect.top,
        winRect.right - winRect.left, winRect.bottom - winRect.top,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hWindow == NULL) {
        return -1;
    }

    ShowWindow(hWindow, SW_SHOWNORMAL);
    UpdateWindow(hWindow);

    // Run the message loop.

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(hWindow);
    UnregisterClass(CLASS_NAME, hInstance);

    return 0;
}

void grfBeginDraw() {
    paintRect.left = clientWidth;
    paintRect.right = 0;
    paintRect.top = clientHeight;
    paintRect.bottom = 0;
    isDrawing = 1;
}

void grfEndDraw() {
    isDrawing = 0;
    InvalidateRect(hWindow, &paintRect, FALSE);
}

void grfDrawImage(GRFImage image, int x, int y, GRFRect* fragment) {
    if (!isDrawing) return;
    SelectObject(imageHdc, image->bitmap);

    if (x < paintRect.left) {
        paintRect.left = x;
    }
    if (y < paintRect.top) {
        paintRect.top = y;
    }

    if (fragment) {
        BitBlt(backbufferHdc, x, y, fragment->w, fragment->h, imageHdc, fragment->x, fragment->y, SRCCOPY);
        if (x + fragment->w > paintRect.right) {
            paintRect.right = x + fragment->w;
        }
        if (y + fragment->h > paintRect.bottom) {
            paintRect.bottom = y + fragment->h;
        }
    } else {
        BitBlt(backbufferHdc, x, y, image->width, image->height, imageHdc, 0, 0, SRCCOPY);
        if (x + image->width > paintRect.right) {
            paintRect.right = x + image->width;
        }
        if (y + image->height > paintRect.bottom) {
            paintRect.bottom = x + image->height;
        }
    }
}

void grfClear() {
    if (!isDrawing) return;
    FillRect(backbufferHdc, &backbufferRect, backgroundBrush);
    paintRect.left = 0;
    paintRect.right = clientWidth;
    paintRect.top = 0;
    paintRect.bottom = clientHeight;
}

void grfFill(GRFRect* area) {
    if (!isDrawing) return;
    if (area) {
        RECT rect = {area->x, area->y, area->x + area->w, area->y + area->h};
        FillRect(backbufferHdc, &rect, backgroundBrush);
        if (rect.left < paintRect.left) {
            paintRect.left = rect.left;
        }
        if (rect.top < paintRect.top) {
            paintRect.top = rect.top;
        }
        if (rect.right > paintRect.right) {
            paintRect.right = rect.right;
        }
        if (rect.bottom > paintRect.bottom) {
            paintRect.bottom = rect.bottom;
        }
    } else {
        grfClear();
    }
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            backgroundBrush = CreateSolidBrush(RGB(bgrR, bgrG, bgrB));
            HDC wdc = GetDC(hwnd);
            InitBackbuffer(wdc, clientWidth, clientHeight);
            isLoaded = 1;
            callbackOnLoad();
            return 0;

        case WM_CLOSE:
            callbackOnExit();
            FreeBackbuffer();
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT paintPs;
            HDC paintHdc;

            paintHdc = BeginPaint(hWindow, &paintPs);
            BitBlt(paintHdc,
                   paintPs.rcPaint.left,
                   paintPs.rcPaint.top,
                   paintPs.rcPaint.right - paintPs.rcPaint.left,
                   paintPs.rcPaint.bottom - paintPs.rcPaint.top,
                   backbufferHdc,
                   paintPs.rcPaint.left,
                   paintPs.rcPaint.top,
                   SRCCOPY);
            EndPaint(hWindow, &paintPs);
        }
            return 0;
        case WM_LBUTTONDOWN:
            callbackOnMouseDown(GRF_BUTTON_LEFT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_RBUTTONDOWN:
            callbackOnMouseDown(GRF_BUTTON_RIGHT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_MBUTTONDOWN:
            callbackOnMouseDown(GRF_BUTTON_MIDDLE, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_LBUTTONUP:
            callbackOnMouseUp(GRF_BUTTON_LEFT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_RBUTTONUP:
            callbackOnMouseUp(GRF_BUTTON_RIGHT, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_MBUTTONUP:
            callbackOnMouseUp(GRF_BUTTON_MIDDLE, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_MOUSEMOVE:
            callbackOnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        case WM_KEYDOWN:
            if (!(lParam & (0x1 << 30))) {
                callbackOnKeyDown(wParam);
            }
            return 0;
        case WM_KEYUP:
            callbackOnKeyUp(wParam);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
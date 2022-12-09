#include "grf.h"

#define CLASS_NAME L"GameRoom"
#define WIN_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)

void dummyOnDraw(HDC hdc, LPPAINTSTRUCT ps) {}
void dummyCallback() {}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static DrawCallback callbackOnDraw = &dummyOnDraw;
static CommonCallback callbackOnLoad = &dummyCallback;
static CommonCallback callbackOnExit = &dummyCallback;

static int isLoaded = 0;
static HBRUSH backgroundBrush;
static uint8_t bgrR = 0;
static uint8_t bgrG = 0;
static uint8_t bgrB = 0;
static HINSTANCE hInst;

void appSetClbDraw(DrawCallback draw_callback) {
    callbackOnDraw = draw_callback;
}

void grfSetOnLoad(CommonCallback load_callback) {
    callbackOnLoad = load_callback;
}

void grfSetOnExit(CommonCallback exit_callback) {
    callbackOnExit = exit_callback;
}

void grfSetClearColor(uint8_t r, uint8_t g, uint8_t b) {
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

    HWND hwnd = CreateWindowEx(
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

    if (hwnd == NULL) {
        return -1;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Run the message loop.

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(hwnd);
    UnregisterClass(CLASS_NAME, hInstance);

    return 0;
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            backgroundBrush = CreateSolidBrush(RGB(bgrR, bgrG, bgrB));
            isLoaded = 1;
            callbackOnLoad();
            return 0;

        case WM_CLOSE:
            callbackOnExit();
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, backgroundBrush);

            (*callbackOnDraw)(hdc, &ps);

            EndPaint(hwnd, &ps);
        }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
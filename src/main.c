#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdint.h>

#define CLASS_NAME L"GameRoom"
#define WIN_W 640
#define WIN_H 395
#define WIN_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)

HBITMAP hBMP;

void OnLoad() {
    // hBMP = (HBITMAP)LoadImage(NULL, L"test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void OnDraw(HDC hdc) {
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class.

    WNDCLASSEX wc;
    SIZE screenSize;
    LONG winX, winY;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

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

    screenSize.cx = GetSystemMetrics(SM_CXSCREEN);
    screenSize.cy = GetSystemMetrics(SM_CYSCREEN);

    winX = (screenSize.cx - (WIN_W + GetSystemMetrics(SM_CXBORDER) * 2)) / 2;
    winY = (screenSize.cy - (WIN_H + GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYCAPTION))) / 2;

    RECT winRect = {.left = winX, .top = winY, .right = winX + WIN_W, .bottom = winY + WIN_H};

    AdjustWindowRectEx(&winRect, WIN_STYLE, FALSE, WS_EX_OVERLAPPEDWINDOW);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,  // Optional window styles.
        CLASS_NAME,              // Window class
        L"Game Room",            // Window text
        WIN_STYLE,               // Window style

        // Size and position
        winRect.left, winRect.top, winRect.right - winRect.left, winRect.bottom - winRect.top,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return -1;
    }

    OnLoad();
    hBMP = (HBITMAP)LoadImage(hInstance, L"bmBack", IMAGE_BITMAP, 0, 0, 0);

    ShowWindow(hwnd, nCmdShow);
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            BITMAP bitmap;
            HDC hdcMem;
            HGDIOBJ oldBitmap;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            hdcMem = CreateCompatibleDC(hdc);
            oldBitmap = SelectObject(hdcMem, hBMP);

            GetObject(hBMP, sizeof(bitmap), &bitmap);
            BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, oldBitmap);
            DeleteDC(hdcMem);
            SetBkMode(hdc, TRANSPARENT);
            TextOut(hdc, 0, 0, L"Hello, Windows!", 15);

            OnDraw(hdc);

            EndPaint(hwnd, &ps);
        }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
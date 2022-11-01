#include "appwindow.h"

#define CLASS_NAME L"GameRoom"
#define WIN_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int appStart(HINSTANCE hInstance, const wchar_t* title, int width, int height) {
    SetProcessDPIAware();

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
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
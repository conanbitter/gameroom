#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include "appwindow.h"
#include <windows.h>
#include <stdint.h>

HBITMAP hBMP;
HINSTANCE app_instance;

void OnLoad() {
    hBMP = (HBITMAP)LoadImage(app_instance, L"bmMinefield", IMAGE_BITMAP, 0, 0, 0);
}

void OnDraw(HDC hdc) {
    HDC hdcMem;
    HGDIOBJ oldBitmap;
    BITMAP bitmap;

    hdcMem = CreateCompatibleDC(hdc);
    oldBitmap = SelectObject(hdcMem, hBMP);

    GetObject(hBMP, sizeof(bitmap), &bitmap);
    BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, oldBitmap);
    DeleteDC(hdcMem);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 0, 0, L"Hello, Windows!", 15);
}

void OnFinish() {
    DeleteObject(hBMP);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    app_instance = hInstance;

    appStart(app_instance, L"Minefield", 320, 320);
    return 0;
}

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include "grf.h"
#include <windows.h>
#include <stdint.h>

HINSTANCE app_instance;
GRFImage img;

void OnLoad() {
    // Load main atlas
    img = grfLoadImageFromRes(L"bmMinefield");
}

void OnDraw(HDC hdc, LPPAINTSTRUCT ps) {
    HDC hdcMem;
    HGDIOBJ oldBitmap;
    BITMAP bitmap;

    hdcMem = CreateCompatibleDC(hdc);
    oldBitmap = SelectObject(hdcMem, img->bitmap);

    BitBlt(hdc, 0, 0, img->width, img->height, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, oldBitmap);
    DeleteDC(hdcMem);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 0, 0, L"Hello, Windows!", 15);
}

void OnFinish() {
    grfFreeImage(img);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    app_instance = hInstance;

    appSetClbDraw(&OnDraw);
    grfSetOnLoad(&OnLoad);
    grfSetOnExit(&OnFinish);

    grfSetClearColor(50, 50, 70);

    grfStart(app_instance, L"Minefield", 320, 320);
    return 0;
}

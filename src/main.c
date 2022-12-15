#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include "grf.h"
#include <windows.h>
#include <stdint.h>

HINSTANCE app_instance;
GRFImage img;
GRFRect rct;

void OnLoad() {
    // Load main atlas
    img = grfLoadImageFromRes(L"bmMinefield");
    rct.x = 32;
    rct.y = 0;
    rct.w = 64;
    rct.h = 64;

    grfBeginDraw();
    grfDrawImage(img, 10, 10, &rct);
    grfEndDraw();
}

void OnDraw(HDC hdc, LPPAINTSTRUCT ps) {
    /*HDC hdcMem;
    HGDIOBJ oldBitmap;
    BITMAP bitmap;

    hdcMem = CreateCompatibleDC(hdc);
    oldBitmap = SelectObject(hdcMem, img->bitmap);

    BitBlt(hdc, 0, 0, img->width, img->height, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, oldBitmap);
    DeleteDC(hdcMem);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 0, 0, L"Hello, Windows!", 15);*/
    grfDrawImage(img, 10, 10, &rct);
}

void OnFinish() {
    grfFreeImage(img);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    app_instance = hInstance;

    appSetClbDraw(&OnDraw);
    grfSetOnLoad(&OnLoad);
    grfSetOnExit(&OnFinish);

    grfSetFillColor(50, 50, 70);

    grfStart(app_instance, L"Minefield", 320, 320);
    return 0;
}

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include "grf.h"
#include <windows.h>
#include <stdint.h>

HINSTANCE app_instance;
GRFImage img;
GRFRect rct, oldr;
int keyy = 10;

void OnLoad() {
    // Load main atlas
    img = grfLoadImageFromRes(L"bmMinefield");
    rct.x = 32;
    rct.y = 0;
    rct.w = 64;
    rct.h = 32;
    oldr.x = 100;
    oldr.y = 100;
    oldr.w = 64;
    oldr.h = 32;

    grfBeginDraw();
    grfDrawImage(img, 10, 10, &rct);
    grfEndDraw();
}

void OnMouseDown(int button, int x, int y) {
    rct.x = 32 * button;
    rct.y = 0;
    grfBeginDraw();
    grfDrawImage(img, x, y, &rct);
    grfEndDraw();
}

void OnMouseUp(int button, int x, int y) {
    rct.x = 32 * button;
    rct.y = 32;
    grfBeginDraw();
    grfDrawImage(img, x, y, &rct);
    grfEndDraw();
}

void OnMouseMove(int x, int y) {
    grfBeginDraw();
    grfFill(&oldr);
    // grfClear();
    grfDrawImage(img, x, y, &rct);
    grfEndDraw();
    oldr.x = x;
    oldr.y = y;
}

void OnKeyDown(int key) {
    if (key == GRF_KEY_T) {
        grfSetTitle(L"New title");
    };

    if (key == GRF_KEY_RETURN) {
        grfSetFrameSize(500, 500);
    };
    if (key == GRF_KEY_L) {
        grfSetFrameSize(320, 320);
    };
    grfBeginDraw();
    if (key == GRF_KEY_C) grfDrawImage(img, 40, keyy, &rct);
    if (key == GRF_KEY_V) grfDrawImage(img, 50, keyy, &rct);
    grfEndDraw();
    keyy += 20;
}

void OnKeyUp(int key) {
    grfBeginDraw();
    grfDrawImage(img, 70, keyy, &rct);
    grfEndDraw();
}

void OnFinish() {
    grfFreeImage(img);
}

void OnUpdate() {
    grfBeginDraw();
    grfDrawImage(img, 40, keyy, &rct);
    grfEndDraw();
    keyy += 20;
    if (keyy > 100) {
        if (keyy > 200) {
            grfDisableUpdate();
        } else {
            grfEnableUpdate(500);
        }
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    app_instance = hInstance;

    // grfSetOnMouseDown(&OnMouseDown);
    // grfSetOnMouseUp(&OnMouseUp);
    // grfSetOnMouseMove(&OnMouseMove);
    grfSetOnKeyDown(&OnKeyDown);
    grfSetOnKeyUp(&OnKeyUp);
    grfSetOnLoad(&OnLoad);
    grfSetOnExit(&OnFinish);
    grfSetOnUpdate(&OnUpdate, 1000.0);

    grfSetFillColor(50, 50, 70);

    grfStart(app_instance, L"Minefield", 320, 320);
    return 0;
}

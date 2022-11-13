#ifndef APPWINDOW_H
#define APPWINDOW_H

#define UNICODE

#include <windows.h>
#include <stdint.h>

typedef void (*DrawCallback)(HDC, LPPAINTSTRUCT);
typedef void (*CommonCallback)();

int appStart(HINSTANCE hInstance, const wchar_t* title, int width, int height);
void appSetClbDraw(DrawCallback draw_callback);
void appSetClbLoad(CommonCallback load_callback);
void appSetClbExit(CommonCallback exit_callback);

#endif
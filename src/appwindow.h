#ifndef APPWINDOW_H
#define APPWINDOW_H

#define UNICODE

#include <windows.h>
#include <stdint.h>

int appStart(HINSTANCE hInstance, const wchar_t* title, int width, int height);

#endif
/***************************\
 *                         *
 *    ###   ####   #####   *
 *   #      #   #  #       *
 *   #  ##  ####   ####    *
 *   #   #  #  #   #       *
 *    ###   #   #  #       *
 *                         *
\***************************/

#ifndef APPWINDOW_H
#define APPWINDOW_H

#define UNICODE

#include <windows.h>
#include <stdint.h>

typedef void (*DrawCallback)(HDC, LPPAINTSTRUCT);
typedef void (*CommonCallback)();
typedef void (*UpdateCallback)(float);
typedef void (*MouseButtonCallback)(int, int, int);
typedef void (*MouseMoveCallback)(int, int);
typedef void (*KeyboardCallback)(int);

typedef HBITMAP GRFImage;
typedef struct {
    int x;
    int y;
    int w;
    int h;
} GRFRect;

int grfStart(HINSTANCE hInstance, const wchar_t* title, int width, int height);
void grfSetFrameSize(int width, int height);
void grfSetTitle(const char* title);

void appSetClbDraw(DrawCallback draw_callback);
void grfSetOnUpdate(UpdateCallback update_callback, float speed);
void grfSetUpdateEnabled(int enabled);
void grfSetOnMouseMove(MouseMoveCallback move_callback);
void grfSetOnMouseDown(MouseButtonCallback mouse_callback);
void grfSetOnMouseUp(MouseButtonCallback mouse_callback);
void grfSetOnKeyDown(KeyboardCallback key_callback);
void grfSetOnKeyUp(KeyboardCallback key_callback);
void grfSetOnLoad(CommonCallback load_callback);
void grfSetOnExit(CommonCallback exit_callback);

GRFImage grfLoadImage(const char* filename);
GRFImage grfLoadImageFromRes(const char* filename);
void grfFreeImage(GRFImage image);

void grfBeginDraw();
void grfEndDraw();
void grfDrawImage(GRFImage image, GRFRect* fragment);
void grfSetFillColor(uint8_t r, uint8_t g, uint8_t b);
void grfClear();
void grfFill(GRFRect* area);

#endif
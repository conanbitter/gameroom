/***************************\
 *                         *
 *    ###   ####   #####   *
 *   #      #   #  #       *
 *   #  ##  ####   ####    *
 *   #   #  #  #   #       *
 *    ###   #   #  #       *
 *                         *
\***************************/

#ifndef GRF_H
#define GRF_H

#define UNICODE

#include <windows.h>
#include <stdint.h>

enum {
    GRF_BUTTON_LEFT = 1,
    GRF_BUTTON_RIGHT = 2,
    GRF_BUTTON_MIDDLE = 3
};

typedef void (*DrawCallback)(HDC, LPPAINTSTRUCT);
typedef void (*CommonCallback)();
typedef void (*UpdateCallback)(float);
typedef void (*MouseButtonCallback)(int, int, int);
typedef void (*MouseMoveCallback)(int, int);
typedef void (*KeyboardCallback)(int);

typedef struct {
    HBITMAP bitmap;
    int width;
    int height;
} __GRFImageData;

typedef __GRFImageData* GRFImage;

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

GRFImage grfLoadImageFromFile(const wchar_t* filename);
GRFImage grfLoadImageFromRes(const wchar_t* filename);
void grfFreeImage(GRFImage image);

void grfBeginDraw();
void grfEndDraw();
void grfDrawImage(GRFImage image, int x, int y, GRFRect* fragment);
void grfSetFillColor(uint8_t r, uint8_t g, uint8_t b);
void grfClear();
void grfFill(GRFRect* area);

#endif
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

enum {
    GRF_KEY_LBUTTON = 0x01,
    GRF_KEY_RBUTTON = 0x02,
    GRF_KEY_CANCEL = 0x03,
    GRF_KEY_MBUTTON = 0x04,
    GRF_KEY_XBUTTON1 = 0x05,
    GRF_KEY_XBUTTON2 = 0x06,
    GRF_KEY_BACK = 0x08,
    GRF_KEY_TAB = 0x09,
    GRF_KEY_CLEAR = 0x0C,
    GRF_KEY_RETURN = 0x0D,
    GRF_KEY_SHIFT = 0x10,
    GRF_KEY_CONTROL = 0x11,
    GRF_KEY_MENU = 0x12,
    GRF_KEY_PAUSE = 0x13,
    GRF_KEY_CAPITAL = 0x14,
    GRF_KEY_KANA = 0x15,
    GRF_KEY_HANGUEL = 0x15,
    GRF_KEY_HANGUL = 0x15,
    GRF_KEY_IME_ON = 0x16,
    GRF_KEY_JUNJA = 0x17,
    GRF_KEY_FINAL = 0x18,
    GRF_KEY_HANJA = 0x19,
    GRF_KEY_KANJI = 0x19,
    GRF_KEY_IME_OFF = 0x1A,
    GRF_KEY_ESCAPE = 0x1B,
    GRF_KEY_CONVERT = 0x1C,
    GRF_KEY_NONCONVERT = 0x1D,
    GRF_KEY_ACCEPT = 0x1E,
    GRF_KEY_MODECHANGE = 0x1F,
    GRF_KEY_SPACE = 0x20,
    GRF_KEY_PRIOR = 0x21,
    GRF_KEY_NEXT = 0x22,
    GRF_KEY_END = 0x23,
    GRF_KEY_HOME = 0x24,
    GRF_KEY_LEFT = 0x25,
    GRF_KEY_UP = 0x26,
    GRF_KEY_RIGHT = 0x27,
    GRF_KEY_DOWN = 0x28,
    GRF_KEY_SELECT = 0x29,
    GRF_KEY_PRINT = 0x2A,
    GRF_KEY_EXECUTE = 0x2B,
    GRF_KEY_SNAPSHOT = 0x2C,
    GRF_KEY_INSERT = 0x2D,
    GRF_KEY_DELETE = 0x2E,
    GRF_KEY_HELP = 0x2F,
    GRF_KEY_0 = 0x30,
    GRF_KEY_1 = 0x31,
    GRF_KEY_2 = 0x32,
    GRF_KEY_3 = 0x33,
    GRF_KEY_4 = 0x34,
    GRF_KEY_5 = 0x35,
    GRF_KEY_6 = 0x36,
    GRF_KEY_7 = 0x37,
    GRF_KEY_8 = 0x38,
    GRF_KEY_9 = 0x39,
    GRF_KEY_A = 0x41,
    GRF_KEY_B = 0x42,
    GRF_KEY_C = 0x43,
    GRF_KEY_D = 0x44,
    GRF_KEY_E = 0x45,
    GRF_KEY_F = 0x46,
    GRF_KEY_G = 0x47,
    GRF_KEY_H = 0x48,
    GRF_KEY_I = 0x49,
    GRF_KEY_J = 0x4A,
    GRF_KEY_K = 0x4B,
    GRF_KEY_L = 0x4C,
    GRF_KEY_M = 0x4D,
    GRF_KEY_N = 0x4E,
    GRF_KEY_O = 0x4F,
    GRF_KEY_P = 0x50,
    GRF_KEY_Q = 0x51,
    GRF_KEY_R = 0x52,
    GRF_KEY_S = 0x53,
    GRF_KEY_T = 0x54,
    GRF_KEY_U = 0x55,
    GRF_KEY_V = 0x56,
    GRF_KEY_W = 0x57,
    GRF_KEY_X = 0x58,
    GRF_KEY_Y = 0x59,
    GRF_KEY_Z = 0x5A,
    GRF_KEY_LWIN = 0x5B,
    GRF_KEY_RWIN = 0x5C,
    GRF_KEY_APPS = 0x5D,
    GRF_KEY_SLEEP = 0x5F,
    GRF_KEY_NUMPAD0 = 0x60,
    GRF_KEY_NUMPAD1 = 0x61,
    GRF_KEY_NUMPAD2 = 0x62,
    GRF_KEY_NUMPAD3 = 0x63,
    GRF_KEY_NUMPAD4 = 0x64,
    GRF_KEY_NUMPAD5 = 0x65,
    GRF_KEY_NUMPAD6 = 0x66,
    GRF_KEY_NUMPAD7 = 0x67,
    GRF_KEY_NUMPAD8 = 0x68,
    GRF_KEY_NUMPAD9 = 0x69,
    GRF_KEY_MULTIPLY = 0x6A,
    GRF_KEY_ADD = 0x6B,
    GRF_KEY_SEPARATOR = 0x6C,
    GRF_KEY_SUBTRACT = 0x6D,
    GRF_KEY_DECIMAL = 0x6E,
    GRF_KEY_DIVIDE = 0x6F,
    GRF_KEY_F1 = 0x70,
    GRF_KEY_F2 = 0x71,
    GRF_KEY_F3 = 0x72,
    GRF_KEY_F4 = 0x73,
    GRF_KEY_F5 = 0x74,
    GRF_KEY_F6 = 0x75,
    GRF_KEY_F7 = 0x76,
    GRF_KEY_F8 = 0x77,
    GRF_KEY_F9 = 0x78,
    GRF_KEY_F10 = 0x79,
    GRF_KEY_F11 = 0x7A,
    GRF_KEY_F12 = 0x7B,
    GRF_KEY_F13 = 0x7C,
    GRF_KEY_F14 = 0x7D,
    GRF_KEY_F15 = 0x7E,
    GRF_KEY_F16 = 0x7F,
    GRF_KEY_F17 = 0x80,
    GRF_KEY_F18 = 0x81,
    GRF_KEY_F19 = 0x82,
    GRF_KEY_F20 = 0x83,
    GRF_KEY_F21 = 0x84,
    GRF_KEY_F22 = 0x85,
    GRF_KEY_F23 = 0x86,
    GRF_KEY_F24 = 0x87,
    GRF_KEY_NUMLOCK = 0x90,
    GRF_KEY_SCROLL = 0x91,
    GRF_KEY_LSHIFT = 0xA0,
    GRF_KEY_RSHIFT = 0xA1,
    GRF_KEY_LCONTROL = 0xA2,
    GRF_KEY_RCONTROL = 0xA3,
    GRF_KEY_LMENU = 0xA4,
    GRF_KEY_RMENU = 0xA5,
    GRF_KEY_BROWSER_BACK = 0xA6,
    GRF_KEY_BROWSER_FORWARD = 0xA7,
    GRF_KEY_BROWSER_REFRESH = 0xA8,
    GRF_KEY_BROWSER_STOP = 0xA9,
    GRF_KEY_BROWSER_SEARCH = 0xAA,
    GRF_KEY_BROWSER_FAVORITES = 0xAB,
    GRF_KEY_BROWSER_HOME = 0xAC,
    GRF_KEY_VOLUME_MUTE = 0xAD,
    GRF_KEY_VOLUME_DOWN = 0xAE,
    GRF_KEY_VOLUME_UP = 0xAF,
    GRF_KEY_MEDIA_NEXT_TRACK = 0xB0,
    GRF_KEY_MEDIA_PREV_TRACK = 0xB1,
    GRF_KEY_MEDIA_STOP = 0xB2,
    GRF_KEY_MEDIA_PLAY_PAUSE = 0xB3,
    GRF_KEY_LAUNCH_MAIL = 0xB4,
    GRF_KEY_LAUNCH_MEDIA_SELECT = 0xB5,
    GRF_KEY_LAUNCH_APP1 = 0xB6,
    GRF_KEY_LAUNCH_APP2 = 0xB7,
    GRF_KEY_OEM_1 = 0xBA,
    GRF_KEY_OEM_PLUS = 0xBB,
    GRF_KEY_OEM_COMMA = 0xBC,
    GRF_KEY_OEM_MINUS = 0xBD,
    GRF_KEY_OEM_PERIOD = 0xBE,
    GRF_KEY_OEM_2 = 0xBF,
    GRF_KEY_OEM_3 = 0xC0,
    GRF_KEY_OEM_4 = 0xDB,
    GRF_KEY_OEM_5 = 0xDC,
    GRF_KEY_OEM_6 = 0xDD,
    GRF_KEY_OEM_7 = 0xDE,
    GRF_KEY_OEM_8 = 0xDF,
    GRF_KEY_OEM_102 = 0xE2,
    GRF_KEY_PROCESSKEY = 0xE5,
    GRF_KEY_PACKET = 0xE7,
    GRF_KEY_ATTN = 0xF6,
    GRF_KEY_CRSEL = 0xF7,
    GRF_KEY_EXSEL = 0xF8,
    GRF_KEY_EREOF = 0xF9,
    GRF_KEY_PLAY = 0xFA,
    GRF_KEY_ZOOM = 0xFB,
    GRF_KEY_NONAME = 0xFC,
    GRF_KEY_PA1 = 0xFD,
    GRF_KEY_OEM_CLEAR = 0xFE
};

enum {
    GRF_TIMER_DISABLE = 0
};

typedef void (*DrawCallback)(HDC, LPPAINTSTRUCT);
typedef void (*CommonCallback)();
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
void grfSetTitle(const wchar_t* title);

void appSetClbDraw(DrawCallback draw_callback);
void grfSetOnUpdate(CommonCallback update_callback, int speed);
void grfEnableUpdate(int speed);
void grfDisableUpdate();
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
// Unified abstraction over system libs (win32 api / x11)

#pragma once
#include "events.h"

typedef struct Gfx Gfx;

typedef enum {
    TE_NoneBtn,

    TE_LeftBtn,
    TE_MiddleBtn,
    TE_RightBtn,
    
    TE_WheelUp,
    TE_WheelDown,
} TE_Button;

void gfx_init(int width, int height);
void gfx_close();
void gfx_clear_wind();
TE_Event gfx_poll();

const char* gfx_keyc_to_str(unsigned int keycode, bool shift_pressed);
TE_Button to_gfx_btn(unsigned int btn);

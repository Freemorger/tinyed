// Abstraction over system events

#pragma once
#include "gfx/keys.h"
#include "stdbool.h"

typedef enum {
    TE_NoneEv,

    TE_ResizeWind,

    TE_ButtonPress,
    TE_ButtonRelease,
    TE_KeyPress,
    TE_KeyRelease,

    TE_InputText,
} TE_EventKind;

typedef struct {
    TE_EventKind kind;
    union {
        struct {
            TE_Keys      key;
            bool         ctrl;
            bool         shift;
            bool         alt;
            char         text[64]; /// only for InputText 
                                   /// TODO: maybe TE_String instead, though its dynamic..
        } key;

        struct {
            int x, y;
            int btn;
        } mouse;

        struct {
            int width, height;
        } resize;
    } val;
} TE_Event;


// Abstraction over system events

#pragma once
#include "stdbool.h"

typedef enum {
    TE_NoneEv,

    TE_ButtonPress,
    TE_ButtonRelease,
    TE_KeyPress,
    TE_KeyRelease,
} TE_EventKind;

typedef struct {
    TE_EventKind kind;
    union {
        struct {
            unsigned int code;
            bool         ctrl;
            bool         shift;
            bool         alt;
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


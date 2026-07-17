#pragma once

#include "widgets/widget.h"

// TODO: maybe some name string, and whatever window attributes could be
typedef struct TE_Window {
    TE_Widget widget;
    unsigned int scr_width;
    unsigned int scr_height;
} TE_Window;

TE_Window* te_window_new(unsigned int w, unsigned int h);
void te_window_free(TE_Window* w);

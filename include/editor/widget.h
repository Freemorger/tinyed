#pragma once
#include "events.h"

/// Basic TE Widget struct 
typedef struct TE_Widget {
    int x, y, w, h;

    void (*draw)(struct TE_Widget*);
    void (*event)(struct TE_Widget*, TE_Event*);
} TE_Widget;

/// Text label widget 
typedef struct TE_Label {
    TE_Widget widget;
    char*     text;
} TE_Label;

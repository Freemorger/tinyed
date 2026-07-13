#pragma once
#include "events.h"
#include "utils/ds.h"
#include <stdbool.h>

/// Basic TE Widget struct 
typedef struct TE_Widget {
    int x, y, w, h;

    void (*draw)(struct TE_Widget*); 
    void (*event)(struct TE_Widget*, TE_Event*);
    void (*dtor)(struct TE_Widget*); // destructor

    bool visible; /// render or not 
    bool enabled; /// receive events or not

} TE_Widget;

TE_VEC_DEFINE(char, TE_String)
TE_VEC_DEF_METHODS(char, TE_String)

/// Text label widget 
typedef struct TE_Label {
    TE_Widget widget;
    TE_String text; 
} TE_Label;

TE_Label* te_label_new(char* text);
void te_label_free(TE_Label* lbl);

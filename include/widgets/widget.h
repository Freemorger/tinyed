#pragma once
#include "events.h"
#include <stdbool.h>
#include "utils/ds.h"

typedef struct Gfx Gfx;

typedef struct TE_Widget TE_Widget;

/// Vector of pointers to TE_Widget
typedef struct { 
        TE_Widget** data; 
        size_t     cap; 
        size_t     len;
} TE_VecP_Widget;

/// Basic TE Widget struct 
typedef struct TE_Widget {
    int x, y, w, h;

    void (*draw)(Gfx* gfx, struct TE_Widget*); 
    void (*event)(struct TE_Widget*, TE_Event*);
    void (*dtor)(struct TE_Widget*); // destructor

    struct TE_Widget* parent;
    TE_VecP_Widget children;

    bool visible; /// render or not 
    bool enabled; /// receive events or not

} TE_Widget;

TE_VEC_DEF_METHODS(TE_Widget*, TE_VecP_Widget)

/// Removes widget from its parent children vec, destroys recursively children and destroys itself
void TE_Widget_destroy(TE_Widget* w);
/// Draw widget and its children (top-to-down) recursively
void TE_Widget_draw_tree(TE_Widget* w, Gfx* gfx);
/// Dispatch event to widget and its children recursively
void TE_Widget_dispatch(TE_Widget* widget, TE_Event* ev) ;

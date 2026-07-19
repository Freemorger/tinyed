#pragma once
#include "events.h"
#include <stdbool.h>
#include "utils/ds.h"
#include "utils/types.h"

typedef enum TE_WidgetKind {
    TE_WidgetKind_None,

    TE_WidgetKind_Window,
    TE_WidgetKind_Label,
    TE_WidgetKind_InputField,
} TE_WidgetKind; 

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
    TE_WidgetKind kind;

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
void TE_Widget_dispatch(TE_Widget* w, TE_Event* ev) ;
/// Whether widget contains point or not.
bool TE_Widget_contains(TE_Widget* w, TE_Vec2 coords);

typedef bool (*TE_WidgetPredic)(TE_Widget*, void*);
/// Recursively walk through widgets starting with `w` and checking each with function `f(cur, a)`. Returns ptr to (first found) widget if found something, NULL otherwise.
TE_Widget* TE_Widget_find(TE_Widget* w, TE_WidgetPredic f, void* a);

/// Predicate to check whether cursor falls in widget GUI area. `c` must be a valid pointer pointing to struct of type `TE_Vec2` (or similar)
static bool TE_WidgetPredic_under_cursor(TE_Widget* w, void* c) {
    CHECK_NULL(w);
    CHECK_NULL(c);

    TE_Vec2* p = (TE_Vec2*)c;

    return TE_Widget_contains(w, *p);
}



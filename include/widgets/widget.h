#pragma once
#include "events.h"
#include <stdbool.h>

typedef struct Gfx Gfx;

/// Basic TE Widget struct 
typedef struct TE_Widget {
    int x, y, w, h;

    void (*draw)(Gfx* gfx, struct TE_Widget*); 
    void (*event)(struct TE_Widget*, TE_Event*);
    void (*dtor)(struct TE_Widget*); // destructor

    bool visible; /// render or not 
    bool enabled; /// receive events or not

} TE_Widget;



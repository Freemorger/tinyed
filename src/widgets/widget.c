#include "widgets/widget.h"
#include "te_dbg.h"
#include "utils/types.h"
#include <stddef.h>

void TE_Widget_destroy(TE_Widget* w) {
    CHECK_NULL(w);

    if (w->parent) {
        TE_VecP_Widget_remove(&w->parent->children, w);
    }

    while (w->children.len) {
        TE_Widget_destroy(w->children.data[w->children.len - 1]);
    }

    if (w->dtor) {
        w->dtor(w);
    }
    free(w);
}

void TE_Widget_draw_tree(TE_Widget* w, Gfx* gfx) {
    if (!w->visible)
        return;

    if (w->draw)
        w->draw(gfx, w);

    for (size_t i = 0; i < w->children.len; i++) {
        TE_Widget_draw_tree(w->children.data[i], gfx);
    }
}

void TE_Widget_dispatch(TE_Widget* widget, TE_Event* ev) {
    if (!widget->enabled || !widget->visible)
        return;

    if (widget->event)
        widget->event(widget, ev);

    for (size_t i = 0; i < widget->children.len; i++) {
        TE_Widget_dispatch(widget->children.data[i], ev);
    }
}

bool TE_Widget_contains(TE_Widget* w, TE_Vec2 coords) {
    return coords.x >= w->x &&
           coords.x <  w->x + w->w &&
           coords.y >= w->y &&
           coords.y <  w->y + w->h;
}

TE_Widget* TE_Widget_find(TE_Widget* w, TE_WidgetPredic f, void* a) {
    CHECK_NULL(w);
    CHECK_NULL(f);

    if (f(w, a)) {
        return w;
    }

    for (size_t i = 0; i < w->children.len; i++) {
        TE_Widget* child = w->children.data[i];
        CHECK_NULL(child);

        if (f(child, a)) {
            return child;
        } 

        TE_Widget* sub = TE_Widget_find(child, f, a);
        if (sub != NULL) {
            return sub;
        }
    }

    return NULL;
}

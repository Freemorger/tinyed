#include "widgets/widget.h"
#include "te_dbg.h"

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

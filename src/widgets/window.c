#include "widgets/window.h"
#include "utils/etc.h"

static void te_window_draw(Gfx* gfx, TE_Widget* w) {
    // trickery to surpress unused params warnings
    (void)gfx;
    (void)w;
}

/// Widget destructor for window
static void te_window_dtor(TE_Widget* w) {
    CHECK_NULL(w);

    TE_Window* wind = container_of(w, TE_Window, widget);

    te_window_free(wind);
}

static void te_window_events(TE_Widget* w, TE_Event* ev) {
    CHECK_NULL(w);
    CHECK_NULL(ev);
}

/// Create a dynamically allocated window widget, with 
/// `TE_Window.scr_width` and height set to `w` and `h` coresp.
TE_Window* te_window_new(unsigned int w, unsigned int h) {
    TE_Window* l = malloc(sizeof(TE_Window));
    CHECK_NULL(l);
    memset(l, 0, sizeof(TE_Window));

    l->widget.kind = TE_WidgetKind_Window;

    l->widget.visible = true;
    l->widget.enabled = true;

    l->widget.draw  = te_window_draw;
    l->widget.dtor  = te_window_dtor;
    l->widget.event = te_window_events;

    l->scr_width  = w;
    l->scr_height = h;

    return l;
}

void te_window_free(TE_Window* w) {
     
}

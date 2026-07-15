#include "widgets/widget.h"
#include "events.h"
#include "te_dbg.h"
#include "te_gfx.h"
#include "utils/etc.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "widgets/te_label.h"

static void te_label_draw(Gfx* gfx, TE_Widget* widget) {
    CHECK_NULL(widget);

    TE_Label* lbl = container_of(widget, TE_Label, widget);

    gfx_draw_string(
        gfx,
        widget->x, 
        widget->y, 
        lbl->text.data, 
        lbl->text.len
    );
}

/// Widget destructor for label
static void te_label_dtor(TE_Widget* widget) {
    CHECK_NULL(widget);

    TE_Label* lbl = container_of(widget, TE_Label, widget);

    te_label_free(lbl);

    free(lbl);
}

/// Label widget event handler
static void te_label_events(TE_Widget* widget, TE_Event* ev) {
    // TODO 
}

/// Returns a dynamically allocated label with text copied into
TE_Label* te_label_new(char* text) {
    TE_Label* l = malloc(sizeof(TE_Label));
    CHECK_NULL(l);
    memset(l, 0, sizeof(TE_Label));

    l->widget.visible = true;
    l->widget.enabled = true;

    l->widget.draw  = te_label_draw;
    l->widget.dtor  = te_label_dtor;
    l->widget.event = te_label_events;

    TE_String s = {0};
    TE_String_extend_from(&s, text, strlen(text));
    l->text = s;

    return l;
}

/// Free resources of label 
void te_label_free(TE_Label* lbl) {
    if (lbl->text.data) {
        TE_String_free(&lbl->text);
    }
}

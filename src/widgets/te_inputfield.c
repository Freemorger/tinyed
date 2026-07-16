#include "widgets/te_inputfield.h"
#include "events.h"
#include "gfx/keys.h"
#include "te_dbg.h"
#include "te_gfx.h"
#include "utils/etc.h"
#include "utils/te_string.h"
#include "utils/utf8.h"
#include "widgets/widget.h"
#include <stddef.h>

static void te_inputfield_draw(Gfx* gfx, TE_Widget* w) {
    CHECK_NULL(gfx);
    CHECK_NULL(w);

    TE_InputField* lbl = container_of(w, TE_InputField, widget);

    gfx_draw_rect(
        gfx, 
        w->x, w->y, 
        w->w, 30
    );

    gfx_draw_string(
        gfx,
        w->x + 5, 
        w->y + 20, 
        lbl->text.data, 
        lbl->text.len
    );
}

/// Widget destructor for label
static void te_inputfield_dtor(TE_Widget* w) {
    CHECK_NULL(w);

    TE_InputField* infi = container_of(w, TE_InputField, widget);

    te_inputfield_free(infi);

    free(infi);
}

/// Label widget event handler
static void te_inputfield_events(TE_Widget* w, TE_Event* ev) {
    CHECK_NULL(w);
    CHECK_NULL(ev);

    TE_InputField* infi = container_of(w, TE_InputField, widget);

    switch (ev->kind) {
        case TE_InputText: {
            const char* text = ev->val.key.text;
            size_t len = strlen(text);

            bool has_control = false;
            for (size_t i = 0; i < len; ++i) {
                unsigned char c = (unsigned char)text[i];
                if (c < 0x20 || c == 0x7F) {
                    has_control = true;
                    break;
                }
            }
            if (has_control) break;

            TE_String_append_cstr(&infi->text, text, len);
            break;
        }
        case TE_KeyPress: {
            if (ev->val.key.key != TE_KEY_BACKSPACE) 
                break;

            size_t prev = utf8_prev(infi->text.data, infi->text.len);
            DBG(prev);
            
            TE_String_remove_range(
                &infi->text, 
                prev, 
                infi->text.len
            );

            break;
        }
        default:
            break;
    } 

}

/// Returns a dynamically allocated input field 
TE_InputField* te_inputfield_new() {
    TE_InputField* l = malloc(sizeof(TE_InputField));
    CHECK_NULL(l);
    memset(l, 0, sizeof(TE_InputField));

    l->widget.visible = true;
    l->widget.enabled = true;

    l->widget.h = 30;
    l->widget.w = 200;

    l->widget.draw  = te_inputfield_draw;
    l->widget.dtor  = te_inputfield_dtor;
    l->widget.event = te_inputfield_events;

    TE_String s = {0};
    l->text = s;

    return l;
}

void te_inputfield_free(TE_InputField *infi) {
    if (infi->text.data) {
        TE_String_free(&infi->text);
    }
}

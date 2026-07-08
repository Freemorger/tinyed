// xlib (x11) implementation of app's GFX (see `include/te_gfx.h`)

#include "utils/ds.h"
#ifndef _WIN32

#include "te_dbg.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBstr.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "events.h"
#include "te_gfx.h"

TE_QUEUE_DEFINE(TE_Event, TE_Queue_Event)
TE_QUEUE_DEF_METHODS(TE_Event, TE_Queue_Event)

static struct Gfx {
    Display* dpy;
    Window w;
    GC gc;
    XIM xim;
    XIC xic;

    TE_Queue_Event ev_queue;
};

Gfx gfx = {0};

void gfx_init(int width, int height) {
    gfx.dpy = XOpenDisplay(NULL);
    CHECK_NULL(gfx.dpy); 

    int blackColor = BlackPixel(gfx.dpy, DefaultScreen(gfx.dpy));
    int whiteColor = WhitePixel(gfx.dpy, DefaultScreen(gfx.dpy));

    int supported = false;
    XkbSetDetectableAutoRepeat(gfx.dpy, True, &supported);

    gfx.w = XCreateSimpleWindow(
        gfx.dpy, 
        DefaultRootWindow(gfx.dpy), 
        0, // pos x 
        0, // pos y 
        width, 
        height, 
        0, // bord width 
        blackColor, // border 
        whiteColor // bg 
    );
    CHECK_NULL(gfx.w);

    gfx.xim = XOpenIM(gfx.dpy, NULL, NULL, NULL);
    CHECK_NULL(gfx.xim);

    gfx.xic = XCreateIC(
        gfx.xim,
        XNInputStyle,
        XIMPreeditNothing | XIMStatusNothing,
        XNClientWindow, gfx.w,
        XNFocusWindow, gfx.w,
        NULL
    );
    CHECK_NULL(gfx.xic);

    XSelectInput(
        gfx.dpy,
        gfx.w, 
        ExposureMask | StructureNotifyMask |
        KeyReleaseMask | KeyPressMask | 
        ButtonReleaseMask | ButtonPressMask
    );

    XMapWindow(gfx.dpy, gfx.w);

    gfx.gc = XCreateGC(gfx.dpy, gfx.w, 0, NULL);

    XSetForeground(gfx.dpy, gfx.gc, blackColor);

    // hope this font magically pops out..
    char* font_name        = "*dejavu sans-bold-r-*-*-*-220-*";
    XFontStruct* font_info = XLoadQueryFont(gfx.dpy, font_name);

    // ..or just rely on default one 
    if (font_info == NULL) {
        fprintf(stderr, "Unrecognized font pattern. Falling back to 'fixed'.\n");
        font_info = XLoadQueryFont(gfx.dpy, "fixed");
        CHECK_NULL(font_info);
    }
    XSetFont(gfx.dpy, gfx.gc, font_info->fid);

    XFlush(gfx.dpy);
}

void gfx_close() {
    if (gfx.dpy && gfx.w) 
        XDestroyWindow(gfx.dpy, gfx.w);

    if (gfx.dpy && gfx.gc) 
        XFreeGC(gfx.dpy, gfx.gc);

    if (gfx.dpy)
        XCloseDisplay(gfx.dpy);
}

void gfx_clear_wind() {
    CHECK_NULL(gfx.dpy);
    CHECK_NULL(gfx.w);
    XClearWindow(gfx.dpy, gfx.w);
}

TE_Event gfx_poll() {
    CHECK_NULL(gfx.dpy);
    CHECK_NULL(gfx.w);

    TE_Event te = {0};
    te.kind = TE_NoneEv;

    if (gfx.ev_queue.len > 0) {
        bool res = TE_Queue_Event_dequeue(&gfx.ev_queue, &te);
        if (res) 
            return te;
    }

    if (XPending(gfx.dpy) == 0) {
        return te;
    }

    XEvent xe;
    XNextEvent(gfx.dpy, &xe);

    switch (xe.type) {
        case KeyPress: {
            TE_Event textev = {0};
            textev.kind = TE_InputText;
            textev.val.key.code = xe.xkey.keycode;

            KeySym keysym;
            Status status;

            size_t len = Xutf8LookupString(
                gfx.xic,
                &xe.xkey,
                textev.val.key.text, sizeof(textev.val.key.text),
                &keysym, &status
            );

            if (status != XBufferOverflow && len < sizeof(textev.val.key.text))
                textev.val.key.text[len] = '\0';

            if (status == XLookupChars || status == XLookupBoth) {
                TE_Queue_Event_enqueue(&gfx.ev_queue, textev);
            }
            // falthru
        }
        case KeyRelease: {
            te.kind = xe.type == KeyRelease ? TE_KeyRelease : TE_KeyPress;
            te.val.key.code  = xe.xkey.keycode;
            te.val.key.shift = (xe.xkey.state & ShiftMask);
            te.val.key.ctrl  = (xe.xkey.state & ControlMask);
            te.val.key.alt   = (xe.xkey.state & Mod1Mask);
            break;
        }
        case ButtonPress:
        case ButtonRelease: {
            te.kind = xe.type == ButtonRelease ? TE_ButtonRelease : TE_ButtonPress;
            te.val.mouse.x = xe.xbutton.x;
            te.val.mouse.y = xe.xbutton.y;
            te.val.mouse.btn = xe.xbutton.button;
            break;
        }
        default:
            break;
    }

    return te;
}

const char* gfx_keyc_to_str(unsigned int keycode, bool shift_pressed) {
    CHECK_NULL(gfx.dpy);
    CHECK_NULL(gfx.w);

    int index = shift_pressed ? 1 : 0;

    KeySym ks = XkbKeycodeToKeysym(gfx.dpy, keycode, 0, index);
    
    if (ks == NoSymbol) {
        return "Unknown";
    }

    const char* key_name = XKeysymToString(ks);

    return key_name ? key_name : "Unknown";
}

/// Convert system button to "normalized" button idx:
TE_Button to_gfx_btn(unsigned int btn) {
    switch (btn) {
        case Button1:
            return TE_LeftBtn;
        case Button2:
            return TE_MiddleBtn;
        case Button3:
            return TE_RightBtn;
        case Button4: 
            return TE_WheelUp;
        case Button5:
            return TE_WheelDown;
        default:
            return TE_NoneBtn;
    } 
}

#endif

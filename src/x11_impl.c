// xlib (x11) implementation of app's GFX (see `include/te_gfx.h`)

#ifndef _WIN32

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

// yeah, global state, whatever. trying to keep things tiny because its tinyed.
Display* dpy = NULL;
Window   w   = 0;
GC       gc  = 0;

void gfx_init(int width, int height) {
    dpy = XOpenDisplay(NULL);
    assert(dpy);

    int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
    int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

    int supported = false;
    XkbSetDetectableAutoRepeat(dpy, True, &supported);

    w = XCreateSimpleWindow(
        dpy, 
        DefaultRootWindow(dpy), 
        0, // pos x 
        0, // pos y 
        width, 
        height, 
        0, // bord width 
        blackColor, // border 
        whiteColor // bg 
    );

    XSelectInput(
        dpy,
        w, 
        ExposureMask | StructureNotifyMask |
        KeyReleaseMask | KeyPressMask | 
        ButtonReleaseMask | ButtonPressMask
    );

    XMapWindow(dpy, w);

    gc = XCreateGC(dpy, w, 0, NULL);

    XSetForeground(dpy, gc, blackColor);

    // hope this font magically pops out..
    char* font_name        = "*dejavu sans-bold-r-*-*-*-220-*";
    XFontStruct* font_info = XLoadQueryFont(dpy, font_name);

    // ..or just rely on default one 
    if (font_info == NULL) {
        fprintf(stderr, "Unrecognized font pattern. Falling back to 'fixed'.\n");
        font_info = XLoadQueryFont(dpy, "fixed");
        assert(font_info);
    }
    XSetFont(dpy, gc, font_info->fid);

    XFlush(dpy);
}

void chk_dpy_wind() {
    if (dpy == NULL) {
        fprintf(stderr, "Display is NULL! Seems like it wasn't initialized.\n");
        exit(1);
    }
    if (w == 0) {
        fprintf(stderr, "Window ID is 0! Seems like it wasn't initialized.\n");
        exit(1);
    }
}

void gfx_close() {
    if (dpy && w) 
        XDestroyWindow(dpy, w);

    if (dpy && gc) 
        XFreeGC(dpy, gc);

    if (dpy)
        XCloseDisplay(dpy);
}

void gfx_clear_wind() {
    chk_dpy_wind();
    XClearWindow(dpy, w);
}

TE_Event gfx_poll() {
    chk_dpy_wind();

    TE_Event te = {0};
    te.kind = TE_NoneEv;

    if (XPending(dpy) == 0) {
        return te;
    }

    XEvent xe;
    XNextEvent(dpy, &xe);

    switch (xe.type) {
        case KeyPress: 
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
    chk_dpy_wind();

    int index = shift_pressed ? 1 : 0;

    KeySym ks = XkbKeycodeToKeysym(dpy, keycode, 0, index);
    
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

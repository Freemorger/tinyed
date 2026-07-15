// xlib (x11) implementation of app's GFX (see `include/te_gfx.h`)

#include "te_gfx.h"

#ifdef TE_BACKEND_X11

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XKBstr.h>
#include <X11/Xft/Xft.h>
#include <fontconfig/fontconfig.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "events.h"
#include "utils/ds.h"
#include "te_dbg.h"
#include "platform/gfxdefs.h"
#include "gfx/te_mousebtn.h"

Gfx gfx_init(int width, int height) {
    Gfx gfx = {0};

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

    gfx.xft_draw = XftDrawCreate(
        gfx.dpy,
        gfx.w,
        DefaultVisual(gfx.dpy, DefaultScreen(gfx.dpy)),
        DefaultColormap(gfx.dpy, DefaultScreen(gfx.dpy))
    );

    CHECK_NULL(gfx.xft_draw);

    XSetForeground(gfx.dpy, gfx.gc, blackColor);

    gfx.font = XftFontOpen(
        gfx.dpy,
        DefaultScreen(gfx.dpy),
        XFT_FAMILY, XftTypeString, "sans-serif",
        XFT_SIZE, XftTypeDouble, 16.0,
        NULL
    );

    CHECK_NULL(gfx.font);

    XRenderColor black = {
        .red = 0,
        .green = 0,
        .blue = 0,
        .alpha = 65535
    };

    XftColorAllocValue(
        gfx.dpy,
        DefaultVisual(gfx.dpy, DefaultScreen(gfx.dpy)),
        DefaultColormap(gfx.dpy, DefaultScreen(gfx.dpy)),
        &black,
        &gfx.text_color
    );

    XFlush(gfx.dpy);

    return gfx;
}

/// Destroys gfx and everything from inside 
void gfx_close(Gfx* gfx) {
    CHECK_NULL(gfx);

    if (gfx->xic)
        XDestroyIC(gfx->xic);

    if (gfx->xim)
        XCloseIM(gfx->xim);

    if (gfx->xft_draw)
        XftDrawDestroy(gfx->xft_draw);

    if (gfx->font)
        XftFontClose(gfx->dpy, gfx->font);

    if (gfx->dpy && gfx->text_color.pixel)
        XftColorFree(
            gfx->dpy,
            DefaultVisual(gfx->dpy, DefaultScreen(gfx->dpy)),
            DefaultColormap(gfx->dpy, DefaultScreen(gfx->dpy)),
            &gfx->text_color
        );

    if (gfx->dpy && gfx->gc)
        XFreeGC(gfx->dpy, gfx->gc);

    if (gfx->dpy && gfx->w)
        XDestroyWindow(gfx->dpy, gfx->w);

    if (gfx->dpy)
        XCloseDisplay(gfx->dpy);

    TE_Queue_Event_free(&gfx->ev_queue);
}

void gfx_clear_wind(Gfx* gfx) {
    CHECK_NULL(gfx);
    CHECK_NULL(gfx->dpy);
    CHECK_NULL(gfx->w);
    XClearWindow(gfx->dpy, gfx->w);
}


static TE_Keys xkb_keycode_to_te(Gfx* gfx, unsigned int keycode) {
    CHECK_NULL(gfx);
    CHECK_NULL(gfx->dpy);

    KeySym base_sym = XkbKeycodeToKeysym(gfx->dpy, keycode, 0, 0);

    switch (base_sym) {
    #define X(xkey, tekey) case xkey: return tekey;
        // Numbers
        X(XK_1, TE_KEY_1) X(XK_2, TE_KEY_2) X(XK_3, TE_KEY_3)
        X(XK_4, TE_KEY_4) X(XK_5, TE_KEY_5) X(XK_6, TE_KEY_6)
        X(XK_7, TE_KEY_7) X(XK_8, TE_KEY_8) X(XK_9, TE_KEY_9)
        X(XK_0, TE_KEY_0)

        // Letters (Group 0 Level 0 evaluates to lowercase keysyms)
        X(XK_a, TE_KEY_A) X(XK_b, TE_KEY_B) X(XK_c, TE_KEY_C)
        X(XK_d, TE_KEY_D) X(XK_e, TE_KEY_E) X(XK_f, TE_KEY_F)
        X(XK_g, TE_KEY_G) X(XK_h, TE_KEY_H) X(XK_i, TE_KEY_I)
        X(XK_j, TE_KEY_J) X(XK_k, TE_KEY_K) X(XK_l, TE_KEY_L)
        X(XK_m, TE_KEY_M) X(XK_n, TE_KEY_N) X(XK_o, TE_KEY_O)
        X(XK_p, TE_KEY_P) X(XK_q, TE_KEY_Q) X(XK_r, TE_KEY_R)
        X(XK_s, TE_KEY_S) X(XK_t, TE_KEY_T) X(XK_u, TE_KEY_U)
        X(XK_v, TE_KEY_V) X(XK_w, TE_KEY_W) X(XK_x, TE_KEY_X)
        X(XK_y, TE_KEY_Y) X(XK_z, TE_KEY_Z)

        // Structural UI Keys
        X(XK_Tab, TE_KEY_TAB)
        X(XK_Caps_Lock, TE_KEY_CAPS_LOCK)
        X(XK_space, TE_KEY_SPACE)
        X(XK_Return, TE_KEY_ENTER)
        X(XK_Escape, TE_KEY_ESCAPE)
        X(XK_BackSpace, TE_KEY_BACKSPACE)

        // Core Modifiers
        X(XK_Shift_L, TE_KEY_LSHIFT)     X(XK_Shift_R, TE_KEY_RSHIFT)
        X(XK_Control_L, TE_KEY_LCTRL)    X(XK_Control_R, TE_KEY_RCTRL)
        X(XK_Alt_L, TE_KEY_LALT)         X(XK_Alt_R, TE_KEY_RALT)
        X(XK_Super_L, TE_KEY_LGUI)       X(XK_Super_R, TE_KEY_RGUI)

        // Navigation Matrix
        X(XK_Insert, TE_KEY_INSERT)      X(XK_Delete, TE_KEY_DELETE)
        X(XK_Home, TE_KEY_HOME)          X(XK_End, TE_KEY_END)
        X(XK_Prior, TE_KEY_PAGE_UP)      X(XK_Next, TE_KEY_PAGE_DOWN)

        // Directional Arrows
        X(XK_Up, TE_KEY_UP)              X(XK_Down, TE_KEY_DOWN)
        X(XK_Left, TE_KEY_LEFT)          X(XK_Right, TE_KEY_RIGHT)

        // Function Matrix
        X(XK_F1, TE_KEY_F1)   X(XK_F2, TE_KEY_F2)   X(XK_F3, TE_KEY_F3)
        X(XK_F4, TE_KEY_F4)   X(XK_F5, TE_KEY_F5)   X(XK_F6, TE_KEY_F6)
        X(XK_F7, TE_KEY_F7)   X(XK_F8, TE_KEY_F8)   X(XK_F9, TE_KEY_F9)
        X(XK_F10, TE_KEY_F10) X(XK_F11, TE_KEY_F11) X(XK_F12, TE_KEY_F12)

        // Punctuation Symbols
        X(XK_grave, TE_KEY_GRAVE)
        X(XK_minus, TE_KEY_MINUS)
        X(XK_equal, TE_KEY_EQUAL)
        X(XK_bracketleft, TE_KEY_LBRACKET)
        X(XK_bracketright, TE_KEY_RBRACKET)
        X(XK_backslash, TE_KEY_BACKSLASH)
        X(XK_semicolon, TE_KEY_SEMICOLON)
        X(XK_apostrophe, TE_KEY_APOSTROPHE)
        X(XK_comma, TE_KEY_COMMA)
        X(XK_period, TE_KEY_PERIOD)
        X(XK_slash, TE_KEY_SLASH)

        // System Control Block
        X(XK_Print, TE_KEY_PRINT_SCREEN)
        X(XK_Scroll_Lock, TE_KEY_SCROLL_LOCK)
        X(XK_Pause, TE_KEY_PAUSE)

        // Numeric Keypad (Numlock ON / Clean Map)
        X(XK_KP_0, TE_KEY_KP_0) X(XK_KP_1, TE_KEY_KP_1) X(XK_KP_2, TE_KEY_KP_2)
        X(XK_KP_3, TE_KEY_KP_3) X(XK_KP_4, TE_KEY_KP_4) X(XK_KP_5, TE_KEY_KP_5)
        X(XK_KP_6, TE_KEY_KP_6) X(XK_KP_7, TE_KEY_KP_7) X(XK_KP_8, TE_KEY_KP_8)
        X(XK_KP_9, TE_KEY_KP_9)
        
        // Numeric Keypad Operators
        X(XK_KP_Divide, TE_KEY_KP_DIV)
        X(XK_KP_Multiply, TE_KEY_KP_MUL)
        X(XK_KP_Subtract, TE_KEY_KP_SUB)
        X(XK_KP_Add, TE_KEY_KP_ADD)
        X(XK_KP_Enter, TE_KEY_KP_ENTER)
        X(XK_KP_Decimal, TE_KEY_KP_DOT)
    #undef X

    default:
        return TE_KEY_UNKNOWN;
    }
}


TE_Event gfx_poll(Gfx* gfx) {
    CHECK_NULL(gfx);
    CHECK_NULL(gfx->dpy);
    CHECK_NULL(gfx->w);

    TE_Event te = {0};
    te.kind = TE_NoneEv;

    if (gfx->ev_queue.len > 0) {
        bool res = TE_Queue_Event_dequeue(&gfx->ev_queue, &te);
        if (res) 
            return te;
    }

    if (XPending(gfx->dpy) == 0) {
        return te;
    }

    XEvent xe;
    XNextEvent(gfx->dpy, &xe);

    switch (xe.type) {
        case KeyPress: {
            TE_Event textev = {0};
            textev.kind = TE_InputText;
            textev.val.key.key = xkb_keycode_to_te(gfx, xe.xkey.keycode);

            KeySym keysym;
            Status status;

            size_t len = Xutf8LookupString(
                gfx->xic,
                &xe.xkey,
                textev.val.key.text, sizeof(textev.val.key.text),
                &keysym, &status
            );

            if (status != XBufferOverflow && len < sizeof(textev.val.key.text))
                textev.val.key.text[len] = '\0';

            if (status == XLookupChars || status == XLookupBoth) {
                TE_Queue_Event_enqueue(&gfx->ev_queue, textev);
            }
            /* fall through */
        }
        case KeyRelease: {
            te.kind = xe.type == KeyRelease ? TE_KeyRelease : TE_KeyPress;
            te.val.key.key   = xkb_keycode_to_te(gfx, xe.xkey.keycode);
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

/// Convert system button to "normalized" button idx
/// Gfx could be NULL for x11 backend 
TE_MouseBtn to_gfx_btn(Gfx* gfx, unsigned int btn) {
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

/// Draw an UTF-8 string.
void gfx_draw_string(Gfx* gfx, int x, int y, char* text, size_t len) {
    CHECK_NULL(gfx);
    CHECK_NULL(gfx->xft_draw);
    CHECK_NULL(&gfx->text_color);
    CHECK_NULL(gfx->font);

    XftDrawStringUtf8(
        gfx->xft_draw,
        &gfx->text_color,
        gfx->font,
        x,
        y,
        (FcChar8*)text,
        len
    );

    XFlush(gfx->dpy);
}

void gfx_flush(Gfx* gfx) {
    CHECK_NULL(gfx);
    XFlush(gfx->dpy);
}

#endif

#pragma once

#include "platform/backends.h"
#include <X11/X.h>

#ifdef TE_BACKEND_WIN32
    // TODO 
#elif defined(TE_BACKEND_X11)
    #include <X11/Xlib.h>
    #include <X11/Xft/Xft.h>
    #include "utils/ds.h"

    TE_QUEUE_DEFINE(TE_Event, TE_Queue_Event)
    TE_QUEUE_DEF_METHODS(TE_Event, TE_Queue_Event)

    typedef struct Gfx {
        Display* dpy;
        Window   w;
        GC       gc;
        
        XftDraw* xft_draw;
        XftFont* font;
        XftColor text_color;

        Visual*  visual;
        Colormap color_map;
        XIM      xim;
        XIC      xic;

        TE_Queue_Event ev_queue;
    } Gfx;
#endif 

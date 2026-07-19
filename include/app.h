#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "widgets/widget.h"
#include "platform/gfxdefs.h"
#include "te_gfx.h"
#include "utils/ds.h"

#define TE_APP_VERSION "v0.0.10"

#ifdef DEBUG 
    #define TE_APP_DEBUG true
#else
    #define TE_APP_DEBUG false
#endif

typedef struct TE_App {
    TE_Widget*     root_widget;
    TE_Widget*     focused_widget;

    bool           running;
    Gfx            gfx;
} TE_App;

TE_App te_app_init(int width, int height);
void te_app_run(TE_App* app);

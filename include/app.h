#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "editor/widget.h"
#include "te_gfx.h"
#include "utils/ds.h"

#define TE_APP_VERSION "v0.0.5"

#ifdef DEBUG 
    #define TE_APP_DEBUG true
#else
    #define TE_APP_DEBUG false
#endif

TE_VEC_DEFINE(TE_Widget*, TE_VecP_Widget)
TE_VEC_DEF_METHODS(TE_Widget*, TE_VecP_Widget)

typedef struct TE_App {
    TE_VecP_Widget widgets;
    bool           running;
} TE_App;

TE_App te_app_init(int width, int height);
void te_app_run(TE_App* app);

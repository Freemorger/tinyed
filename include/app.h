#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "editor/widget.h"
#include "te_gfx.h"
#include "utils/ds.h"

#define TE_APP_VERSION "v0.0.3"

#ifdef DEBUG 
    #define TE_APP_DEBUG true
#else
    #define TE_APP_DEBUG false
#endif

TE_VEC_DEFINE(TE_Widget, TE_Vec_Widget);

typedef struct TE_App {
    TE_Vec_Widget widgets;
} TE_App;

TE_App te_app_init(int width, int height);
void te_app_run(TE_App* app);

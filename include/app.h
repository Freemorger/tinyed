#pragma once
#include <stdbool.h>
#include "te_gfx.h"

#define TE_APP_VERSION "v0.0.2"

#ifdef DEBUG 
    const bool TE_APP_DEBUG = true;
#else
    const bool TE_APP_DEBUG = false;
#endif

void te_app_init(int width, int height);
void te_app_run();

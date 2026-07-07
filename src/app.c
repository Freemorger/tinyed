#include "events.h"
#include "te_dbg.h"
#include "te_gfx.h"
#include <stdbool.h>
#include <stdio.h>

void te_app_init(int w, int h) {
    gfx_init(w, h);

    // TODO: prepare basic widgets
}

void te_app_run() {
    bool running = true;
    while (running) {
        gfx_clear_wind();
        
        TE_Event te = gfx_poll();
        
        switch (te.kind) {
            default:
                break;
        }
    }

    gfx_close();
}

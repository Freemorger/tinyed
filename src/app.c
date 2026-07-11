#include "editor/util.h"
#include "app.h"
#include "events.h"
#include "gfx/keys.h"
#include "te_dbg.h"
#include "te_gfx.h"
#include <bits/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

TE_App te_app_init(int w, int h) {
    gfx_init(w, h);

    TE_App app = {0};

    // TODO: prepare basic widgets

    return app;
}

void te_app_run(TE_App* app) {
    long tgt_fps = 60;
    long tgt_frame_time = (long)(1000.0 / (double)tgt_fps);
    DBG_PRINT("TGT FPS: %lu, TGT FRAME TIME: %lu\n", tgt_fps, tgt_frame_time);

    bool running = true;
    while (running) {
        struct timespec start_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        gfx_clear_wind();
        
        TE_Event te = gfx_poll();

        while (te.kind != TE_NoneEv) {
            switch (te.kind) {
                case TE_KeyPress: {
                    DBG_PRINT("Pressed key %s\n", 
                        TE_Key_names[te.val.key.key]
                    );
                    break;
                }
                case TE_InputText: {
                    DBG_PRINT("Text input %s\n",
                        te.val.key.text
                    ); 
                    break;
                }
                default:
                    break;
            }
            

            te = gfx_poll();
        }

        struct timespec end_time;
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                          (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

        long elapsed_ms = (long)(elapsed_time * 1000.0);
        if (elapsed_ms < tgt_frame_time) {
            TE_Sleep(tgt_frame_time - elapsed_ms);
        }
    }

    gfx_close();
}

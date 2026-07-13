#include "editor/util.h"
#include "app.h"
#include "editor/widget.h"
#include "events.h"
#include "gfx/keys.h"
#include "te_dbg.h"
#include "te_gfx.h"
#include <bits/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

TE_App te_app_init(int w, int h) {
    gfx_init(w, h);

    TE_App app = {0};

    // TODO: prepare basic widgets

    TE_Label* lbl = te_label_new("Hello, world!");
    lbl->widget.x = 50;
    lbl->widget.y = 100;

    TE_VecP_Widget_push(&app.widgets, &lbl->widget);

    return app;
}

void te_app_run(TE_App* app) {
    long tgt_fps = 60;
    long tgt_frame_time = (long)(1000.0 / (double)tgt_fps);
    DBG_PRINT("TGT FPS: %lu, TGT FRAME TIME: %lu\n", tgt_fps, tgt_frame_time);
    
    app->running = true;
    while (app->running) {
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
                case TE_KeyRelease: {
                    if (te.val.key.key == TE_KEY_ESCAPE) {
                        app->running = false;
                    }
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
            
            // TODO: send event to widget if needed

            te = gfx_poll();
        }

        for (size_t i = 0; i < app->widgets.len; i++) {
            TE_Widget* widget = app->widgets.data[i];
            if (widget->visible) {
                widget->draw(widget);
            }
        }

        gfx_flush(); 

        struct timespec end_time;
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                          (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;

        long elapsed_ms = (long)(elapsed_time * 1000.0);
        if (elapsed_ms < tgt_frame_time) {
            TE_Sleep(tgt_frame_time - elapsed_ms);
        }
    }

    for (size_t i = 0; i < app->widgets.len; i++) {
        TE_Widget* widget = app->widgets.data[i];
       
        if (widget->dtor) {
            widget->dtor(widget);
        }
    }

    gfx_close();
}

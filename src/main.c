#include "events.h"
#include "te_gfx.h"
#include "te_dbg.h"
#include "unistd.h"
#include <stdio.h>

int main() {
    gfx_init(800, 600);

    int running = 1;
    while (running) {
        TE_Event te = gfx_poll();

        if (te.kind != TE_NoneEv) {
            print_event_info(&te);
            running = 0;
        }
    }

    gfx_close();

    return 0;
}

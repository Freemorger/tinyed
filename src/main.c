#include "events.h"
#include "te_gfx.h"
#include "te_dbg.h"
#include "unistd.h"
#include "app.h"
#include <stdio.h>

int main() {
    printf(
        "tinyed %s%s, built on %s %s for %s, detected compiler: %s\n",
        TE_APP_VERSION, 
        TE_APP_DEBUG ? " [debug]" : "", 
        __DATE__, __TIME__, PLATFORM,
        detect_compiler()
    );

    te_app_init(640, 480);
    te_app_run();

    return 0;
}

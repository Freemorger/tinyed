#include "events.h"
#include "platform/gfxdefs.h"
#include "te_gfx.h"
#include "te_dbg.h"
#include "unistd.h"
#include "app.h"
#include <stdio.h>

int main() {
    printf(
        "tinyed %s%s, built on %s %s for %s (%s; %s), detected compiler: %s\n",
        TE_APP_VERSION, 
        TE_APP_DEBUG ? " [debug]" : "", 
        __DATE__, __TIME__, PLATFORM,
        te_backend_name(),
        detect_arch(),
        detect_compiler()
    );

    TE_App app = te_app_init(640, 480);
    te_app_run(&app);

    return 0;
}

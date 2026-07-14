#include <stdbool.h>
#include <stdio.h>
#include "events.h" 
#include "gfx/keys.h"
#include "te_gfx.h"
#include "te_dbg.h"

const char* te_btn_to_str(TE_Button btn) {
    switch (btn) {
        case TE_NoneBtn: 
            return "None Button";
        case TE_LeftBtn:
            return "Left Mouse Button";
        case TE_MiddleBtn:
            return "Middle Mouse Button";
        case TE_RightBtn:
            return "Right Mouse Button";
        case TE_WheelUp:
            return "Wheel Scroll Up";
        case TE_WheelDown:
            return "Wheel Scroll Down";
        default:
            return "(unknown)";
    }
}

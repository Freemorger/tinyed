#include <stdbool.h>
#include <stdio.h>
#include "events.h" 
#include "te_gfx.h"
#include "te_dbg.h"

/// Debug func to print TE_Event info 
void print_event_info(TE_Event* ev) {
    switch (ev->kind) {
        case TE_NoneEv: 
            printf("None Event\n");
            break;
        case TE_KeyRelease: 
        case TE_KeyPress: {
            bool shift = ev->val.key.shift;
            printf(
                "%s key %s; shift = %d, ctrl = %d, alt = %d\n",
                ev->kind == TE_KeyRelease ? "Released" : "Pressed",
                gfx_keyc_to_str(ev->val.key.code, shift),
                shift, ev->val.key.ctrl, ev->val.key.alt
            );
            break;
        }
        case TE_ButtonPress:
        case TE_ButtonRelease: {
            printf(
                "%s %s at (%d; %d)\n",
                te_btn_to_str(to_gfx_btn(ev->val.mouse.btn)),
                ev->kind == TE_ButtonRelease ? "released" : "pressed",
                ev->val.mouse.x, ev->val.mouse.y
            );
            break;
        }
        default:
            printf("(can't print info about event kind %d)\n", ev->kind);
            break;
    }
}

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

const char* detect_compiler() {
    #if defined(__TINYC__)
        return "TCC";
    #elif defined(__GNUC__) && defined(__VERSION__) && !defined(__clang__) 
        return "GCC " __VERSION__;
    #elif defined(__clang__) && defined(__VERSION__)
        return "Clang " __VERSION__;
    #elif defined(_MSC_FULL_VER)
        return "MSVC " STR(_MSC_VER) " (" STR(_MSC_FULL_VER) ")";
    #else
        return "unknown";
    #endif
}

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

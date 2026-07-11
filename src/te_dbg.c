#include <stdbool.h>
#include <stdio.h>
#include "events.h" 
#include "gfx/keys.h"
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
                TE_Key_names[ev->val.key.key],
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

const char* te_backend_name() {
    #if defined(TE_BACKEND_X11)
        return "X11";
    #elif defined(TE_BACKEND_WIN32)
        return "Win32 API";
    #else 
        return "unknown";
    #endif
}

const char* detect_arch() {
    #if defined(__x86_64__) || defined(_M_X64)
        return "x86_64";
    #elif defined(__i386__) || defined(_M_IX86)
        return "i386";
    #elif defined(__aarch64__) || defined(_M_ARM64)
        return "aarch64";
    #elif defined(__arm__) || defined(_M_ARM)
        return "aarch32";
    #elif defined(__mips__)
        return "mips";
    #elif defined(__powerpc__) || defined(_M_PPC)
        return "PowerPC";
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

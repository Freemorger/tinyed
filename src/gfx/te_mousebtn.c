#include "gfx/te_mousebtn.h"

const char* te_btn_to_str(TE_MouseBtn btn) {
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

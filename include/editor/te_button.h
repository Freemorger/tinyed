#pragma once

typedef enum {
    TE_NoneBtn,

    TE_LeftBtn,
    TE_MiddleBtn,
    TE_RightBtn,
    
    TE_WheelUp,
    TE_WheelDown,
} TE_Button;

const char* te_btn_to_str(TE_Button btn);


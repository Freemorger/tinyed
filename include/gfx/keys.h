#pragma once

#define TE_KEYLIST \
    X(TE_KEY_UNKNOWN, "Unknown") \
    X(TE_KEY_1, "1") X(TE_KEY_2, "2") X(TE_KEY_3, "3")\
    X(TE_KEY_4, "4") X(TE_KEY_5, "5") \
    X(TE_KEY_6, "6") X(TE_KEY_7, "7") X(TE_KEY_8, "8")\
    X(TE_KEY_9, "9") X(TE_KEY_0, "0") \
    X(TE_KEY_A, "A") X(TE_KEY_B, "B") X(TE_KEY_C, "C")\
    X(TE_KEY_D, "D") X(TE_KEY_E, "E") \
    X(TE_KEY_F, "F") X(TE_KEY_G, "G") X(TE_KEY_H, "H")\
    X(TE_KEY_I, "I") X(TE_KEY_J, "J") \
    X(TE_KEY_K, "K") X(TE_KEY_L, "L") X(TE_KEY_M, "M")\
    X(TE_KEY_N, "N") X(TE_KEY_O, "O") \
    X(TE_KEY_P, "P") X(TE_KEY_Q, "Q") X(TE_KEY_R, "R")\
    X(TE_KEY_S, "S") X(TE_KEY_T, "T") \
    X(TE_KEY_U, "U") X(TE_KEY_V, "V") X(TE_KEY_W, "W")\
    X(TE_KEY_X, "X") X(TE_KEY_Y, "Y") \
    X(TE_KEY_Z, "Z") \
    X(TE_KEY_TAB, "Tab") X(TE_KEY_CAPS_LOCK, "Caps Lock")\
    X(TE_KEY_SPACE, "Space") X(TE_KEY_ENTER, "Enter") \
    X(TE_KEY_LSHIFT, "Left Shift") X(TE_KEY_RSHIFT, "Right Shift") \
    X(TE_KEY_LCTRL, "Left Ctrl")   X(TE_KEY_RCTRL, "Right Ctrl") \
    X(TE_KEY_LALT, "Left Alt")     X(TE_KEY_RALT, "Right Alt") \
    X(TE_KEY_LGUI, "Left GUI")     X(TE_KEY_RGUI, "Right GUI") \
    X(TE_KEY_ESCAPE, "Escape")     X(TE_KEY_BACKSPACE, "Backspace") \
    X(TE_KEY_INSERT, "Insert")     X(TE_KEY_DELETE, "Delete") \
    X(TE_KEY_HOME, "Home")         X(TE_KEY_END, "End") \
    X(TE_KEY_PAGE_UP, "Page Up")   X(TE_KEY_PAGE_DOWN, "Page Down") \
    X(TE_KEY_UP, "Up")             X(TE_KEY_DOWN, "Down") \
    X(TE_KEY_LEFT, "Left")         X(TE_KEY_RIGHT, "Right") \
    X(TE_KEY_F1, "F1")   X(TE_KEY_F2, "F2")   X(TE_KEY_F3, "F3")   X(TE_KEY_F4, "F4") \
    X(TE_KEY_F5, "F5")   X(TE_KEY_F6, "F6")   X(TE_KEY_F7, "F7")   X(TE_KEY_F8, "F8") \
    X(TE_KEY_F9, "F9")   X(TE_KEY_F10, "F10") X(TE_KEY_F11, "F11") X(TE_KEY_F12, "F12") \
    X(TE_KEY_GRAVE, "`")         X(TE_KEY_MINUS, "-")         X(TE_KEY_EQUAL, "=") \
    X(TE_KEY_LBRACKET, "[")      X(TE_KEY_RBRACKET, "]")      X(TE_KEY_BACKSLASH, "\\") \
    X(TE_KEY_SEMICOLON, ";")     X(TE_KEY_APOSTROPHE, "'")    X(TE_KEY_COMMA, ",") \
    X(TE_KEY_PERIOD, ".")        X(TE_KEY_SLASH, "/") \
    X(TE_KEY_PRINT_SCREEN, "Print Screen") X(TE_KEY_SCROLL_LOCK, "Scroll Lock")\
    X(TE_KEY_PAUSE, "Pause") \
    X(TE_KEY_KP_0, "NP 0") X(TE_KEY_KP_1, "NP 1") X(TE_KEY_KP_2, "NP 2")\
    X(TE_KEY_KP_3, "NP 3") X(TE_KEY_KP_4, "NP 4") X(TE_KEY_KP_5, "NP 5")\
    X(TE_KEY_KP_6, "NP 6") X(TE_KEY_KP_7, "NP 7") \
    X(TE_KEY_KP_8, "NP 8") X(TE_KEY_KP_9, "NP 9") \
    X(TE_KEY_KP_DIV, "NP /") X(TE_KEY_KP_MUL, "NP *") X(TE_KEY_KP_SUB, "NP -") \
    X(TE_KEY_KP_ADD, "NP +") X(TE_KEY_KP_ENTER, "NP Enter") X(TE_KEY_KP_DOT, "NP .")


typedef enum {
#define X(member, string) member,
    TE_KEYLIST
#undef X

    TE_Key_Count
} TE_Keys;

extern const char* TE_Key_names[];

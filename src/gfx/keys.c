#include "gfx/keys.h"

#define X(member, string) string,

const char* TE_Key_names[] = {
    TE_KEYLIST
};

#undef X

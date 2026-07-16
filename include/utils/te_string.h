#pragma once
#include "utils/ds.h"
#include <stddef.h>

TE_VEC_DEFINE(char, TE_String)
TE_VEC_DEF_METHODS(char, TE_String)

static void TE_String_append_cstr(TE_String* s, const char* text, size_t len)
{
    TE_String_reserve(s, s->len + len + 1);

    memcpy(
        &s->data[s->len],
        text,
        len
    );

    s->len += len;
    s->data[s->len] = '\0';
}

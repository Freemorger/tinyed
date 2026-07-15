#pragma once
#include "utils/ds.h"

TE_VEC_DEFINE(char, TE_String)
TE_VEC_DEF_METHODS(char, TE_String)

#define STR_FMT(s) "%.*s"
#define STR_ARG(s) (int)(s).len, (s).data

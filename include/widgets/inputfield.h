#pragma once

#include "utils/te_string.h"
#include "widgets/widget.h"

/// Simple input field widget
typedef struct TE_InputField {
    TE_Widget widget;

    TE_String text;

    size_t cursor;
    int scroll_x;
} TE_InputField;

TE_InputField* te_inputfield_new();
void te_inputfield_free(TE_InputField* infi);

#pragma once

#include "widgets/widget.h"
#include "utils/ds.h"
#include "utils/te_string.h"

/// Text label widget 
typedef struct TE_Label {
    TE_Widget widget;
    TE_String text; 
} TE_Label;

TE_Label* te_label_new(char* text);
void te_label_free(TE_Label* lbl);

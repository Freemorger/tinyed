#include <stddef.h>
#include "utils/utf8.h"

size_t utf8_next(char* s, size_t i) {
    unsigned char c = s[i];

    if (c < 0x80)        return i + 1; // 0xxxxxxx
    if ((c & 0xE0) == 0xC0) return i + 2; // 110xxxxx
    if ((c & 0xF0) == 0xE0) return i + 3; // 1110xxxx
    if ((c & 0xF8) == 0xF0) return i + 4; // 11110xxx

    return i + 1; // invalid fallback
}

size_t utf8_prev(char* s, size_t i) {
    if (i == 0)
        return 0;

    i--;

    while (i > 0 && ((unsigned char)s[i] & 0xC0) == 0x80) {
        i--;
    }

    return i; // invalid fallback
}

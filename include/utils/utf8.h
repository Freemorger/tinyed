#pragma once

/// Finds byte index of next utf8 char, given i is index of start of this char 
size_t utf8_next(char* s, size_t i);
/// Finds byte index of prev utf8 char, given i is index of utf8 char after
size_t utf8_prev(char* s, size_t i);

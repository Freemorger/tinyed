v0.0.7:
- extracted `TE_String` type 
- `STR_FMT`, `STR_ARG` macros
- changed make's used compiler to `cc` by default
- changed makefile links for better compatibility
- add README note for make and macos
- some refactor:
- renamed `TE_Button` to `TE_MouseBtn`
- moved implementation of `te_btn_to_str` from `te_dbg.c` to `gfx/te_mousebtn.c`
- moved `widget.h` and `widget.c` to `include/widgets` and `src/widgets` corresp.


// Unified abstraction over system libs (win32 api / x11)

#pragma once
#include "events.h"
#include "gfx/keys.h"
#include <stddef.h>
#include "platform/gfxdefs.h"
#include "editor/te_button.h"

Gfx gfx_init(int width, int height);
void gfx_close(Gfx* gfx);
void gfx_clear_wind(Gfx* gfx);
void gfx_flush(Gfx* gfx);
TE_Event gfx_poll(Gfx* gfx);

TE_Button to_gfx_btn(Gfx* gfx, unsigned int btn);

void gfx_draw_string(Gfx* gfx, int x, int y, char* text, size_t len);

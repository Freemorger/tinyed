CC ?= cc

INPUT = $(wildcard src/*.c) \
        $(wildcard src/editor/*.c) \
        $(wildcard src/platform/*.c) \
        $(wildcard src/utils/*.c) \
		$(wildcard src/gfx/*.c) \
		$(wildcard src/widgets/*.c)

INCLUDE = include
LINK = $(shell pkg-config --libs x11 xft fontconfig)

COMMON_CFLAGS = -std=c11 -Wall -Wextra -Wno-unused-function
COMMON_CFLAGS += $(shell pkg-config --cflags x11 xft fontconfig)

DEBUG_CFLAGS = $(COMMON_CFLAGS) -O0 -g -DDEBUG -fsanitize=address,undefined
DEBUG_LFLAGS = -fsanitize=address,undefined
RELEASE_CFLAGS = $(COMMON_CFLAGS) -O3 -DNDEBUG

DEBUG_OUTPUT = build/debug/tinyed
RELEASE_OUTPUT = build/release/tinyed

DEBUG_OBJDIR = build/debug/obj
RELEASE_OBJDIR = build/release/obj

DEBUG_OBJS = $(patsubst src/%.c,$(DEBUG_OBJDIR)/%.o,$(INPUT))
RELEASE_OBJS = $(patsubst src/%.c,$(RELEASE_OBJDIR)/%.o,$(INPUT))

.PHONY: debug release clean cleandbg

debug: $(DEBUG_OUTPUT)

release: $(RELEASE_OUTPUT)

$(DEBUG_OUTPUT): $(DEBUG_OBJS)
	mkdir -p $(dir $@)
	$(CC) $(DEBUG_LFLAGS) $(DEBUG_OBJS) -o $@ $(LINK)

$(RELEASE_OUTPUT): $(RELEASE_OBJS)
	mkdir -p $(dir $@)
	$(CC) $(RELEASE_OBJS) -o $@ $(LINK)

$(DEBUG_OBJDIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(DEBUG_CFLAGS) -I$(INCLUDE) -MMD -MP -c $< -o $@

$(RELEASE_OBJDIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(RELEASE_CFLAGS) -I$(INCLUDE) -MMD -MP -c $< -o $@

-include $(DEBUG_OBJS:.o=.d)
-include $(RELEASE_OBJS:.o=.d)

clean:
	rm -rf build

cleandbg:
	rm -rf build/debug

CC = gcc

INPUT = $(wildcard src/*.c) \
        $(wildcard src/editor/*.c) \
        $(wildcard src/platform/*.c) \
        $(wildcard src/utils/*.c)

INCLUDE = include
LINK = -lX11

DEBUG_CFLAGS = -O0 -DDEBUG -g -Wall -Wextra -fsanitize=address,undefined -std=c11 -Wno-unused-function
RELEASE_CFLAGS = -O3 -DNDEBUG -Wall -Wextra -std=c11 -Wno-unused-function

DEBUG_OUTPUT = build/debug/tinyed
RELEASE_OUTPUT = build/release/tinyed

.PHONY: debug release clean

debug: $(DEBUG_OUTPUT)

release: $(RELEASE_OUTPUT)

$(DEBUG_OUTPUT):
	mkdir -p $(dir $@)
	$(CC) $(DEBUG_CFLAGS) -I$(INCLUDE) $(INPUT) -o $@ $(LINK)

$(RELEASE_OUTPUT):
	mkdir -p $(dir $@)
	$(CC) $(RELEASE_CFLAGS) -I$(INCLUDE) $(INPUT) -o $@ $(LINK)

clean:
	rm -rf build

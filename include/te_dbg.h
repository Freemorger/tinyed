#pragma once
// Debug and utilities

#include <stdlib.h>
#include "events.h"
#include "te_gfx.h"

/// Checks value for being zero and exits if its 0
#define CHECK_NULL(ptr) \
    do { \
        if ((ptr) == 0) {\
            fprintf(stderr, \
                "[%s %s] CRITICAL: %s is null! In source file %s, function %s, line %d.\n",\
                __DATE__, __TIME__, \
                #ptr, __FILE__, __func__, __LINE__\
            );\
            exit(EXIT_FAILURE);\
        } \
    } while (0)

#ifdef DEBUG
    #define DBG_PRINT(...) \
            printf(__VA_ARGS__);
#else 
    #define DBG_PRINT(...) ((void)0)
#endif

#if defined(_WIN32)
    /* Windows (32-bit or 64-bit) */
    #define PLATFORM "Windows"

#elif defined(__linux__)
    /* Linux */
    #define PLATFORM "Linux"

#elif defined(__APPLE__) && defined(__MACH__)
    /* macOS / Darwin */
    #define PLATFORM "macOS"

#elif defined(__FreeBSD__)
    #define PLATFORM "FreeBSD"

#else
    #define PLATFORM "Unknown"
#endif

void print_event_info(TE_Event* ev);

const char* detect_compiler();
const char* te_backend_name();
const char* detect_arch();

const char* te_btn_to_str(TE_Button btn);

#pragma once
// Debug and utilities

#include <stdlib.h>
#include "events.h"

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

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

static inline const char* detect_compiler() {
    #if defined(__TINYC__)
        return "TCC";
    #elif defined(__GNUC__) && defined(__VERSION__) && !defined(__clang__) 
        return "GCC " __VERSION__;
    #elif defined(__clang__) && defined(__VERSION__)
        return __VERSION__; // already contains clang 
    #elif defined(_MSC_FULL_VER)
        return "MSVC " STR(_MSC_VER) " (" STR(_MSC_FULL_VER) ")";
    #else
        return "unknown";
    #endif
}

static inline const char* detect_arch() {
    #if defined(__x86_64__) || defined(_M_X64)
        return "x86_64";
    #elif defined(__i386__) || defined(_M_IX86)
        return "i386";
    #elif defined(__aarch64__) || defined(_M_ARM64)
        return "aarch64";
    #elif defined(__arm__) || defined(_M_ARM)
        return "aarch32";
    #elif defined(__mips__)
        return "mips";
    #elif defined(__powerpc__) || defined(_M_PPC)
        return "PowerPC";
    #else
        return "unknown";
    #endif
}


#pragma once

#ifndef _WIN32
    #define _POSIX_C_SOURCE 199309L
#endif

#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>

    /// Cross platform macro to sleep for `ms` milliseconds
    #define TE_Sleep(ms) Sleep(ms)
#else
    #include <time.h>
    
    /// Cross platform macro/func to sleep for `ms` milliseconds
    /// Macro on windows, func on non-windows
    static inline void TE_Sleep(long ms) {
        struct timespec ts;
        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000L;
        nanosleep(&ts, NULL);
    }
#endif

/// Check rectangles collision (AABB)
bool te_chk_aabb(
    int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2
) {
    return (x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}

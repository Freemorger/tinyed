#pragma once

#ifdef _WIN32
    #define TE_BACKEND_WIN32
#else 
    #define TE_BACKEND_X11
#endif

static inline const char* te_backend_name() {
    #if defined(TE_BACKEND_X11)
        return "X11";
    #elif defined(TE_BACKEND_WIN32)
        return "Win32 API";
    #else 
        return "unknown";
    #endif
}

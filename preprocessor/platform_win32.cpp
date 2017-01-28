/*===================================================================================================
  File:                    platform_win32.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include <windows.h>
#include "platform.h"

Uint64 system_get_performance_counter(void) {
    Uint64 res = 0;

#if 0
    res = __rdtsc();
#else
    LARGE_INTEGER large_int;
    if(QueryPerformanceCounter(&large_int)) {
        res = large_int.QuadPart;
    }
#endif

    return(res);
}

Void system_print_timer(Uint64 value) {
    LARGE_INTEGER freq;
    if(QueryPerformanceFrequency(&freq)) {
        Uint64 duration = value * 1000 / freq.QuadPart;
        printf("The program took %llums.\n", duration);
    }
}

Bool system_check_for_debugger(void) {
    Bool res = IsDebuggerPresent() != 0;

    return(res);
}

Void *system_malloc(PtrSize size, PtrSize cnt/*= 1*/) {
    Void *res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size * cnt);

    return(res);
}

Bool system_free(Void *ptr) {
    Bool res = false;
    if(ptr) {
        res = HeapFree(GetProcessHeap(), 0, ptr) != 0;
    }

    return(res);
}

Void *system_realloc(Void *ptr, PtrSize size) {
    Void *res = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, size);

    return(res);
}
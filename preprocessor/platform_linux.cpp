/*===================================================================================================
  File:                    platform_linux.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include "platform.h"

Uint64 system_get_performance_counter(void) {
    Uint64 res = 0;

    return(res);
}

Void system_print_timer(Uint64 value) {

}

Bool system_check_for_debugger(void) {
    Bool res = false;

    return(res);
}

#if defined(malloc)
    #undef malloc
#endif
Void *system_malloc(PtrSize size, PtrSize cnt/*= 1*/) {
    Void *res = malloc(size * cnt);
    if(res) { memset(res, 0, size * cnt); }

    return(res);
}

#if defined(free)
    #undef free
#endif
Bool system_free(Void *ptr) {
    Bool res = false;
    if(ptr) {
        free(ptr);
        res = true;
    }

    return(res);
}

#if defined(realloc)
    #undef realloc
#endif
Void *system_realloc(Void *ptr, PtrSize size) {
    Void *res = realloc(ptr, size);

    return(res);
}
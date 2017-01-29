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

File read_entire_file_and_null_terminate(Char *fname, Void *memory) {
    File res = {};

    FILE *file = fopen(fname, "r");
    if(file) {
        fseek(file, 0, SEEK_END);
        res.size = ftell(file);
        fseek(file, 0, SEEK_SET);

        res.data = cast(Char *)memory;
        fread(res.data, 1, res.size, file);
        fclose(file);
    }

    return(res);
}

Bool write_to_file(Char *fname, Void *data, PtrSize data_size) {
    assert(data_size > 0);

    Bool res = false;

    FILE *file = fopen(fname, "w");
    if(file) {
        fwrite(data, 1, data_size, file);
        fclose(file);
        res = true;
    }

    return(res);
}

PtrSize get_file_size(Char *fname) {
    PtrSize size = 0;

    FILE *file = fopen(fname, "r");
    if(file) {
        fseek(file, 0, SEEK_END);
        size = ftell(file) + 1;
        fseek(file, 0, SEEK_SET);
        fclose(file);
    }

    return(size);
}

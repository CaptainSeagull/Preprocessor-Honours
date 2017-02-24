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
#include "utils.h"
#include "stdio.h"

Uint64 system_get_performance_counter(void) {
    Uint64 res = 0;
    LARGE_INTEGER large_int;

    if(QueryPerformanceCounter(&large_int)) res = large_int.QuadPart;

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
    return IsDebuggerPresent() != 0;
}

Void *system_malloc(PtrSize size, PtrSize cnt/*= 1*/) {
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size * cnt);
}

Bool system_free(Void *ptr) {
    if(ptr) return HeapFree(GetProcessHeap(), 0, ptr) != 0;
    else    return false;
}

Void *system_realloc(Void *ptr, PtrSize size) {
    return HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, size);
}

File system_read_entire_file_and_null_terminate(Char *fname, Void *memory) {
    File res = {};
    HANDLE fhandle;
    LARGE_INTEGER fsize;
    DWORD fsize32, bytes_read;

    fhandle = CreateFileA(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(fhandle != INVALID_HANDLE_VALUE) {
        if(GetFileSizeEx(fhandle, &fsize)) {
            fsize32 = safe_truncate_size_64(fsize.QuadPart);
            if(ReadFile(fhandle, memory, fsize32, &bytes_read, 0)) {
                if(bytes_read != fsize32) {
                    push_error(ErrorType_did_not_read_entire_file);
                } else {
                    res.size = fsize32;
                    res.data = cast(Char *)memory;
                    res.data[res.size] = 0;
                }
            }

            CloseHandle(fhandle);
        }
    }

    return(res);
}

Bool system_write_to_file(Char *fname, Void *data, PtrSize data_size) {
    Bool res = false;
    HANDLE fhandle;
    DWORD fsize32, bytes_written;

    fhandle = CreateFileA(fname, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
    if(fhandle != INVALID_HANDLE_VALUE) {
#if ENVIRONMENT32
        fsize32 = data_size;
#else
        fsize32 = safe_truncate_size_64(data_size);
#endif
        if(WriteFile(fhandle, data, fsize32, &bytes_written, 0)) {
            if(bytes_written != fsize32) push_error(ErrorType_did_not_write_entire_file);
            else                         res = true;
        }

        CloseHandle(fhandle);
    }

    return res;
}

PtrSize system_get_file_size(Char *fname) {
    PtrSize res = 0;
    HANDLE fhandle;
    LARGE_INTEGER large_int;

    fhandle = CreateFileA(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(fhandle != INVALID_HANDLE_VALUE) {
        if(GetFileSizeEx(fhandle, &large_int)) {
#if ENVIRONMENT32
            res = safe_truncate_size_64(large_int.QuadPart);
#else
            res = large_int.QuadPart;
#endif
        }

        CloseHandle(fhandle);
    }

    return(res);
}

Bool system_create_folder(Char *name) {
    Int create_dir_res = CreateDirectory(name, 0);

    Bool res = (create_dir_res == 0);

    return(res);
}

Void system_write_to_console(Char *str) {
    printf("%s", str);
}

Void system_write_to_stderr(Char *str) {
    fprintf(stderr, "%s", str);
}
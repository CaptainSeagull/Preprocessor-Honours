/*===================================================================================================
  File:                    platform.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include "shared.h"
#include "platform.h"
#include "utils.h"
#include "stdio.h"
#include "stb_sprintf.h"

internal Char *global_folder = 0;
Void system_set_current_folder(Char const *folder_name) {
    PtrSize len = string_length(folder_name);

    global_folder = system_alloc(Char, len + 2);
    if(global_folder) {
        string_copy(global_folder, folder_name);
        global_folder[len] = '/';

    }
}

//
// Win32
//
#if OS_WIN32

#include <windows.h>
#include <Shlwapi.h>

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

File system_read_entire_file_and_null_terminate(Char const *fname, Void *memory) {
    File res = {};
    HANDLE fhandle;
    LARGE_INTEGER fsize;
    DWORD fsize32, bytes_read;

    PtrSize const name_buf_size = 256;
    Char name_buf[name_buf_size] = {}; // MAX_PATH?
    string_concat(name_buf, name_buf_size, global_folder, string_length(global_folder), fname, string_length(fname));

    fhandle = CreateFileA(name_buf, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
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

Bool system_write_to_file(Char const *fname, Char const *data, PtrSize data_size) {
    Bool res = false;
    HANDLE fhandle;
    DWORD fsize32, bytes_written;

    PtrSize const name_buf_size = 256;
    Char name_buf[name_buf_size] = {}; // MAX_PATH?
    string_concat(name_buf, name_buf_size, global_folder, string_length(global_folder), fname, string_length(fname));

    fhandle = CreateFileA(name_buf, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
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

PtrSize system_get_file_size(Char const *fname) {
    PtrSize res = 0;
    HANDLE fhandle;
    LARGE_INTEGER large_int;

    PtrSize const name_buf_size = 256;
    Char name_buf[name_buf_size] = {}; // MAX_PATH?
    string_concat(name_buf, name_buf_size, global_folder, string_length(global_folder), fname, string_length(fname));

    fhandle = CreateFileA(name_buf, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
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

Bool system_create_folder(Char const *name) {
    PtrSize const name_buf_size = 256;
    Char name_buf[name_buf_size] = {}; // MAX_PATH?
    string_concat(name_buf, name_buf_size, global_folder, string_length(global_folder), name, string_length(name));

    Int create_dir_res = CreateDirectory(name_buf, 0);

    Bool res = (create_dir_res == 0);

    return(res);
}

Void system_write_to_console(Char const *str, ...) {
    PtrSize buf_size = 1024;
    Char buf[1024] = {};

    va_list args;
    va_start(args, str);
    PtrSize bytes_written = stbsp_vsnprintf(buf, buf_size, str, args);

    printf("%s", buf);
}

Void system_write_to_stderr(Char const *str) {
    fprintf(stderr, "%s", str);
}

Char const *system_get_file_extension(Char const *fname) {
    Char *res = PathFindExtensionA(fname);

    return(res);
}

//
// Linux
//
#elif OS_LINUX

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

Void *system_malloc(PtrSize size, PtrSize cnt/*= 1*/) {
    Void *res = malloc(size * cnt);
    if(res) {
        zero(res, size * cnt);
    }

    return(res);
}

Bool system_free(Void *ptr) {
    Bool res = false;
    if(ptr) {
        free(ptr);
        res = true;
    }

    return(res);
}

Void *system_realloc(Void *ptr, PtrSize new_size) {
    Void *res = realloc(ptr, new_size);
    // TODO(Jonny): Is there a realloc and zero for linux?

    return(res);
}

File system_read_entire_file_and_null_terminate(Char const *fname, Void *memory) {
    File res = {};

    PtrSize const name_buf_size = 256;
    Char name_buf[name_buf_size] = {}; // MAX_PATH?
    string_concat(name_buf, name_buf_size, global_folder, string_length(global_folder), fname, string_length(fname));

    FILE *file = fopen(name_buf, "r");
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

Bool system_write_to_file(Char const *fname, Char const *data, PtrSize data_size) {
    assert(data_size > 0);

    Bool res = false;

    PtrSize const name_buf_size = 256;
    Char name_buf[name_buf_size] = {}; // MAX_PATH?
    string_concat(name_buf, name_buf_size, global_folder, string_length(global_folder), fname, string_length(fname));

    FILE *file = fopen(name_buf, "w");
    if(file) {
        fwrite(data, 1, data_size, file);
        fclose(file);
        res = true;
    }

    return(res);
}

PtrSize system_get_file_size(Char const *fname) {
    PtrSize size = 0;

    PtrSize const name_buf_size = 256;
    Char name_buf[name_buf_size] = {}; // MAX_PATH?
    string_concat(name_buf, name_buf_size, global_folder, string_length(global_folder), fname, string_length(fname));

    FILE *file = fopen(name_buf, "r");
    if(file) {
        fseek(file, 0, SEEK_END);
        size = ftell(file) + 1;
        fseek(file, 0, SEEK_SET);
        fclose(file);
    }

    return(size);
}

Bool system_create_folder(Char const *name) {
    Bool res = false;
    struct stat st = {};

    if(stat(name, &st) == -1) res = (mkdir(name, 0700) == 0);
    else                      res = true;

    return(res);
}

Void system_write_to_console(Char const *str, ...) {
    PtrSize buf_size = 1024;
    Char buf[1024] = {};

    va_list args;
    va_start(args, str);
    PtrSize bytes_written = stbsp_vsnprintf(buf, buf_size, str, args);
    assert(bytes_written < buf_size);

    printf("%s", buf);
}

Void system_write_to_stderr(Char const *str) {
    fprintf(stderr, "%s", str);
}

Char const *system_get_file_extension(Char const *fname) {
    Char const *res = 0;
    Int dot_pos = string_contains_pos(fname, ".");

    if(dot_pos != -1) {
        res = fname + dot_pos;
    }

    return(res);
}


#endif

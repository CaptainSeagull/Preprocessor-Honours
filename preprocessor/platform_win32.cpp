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

#include "platform.h"
#include <windows.h>

//
// Stuff I need because I don't link to the crt.
//

#if WIN32
extern "C" { int _fltused; }
#endif

#pragma function(memset)
Void   *__cdecl
memset(_Out_writes_bytes_all_(_Size) Void *dest, _In_ int value, _In_ size_t num)
{
    assert((dest) && (value < 0xFFFF) && (num));

    Byte *dest8 = cast(Byte *)dest;

    while(num-- > 0) {
        *dest8++ = cast(Byte)value;
    }


    return(dest);
}

#pragma function(memcpy)
Void   *__cdecl
memcpy(_Out_writes_bytes_all_(_Size) Void *dest, _In_reads_bytes_(_Size) const Void *source, _In_ size_t num)
{
    assert((dest) && (source) && (num));

    copy_memory_block(dest, cast(Void *)source, num);

    return(dest);
}

#define GetProcAddress(lib, name) cast(Void *)(GetProcAddress(lib, name)) // To avoid warning C4191.

internal Uint32
safe_truncate_size_64(Uint64 value)
{
    assert(value <= 0xFFFFFFFF);
    Uint32 res = cast(Uint32)value;

    return(res);
}

internal Char *
win32_read_entire_file_and_null_terminate(Char *filename, Memory *memory)
{
    assert((filename) && (memory));

    Char *res = {};

    HANDLE file_handle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(file_handle != INVALID_HANDLE_VALUE) {
        LARGE_INTEGER file_size = {};
        if(GetFileSizeEx(file_handle, &file_size)) {
            Uint32 file_size_32 = safe_truncate_size_64(cast(size_t)file_size.QuadPart);
            res = push_file_memory(memory, file_size_32 + 1);

            DWORD BytesRead = 0;
            if((ReadFile(file_handle, res, file_size_32, &BytesRead, 0)) && (file_size_32 == BytesRead)) {
                // Success case.
            } else {
                res = 0;
            }
        }

        CloseHandle(file_handle);
    }

    return(res);
}

internal PtrSize
win32_get_file_size(Char *filename)
{
    assert(filename);

    PtrSize size = {};

    HANDLE file_handle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(file_handle != INVALID_HANDLE_VALUE) {
        LARGE_INTEGER file_size = {};
        if(GetFileSizeEx(file_handle, &file_size)) {
            size = safe_truncate_size_64(file_size.QuadPart + default_memory_alignment + 1);
        }

        CloseHandle(file_handle);
    }

    return(size);
}

// TODO(Jonny): Need to turn /n to /r/n.
internal Bool
win32_write_to_file(Char *filename, Void *data, PtrSize data_size)
{
    assert((filename) && (data) && (data_size));

    Bool res = false;
    HANDLE file_handle = CreateFileA(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if((file_handle) && (file_handle != INVALID_HANDLE_VALUE)) {
        DWORD bytes_written = 0;
        Uint data_size32 = safe_truncate_size_64(data_size);
        if(WriteFile(file_handle, data, data_size32, &bytes_written, 0)) {
            // Success case.
            res = (bytes_written  == data_size);
        } else {
            // TODO(Jonny): Fail.
        }

        CloseHandle(file_handle);
    }

    return(res);
}

enum ExtensionType {
    unknown,
    cpp,
    c,
};

internal ExtensionType
get_extension_from_str(Char *str)
{
    assert(str);

    ExtensionType res = ExtensionType::unknown;

    Int len = string_length(str);
    // TODO(Jonny): Do this properly...
    if((str[len - 1] == 'c') && (str[len - 2] == '.')) {
        res = ExtensionType::c;
    } else if((str[len - 1] == 'p') && (str[len - 2] == 'p') && (str[len - 3] == 'c') && (str[len - 4] == '.') ) {
        res = ExtensionType::cpp;
    }

    return(res);
}

Int
main(Int argc, Char *argv[])
{
    Int tot_size_of_all_files = 0;

    for(Int file_index = 1; (file_index < argc); ++file_index) {
        tot_size_of_all_files += win32_get_file_size(argv[file_index]);
        ExtensionType type = get_extension_from_str(argv[file_index]);
        assert(type);
    }

    ExtensionType type = get_extension_from_str(argv[1]); // TODO(Jonny): Hacky, should probably pass it in.
    assert(type);

    Int permanent_size = 1024 * 1024; // TODO(Jonny): Arbitrary size.
    Int temp_size = 1024 * 1024;
    Void *all_memory = VirtualAlloc(0, permanent_size + temp_size + tot_size_of_all_files, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    char *header_name = "generated.h";
    char *source_name = (type == ExtensionType::cpp) ? "generated.cpp" : "generated.c";

    if(all_memory) {
        Memory memory = create_memory(all_memory, tot_size_of_all_files, permanent_size, temp_size);

        AllFiles all_files = {};
        for(Int file_index = 1; (file_index < argc); ++file_index) {
            all_files.file[all_files.count++] = win32_read_entire_file_and_null_terminate(argv[file_index], &memory);
        }

        StuffToWrite stuff_to_write = start_parsing(all_files, &memory);

        Bool header_success = win32_write_to_file(header_name, stuff_to_write.header_data, stuff_to_write.header_size);
        Bool source_success = win32_write_to_file(source_name, stuff_to_write.source_data, stuff_to_write.source_size);
        assert((header_success) && (source_success));
    }


    Bool mem_freed = VirtualFree(all_memory, 0, MEM_RELEASE) != 0;
    assert(mem_freed);

    return(0);
}

Void
mainCRTStartup(Void)
{
    Char *buf[32] = {};
    Int buf_index = 0;

    Char *args = GetCommandLine();
    int arg_count = 0;

    buf[buf_index++] = args;
    while(*args) {
        if(is_whitespace(*args)) {
            while(is_whitespace(*args)) {
                *args++ = 0;
            }

            buf[buf_index++] = args;
        }

        ++args;
    }

    int res = main(buf_index, buf);
    ExitProcess(res);
}

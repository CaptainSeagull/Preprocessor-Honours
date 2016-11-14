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

#if !defined(_GNU_SOURCE)
    #define _GNU_SOURCE
#endif

#include <X11/X.h>
#include <x86intrin.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <dlfcn.h>

#include "stdio.h"

#include "platform.h"

internal Char *
linux_read_entire_file_and_null_terminate(Char *filename, Memory *memory)
{
    assert((filename) &&(memory));

    Char *res = 0;

    Int file_des = open(filename, 0, O_RDONLY);
    if(file_des != -1) {
        PtrSize size = lseek(file_des, 0, SEEK_END);
        lseek(file_des, 0, SEEK_SET);

        res = push_file_memory(memory, size + 1);
        read(file_des, res, size);
        close(file_des);
    }

    return(res);
}

internal Bool
linux_write_to_file(Char *filename, Void *data, PtrSize data_size)
{
    assert((filename) && (data) && (data_size));

    Bool res = false;

#if 1
    // TODO(Jonny): Use Posix version, not C standard lib version.
    FILE *file = fopen(filename, "w");
    if(file) {
        fwrite(data, 1, data_size, file);
        fclose(file);
        res = true;
    }
#else
    Int file_des = open(filename, 0, O_WRONLY | O_CREAT);
    if(file_des != -1) {
        signed long long bytes_written = pwrite(file_des, data, data_size, 0);
        assert(bytes_written != -1);
        close(file_des);
    } else {
        assert(0);
    }
#endif

    return(res);
}

internal PtrSize
linux_get_file_size(Char *filename)
{
    assert(filename);

    PtrSize size = 0;

    Int file_des = open(filename, 0, O_RDONLY);
    if(file_des != -1) {
        size = lseek(file_des, 0, SEEK_END) + default_memory_alignment + 1;
        lseek(file_des, 0, SEEK_SET);

        close(file_des);
    }

    return(size);
}

#define linux_write_to_console(str, ...) printf(str, ##__VA_ARGS__)

Int
main(Int argc, Char **argv)
{
    if(argc <= 1) {
        linux_write_to_console("\nError: No parameters");
    } else {
        Bool write_to_file = true;
        Int start_index = 1;
        if(string_compare(argv[1], "-s")) {
            write_to_file = false;
            ++start_index;
        }

        PtrSize tot_size_of_all_files = 0;
        for(Int file_index = start_index; (file_index < argc); ++file_index) {
            Int file_size = linux_get_file_size(argv[file_index]);
            if(file_size) {
                tot_size_of_all_files += file_size;
            } else {
                linux_write_to_console("\nCould not find file: \"%s\"", argv[file_index]);
            }
        }

        if(tot_size_of_all_files) {
            ExtensionType type = get_extension_from_str(argv[start_index]); // TODO(Jonny): Hacky.
            assert(type);

            Char *header_name = "generated.h";
            Char *source_name = cast(Char *)((type == ExtensionType_cpp) ? "generated.cpp" : "generated.c");

            PtrSize permanent_size = 1024 * 1024; // TODO(Jonny): Arbitrary size.
            PtrSize temp_size = 1024 * 1024; // TODO(Jonny): Arbitrary size.
            Void *all_memory = mmap(0, permanent_size + temp_size + tot_size_of_all_files, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            if((all_memory) && (all_memory != MAP_FAILED)) {
                Memory memory = create_memory(all_memory, tot_size_of_all_files, permanent_size, temp_size);

                AllFiles all_files = {};
                for(Int file_index = start_index; (file_index < argc); ++file_index) {
                    Char *file = linux_read_entire_file_and_null_terminate(argv[file_index], &memory);
                    if(file) {
                        all_files.file[all_files.count++] = file;
                    }
                }

                StuffToWrite stuff_to_write = start_parsing(all_files, &memory);

                char *static_file_data = get_static_file();
                Int static_file_len = string_length(static_file_data);
                Bool static_success = linux_write_to_file("static_generated.h", static_file_data, static_file_len);
                assert(static_success);

                Bool header_success = linux_write_to_file(header_name, stuff_to_write.header_data, stuff_to_write.header_size);
                Bool source_success = linux_write_to_file(source_name, stuff_to_write.source_data, stuff_to_write.source_size);
                assert((header_success) && (source_success));

                // TODO(Jonny): Unmap memory.
            }
        }
    }

    return(0);
}

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

internal char *
linux_read_entire_file_and_null_terminate(char *filename, Memory *memory)
{
    assert((filename) &&(memory));

    char *res = 0;

    int file_des = open(filename, 0, O_RDONLY);
    if(file_des != -1) {
        PtrSize size = lseek(file_des, 0, SEEK_END);
        lseek(file_des, 0, SEEK_SET);

        res = push_file_memory(memory, size + 1);
        read(file_des, res, size);
        close(file_des);
    }

    assert(res);
    return(res);
}

internal B32
linux_write_to_file(char *filename, void *data, PtrSize data_size)
{
    assert((filename) && (data) && (data_size > 0));

    B32 res = false;

#if 1
    // TODO(Jonny): Use Posix version, not C standard lib version.
    FILE *file = fopen(filename, "w");
    if(file) {
        fwrite(data, 1, data_size, file);
        fclose(file);
        res = true;
    }
#else
    int file_des = open(filename, 0, O_WRONLY | O_CREAT);
    if(file_des != -1) {
        SignedPtrSize bytes_written = pwrite(file_des, data, data_size, 0);
        assert(bytes_written != -1);
        close(file_des);
    } else {
        assert(0);
    }
#endif

    return(res);
}

internal PtrSize
linux_get_file_size(char *filename)
{
    assert(filename);

    PtrSize size = 0;

    int file_des = open(filename, 0, O_RDONLY);
    if(file_des != -1) {
        size = lseek(file_des, 0, SEEK_END) + DEFAULT_MEMORY_ALIGNMENT + 1;
        lseek(file_des, 0, SEEK_SET);

        close(file_des);
    }

    assert(size > 0);
    return(size);
}

int
main(int argc, char *argv[])
{
    PtrSize tot_size_of_all_files = 0;
    for(S32 file_index = 1; (file_index < argc); ++file_index) {
        tot_size_of_all_files += linux_get_file_size(argv[file_index]);
    }

    PtrSize permanent_size = 1024 * 1024; // TODO(Jonny): Arbitrary size.
    PtrSize temp_size = 1024 * 1024; // TODO(Jonny): Arbitrary size.
    void *all_memory = mmap(0, permanent_size + temp_size + tot_size_of_all_files, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if((all_memory) && (all_memory != MAP_FAILED)) {
        Memory memory = create_memory(all_memory, tot_size_of_all_files, permanent_size, temp_size);

        AllFiles all_files = {};
        for(S32 file_index = 1; (file_index < argc); ++file_index) {
            all_files.file[all_files.count++] = linux_read_entire_file_and_null_terminate(argv[file_index], &memory);
        }

        StuffToWrite stuff_to_write = start_parsing(all_files, &memory);

        B32 header_success = linux_write_to_file("generated.h", stuff_to_write.header_data, stuff_to_write.header_size);
        B32 source_success = linux_write_to_file("generated.cpp", stuff_to_write.source_data, stuff_to_write.source_size);
        assert((header_success) && (source_success));

        // TODO(Jonny): Unmap memory.
    }

    return(0);
}

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

#if !defined(_GNU_SOURCE)
    #define _GNU_SOURCE
#endif

#include "stdio.h"
#include "stdlib.h"

#include "platform.h"

internal Char *
read_entire_file_and_null_terminate(Char *filename, Memory *memory)
{
    assert((filename) &&(memory));

    Char *res = 0;

    FILE *file = fopen(filename, "r");
    if(file) {
        fseek(file, 0, SEEK_END);
        PtrSize size = ftell(file);
        fseek(file, 0, SEEK_SET);

        res = push_file_memory(memory, size + 1);
        PtrSize bytes_read = fread(res, 1, size, file);
        assert(bytes_read == size);
        fclose(file);
    }

    return(res);
}

internal Bool
write_to_file(Char *filename, Void *data, PtrSize data_size)
{
    assert((filename) && (data) && (data_size));

    Bool res = false;

    FILE *file = fopen(filename, "w");
    if(file) {
        fwrite(data, 1, data_size, file);
        fclose(file);
        res = true;
    }

    return(res);
}

internal PtrSize
get_file_size(Char *filename)
{
    assert(filename);

    PtrSize size = 0;

    FILE *file = fopen(filename, "r");
    if(file) {
        fseek(file, 0, SEEK_END);
        size = ftell(file) + 1;
        fseek(file, 0, SEEK_SET);
        fclose(file);
    }

    return(size);
}

Int
main(Int argc, Char **argv)
{
    if(argc <= 1) {
        printf("\nError: No parameters");
    } else {
        Bool should_write_to_file = true;
        Int start_index = 1;
        if(string_compare(argv[1], "-s")) {
            should_write_to_file = false;
            ++start_index;
        }

        PtrSize tot_size_of_all_files = 0;
        for(Int file_index = start_index; (file_index < argc); ++file_index) {
            Int file_size = get_file_size(argv[file_index]);
            if(file_size) {
                tot_size_of_all_files += file_size;
            } else {
                printf("\nCould not find file: \"%s\"", argv[file_index]);
            }
        }

        if(tot_size_of_all_files) {
            ExtensionType type = get_extension_from_str(argv[start_index]); // TODO(Jonny): Hacky.
            if(!type) {
                printf("Error: Unknown file type for file \"%s\"", argv[start_index]);
            } else {
                Char *header_name = "generated.h";
                Char *source_name = cast(Char *)((type == ExtensionType_cpp) ? "generated.cpp" : "generated.c");

                PtrSize permanent_size = 1024 * 1024; // TODO(Jonny): Arbitrary size.
                PtrSize temp_size = 1024 * 1024; // TODO(Jonny): Arbitrary size.
                Void *all_memory = malloc(permanent_size + temp_size + tot_size_of_all_files);
                if(all_memory) {
                    Memory memory = create_memory(all_memory, tot_size_of_all_files, permanent_size, temp_size);

                    AllFiles all_files = {};
                    for(Int file_index = start_index; (file_index < argc); ++file_index) {
                        Char *file = read_entire_file_and_null_terminate(argv[file_index], &memory);
                        if(file) {
                            all_files.file[all_files.count++] = file;
                        }
                    }

                    StuffToWrite stuff_to_write = start_parsing(all_files, &memory);

                    char *static_file_data = get_static_file();
                    Int static_file_len = string_length(static_file_data);
                    if(should_write_to_file) {
                        Bool static_success = write_to_file("static_generated.h", static_file_data, static_file_len);
                        assert(static_success);

                        Bool header_success = write_to_file(header_name, stuff_to_write.header_data, stuff_to_write.header_size);
                        Bool source_success = write_to_file(source_name, stuff_to_write.source_data, stuff_to_write.source_size);
                        assert((header_success) && (source_success));
                    }

                    // TODO(Jonny): Unmap memory.
                }
            }
        }
    }

    return(0);
}

/*===================================================================================================
  File:                    main.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include "utils.h"
#include "lexer.h"
#include "platform.h"
#include "write_file.h"
#include "test.h"

enum SwitchType {
    SwitchType_unknown,

    SwitchType_silent,
    SwitchType_log_errors,
    SwitchType_run_tests,
    SwitchType_print_help,
    SwitchType_display_time_taken,
    SwitchType_source_file,
    SwitchType_set_dir,

    SwitchType_count,
};

internal SwitchType get_switch_type(Char const *str) {
    SwitchType res = SwitchType_unknown;

    Int len = string_length(str);
    if(len >= 2) {
        if(str[0] == '-') {
            switch(str[1]) {
                case 'e': { res = SwitchType_log_errors;         } break;
                case 'h': { res = SwitchType_print_help;         } break;
                case 'p': { res = SwitchType_display_time_taken; } break;
                case 'd': { res = SwitchType_set_dir;            } break;
#if INTERNAL
                case 's': { res = SwitchType_silent;    } break;
                case 't': { res = SwitchType_run_tests; } break;
#endif
                default: { assert(0); } break;
            }
        } else if((str[len - 1] == 'h') && (str[len - 2] == '.')) {
            res = SwitchType_source_file;
        } else if((str[len - 1] == 'c') && (str[len - 2] == '.')) {
            res = SwitchType_source_file;
        } else if((str[len - 1] == 'p') && (str[len - 2] == 'p') && (str[len - 3] == 'c') && (str[len - 4] == '.') ) {
            res = SwitchType_source_file;
        }
    }

    return(res);
}

internal Bool write_static_file() {
    Char const *file =
        "//\n"
        "// Code shared between generated files.\n"
        "#if !defined(STATIC_GENERATED_H)\n"
        "\n"
        "#include <stdio.h>\n"
        "#include <string.h>\n"
        "#include <assert.h>\n"
        "#include <stdlib.h>\n"
        "#include <stddef.h>\n"
        "// TODO(Jonny): Only include these if their needed?\n"
        "#include <vector>\n"
        "#include <deque>\n"
        "#include <forward_list>\n"
        "#include <list>\n"
        "\n"
        "namespace pp { // PreProcessor\n"
        "\n"
        "typedef void _void;\n"
        "typedef char _char;\n"
        "typedef short _short;\n"
        "typedef int _int;\n"
        "typedef long _long;\n"
        "typedef float _float;\n"
        "typedef double _double;\n"
        "typedef bool _bool;\n"
        "\n"
        "#define PP_COMPILER_MSVC 0\n"
        "#define PP_COMPILER_CLANG 0\n"
        "#define PP_COMPILER_GCC 0\n"
        "\n"
        "#define PP_ENVIRONMENT64 0\n"
        "#define PP_ENVIRONMENT32 0\n"
        "\n"
        "#define PP_OS_WIN32 0\n"
        "#define PP_OS_LINUX 0\n"
        "\n"
        "// TODO(Jonny): Add Type in here?\n"
        "template<typename T> struct TypeInfo {\n"
        "    using type      = void;\n"
        "    using weak_type = void;\n"
        "    using base      = void;\n"
        "\n"
        "    static constexpr char const * const name      = 0;\n"
        "    static constexpr char const * const weak_name = 0;\n"
        "\n"
        "    static constexpr size_t const member_count = 0;\n"
        "    static constexpr size_t const base_count   = 0;\n"
        "\n"
        "    static constexpr bool const ptr    = 0;\n"
        "    static constexpr bool const is_ref = 0;\n"
        "\n"
        "\n"
        "    static constexpr bool const is_primitive = 0;\n"
        "    static constexpr bool const is_class     = 0;\n"
        "    static constexpr bool const is_enum      = 0;\n"
        "};\n"
        "\n"
        "struct MemberDefinition {\n"
        "    Type type;\n"
        "    char const *name;\n"
        "    size_t offset;\n"
        "    int is_ptr;\n"
        "    int arr_size;\n"
        "};\n"
        "\n"
        "\n"
        "struct Variable {\n"
        "    char const *ret_type;\n"
        "    char const *name;\n"
        "};\n"
        "\n"
        "struct MemberIter {\n"
        "    Type type;\n"
        "    char *name;\n"
        "    void *ptr;\n"
        "    bool is_ptr;\n"
        "    int arr;\n"
        "};\n"
        "\n"
        "template<typename T> static MemberDefinition *get_members_of_();\n"
        "\n"
        "template<typename T>MemberIter get_member_information(T *var, size_t i) {\n"
        "    pp::MemberDefinition *mems = pp::get_members_of_<T>();\n"
        "\n"
        "    pp::MemberDefinition cur = mems[i];\n"
        "\n"
        "    size_t *member_ptr = (size_t *)((char unsigned *)var + cur.offset);"
        "\n"
        "    MemberIter res;\n"
        "    res.name = (char *)cur.name;\n"
        "    res.type = cur.type;\n"
        "    res.ptr = member_ptr;\n"
        "    res.is_ptr = cur.is_ptr != 0;\n"
        "    res.arr = (cur.arr_size > 1) ? cur.arr_size : 0;\n"
        "\n"
        "    return(res);\n"
        "}\n"
        "\n"
        "#define serialize_type(var, T, buf, size) serialize_struct_(&var, #var, pp::TypeInfo<T>::name, 0, buf, size, 0)\n"
        "#define serialize(var, buf, size) serialize_type(var, decltype(var), buf, size)\n"
        "\n"
        "static MemberDefinition *get_members_of_str(char const *str);\n"
        "static int get_number_of_members_str(char const *str);\n"
        "\n"
        "static size_t serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer,\n"
        "                                size_t buf_size, size_t bytes_written);\n"
        "#define print_type(var, Type, ...) print_<Type>(&var, #var, ##__VA_ARGS__)\n"
        "#define print(var, ...) print_type(var, decltype(var), ##__VA_ARGS__)\n"
        "template<typename T>static void print_(T *var, char const *name, char *buf = 0, size_t size = 0) {\n"
        "    bool custom_buf = false;\n"
        "\n"
        "    if(!buf) {\n"
        "        size = 256 * 256;\n"
        "        buf = (char *)malloc(size);\n"
        "        custom_buf = true;\n"
        "    }\n"
        "\n"
        "    if(buf) {\n"
        "        memset(buf, 0, size);\n"
        "        size_t bytes_written = serialize_struct_(var, name, TypeInfo<T>::name, 0, buf, size, 0);\n"
        "        if(bytes_written < size) {\n"
        "            printf(\"%s\", buf);\n"
        "        }\n"
        "\n"
        "        if(custom_buf) {\n"
        "            free(buf);\n"
        "        }\n"
        "    }\n"
        "}\n"
        "\n"
        "template<class T, class U>struct TypeCompare_{ static const bool e = false; };\n"
        "template<class T>struct TypeCompare_<T, T>{ static const bool e = true; };\n"
        "#define type_compare(a, b) TypeCompare_<a, b>::e\n"
        "\n"
        "template<typename T> static int get_base_type_count_(void);\n"
        "#define get_base_type_count(Type) get_base_type_count_<Type>()\n"
        "\n"
        "template<typename T> static char const *get_base_type_as_string_(int index = 0);\n"
        "#define get_base_type_as_string(Type)       get_base_type_as_string_<Type>()\n"
        "#define get_base_type_as_string_index(Type, i) get_base_type_as_string_<Type>(i)\n"
        "\n"
        "#define fuzzy_type_compare(A, B) fuzzy_type_compare_<A, B>()\n"
        "template<typename T, typename U> bool fuzzy_type_compare_(void) {\n"
        "    char const *a_str = TypeInfo<T>::name;\n"
        "    char const *b_str = TypeInfo<U>::name;\n"
        "    if((a_str) && (b_str)) {\n"
        "        if(strcmp(a_str, b_str) == 0) {\n"
        "            return(true);\n"
        "        } else {\n"
        "            int base_count = get_base_type_count(T);\n"
        "            for(int i = 0; (i < base_count); ++i) {\n"
        "                char const *str = get_base_type_as_string_<T>(i);\n"
        "                if(strcmp(b_str, str)) { return(true); }\n"
        "            }\n"
        "            \n"
        "            for(int i = 0; (i < base_count); ++i) {\n"
        "                char const *str = get_base_type_as_string_<U>(i);\n"
        "                if(strcmp(a_str, str)) { return(true); }\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "\n"
        "    return(false);\n"
        "}\n"
        "\n"
        "enum Access {\n"
        "    Access_unknown,\n"
        "    Access_public,\n"
        "    Access_private,\n"
        "    Access_protected,\n"
        "\n"
        "    Access_count,\n"
        "};\n"
        "\n"
        "#if defined(_MSC_VER)\n"
        "    #define pp_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)\n"
        "#else\n"
        "    #define pp_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)\n"
        "#endif\n"
        "\n"
        "template<typename T>static size_t\n"
        "serialize_primitive_(T *member_ptr, bool is_ptr, int arr_size, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {\n"
        "    char const *type_as_string = TypeInfo<T>::name;\n"
        "    char indent_buf[256] = {};\n"
        "    for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}\n"
        "\n"
        "    if(arr_size > 1) {\n"
        "        for(int j = 0; (j < arr_size); ++j) {\n"
        "            size_t *member_ptr_as_size_t = (size_t *)member_ptr; // For arrays of pointers.\n"
        "            bool is_null = (is_ptr) ? member_ptr_as_size_t[j] == 0 : false;\n"
        "            if(!is_null) {\n"
        "                T v;\n"
        "                if(is_ptr) {\n"
        "                    v = *(T *)member_ptr_as_size_t[j];\n"
        "                } else {\n"
        "                    v = member_ptr[j];\n"
        "                }\n"
        "\n"
        "#define print_prim_arr(m, type) bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%s%s \" #type \" %s[%d] = \" m \"\", indent_buf, (is_ptr) ? \"*\" : \"\", name, j, (type)v)\n"
        "                if(type_compare(T, double))     print_prim_arr(\"%f\",  double);\n"
        "                else if(type_compare(T, float)) print_prim_arr(\"%f\",  float);\n"
        "                else if(type_compare(T, int))   print_prim_arr(\"%d\",  int);\n"
        "                else if(type_compare(T, long))  print_prim_arr(\"%ld\", long);\n"
        "                else if(type_compare(T, short)) print_prim_arr(\"%d\",  short);\n"
        "                else if(type_compare(T, bool))  print_prim_arr(\"%d\",  int); // This is int to avoid warning C4800 on MSVC. Bool values get serialized as int (1 or 0) anyway.\n"
        "#undef print_prim_arr\n"
        "            } else {\n"
        "                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%s%s %s %s[%d] = (null)\", indent_buf, (is_ptr) ? \"*\" : \"\", type_as_string, name, j);\n"
        "            }\n"
        "        }\n"
        "    } else {\n"
        "        T *v = (is_ptr) ? *(T **)member_ptr : (T *)member_ptr;\n"
        "        if(v) {\n"
        "#define print_prim(m, type) bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%s%s \" #type \" %s = \" m \"\", indent_buf, (is_ptr) ? \"*\" : \"\", name, (type)*v)\n"
        "            if(type_compare(T, double))     print_prim(\"%f\",  double);\n"
        "            else if(type_compare(T, float)) print_prim(\"%f\",  float);\n"
        "            else if(type_compare(T, int))   print_prim(\"%d\",  int);\n"
        "            else if(type_compare(T, long))  print_prim(\"%ld\", long);\n"
        "            else if(type_compare(T, short)) print_prim(\"%d\",  short);\n"
        "            else if(type_compare(T, bool))  print_prim(\"%d\",  int);// This is int to avoid warning C4800 on MSVC. Bool values get serialized as int (1 or 0) anyway.\n"
        "#undef print_prim\n"
        "        } else {\n"
        "            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%s %s *%s = (null)\", indent_buf, type_as_string, name);\n"
        "        }\n"
        "    }\n"
        "\n"
        "    return(bytes_written);\n"
        "\n"
        "}"
        "\n"
        "static size_t serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written);"
        "template<typename T, typename U> static size_t\n"
        "serialize_container(void *member_ptr, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {\n"
        "    char indent_buf[256] = {};\n"
        "    for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}\n"
        "\n"
        "    bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%s%s %s\", indent_buf, TypeInfo<T>::name, name);\n"
        "    T &container = *(T *)member_ptr;\n"
        "    for(auto &iter : container) {\n"
        "        bytes_written = serialize_struct_((void *)&iter, \"\", TypeInfo<U>::name, indent, buffer, buf_size, bytes_written);\n"
        "    }\n"
        "\n"
        "    return(bytes_written);\n"
        "}\n"
        "\n"
        "template<typename T, typename U> static size_t offset_of(U T::*member) {\n"
        "    return((char *)&((T *)0->*member) - (char *)0);\n"
        "}\n"
        "\n"
        "} // namespace pp\n"
        "\n"
        "#define STATIC_GENERATED\n"
        "#endif // !defined(STATIC_GENERATED_H)\n"
        "\n";

    Int static_file_len = string_length(file);
    Bool res = system_write_to_file(dir_name "/static_generated.h", file, static_file_len);

    if(!res) {
        push_error(ErrorType_could_not_write_to_disk);
    }

    return(res);
}

internal Bool should_write_to_file = false;

internal Void start_parsing(Char const *fname, Char const *file) {
    ParseResult parse_res = parse_stream(file);

    File file_to_write = write_data(fname, parse_res.struct_data, parse_res.struct_cnt,
                                    parse_res.enum_data, parse_res.enum_cnt,
                                    parse_res.func_data, parse_res.func_cnt);

    if(should_write_to_file) {
        PtrSize const len = 256;
        Char generated_file_name[len] = dir_name "/"; // TODO(Jonny): MAX_PATH?
        Int start = string_length(dir_name "/");
        Char const *generated_extension = "_generated.h";

        // Add _generated.h to the filename.
        if(string_concat(generated_file_name + start, len - start,
                         fname, string_length(fname) - 4, // TODO(Jonny): Hacky, actually detect the extension properly.
                         generated_extension, string_length(generated_extension))) {
            Bool header_write_success = system_write_to_file(generated_file_name, file_to_write.data, file_to_write.size);
            if(!header_write_success) {
                push_error(ErrorType_could_not_write_to_disk);
            }

            system_free(file_to_write.data);
        }
    }

    for(Int i = 0; (i < parse_res.struct_cnt); ++i) {
        system_free(parse_res.struct_data[i].members);
        system_free(parse_res.struct_data[i].inherited);
    }
    system_free(parse_res.struct_data);

    for(Int i = 0; (i < parse_res.enum_cnt); ++i) {
        system_free(parse_res.enum_data[i].values);
    }
    system_free(parse_res.enum_data);

    for(Int i = 0; (i < parse_res.func_cnt); ++i) {
        system_free(parse_res.func_data[i].params);
    }
    system_free(parse_res.func_data);
}

internal Void print_help(void) {
    Char const *help = "    List of Commands.\n"
                       "        -e - Print errors to the console.\n"
                       "        -h - Print this help.\n"
#if INTERNAL
                       "    Internal Commands.\n"
                       "        -s - Do not output any code, just see if there were errors parsing a file.\n"
                       "        -t - Run tests on the code.\n"
#endif
                       "\n";

    system_write_to_console(help);
}

Int main(Int argc, Char **argv) {// TODO(Jonny): Support wildcards.
    system_get_file_extension("test_code.cpp");

    Int res = 0;

    Bool display_time_taken = false;

    if(argc <= 1) {
        push_error(ErrorType_no_parameters);
        print_help();
    } else {
        Bool should_log_errors = true;
        Bool should_run_tests = false;
        should_write_to_file = true;

        PtrSize largest_source_file_size = 0;
        Int number_of_files = 0;
        for(Int i = 1; (i < argc); ++i) {
            Char const *switch_name = argv[i];

            SwitchType type = get_switch_type(switch_name);
            switch(type) {
                case SwitchType_silent:             { should_write_to_file = false;               } break;
                case SwitchType_log_errors:         { should_log_errors = true;                   } break;
                case SwitchType_run_tests:          { should_run_tests = true;                    } break;
                case SwitchType_print_help:         { print_help();                               } break;
                case SwitchType_display_time_taken: { display_time_taken = true;                  } break;
                case SwitchType_set_dir:            { system_set_current_folder(switch_name + 2); } break;

                case SwitchType_source_file: {
                    if(!string_contains(switch_name, dir_name)) {
                        PtrSize file_size = system_get_file_size(switch_name);
                        if(!file_size) {
                            push_error(ErrorType_cannot_find_file);
                        } else {
                            ++number_of_files;

                            if(file_size > largest_source_file_size) {
                                largest_source_file_size = file_size + 1; // We read the nul-terminator, so this has to be one greater.
                            }
                        }
                    }
                } break;

                default: {
                    system_write_to_console("Unknown argument %s", switch_name);
                } break;
            }
        }

        if(should_run_tests) {
#if RUN_TESTS
            Int run_tests(void);
            res = run_tests();
#endif
        } else {
            if(!number_of_files) {
                push_error(ErrorType_no_files_pass_in);
            } else {
                Byte *file_memory = system_alloc(Byte, largest_source_file_size);
                if(file_memory) {
                    // Write static file to disk.
                    if(should_write_to_file) {
                        Bool create_folder_success = system_create_folder(dir_name);

                        if(!create_folder_success) { push_error(ErrorType_could_not_create_directory); }
                        else                       { write_static_file();                              }
                    }

                    // Parse files
                    for(Int i = 1; (i < argc); ++i) {
                        Char const *file_name = argv[i];
                        zero(file_memory, largest_source_file_size);

                        SwitchType type = get_switch_type(file_name);
                        if(type == SwitchType_source_file) {
                            File file = system_read_entire_file_and_null_terminate(file_name, file_memory);

                            if(file.data) { start_parsing(file_name, file.data);       }
                            else          { push_error(ErrorType_could_not_load_file); }
                        }
                    }

                    system_free(file_memory);
                }
            }

            free_scratch_memory();
        }

        // Output errors.
        if(should_log_errors) {
            if(print_errors()) {
                res = 255;
            }
        }
    }

    return(res);
}


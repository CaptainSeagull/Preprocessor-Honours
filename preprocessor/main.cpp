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

/* TODO(Jonny):
    - Struct meta data.
        - It breaks if you use a comma to declare members of the same type.
        - Have a way to get the type of different elements (as strings or types).
        - Get a get_member(v, i) function, which simple returns the member at index i.
        - Output a _useful_ error message if the user declares the same struct twice.
        - In serialize struct, if there is a member which is an enum, call enum_to_string on it's value.
        - Create bool is_primitive(T) which returns if something is a primitive or not.
    - Union meta data.
        - Simple version of struct.
    - Function meta data.
        - Get name (as string).
        - Get linkage (as string).
        - Get return type.
        - Get param count.
        - Get params types, and names as strings.
    - References.
    - Templates.
    - Allow mathematical macros (1 + 1) to be the index for an array.
    - Global consts for arrays.
    - Handle typedefs.
    - Base type macro. If the programmer enters non-pointer (or non reference) value, just return the same value.
    - Make a variable_to_string macro (#define var_to_string(v) #v).
    - Make a is_primitive function.
    - Make a function tell if something's a pointer or not. Could return false if not a pointer, and a positive integer
      for the level of pointer otherwise. Should work with references too.
    - If the user puts a directory in front of the file name ("dir/source.cpp") then the outputted code will get
      placed in the directories parent, not the directory with the code.
    - I don't think #if 1 #else blocks work correctly...
*/

#include "utils.h"
#include "lexer.h"
#include "platform.h"
#if RUN_TESTS
    #include "test.h"
#endif

enum SwitchType {
    SwitchType_unknown,

    SwitchType_silent,
    SwitchType_log_errors,
    SwitchType_run_tests,
    SwitchType_print_help,
    SwitchType_display_time_taken,
    SwitchType_source_file,

    SwitchType_count,
};

SwitchType get_switch_type(Char *str) {
    SwitchType res = SwitchType_unknown;

    Int len = string_length(str);
    if(len >= 2) {
        if(str[0] == '-') {
            switch(str[1]) {
                case 'e': { res = SwitchType_log_errors;          } break;
                case 'h': { res = SwitchType_print_help;          } break;
                case 'p': { res = SwitchType_display_time_taken;  } break;
#if INTERNAL
                case 's': { res = SwitchType_silent;              } break;
                case 't': { res = SwitchType_run_tests;           } break;
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

Char *get_static_file(void) {
    Char *res = "// Preprocessor API.\n"
                "//\n"
                "// Reference.\n"
                "//\n"
                "// Structs\n"
                "//     - Print a struct to the console.\n"
                "//     bool pp::print(TYPE var, char *buffer = 0, size_t buf_size = 0);\n"
                "//\n"
                "//     - Serialize a struct for output.\n"
                "//     size_t pp::serialize(TYPE var, char *buffer, size_t buf_size);\n"
                "//\n"
                "//     - Get the number of members of a struct/class.\n"
                "//     int pp::get_num_of_members(TYPE type);\n"
                "//\n"
                "//     - Turn type t into a string literal.\n"
                "//     char const * pp::type_to_string(TYPE t);\n"
                "//\n"
                "//     - Turn type t into a string literal. Ignores pointer status.\n"
                "//     char const * pp::weak_type_to_string(TYPE t);\n"
                "//\n"
                "//     - Get the number of objects this struct inherits from\n"
                "//     int pp::get_base_type_count(TYPE t);\n"
                "//\n"
                "//     - Get the class t inherits from, as a string.\n"
                "//     char const * pp::get_base_type_as_string(TYPE t, int index = 0);\n"
                "//\n"
                "// Enums\n"
                "//     - Convert an enum index to a string.\n"
                "//     char const * pp::enum_to_string(EnumType, EnumType value);\n"
                "//\n"
                "//     - Convert a string to an enum index.\n"
                "//     int pp::string_to_enum(EnumType, char const *str);\n"
                "//\n"
                "//     - Get the total number of elements for an enum.\n"
                "//     size_t pp::get_number_of_enum_elements(EnumType);\n"
                "//\n"
                "// Misc.\n"
                "//     - Tests whether two types are the same.\n"
                "//     bool pp::type_compare(TYPE a, TYPE b);\n"
                "//\n"
                "//     - Tests whether two types are the same, or if one is a base class of another.\n"
                "//     bool pp::fuzzy_type_compare(TYPE a, TYPE b);\n"
                "//\n"
                "//     - Tests whether two types are the same, ignoring pointer status.\n"
                "//     bool pp::weak_type_compare(TYPE a, TYPE b);\n"
                "\n"
                "//\n"
                "// Code shared between generated files.\n"
                "#if !defined(STATIC_GENERATED_H)\n"
                "\n"
                "#include <stdio.h>\n"
                "#include <string.h>\n"
                "#include <assert.h>\n"
                "#include <stdlib.h>\n"
                "#include <stddef.h>\n"
                "#include <vector> // TODO(Jonny): Only include this if it's needed.\n"
                "\n"
                "namespace pp { // PreProcessor\n"
                "\n"
                "typedef char _char;\n"
                "typedef short _short;\n"
                "typedef int _int;\n"
                "typedef long _long;\n"
                "typedef float _float;\n"
                "typedef double _double;\n"
                "typedef bool _bool;\n"
                "\n"
                "struct MemberDefinition {\n"
                "    int/*MetaType*/ type;\n"
                "    char const *name;\n"
                "    size_t offset;\n"
                "    int is_ptr;\n"
                "    int arr_size;\n"
                "};\n"
                "\n"
                "struct Variable {\n"
                "    char const *ret_type;\n"
                "    char const *name;\n"
                "};\n"
                "\n"
                "#define get_num_of_members(type) get_number_of_members_<type>()\n"
                "\n"
                "template<typename T> static char const *type_to_string_(void);\n"
                "#define type_to_string(Type) type_to_string_<Type>()\n"
                "#define weak_type_to_string(Type) weak_type_to_string_<Type>()\n"
                "\n"
                "#define serialize_type(var, Type, buf, size) serialize_struct_(&var, #var, pp::type_to_string(Type), 0, buf, size, 0)\n"
                "#define serialize(var, buf, size) serialize_type(var, decltype(var), buf, size)\n"
                "\n"
                "static MemberDefinition *get_members_of_str(char const *str);\n"
                "static int get_number_of_members_str(char const *str);\n"
                "\n"
                "static size_t serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written);\n"
                "#define print_type(var, Type, ...) print_<Type>(&var, #var, ##__VA_ARGS__)\n"
                "#define print(var, ...) print_type(var, decltype(var), ##__VA_ARGS__)\n"
                "template<typename T>static bool print_(T *var, char const *name, char *buf = 0, size_t size = 0) {\n"
                "    bool res = false, custom_buf = false;\n"
                "\n"
                "    if(!buf) {\n"
                "        size = 256 * 256;\n"
                "        buf = (char *)malloc(size);\n"
                "        custom_buf = true;\n"
                "    }\n"
                "\n"
                "    if(buf) {\n"
                "        memset(buf, 0, size);\n"
                "        size_t bytes_written = serialize_struct_(var, name, type_to_string(T), 0, buf, size, 0);\n"
                "        if(bytes_written < size) {\n"
                "            printf(\"%s\", buf);\n"
                "            res = true;\n"
                "        }\n"
                "\n"
                "        if(custom_buf) { free(buf); }\n"
                "    }\n"
                "\n"
                "    return(res);\n"
                "}\n"
                "\n"
                "#define enum_to_string(Type, v) enum_to_string_##Type((int)v)\n"
                "\n"
                "#define string_to_enum(Type, str) string_to_enum_##Type(str)\n"
                "\n"
                "#define get_number_of_enum_elements(Type) number_of_elements_in_enum_##Type\n"
                "\n"
                "template<class T, class U>struct TypeCompare_{ enum {e = 0}; };\n"
                "template<class T>struct TypeCompare_<T, T>{ enum {e = 1}; };\n"
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
                "    char const *a_str = type_to_string(T);\n"
                "    char const *b_str = type_to_string(U);\n"
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
                "template<typename T> static char const *weak_type_to_string_(void);\n"
                "#define weak_type_compare(A, B) weak_type_compare_<A, B>()\n"
                "template<typename T, typename U> bool weak_type_compare_(void) {\n"
                "    char const *a_str = weak_type_to_string(T);\n"
                "    char const *b_str = weak_type_to_string(U);\n"
                "    if((a_str) && (b_str)) {\n"
                "        if(strcmp(a_str, b_str) == 0) { return(true); }\n"
                "    }\n"
                "\n"
                "    return(false);\n"
                "}\n"
                "\n"
                "template<typename T, typename U> static /*constexpr*/ size_t offset_of(U T::*member) { return (char *)&((T *)0->*member) - (char *)0; }\n"
                "\n"
                "#if defined(_MSC_VER)\n"
                "    #define pp_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)\n"
                "#else\n"
                "    #define pp_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)\n"
                "#endif\n"
                "\n"
                "} // namespace pp\n"
                "\n"
                "#define STATIC_GENERATED\n"
                "#endif // !defined(STATIC_GENERATED_H)"
                "\n";

    return(res);
}

struct File { Char *data; Int size; };
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

struct OutputBuffer {
    Char *buffer;
    Int index;
    Int size;
};

Void write_to_output_buffer(OutputBuffer *ob, Char *format, ...) {
    va_list args;
    va_start(args, format);
    ob->index += vsnprintf(ob->buffer + ob->index, ob->size - ob->index, format, args);
    va_end(args);
}

struct FunctionData {
    String linkage;
    String ret_type;
    String name;
    Variable params[32];
    Int param_count;
};

Void write_serialize_struct_implementation(Char *def_struct_code, OutputBuffer *ob) {
    Char *top =
        "// Function to serialize a struct to a char array buffer.\n"
        "static size_t\nserialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {\n"
        "    assert((name) && (buffer) && (buf_size > 0)); // Check params.\n"
        "\n"
        "    if(!indent) { memset(buffer + bytes_written, 0, buf_size - bytes_written); } // If this is the first time through, zero the buffer.\n"
        "\n"
        "    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); assert(members_of_Something); // Get the members_of pointer. \n"
        "    if(members_of_Something) {\n"
        "        // Setup the indent buffer.\n"
        "        char indent_buf[256] = {};\n"
        "        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }\n"
        "\n"
        "        // Write the name and the type.\n"
        "        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%s%%s %%s\", indent_buf, type_as_str, name);\n"
        "        indent += 4;\n"
        "\n"
        "        // Add 4 to the indent.\n"
        "        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }\n"
        "\n"
        "        int num_members = get_number_of_members_str(type_as_str); assert(num_members != -1); // Get the number of members for the for loop.\n"
        "        for(int i = 0; (i < num_members); ++i) {\n"
        "            MemberDefinition *member = members_of_Something + i; // Get the member pointer with meta data.\n"
        "            size_t *member_ptr = (size_t *)((char *)var + member->offset); // Get the actual pointer to the memory address.\n"
        "            // TODO(Jonny): Go through and check all the pointers are correct on these.\n"
        "            switch(member->type) {\n"
        "                // double.\n"
        "                case MetaType_double: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(double **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                double v = (member->is_ptr) ? *(double *)member_ptr[j] : *(double *)member_ptr + j;\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        double *double_value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;\n"
        "                        if(double_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble %%s%%s = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *double_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_double\n"
        "\n"
        "                // float.\n"
        "                case MetaType_float: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(float **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                float v = (member->is_ptr) ? *(float *)member_ptr[j] : *(float *)member_ptr + j;\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        float *float_value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;\n"
        "                        if(float_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat %%s%%s = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *float_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_float\n"
        "\n"
        "                // int.\n"
        "                case MetaType_int: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(int **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                int v = (member->is_ptr) ? *(int *)member_ptr[j] : *(int *)member_ptr + j;\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        int *int_value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;\n"
        "                        if(int_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *int_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_int\n"
        "\n"
        "                // long.\n"
        "                case MetaType_long: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(long **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                long v = (member->is_ptr) ? *(long *)member_ptr[j] : *(long *)member_ptr + j;\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%ld\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        long *long_value = (member->is_ptr) ? *(long **)member_ptr : (long *)member_ptr;\n"
        "                        if(long_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s = %%ld\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *long_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_long\n"
        "\n"
        "                // short.\n"
        "                case MetaType_short: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(short **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                short v = (short)((member->is_ptr) ? (*(short *)member_ptr[j]) : (*(short *)member_ptr + j));\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        short *short_value = (member->is_ptr) ? *(short **)member_ptr : (short *)member_ptr;\n"
        "                        if(short_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *short_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_short\n"
        "\n"
        "                // bool.\n"
        "                case MetaType_bool: {\n"
        "                    bool *bool_value = 0;\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(bool **)(member_ptr + j)) : 0;\n"
        "                            if(is_null) {\n"
        "                                size_t v = (member->is_ptr) ? **(bool **)(member_ptr + j) : *(bool *)member_ptr + j;\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool %%s%%s[%%d] = %%s\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (v) ? \"true\" : \"false\");\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        bool_value = (member->is_ptr) ? *(bool **)member_ptr : (bool *)member_ptr;\n"
        "                        if(bool_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool %%s%%s = %%s\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, (bool_value) ? \"true\" : \"false\");\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_bool\n"
        "\n"
        "                // char.\n"
        "                case MetaType_char: {\n"
        "                    if(member_ptr) {\n"
        "                        if(member->is_ptr) {\n"
        "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar *%%s = \\\"%%s\\\"\", indent_buf, member->name, (char *)(*(size_t *)member_ptr));\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar %%s = %%c\", indent_buf, member->name, *(char *)((size_t *)member_ptr));\n"
        "                        }\n"
        "                    } else {\n"
        "                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar *%%s = (null)\", indent_buf, member->name);\n"
        "                    }\n"
        "                } break; // case MetaType_char\n"
        "\n"
        "                // If the type wasn't a primtive, do a switchon the type again, but search for structs.\n"
        "                // Then that should recursively call this function again.\n"
        "                default: {\n";
    Char *bottom = "\n"
                   "                } break; // default \n"
                   "            }\n"
                   "        }\n"
                   "    }\n"
                   "\n"
                   "    return(bytes_written);\n"
                   "}\n";

    write_to_output_buffer(ob, top);
    write_to_output_buffer(ob, def_struct_code);
    write_to_output_buffer(ob, bottom);
}

Bool is_meta_type_already_in_array(String *array, Int len, String test) {
    Bool res = false;

    for(Int i = 0; (i < len); ++i) {
        if(string_compare(array[i], test)) {
            res = true;
            break; // for
        }
    }

    return(res);
}

Char *primitive_types[] = {"char", "short", "int", "long", "float", "double", "bool"};
#define get_num_of_primitive_types() array_count(primitive_types)

Int set_primitive_type(String *array) {
    Int res = array_count(primitive_types);

    for(int i = 0; (i < res); ++i) {
        array[i].e = primitive_types[i];
        array[i].len = string_length(primitive_types[i]);
    }

    return(res);
}

// TODO(Jonny): I don't like this...
#define copy_literal_to_char_buffer(buf, index, lit) copy_literal_to_char_buffer_(buf, index, lit, sizeof(lit) - 1)
Int copy_literal_to_char_buffer_(Char *buf, Int index, Char *literal, Int literal_len) {
    buf += index;

    for(Int i = 0; (i < literal_len); ++i) { buf[i] = literal[i]; }

    Int res = index + literal_len;
    return(res);
}

StructData *find_struct(String str, StructData *structs, Int struct_count) {
    StructData *res = 0;

    if(str.len) {
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = structs + i;

            if(string_compare(str, sd->name)) {
                res = sd;
                break; // for
            }
        }
    }

    if(!res) { push_error(ErrorType_could_not_find_struct); }

    return(res);
}

Char to_caps(Char c) {
    Char res = c;
    if((c >= 'a') && (c <= 'z')) { res += ('A' - 'a'); }

    return(res);
}

enum StdTypes {
    StdTypes_not,
    StdTypes_vector,

    StdTypes_cnt,
};

struct StdResult {
    StdTypes type;
    String stored_type;
};

StdResult get_std_information(String str) {
    StdResult res = {};

    Char *std_vector_str = "std::vector";
    if(string_contains(str, std_vector_str)) {
        res.type = StdTypes_vector;

        Int len = string_length(std_vector_str);
        res.stored_type.len=  str.len - len - 2;
        res.stored_type.e = str.e + len + 1;
    }

    return(res);
}

File write_data(Char *fname, StructData *struct_data, Int struct_count, EnumData *enum_data, Int enum_count) {
    File res = {};

    OutputBuffer ob = {};
    ob.size = 256 * 256;
    ob.buffer = alloc(Char, ob.size);
    if(ob.buffer) {

        Char *name_buf = cast(Char *)push_scratch_memory();
        Int len_wo_extension = string_length(fname) - 4; // TODO(Jonny): Do properly.
        for(Int i = 0; (i < len_wo_extension); ++i) {
            name_buf[i] = to_caps(fname[i]);
        }

        write_to_output_buffer(&ob,
                               "#if !defined(%s_GENERATED_H)\n"
                               "#define %s_GENERATED_H\n"
                               "\n",
                               name_buf, name_buf);

        clear_scratch_memory();

        // Forward declare structs.
        write_to_output_buffer(&ob,
                               "// Forward declared structs (these must be declared outside the namespace...)\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(sd->struct_type == StructType_struct)     { write_to_output_buffer(&ob, "struct %.*s;\n", sd->name.len, sd->name.e); }
            else if(sd->struct_type == StructType_class) { write_to_output_buffer(&ob, "class %.*s;\n", sd->name.len, sd->name.e);  }
            else if(sd->struct_type == StructType_union) { write_to_output_buffer(&ob, "union %.*s;\n", sd->name.len, sd->name.e);  }
            else { assert(0); }
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "#include \"static_generated.h\"\n"
                               "\n"
                               "namespace pp { // PreProcessor\n"
                               "#define _std std");

        //
        // MetaTypes enum.
        //
        // Get the absolute max number of meta types. This will be significantly bigger than the
        // actual number of unique types...
        Int max_type_count = get_num_of_primitive_types();
        for(Int i = 0; (i < struct_count); ++i) {
            max_type_count += struct_data[i].member_count + 1;
        }

        String *types = alloc(String, max_type_count);

        Int type_count = set_primitive_type(types);

        // Fill out the enum meta type enum.
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(!is_meta_type_already_in_array(types, type_count, sd->name)) {
                types[type_count++] = sd->name;
            }

            for(Int j = 0; (j < sd->member_count); ++j) {
                Variable *md = sd->members + j;

                if(!is_meta_type_already_in_array(types, type_count, md->type)) {
                    types[type_count++] = md->type;
                }
            }
        }

        assert(type_count <= max_type_count);

        // Write the meta type enum to file.
        write_to_output_buffer(&ob, "\n// Enum with field for every type detected.\n");
        write_to_output_buffer(&ob, "enum MetaType {\n");
        for(Int i = 0; (i < type_count); ++i) {
            String *type = types + i;

            StdResult std_res = get_std_information(*type);
            switch(std_res.type) {
                case StdTypes_not: {
                    write_to_output_buffer(&ob, "    MetaType_%.*s,\n", type->len, type->e);
                } break;

                case StdTypes_vector: {
                    write_to_output_buffer(&ob, "    MetaType_std_vector_%.*s,\n", std_res.stored_type.len, std_res.stored_type.e);
                } break;

                default: { assert(0); } break;
            }
        }

        write_to_output_buffer(&ob, "};");

        //
        // Struct Meta Data
        //

        // Recursive part for calling on members of structs.
        write_to_output_buffer(&ob, "\n\n");

        Int def_struct_code_size = 10000;
        Char *def_struct_code_mem = alloc(Char, def_struct_code_size);
        if(def_struct_code_mem) {
            Int index = 0;

            Bool any_stds = false;
            for(Int i = 0; (i < type_count); ++i) {
                String *type = types + i;

                StdResult std_res = get_std_information(*type);
                switch(std_res.type) {
                    case StdTypes_vector: { any_stds = true; } break;
                }

                if(any_stds) {
                    break; // for
                }
            }


            if((struct_count) || (any_stds)) {
                Char *switch_start = "                    switch(member->type) {\n";
                strcpy(def_struct_code_mem + index, switch_start);
                index += string_length(switch_start);

                // Add structs.
                for(Int i = 0; (i < struct_count); ++i) {
                    StructData *sd = struct_data + i;

                    // TODO(Jonny): This could support unions better...
                    index +=
                        my_sprintf(def_struct_code_mem + index, def_struct_code_size - index,
                                   "                        case MetaType_%.*s: {\n"
                                   "                            // %.*s\n"
                                   "                            if(member->is_ptr) {\n"
                                   "                                bytes_written = serialize_struct_(member_ptr, member->name, \"%.*s *\", indent, buffer, buf_size - bytes_written, bytes_written);\n"
                                   "                            } else {\n"
                                   "                                bytes_written = serialize_struct_(member_ptr, member->name, \"%.*s\", indent, buffer, buf_size - bytes_written, bytes_written);\n"
                                   "                            }\n"
                                   "                        } break; // case MetaType_%.*s\n"
                                   "\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e,
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);
                }

                // Add std things.
                for(Int i = 0; (i < type_count); ++i) {
                    String *type = types + i;

                    StdResult std_res = get_std_information(*type);

                    switch(std_res.type) {
                        case StdTypes_vector: {
                            index += my_sprintf(def_struct_code_mem + index, def_struct_code_size - index,
                                                "                        case MetaType_std_vector_%.*s: {\n"
                                                "                            std::vector<%.*s> temp = *(std::vector<%.*s> *)member_ptr;\n"
                                                "                            size_t size = temp.size();\n"
                                                "                            for(size_t i = 0; (i < size); ++i) {\n"
                                                "                                bytes_written = serialize_struct_((void *)&temp[i], member->name, \"%.*s\", indent, buffer, buf_size - bytes_written, bytes_written);\n"
                                                "                            }\n"
                                                "                        } break;\n"
                                                "\n",
                                                std_res.stored_type.len, std_res.stored_type.e,
                                                std_res.stored_type.len, std_res.stored_type.e,
                                                std_res.stored_type.len, std_res.stored_type.e,
                                                std_res.stored_type.len, std_res.stored_type.e);
                        } break;
                    }
                }

                Char *switch_end = "                    } // switch(member->type)";
                strcpy(def_struct_code_mem + index, switch_end);
                index += string_length(switch_end);

                assert(index < def_struct_code_size);
            } else {
                index += my_sprintf(def_struct_code_mem + index, def_struct_code_size - index,
                                    "                    // NOTE: No types found.");
            }

            write_serialize_struct_implementation(def_struct_code_mem, &ob);

            free(def_struct_code_mem);
        }

        // Recreated structs.
        write_to_output_buffer(&ob, "// Recreated structs (Clang in std=C++98 complains if these are local).\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            write_to_output_buffer(&ob, "%s _%.*s", (sd->struct_type != StructType_union) ? "struct" : "union",
                                   sd->name.len, sd->name.e);
            if(sd->inherited) {
                write_to_output_buffer(&ob, " :");

                for(Int j = 0; (j < sd->inherited_count); ++j) {
                    String *inherited = sd->inherited + j;

                    if(j) { write_to_output_buffer(&ob, ","); }

                    write_to_output_buffer(&ob, " public _%.*s", inherited->len, inherited->e);
                }
            }
            write_to_output_buffer(&ob, " { ");

            Bool is_inside_anonymous_struct = false;
            for(Int j = 0; (j < sd->member_count); ++j) {
                Variable *md = sd->members + j;


                if(md->is_inside_anonymous_struct != is_inside_anonymous_struct) {
                    is_inside_anonymous_struct = !is_inside_anonymous_struct;

                    if(is_inside_anonymous_struct) { write_to_output_buffer(&ob, " struct {"); }
                    else                           { write_to_output_buffer(&ob, "};");        }
                }

                Char *arr = "";
                Char arr_buffer[256] = {};
                if(md->array_count > 1) {
                    my_sprintf(arr_buffer, 256, "[%u]", md->array_count);
                    arr = arr_buffer;
                }

                write_to_output_buffer(&ob, " _%.*s %s%.*s%s; ",
                                       md->type.len, md->type.e,
                                       (md->is_ptr) ? "*" : "",
                                       md->name.len, md->name.e,
                                       (md->array_count > 1) ? arr_buffer : arr);

            }

            if(is_inside_anonymous_struct) { write_to_output_buffer(&ob, " };"); }
            write_to_output_buffer(&ob, " };\n");
        }

        // Get Members of.
        write_to_output_buffer(&ob,
                               "\n"
                               "// Convert a type into a members of pointer.\n"
                               "template<typename T> static MemberDefinition *get_members_of_(void) {\n");

        if(struct_count) {
            for(Int i = 0; (i < struct_count); ++i) {
                StructData *sd = struct_data + i;

                if(!i) {
                    write_to_output_buffer(&ob,
                                           "    // %.*s\n"
                                           "    if(type_compare(T, %.*s)) {\n",
                                           sd->name.len, sd->name.e,
                                           sd->name.len, sd->name.e);
                } else {
                    write_to_output_buffer(&ob,
                                           "\n"
                                           "    // %.*s\n"
                                           "    } else if(type_compare(T, %.*s)) {\n",
                                           sd->name.len, sd->name.e,
                                           sd->name.len, sd->name.e);
                }

                write_to_output_buffer(&ob, "        static MemberDefinition members_of_%.*s[] = {\n", sd->name.len, sd->name.e);
                for(Int j = 0; (j < sd->member_count); ++j) {
                    Variable *md = sd->members + j;

                    StdResult std_res = get_std_information(md->type);
                    switch(std_res.type) {
                        case StdTypes_not: {
                            write_to_output_buffer(&ob, "            {MetaType_%.*s", md->type.len, md->type.e);
                        } break;

                        case StdTypes_vector: {
                            write_to_output_buffer(&ob, "            {MetaType_std_vector_%.*s", std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        default: { assert(0); } break;
                    }

                    write_to_output_buffer(&ob, ", \"%.*s\", offset_of(&_%.*s::%.*s), %s, %d},\n",
                                           md->name.len, md->name.e,
                                           sd->name.len, sd->name.e,
                                           md->name.len, md->name.e,
                                           (md->is_ptr) ? "true" : "false",
                                           md->array_count);
                }

                if(sd->inherited) {
                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);

                        write_to_output_buffer(&ob, "            // Members inherited from %.*s.\n",
                                               base_class->name.len, base_class->name.e);
                        for(Int k = 0; (k < base_class->member_count); ++k) {
                            Variable *base_class_var = base_class->members + k;

                            StdResult std_res = get_std_information(base_class_var->type);
                            switch(std_res.type) {
                                case StdTypes_not: {
                                    write_to_output_buffer(&ob,
                                                           "            {MetaType_%.*s",
                                                           base_class_var->type.len, base_class_var->type.e);
                                } break;

                                case StdTypes_vector: {
                                    write_to_output_buffer(&ob,
                                                           "            {MetaType_std_vector_%.*s",
                                                           std_res.stored_type.len, std_res.stored_type.e);
                                } break;

                                default: { assert(0); } break;
                            }

                            write_to_output_buffer(&ob, ", \"%.*s\", (size_t)&((_%.*s *)0)->%.*s, %s, %d},\n",
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   sd->name.len, sd->name.e,
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   (base_class_var->is_ptr) ? "true" : "false",
                                                   base_class_var->array_count);
                        }
                    }
                }

                write_to_output_buffer(&ob,
                                       "        };\n"
                                       "        return(members_of_%.*s);\n",
                                       sd->name.len, sd->name.e);
            }

            write_to_output_buffer(&ob, "    }\n");
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Error.\n"
                               "}\n");

        // Get number of members.
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the number of members for a type.\n"
                               "template<typename T> static int get_number_of_members_(void) {\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            Int member_count = sd->member_count;

            // Add inherited struct members onto the member count.
            for(Int j = 0; (j < sd->inherited_count); ++j) {
                StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);


                member_count += base_class->member_count;
            }

            if(i == 0) {
                write_to_output_buffer(&ob,
                                       "    if(type_compare(T, %.*s)) { return(%d); } // %.*s\n",
                                       sd->name.len, sd->name.e, member_count, sd->name.len, sd->name.e);
            } else {
                write_to_output_buffer(&ob,
                                       "    else if(type_compare(T, %.*s)) { return(%d); } // %.*s\n",
                                       sd->name.len, sd->name.e, member_count, sd->name.len, sd->name.e);
            }
        }

        write_to_output_buffer(&ob,
                               "\n    return(-1); // Error.\n"
                               "}\n");

        clear_scratch_memory();


        //
        // Get Members of str.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Convert a type into a members of pointer.\n"
                               "static MemberDefinition *get_members_of_str(char const *str) {\n");

        String prim[array_count(primitive_types)] = {};
        set_primitive_type(prim);

        for(Int i = 0, cnt = array_count(prim); (i < cnt); ++i) {
            String *s = prim + i;

            if(!i) {
                write_to_output_buffer(&ob,
                                       "    // %.*s\n"
                                       "    if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e);
            } else {
                write_to_output_buffer(&ob,
                                       "    // %.*s\n"
                                       "    } else if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e);
            }

            Int len = 0;
            Char *output_string = 0;

            StdResult std_res = get_std_information(*s);
            switch(std_res.type) {
                case StdTypes_not: {
                    output_string = s->e;
                    len = s->len;
                } break;

                case StdTypes_vector: {
                    output_string = std_res.stored_type.e;
                    len = std_res.stored_type.len;
                } break;

                default: { assert(0); } break;
            }

            write_to_output_buffer(&ob,
                                   "        static MemberDefinition members_of_%.*s[] = {\n"
                                   "            {MetaType_%.*s, \"\", 0, false, 1}\n"
                                   "        };\n"
                                   "        return(members_of_%.*s);\n"
                                   "\n",
                                   len, output_string,
                                   len, output_string,
                                   len, output_string,
                                   len, output_string);

        }
        //if((strcmp(str, "SomeStruct") == 0) || (strcmp(str, "SomeStruct *") == 0) || (strcmp(str, "SomeStruct **") == 0)) {


        if(struct_count) {
            for(Int i = 0; (i < struct_count); ++i) {
                StructData *sd = struct_data + i;

                write_to_output_buffer(&ob,
                                       "\n"
                                       "    // %.*s\n"
                                       "    } else if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e);

                write_to_output_buffer(&ob, "        static MemberDefinition members_of_%.*s[] = {\n", sd->name.len, sd->name.e);
                for(Int j = 0; (j < sd->member_count); ++j) {
                    Variable *md = sd->members + j;

                    StdResult std_res = get_std_information(md->type);
                    switch(std_res.type) {
                        case StdTypes_not: {
                            write_to_output_buffer(&ob, "            {MetaType_%.*s",
                                                   md->type.len, md->type.e);
                        } break;

                        case StdTypes_vector: {
                            write_to_output_buffer(&ob, "            {MetaType_std_vector_%.*s",
                                                   std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        default: { assert(0); } break;
                    }

                    write_to_output_buffer(&ob, ", \"%.*s\", offset_of(&_%.*s::%.*s), %s, %d},\n",
                                           md->name.len, md->name.e,
                                           sd->name.len, sd->name.e,
                                           md->name.len, md->name.e,
                                           (md->is_ptr) ? "true" : "false",
                                           md->array_count);
                }

                if(sd->inherited) {
                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);

                        write_to_output_buffer(&ob, "            // Members inherited from %.*s.\n",
                                               base_class->name.len, base_class->name.e);
                        for(Int k = 0; (k < base_class->member_count); ++k) {
                            Variable *base_class_var = base_class->members + k;

                            StdResult std_res = get_std_information(base_class_var->type);
                            switch(std_res.type) {
                                case StdTypes_not: {
                                    write_to_output_buffer(&ob, "            {MetaType_%.*s",
                                                           base_class_var->type.len, base_class_var->type.e);
                                } break;

                                case StdTypes_vector: {
                                    write_to_output_buffer(&ob, "            {MetaType_std_vector_%.*s",
                                                           std_res.stored_type.len, std_res.stored_type.e);
                                } break;
                            }


                            write_to_output_buffer(&ob, ", \"%.*s\", (size_t)&((_%.*s *)0)->%.*s, %s, %d},\n",
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   sd->name.len, sd->name.e,
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   (base_class_var->is_ptr) ? "true" : "false",
                                                   base_class_var->array_count);
                        }
                    }
                }

                write_to_output_buffer(&ob,
                                       "        };\n"
                                       "        return(members_of_%.*s);\n",
                                       sd->name.len, sd->name.e);
            }

        }
        write_to_output_buffer(&ob, "    }\n");

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Error.\n"
                               "}\n");

        //
        // Get number of members from string.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the number of members for a type.\n"
                               "static int get_number_of_members_str(char const *str) {\n");

        for(Int i = 0, cnt = array_count(prim); (i < cnt); ++i) {
            String *p = prim + i;

            if(!i) {
                write_to_output_buffer(&ob,
                                       "    if(strcmp(str, \"%.*s\") == 0) { return(1); }\n",
                                       p->len, p->e);
            } else {
                write_to_output_buffer(&ob,
                                       "    else if(strcmp(str, \"%.*s\") == 0) { return(1); }\n",
                                       p->len, p->e);
            }
        }


        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            Int member_count = sd->member_count;

            // Add inherited struct members onto the member count.
            for(Int j = 0; (j < sd->inherited_count); ++j) {
                StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);

                member_count += base_class->member_count;
            }

            write_to_output_buffer(&ob,
                                   "    else if(strcmp(str, \"%.*s\") == 0) { return(%d); } // %.*s\n",
                                   sd->name.len, sd->name.e, member_count, sd->name.len, sd->name.e);
        }

        write_to_output_buffer(&ob,
                               "\n    return(-1); // Error.\n"
                               "}\n");

        // type_to_string.
        write_to_output_buffer(&ob,
                               "\n// Convert a type to a string.\n"
                               "template<typename T> static char const *type_to_string_(void) {\n"
                               "    // Primitives.\n");
        for(Int i = 0; (i < get_num_of_primitive_types()); ++i) {
            Char *primitive = primitive_types[i];

            if(!i) {
                write_to_output_buffer(&ob, "    if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s *\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s **\"); }\n", primitive, primitive);
            } else {
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s *\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s **\"); }\n", primitive, primitive);
            }
        }

        write_to_output_buffer(&ob, "\n    // Struct types.\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s *)) { return(\"%.*s *\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s **)) { return(\"%.*s **\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);
        }
        write_to_output_buffer(&ob, "\n    else { return(0); } // Unknown Type.\n}\n");

        // type_to_string ignore.
        write_to_output_buffer(&ob,
                               "\n// Convert a type to a string.\n"
                               "template<typename T> static char const *weak_type_to_string_(void) {\n"
                               "    // Primitives.\n");
        for(Int i = 0; (i < get_num_of_primitive_types()); ++i) {
            Char *primitive = primitive_types[i];

            if(!i) {
                write_to_output_buffer(&ob, "    if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s\"); }\n", primitive, primitive);
            } else {
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s\"); }\n", primitive, primitive);
            }
        }

        write_to_output_buffer(&ob, "\n    // Struct types.\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s *)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s **)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);
        }
        write_to_output_buffer(&ob, "\n    else { return(0); } // Unknown Type.\n}\n");

        //
        // Get base type count.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the number of base types.\n"
                               "template<typename T> static int get_base_type_count_(void) {\n");

        for(Int i = 0, written_count = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(sd->inherited_count) {
                if(!written_count) {
                    write_to_output_buffer(&ob, "    if(type_compare(T, %.*s))    { return(%d); }\n",
                                           sd->name.len, sd->name.e, sd->inherited_count);
                } else {
                    write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s)) { return(%d); }\n",
                                           sd->name.len, sd->name.e, sd->inherited_count);
                }

                ++written_count;
            }
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Not found.\n"
                               "}\n");

        //
        // Get base type as string.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the base type.\n"
                               "template<typename T> static char const *get_base_type_as_string_(int index/*= 0*/) {\n");

        if(struct_count) {
            Bool actually_written_anything = false;
            for(Int i = 0, written_count = 0; (i < struct_count); ++i) {
                StructData *sd = struct_data + i;

                if(sd->inherited_count) {
                    actually_written_anything = true;
                    // TODO(Jonny): Make the index return the inherited index.
                    if(!written_count) {
                        write_to_output_buffer(&ob,
                                               "    if(type_compare(T, %.*s)) {\n",
                                               sd->name.len, sd->name.e);
                    } else {
                        write_to_output_buffer(&ob,
                                               "    } else if(type_compare(T, %.*s)) {\n",
                                               sd->name.len, sd->name.e);
                    }

                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        if(!j) {
                            write_to_output_buffer(&ob,
                                                   "        if(index == %d)      { return(\"%.*s\"); }\n",
                                                   j,
                                                   sd->inherited[j].len, sd->inherited[j].e);
                        } else {
                            write_to_output_buffer(&ob,
                                                   "        else if(index == %d) { return(\"%.*s\"); }\n",
                                                   j,
                                                   sd->inherited[j].len, sd->inherited[j].e);
                        }

                    }

                    ++written_count;
                }
            }

            if(actually_written_anything) {
                write_to_output_buffer(&ob,
                                       "    }\n");
            }
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Not found.\n"
                               "}\n");
        //
        // Enum Meta data.
        //

        // TODO(Jonny): Can I make the enum meta data templates as well, similar to the structs?
        if(enum_count) {
            write_to_output_buffer(&ob,
                                   "\n"
                                   "//\n"
                                   "// Enum meta data.\n"
                                   "//\n");

            Int half_scratch_memory_size = cast(Int)(cast(Float)scratch_memory_size * 0.5f);
            for(Int i = 0; (i < enum_count); ++i) {
                EnumData *ed = enum_data + i;
                write_to_output_buffer(&ob, "\n// Meta Data for %.*s.\n", ed->name.len, ed->name.e);

                Char type[32];
                if(ed->type.len) {
                    for(int j = 0; (j < ed->type.len); ++j) { type[j] = ed->type.e[j]; }
                    type[ed->type.len] = 0;
                } else {
                    type[0] = 'i'; type[1] = 'n'; type[2] = 't'; type[3] = 0;
                }

                // Enum size.
                {
                    Char *buf = cast(Char *)push_scratch_memory();

                    int bytes_written = my_sprintf(buf, scratch_memory_size,
                                                   "static %s number_of_elements_in_enum_%.*s = %d;",
                                                   type,
                                                   ed->name.len, ed->name.e,
                                                   ed->no_of_values);
                    assert(bytes_written < scratch_memory_size);

                    write_to_output_buffer(&ob, buf);

                    clear_scratch_memory();
                }

                // enum_to_string.
                {
                    Char *buf1 = cast(Char *)push_scratch_memory(half_scratch_memory_size);
                    Char *buf2 = cast(Char *)push_scratch_memory(half_scratch_memory_size);

                    Int index = 0;
                    for(int j = 0; (j < ed->no_of_values); ++j) {
                        index += my_sprintf(buf1 + index, half_scratch_memory_size - index,
                                            "        case %d: { return(\"%.*s\"); } break;\n",
                                            ed->values[j].value,
                                            ed->values[j].name.len, ed->values[j].name.e);
                    }

                    Int bytes_written = my_sprintf(buf2, half_scratch_memory_size,
                                                   "\nstatic char const *enum_to_string_%.*s(%s v) {\n"
                                                   "    switch(v) {\n"
                                                   "%s"
                                                   "    }\n"
                                                   "\n"
                                                   "    return(0); // v is out of bounds.\n"
                                                   "}\n",
                                                   ed->name.len, ed->name.e,
                                                   type,
                                                   buf1);
                    assert(bytes_written < half_scratch_memory_size);

                    write_to_output_buffer(&ob, buf2);

                    clear_scratch_memory();
                }

                // string_to_enum.
                {
                    Char *buf1 = cast(Char *)push_scratch_memory(half_scratch_memory_size);
                    Char *buf2 = cast(Char *)push_scratch_memory(half_scratch_memory_size);

                    Int index = 0;
                    index += my_sprintf(buf1 + index, half_scratch_memory_size - index,
                                        "        if(strcmp(str, \"%.*s\") == 0) { return(%d); }\n",
                                        ed->values[0].name.len, ed->values[0].name.e,
                                        ed->values[0].value);
                    for(int j = 1; (j < ed->no_of_values); ++j) {
                        index += my_sprintf(buf1 + index, half_scratch_memory_size - index,
                                            "        else if(strcmp(str, \"%.*s\") == 0) { return(%d); }\n",
                                            ed->values[j].name.len, ed->values[j].name.e,
                                            ed->values[j].value);
                    }
                    assert(index < half_scratch_memory_size);

                    Int bytes_written = my_sprintf(buf2, half_scratch_memory_size,
                                                   "static %s string_to_enum_%.*s(char const *str) {\n"
                                                   "    if(str) {\n"
                                                   "%s"
                                                   "    }\n"
                                                   "\n"
                                                   "    return(0);  // str didn't match.\n" // TODO(Jonny): Throw an error here?
                                                   "}\n",
                                                   type,
                                                   ed->name.len, ed->name.e, buf1);
                    assert(bytes_written < half_scratch_memory_size);


                    write_to_output_buffer(&ob, buf2);

                    clear_scratch_memory();
                }
            }
        }

        //
        // # Guard macro.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "#undef _std\n"
                               "} // namespace pp\n"
                               "\n"
                               "#endif // Header guard.\n"
                               "\n");

        res.size = ob.index;
        res.data = ob.buffer;

        free(types);
    }

    return(res);
}

Bool should_write_to_file = false;

Void start_parsing(Char *fname, Char *file) {
    ParseResult parse_res = parse_stream(file);

    File file_to_write = write_data(fname, parse_res.struct_data, parse_res.struct_cnt,
                                    parse_res.enum_data, parse_res.enum_cnt);

    if(should_write_to_file) {
        Char generated_file_name[256] = {};
        Char *generated_extension = "_generated.h";

        if(string_concat(generated_file_name, array_count(generated_file_name),
                         fname, string_length(fname) - 4, // TODO(Jonny): Hacky, actually detect the extension properly.
                         generated_extension, string_length(generated_extension))) {

            Bool header_write_success = write_to_file(generated_file_name, file_to_write.data, file_to_write.size);
            if(!header_write_success) { push_error(ErrorType_could_not_write_to_disk); }

            free(file_to_write.data);
        }
    }

    for(Int i = 0; (i < parse_res.struct_cnt); ++i) { free(parse_res.struct_data[i].members);   }
    for(Int i = 0; (i < parse_res.struct_cnt); ++i) { free(parse_res.struct_data[i].inherited); }
    free(parse_res.struct_data);

    for(Int i = 0; (i < parse_res.enum_cnt); ++i) { free(parse_res.enum_data[i].values); }
    free(parse_res.enum_data);
}


Void print_help(void) {
    Char *help = "    List of Commands.\n"
                 "        -e - Print errors to the console.\n"
                 "        -h - Print this help.\n"
#if INTERNAL
                 "    Internal Commands.\n"
                 "        -s - Do not output any code, just see if there were errors parsing a file.\n"
                 "        -t - Run tests on the code.\n"
#endif
                 "\n";

    printf("%s", help);
}

Int main(Int argc, Char **argv) {
    Int res = 0;

    Bool display_time_taken = false;
    Uint64 start_time = system_get_performance_counter();

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
            Char *switch_name = argv[i];

            SwitchType type = get_switch_type(switch_name);
            switch(type) {
                case SwitchType_silent:             { should_write_to_file = false; } break;
                case SwitchType_log_errors:         { should_log_errors = true;     } break;
                case SwitchType_run_tests:          { should_run_tests = true;      } break;
                case SwitchType_print_help:         { print_help();                 } break;
                case SwitchType_display_time_taken: { display_time_taken = true;    } break;

                case SwitchType_source_file: {
                    PtrSize file_size = get_file_size(switch_name);
                    if(!file_size) {push_error(ErrorType_cannot_find_file); }
                    else {
                        ++number_of_files;
                        if(file_size > largest_source_file_size) { largest_source_file_size = file_size; }
                    }
                } break;
            }
        }

        if(should_run_tests) {
#if RUN_TESTS
            Int run_tests(void);
            res = run_tests();
#endif
        } else {
            if(!number_of_files) { push_error(ErrorType_no_files_pass_in); }
            else {
                Byte *file_memory = alloc(Byte, largest_source_file_size);
                if(file_memory) {
                    // Write static file to disk.
                    if(should_write_to_file) {
                        Char *static_file_data = get_static_file();
                        Int static_file_len = string_length(static_file_data);
                        Bool static_write_success = write_to_file("static_generated.h", static_file_data, static_file_len);
                        if(!static_write_success) { push_error(ErrorType_could_not_write_to_disk); }
                    }

                    // Parse files
                    for(Int i = 1; (i < argc); ++i) {
                        Char *file_name = argv[i];
                        memset(file_memory, 0, largest_source_file_size);

                        SwitchType type = get_switch_type(file_name);
                        if(type == SwitchType_source_file) {
                            File file = read_entire_file_and_null_terminate(file_name, file_memory);
                            if(file.data) { start_parsing(file_name, file.data);       }
                            else          { push_error(ErrorType_could_not_load_file); }
                        }
                    }

                    free(file_memory);
                }
            }
#if MEM_CHECK
            free_scratch_memory();

            // Check memory leaks.
            MemList *next = mem_list_root;
            while(next) {
                if(!next->freed) { push_error_(ErrorType_memory_not_freed, next->guid); }

                next = next->next;
            }
#endif
            // Output errors.
        }

        //if(should_log_errors) {
        //    Bool any_errors = print_errors();
        //    if(any_errors) { res = 255; }
        //}
    }

    Uint64 end_time = system_get_performance_counter();
    if(display_time_taken) { system_print_timer(end_time - start_time); }

    return(res);
}


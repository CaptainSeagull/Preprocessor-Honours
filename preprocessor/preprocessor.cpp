/*===================================================================================================
  File:                    preprocessor.cpp
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
    - Typedefs.
    - Base type macro. If the programmer enters non-pointer (or non reference) value, just return the same value.
    - Make a variable_to_string macro (#define var_to_string(v) #v).
    - Make a is_primitive function.
    - Make a function tell if something's a pointer or not. Could return false if not a pointer, and a positive integer
      for the level of pointer otherwise. Should work with references too.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#if defined(_MSC_VER)
    #define my_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)
#else
    #define my_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)
#endif

typedef uint64_t Uint64;
typedef uint32_t Uint32;
typedef uint16_t Uint16;
typedef uint8_t Uint8;

typedef int64_t Int64;
typedef int32_t Int32;
typedef int16_t Int16;
typedef int8_t Int8;

typedef bool Bool;
typedef void Void;
typedef char Char;

typedef Int32 Int; // Int guaranteed to be bits = 32.

typedef Uint8 Byte;
typedef intptr_t PtrSize;

typedef float Float;
typedef double Float64;

#define cast(type) (type)

#define array_count(arr) (sizeof(arr) / (sizeof(*(arr))))

//
// Error stuff.
//
enum ErrorType {
    ErrorType_ran_out_of_memory,
    ErrorType_assert_failed,
    ErrorType_no_parameters,
    ErrorType_cannot_find_file,
    ErrorType_could_not_write_to_disk,
    ErrorType_could_not_load_file,
    ErrorType_no_files_pass_in,
    ErrorType_could_not_find_mallocd_ptr,
    ErrorType_memory_not_freed,
    ErrorType_could_not_detect_struct_name,
    ErrorType_could_not_find_struct,
    ErrorType_unknown_token_found,
    ErrorType_failed_to_parse_enum,
    ErrorType_failed_parsing_variable,
    ErrorType_failed_to_find_size_of_array,

    ErrorType_count,
};
Char *ErrorTypeToString(ErrorType e) {
    Char *res = 0;

#define ERROR_TYPE_TO_STRING(err) err: { res = #err; } break

    switch(e) {
        case ERROR_TYPE_TO_STRING(ErrorType_ran_out_of_memory);
        case ERROR_TYPE_TO_STRING(ErrorType_assert_failed);
        case ERROR_TYPE_TO_STRING(ErrorType_no_parameters);
        case ERROR_TYPE_TO_STRING(ErrorType_cannot_find_file);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_write_to_disk);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_load_file);
        case ERROR_TYPE_TO_STRING(ErrorType_no_files_pass_in);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_find_mallocd_ptr);
        case ERROR_TYPE_TO_STRING(ErrorType_memory_not_freed);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_find_struct);
        case ERROR_TYPE_TO_STRING(ErrorType_unknown_token_found);
        case ERROR_TYPE_TO_STRING(ErrorType_failed_to_parse_enum);
        case ERROR_TYPE_TO_STRING(ErrorType_failed_parsing_variable);
        case ERROR_TYPE_TO_STRING(ErrorType_failed_to_find_size_of_array);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_detect_struct_name);
    }

#undef ERROR_TYPE_TO_STRING

    return(res);
}

struct Error {
    ErrorType type;
    Char *file;
    Int line;
};

Error global_errors[32];
Int global_error_count = 0;
#if ERROR_LOGGING
    #define push_error(type) push_error_(type, __FILE__, __LINE__)
#else
    #define push_error(type) {}
#endif

Void push_error_(ErrorType type, Char *file, Int line) {
    if(global_error_count + 1 < array_count(global_errors)) {
        Error *e = global_errors + global_error_count;

        e->type = type;
        e->file = file;
        e->line = line;

        ++global_error_count;
    }
}

#if INTERNAL
    #define assert(Expression, ...) do { static Bool Ignore = false; if(!Ignore) { if(!(Expression)) { push_error(ErrorType_assert_failed); *cast(int volatile *)0 = 0; } } } while(0)
#else
    #define assert(Expression, ...) {}
#endif

Uint32 safe_truncate_size_64(Uint64 v) {
    assert(v <= 0xFFFFFFFF);
    Uint32 res = cast(Uint32)v;

    return(res);
}

//
// System stuff.
//
#if WIN32
namespace win32 {
#include <windows.h>
}
#endif

Uint64 system_get_performance_counter(void) {
    Uint64 res = 0;

#if WIN32
    //res = win32::__rdtsc();
    win32::LARGE_INTEGER i;
    if(win32::QueryPerformanceCounter(&i)) { res = i.QuadPart; }
#else
    // TODO(Jonny): Implement.
#endif

    return(res);
}

Void system_print_timer(Uint64 value) {
#if WIN32
    win32::LARGE_INTEGER freq;
    if(win32::QueryPerformanceFrequency(&freq)) {
        Uint64 duration = value * 1000 / freq.QuadPart;
        printf("The program took %llums.\n", duration);
    }
#else
    // TODO(Jonny): Implement.
#endif
}

Bool system_check_for_debugger(void) {
    Bool res = false;
#if WIN32
    res = win32::IsDebuggerPresent() != 0;
#else

#endif

    return(res);
}

//
// Memory stuff.
//
#if MEM_CHECK
struct MemList {
    Void *ptr;
    MemList *next;
    Char *file;

    Int line;
    Bool freed;
};
MemList *mem_list_root = 0;
#endif

Void *get_raw_pointer(Void *ptr)  { return(cast(PtrSize *)ptr - 1);    }
PtrSize get_alloc_size(Void *ptr) { return(*(cast(PtrSize *)ptr - 1)); }
#define get_alloc_size_arr(ptr) (get_alloc_size(ptr) / sizeof(*(ptr)))

#define alloc(Type, ...) cast(Type *)alloc_(sizeof(Type), __FILE__, __LINE__, ##__VA_ARGS__)
Void *alloc_(PtrSize size, Char *file = 0, Int line = 0, PtrSize count = 1) {
    Void *res = 0;

    size *= count;
    PtrSize *raw_ptr = cast(PtrSize *)malloc(size + sizeof(PtrSize) * 1);
    if(!raw_ptr) {
        if(file) { push_error_(ErrorType_ran_out_of_memory, file, line); }
        else     { push_error_(ErrorType_ran_out_of_memory, __FILE__, __LINE__); }
    } else {
        *raw_ptr = size;
        res = (raw_ptr + 1);
        memset(res, 0, size);
    }
#if MEM_CHECK
    if(res) {
        MemList *cur = cast(MemList *)malloc(sizeof(MemList));
        if(!cur) { push_error(ErrorType_ran_out_of_memory); }
        else {
            memset(cur, 0, sizeof(MemList));
            cur->ptr = res;
            cur->file = file;
            cur->line = line;

            if(!mem_list_root) { mem_list_root = cur; }
            else {
                MemList *next = mem_list_root;
                while(next->next) { next = next->next; }

                next->next = cur;
            }
        }
    }
#endif

#if MEM_CHECK
    if(res) { assert(get_alloc_size(res) == size); }
#endif

    return(res);
}

// Free Memory.
Void free_(Void *ptr) {
#if MEM_CHECK
    if(ptr) {
        Void *raw_ptr = get_raw_pointer(ptr);
        free(raw_ptr);

        Bool found = false;
        MemList *next = mem_list_root;
        while(next) {
            if(next->ptr == ptr) {
                found = true;
                next->freed = true;
            }

            next = next->next;
        }

        assert(found);
    }
#else
    if(ptr) {
        Void *raw_ptr = get_raw_pointer(ptr);
        free(raw_ptr);
    }
#endif
}

// realloc
Void *realloc_(Void *ptr, Char *file = 0, Int line = 0, PtrSize size = 0) {
    Void *res = 0;
    if(ptr) {
#if MEM_CHECK
        MemList *next = mem_list_root;
        while(next) {
            if(next->ptr == ptr) { break; } // while
            next = next->next;
        }

        if(!next) {
            if(file) { push_error_(ErrorType_could_not_find_mallocd_ptr, file, line); }
            else     { push_error(ErrorType_could_not_find_mallocd_ptr); }
        }
#endif
        PtrSize *old_raw_ptr = cast(PtrSize *)get_raw_pointer(ptr);
        PtrSize old_size = *old_raw_ptr;
        if(!size) { size = old_size * 2; }

        if(size <= old_size) {
            res = ptr;
        } else {
            PtrSize *raw_ptr = cast(PtrSize *)realloc(old_raw_ptr, size + sizeof(PtrSize) * 2);
            if(!raw_ptr) { push_error(ErrorType_ran_out_of_memory); }
            else {
                *cast(PtrSize *)raw_ptr = size;
                res = (PtrSize *)raw_ptr + 1;
                memset(cast(Char *)res + old_size, 0, size - old_size);
#if MEM_CHECK
                if(next) { next->ptr = res; }
#endif
            }
        }
    } else {
        if(!size) { size = sizeof(PtrSize); }

        res = alloc_(size, file, line);
    }

    return(res);
}

#define malloc(size) alloc_(size, __FILE__, __LINE__)
#define calloc(size, count) alloc_(size, __FILE__, __LINE__, count)
#define realloc(ptr, ...) realloc_(ptr, __FILE__, __LINE__, ##__VA_ARGS__)
#define free(ptr) free_(ptr)

// A quick-to-access temp region of memory. Should be frequently cleared.
Int scratch_memory_index = 0;
Int scratch_memory_size = 256 * 256;
Void *global_scratch_memory = 0;
Void *push_scratch_memory(Int size = scratch_memory_size) {
    if(!global_scratch_memory) { global_scratch_memory = malloc(scratch_memory_size + 256); } // Allocate a little extra, just in case.

    Void *res = 0;
    if(global_scratch_memory) {
        assert(get_alloc_size(global_scratch_memory) > scratch_memory_index + size);
        res = cast(Byte *)global_scratch_memory + scratch_memory_index;
        scratch_memory_index += size;
    }

    return(res);
}

Void clear_scratch_memory(void) {
    if(global_scratch_memory) {
        memset(global_scratch_memory, 0, scratch_memory_index);
        scratch_memory_index = 0;
    }
}

//
// Utils.
//
struct Tokenizer { Char *at; }; // TODO(Jonny): Might be nice to have a line variable in here.

Bool is_end_of_line(Char c) { return((c == '\n') || (c == '\r')); }
Bool is_whitespace(Char c) { return((c == ' ') || (c == '\t') || (c == '\v') || (c == '\f') || (is_end_of_line(c))); }
Void skip_to_end_of_line(Tokenizer *tokenizer) { while(is_end_of_line(*tokenizer->at)) { ++tokenizer->at; } }

Int string_length(Char *str) {
    Int res = 0;
    while(*str++) { ++res; }

    return(res);
}

Bool string_concat(Char *dest, Int len, Char *a, Int a_len, Char *b, Int b_len) {
    Bool res = false;

    if(len > a_len + b_len) {
        for(Int i = 0; (i < a_len); ++i) { *dest++ = *a++; }
        for(Int i = 0; (i < b_len); ++i) { *dest++ = *b++; }

        res = true;
    }

    return(res);
}

Bool string_compare(Char *a, Char *b, Int len) {
    for(Int i = 0; (i < len); ++i, ++a, ++b) { if(*a != *b) { return(false); } }

    return(true);
}

Bool string_compare(Char *a, Char *b) {
    for(;; ++a, ++b) {
        if((*a == 0) && (*b == 0)) { return(true);  }
        else if(*a != *b)          { return(false); }
    }
}

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
                "#define serialize_type(var, Type, buf, size) serialize_struct_<Type>(var, #var, 0, buf, size, 0)\n"
                "#define serialize(var, buf, size) serialize_type(var, decltype(var), buf, size)\n"
                "\n"
                "template <typename T>static size_t serialize_struct_(void *var, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written);\n"
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
                "        size_t bytes_written = serialize_struct_<T>(var, name, 0, buf, size, 0);\n"
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
                "template<typename T> static char const *type_to_string_(void);\n"
                "#define type_to_string(Type) type_to_string_<Type>()\n"
                "#define weak_type_to_string(Type) weak_type_to_string_<Type>()\n"
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

// TODO(Jonny): Rename some of these so they're more clear.
enum TokenType {
    TokenType_unknown,

    TokenType_open_paren,
    TokenType_close_paren,
    TokenType_colon,
    TokenType_close_param,
    TokenType_semi_colon,
    TokenType_asterisk,
    TokenType_open_bracket,
    TokenType_close_bracket,
    TokenType_open_brace,
    TokenType_close_brace,
    TokenType_open_angle_bracket,
    TokenType_close_angle_bracket,
    TokenType_hash,
    TokenType_equals,
    TokenType_comma,
    TokenType_tilde,
    TokenType_period,
    TokenType_ampersand,
    TokenType_var_args,

    TokenType_plus,
    TokenType_minus,
    TokenType_divide,

    TokenType_number,
    TokenType_identifier,
    TokenType_string,

    TokenType_error,

    TokenType_end_of_stream,
};

struct Token {
    Char *e;
    Int len;

    TokenType type;
};

struct String {
    Char *e;
    Int len;
};

String create_string(Char *str, Int len = 0) { String res = {str, (len) ? len : string_length(str)}; return(res); }
String token_to_string(Token token) { String res = { token.e, token.len }; return(res); }

Void token_to_string(Token token, Char *buf, Int size) {
    assert(size > token.len);
    for(Int i = 0; (i < token.len); ++i, ++buf) { *buf = token.e[i]; }

    *buf = 0;
}

Bool token_compare(Token a, Token b) {
    Bool res = false;

    if(a.len == b.len) {
        res = true;

        for(Int i = 0; (i < a.len); ++i) {
            if(a.e[i] != b.e[i]) {
                res = false;
                break; // for
            }
        }
    }

    return(res);
}

Bool string_compare(String a, String b) {
    Bool res = false;

    if(a.len == b.len) {
        res = true;

        for(Int i = 0; (i < a.len); ++i) {
            if(a.e[i] != b.e[i]) {
                res = false;
                break; // for
            }
        }
    }

    return(res);
}

Bool string_compare_array(String *a, String *b, Int len) {
    Bool res = true;
    for(Int i = 0; (i < len); ++i) {
        if(!string_compare(a[i], b[i])) {
            res = false;
            break; // for
        }
    }

    return(res);
}

Void eat_whitespace(Tokenizer *tokenizer) {
    for(;;) {
        if(is_whitespace(tokenizer->at[0])) { // Whitespace
            ++tokenizer->at;
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '/')) { // C++ comments.
            tokenizer->at += 2;
            while((tokenizer->at[0]) && (!is_end_of_line(tokenizer->at[0]))) { ++tokenizer->at; }
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '*')) { // C comments.
            tokenizer->at += 2;
            while((tokenizer->at[0]) && !((tokenizer->at[0] == '*') && (tokenizer->at[1] == '/'))) { ++tokenizer->at; }

            if(tokenizer->at[0] == '*') { tokenizer->at += 2; }
        } else if(tokenizer->at[0] == '#') { // #if 0 blocks.
            Char *hash_if_zero = "#if 0";
            Int hash_if_zero_length = string_length(hash_if_zero);

            Char *hash_if_one = "#if 1";
            Int hash_if_one_length = string_length(hash_if_one);

            if(string_compare(tokenizer->at, hash_if_zero, hash_if_zero_length)) {
                tokenizer->at += hash_if_zero_length;

                Char *hash_end_if = "#endif";
                Int hash_end_if_length = string_length(hash_end_if);

                Int level = 0;
                while(++tokenizer->at) {
                    if(tokenizer->at[0] == '#') {
                        if((tokenizer->at[1] == 'i') && (tokenizer->at[2] == 'f')) {
                            ++level;

                        } else if(string_compare(tokenizer->at, hash_end_if, hash_end_if_length)) {
                            if(level) {
                                --level;
                            } else {
                                tokenizer->at += hash_end_if_length;
                                eat_whitespace(tokenizer);

                                break; // for
                            }
                        }
                    }
                }
            } else if(string_compare(tokenizer->at, hash_if_one, hash_if_one_length)) { // #if 1 #else blocks.
                tokenizer->at += hash_if_zero_length;

                Char *hash_else = "#else";
                Int hash_else_length = string_length(hash_else);

                Char *hash_end_if = "#endif";
                Int hash_end_if_length = string_length(hash_end_if);

                Int level = 0;
                while(++tokenizer->at) {
                    if(tokenizer->at[0] == '#') {
                        if((tokenizer->at[1] == 'i') && (tokenizer->at[2] == 'f')) {
                            ++level;
                        } else if(string_compare(tokenizer->at, hash_end_if, hash_end_if_length)) {
                            if(level != 0) {
                                --level;
                            } else {
                                tokenizer->at += hash_end_if_length;
                                break; // for
                            }
                        } else if(string_compare(tokenizer->at, hash_else, hash_else_length)) {
                            if(level == 0) {
                                tokenizer->at += hash_else_length;
                                Int Level2 = 0;

                                while(++tokenizer->at) {
                                    if(tokenizer->at[0] == '#') {
                                        if((tokenizer->at[1] == 'i') && (tokenizer->at[2] == 'f')) {
                                            ++Level2;

                                        } else if(string_compare(tokenizer->at, hash_end_if, hash_end_if_length)) {
                                            if(Level2 != 0) {
                                                --Level2;
                                            } else {
                                                tokenizer->at += hash_end_if_length;
                                                eat_whitespace(tokenizer);

                                                break; // for
                                            }
                                        }
                                    }

                                    tokenizer->at[0] = ' ';
                                }

                                break; // for
                            }
                        }
                    }
                }
            }

            break; // for
        } else {
            break; // for
        }
    }
}

Bool is_alphabetical(Char c) { return(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))); }
Bool is_num(Char c) { return((c >= '0') && (c <= '9')); }
Void parse_number(Tokenizer *tokenizer) { /* TODO(Jonny): Implement. */ }

struct MacroData {
    String iden;
    String res;
};
Int macro_count = 0;
MacroData *macro_data = 0;

Token get_token(Tokenizer *tokenizer); // Because C++...
#define eat_token(tokenizer) eat_tokens(tokenizer, 1);
Void eat_tokens(Tokenizer *tokenizer, Int num_tokens_to_eat) { for(Int i = 0; (i < num_tokens_to_eat); ++i) { get_token(tokenizer); } }

TokenType get_token_type(String s) {
    assert(s.len);

    TokenType res = TokenType_unknown;
    switch(s.e[0]) {
        case 0:    { res = TokenType_end_of_stream;       } break;

        case '(':  { res = TokenType_open_paren;          } break;
        case ')':  { res = TokenType_close_param;         } break;
        case ':':  { res = TokenType_colon;               } break;
        case ';':  { res = TokenType_semi_colon;          } break;
        case '*':  { res = TokenType_asterisk;            } break;
        case '[':  { res = TokenType_open_bracket;        } break;
        case ']':  { res = TokenType_close_bracket;       } break;
        case '{':  { res = TokenType_open_brace;          } break;
        case '}':  { res = TokenType_close_brace;         } break;
        case '<':  { res = TokenType_open_angle_bracket;  } break;
        case '>':  { res = TokenType_close_angle_bracket; } break;
        case '=':  { res = TokenType_equals;              } break;
        case ',':  { res = TokenType_comma;               } break;
        case '~':  { res = TokenType_tilde;               } break;
        case '#':  { res = TokenType_hash;                } break;
        case '&':  { res = TokenType_ampersand;           } break;
        case '+':  { res = TokenType_plus;                } break;
        case '-':  { res = TokenType_minus;               } break;
        case '/':  { res = TokenType_divide;              } break;

        default: {
            if(is_num(s.e[0])) { res = TokenType_number;     }
            else               { res = TokenType_identifier; }
        } break;
    }

    return(res);
}

Token string_to_token(String str) {
    Token res = {};

    res.e = str.e;
    res.len = str.len;

    // TODO(Jonny): This isn't foolproof.
    switch(res.e[0]) {
        case 0:    { res.type = TokenType_end_of_stream;       } break;

        case '(':  { res.type = TokenType_open_paren;          } break;
        case ')':  { res.type = TokenType_close_param;         } break;
        case ':':  { res.type = TokenType_colon;               } break;
        case ';':  { res.type = TokenType_semi_colon;          } break;
        case '*':  { res.type = TokenType_asterisk;            } break;
        case '[':  { res.type = TokenType_open_bracket;        } break;
        case ']':  { res.type = TokenType_close_bracket;       } break;
        case '{':  { res.type = TokenType_open_brace;          } break;
        case '}':  { res.type = TokenType_close_brace;         } break;
        case '<':  { res.type = TokenType_open_angle_bracket;  } break;
        case '>':  { res.type = TokenType_close_angle_bracket; } break;
        case '=':  { res.type = TokenType_equals;              } break;
        case ',':  { res.type = TokenType_comma;               } break;
        case '~':  { res.type = TokenType_tilde;               } break;
        case '#':  { res.type = TokenType_hash;                } break;
        case '&':  { res.type = TokenType_ampersand;           } break;
        case '+':  { res.type = TokenType_plus;                } break;
        case '-':  { res.type = TokenType_minus;               } break;
        case '/':  { res.type = TokenType_divide;              } break;

        default: {
            if(is_num(res.e[0])) { res.type = TokenType_number;     }
            else                 { res.type = TokenType_identifier; }
        } break;
    }

    return(res);
}

Token get_token(Tokenizer *tokenizer) {
    eat_whitespace(tokenizer);

    Token res = {};
    res.len = 1;
    res.e = tokenizer->at;
    Char c = tokenizer->at[0];
    ++tokenizer->at;

    switch(c) {
        case 0:    { res.type = TokenType_end_of_stream;       } break;

        case '(':  { res.type = TokenType_open_paren;          } break;
        case ')':  { res.type = TokenType_close_param;         } break;
        case ':':  { res.type = TokenType_colon;               } break;
        case ';':  { res.type = TokenType_semi_colon;          } break;
        case '*':  { res.type = TokenType_asterisk;            } break;
        case '[':  { res.type = TokenType_open_bracket;        } break;
        case ']':  { res.type = TokenType_close_bracket;       } break;
        case '{':  { res.type = TokenType_open_brace;          } break;
        case '}':  { res.type = TokenType_close_brace;         } break;
        case '<':  { res.type = TokenType_open_angle_bracket;  } break;
        case '>':  { res.type = TokenType_close_angle_bracket; } break;
        case '=':  { res.type = TokenType_equals;              } break;
        case ',':  { res.type = TokenType_comma;               } break;
        case '~':  { res.type = TokenType_tilde;               } break;
        case '#':  { res.type = TokenType_hash;                } break;
        case '&':  { res.type = TokenType_ampersand;           } break;
        case '+':  { res.type = TokenType_plus;                } break;
        case '-':  { res.type = TokenType_minus;               } break;
        case '/':  { res.type = TokenType_divide;              } break;

        case '.':  {
            Bool var_args = false;
            Tokenizer tokenizer_copy = *tokenizer;
            Token next = get_token(&tokenizer_copy);
            if(next.type == TokenType_period) {
                next = get_token(&tokenizer_copy);
                if(next.type == TokenType_period) {
                    var_args = true;

                    res.type = TokenType_var_args;
                    res.len = 3;

                    eat_tokens(tokenizer, 2);
                }
            }

            if(!var_args) { res.type = TokenType_period; }
        } break;

        case '"': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '"')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { ++tokenizer->at; }
                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '"') { ++tokenizer->at; }
        } break;

        case '\'': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '\'')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { ++tokenizer->at; }
                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '\'') { ++tokenizer->at; }
        } break;

        default: {
            if((is_alphabetical(c)) || (tokenizer->at[0] == '_')) {
                while((is_alphabetical(tokenizer->at[0])) || (is_num(tokenizer->at[0])) || (tokenizer->at[0] == '_')) {
                    ++tokenizer->at;
                }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_identifier;
            } else if(is_num(c)) {
                while(is_num(tokenizer->at[0])) { ++tokenizer->at; }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_number;
            } else {
                res.type = TokenType_unknown;
            }
        } break;
    }

    if(res.type == TokenType_identifier) {
        Bool changed = false;
        do {
            changed = false;
            for(Int i = 0; (i < macro_count); ++i) {
                MacroData *md = macro_data + i;

                String token_as_string = token_to_string(res);
                if(string_compare(token_as_string, md->iden)) {
                    res = string_to_token(md->res);
                    changed = true;
                }
            }
        } while(changed);
    }

    if(res.type == TokenType_unknown) { push_error(ErrorType_unknown_token_found); }

    return(res);
}

Token peak_token(Tokenizer *tokenizer) {
    Tokenizer cpy = *tokenizer;
    Token res = get_token(&cpy);

    return(res);
}

// TODO(Jonny): Create a token_equals_keyword function. This could also test macro'd aliases for keywords,
//              as well as the actual keyword.

Bool token_equals(Token token, Char *str) {
    Bool res = false;

    Int len = string_length(str);
    if(len == token.len) { res = string_compare(token.e, str, len); }

    return(res);
}

struct ResultInt {
    Int e;
    Bool success;
};

ResultInt char_to_int(Char c) {
    ResultInt res = {};
    switch(c) {
        case '0': { res.e = 0; res.success = true; } break;
        case '1': { res.e = 1; res.success = true; } break;
        case '2': { res.e = 2; res.success = true; } break;
        case '3': { res.e = 3; res.success = true; } break;
        case '4': { res.e = 4; res.success = true; } break;
        case '5': { res.e = 5; res.success = true; } break;
        case '6': { res.e = 6; res.success = true; } break;
        case '7': { res.e = 7; res.success = true; } break;
        case '8': { res.e = 8; res.success = true; } break;
        case '9': { res.e = 9; res.success = true; } break;
    }

    return(res);
}

ResultInt string_to_int(String str) {
    ResultInt res = {};

    for(Int i = 0; (i < str.len); ++i) {
        ResultInt temp_int = char_to_int(str.e[i]);
        if(!temp_int.success) { break; } // for

        res.e *= 10;
        res.e += temp_int.e;

        if(i == str.len - 1) { res.success = true; }
    }

    return(res);
}

ResultInt token_to_int(Token t) {
    String str = token_to_string(t);
    ResultInt res = string_to_int(str);

    return(res);
}

ResultInt string_to_int(Char *str) {
    String string;
    string.e = str;
    string.len = string_length(str);
    ResultInt res = string_to_int(string);

    return(res);
}

ResultInt calculator_string_to_int(Char *str) {
    ResultInt res = {};

    /* TODO(Jonny);
        - Make sure each element in the string is either a number or a operator.
        - Do the calculator in order (multiply, divide, add, subtract).
    */
    String *arr = alloc(String, 256); // TODO(Jonny): Random size.
    if(arr) {
        Char *at = str;
        arr[0].e = at;
        Int cnt = 0;
        for(; (*at); ++at, ++arr[cnt].len) {
            if(*at == ' ') {
                ++at;
                arr[++cnt].e = at;
            }
        }
        ++cnt;

        Int *nums = alloc(Int, cnt);
        Char *ops = alloc(Char, cnt);
        if((nums) && (ops)) {
            for(Int i = 0, j = 0; (j < cnt); ++i, j += 2) {
                ResultInt r = string_to_int(arr[j]);
                if(r.success) { nums[i] = r.e; }
                else          { goto clean_up; }
            }

            for(Int i = 0, j = 1; (j < cnt); ++i, j += 2) {
                assert(arr[j].len == 1);
                ops[i] = *arr[j].e;
            }

            // TODO(Jonny): At this point, I have all the numbers and ops in seperate arrays.

clean_up:;
            free(ops);
            free(nums);
        }

        free(arr);
    }

    return(res);
}

struct Variable {
    String type;
    String name;
    Bool is_ptr;
    Int array_count; // This is 1 if it's not an array. TODO(Jonny): Is this true anymore?
};

Variable create_variable(Char *type, Char *name, Bool is_ptr = false, Int array_count = 1) {
    Variable res;
    res.type = create_string(type);
    res.name = create_string(name);
    res.is_ptr = is_ptr;
    res.array_count = array_count;

    return(res);
}

Bool compare_variable(Variable a, Variable b) {
    Bool res = true;

    if(!string_compare(a.type, b.type))      { res = false; }
    else if(!string_compare(a.name, b.name)) { res = false; }
    else if(a.is_ptr != b.is_ptr)            { res = false; }
    else if(a.array_count != b.array_count)  { res = false; }

    return(res);
}

Bool compare_variable_array(Variable *a, Variable *b, Int count) {
    for(Int i = 0; (i < count); ++i) {
        if(!compare_variable(a[i], b[i])) { return(false); }
    }

    return(true);
}

Variable parse_member(Tokenizer *tokenizer) {
    Variable res = {};
    res.array_count = 1;
    res.type = token_to_string(get_token(tokenizer));

    Bool parsing = true;
    while(parsing) {
        Token token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_asterisk:                                 { res.is_ptr = true;                 } break;
            case TokenType_identifier:                               { res.name = token_to_string(token); } break;
            case TokenType_semi_colon: case TokenType_end_of_stream: { parsing = false;                   } break;

            case TokenType_open_bracket: {
                Token size_token = get_token(tokenizer);
                if(size_token.type == TokenType_number) {
                    Char *buffer = cast(Char *)push_scratch_memory();

                    token_to_string(size_token, buffer, scratch_memory_size);
                    ResultInt arr_count = string_to_int(buffer);
                    if(arr_count.success) { res.array_count = arr_count.e;                      }
                    else                  { push_error(ErrorType_failed_to_find_size_of_array); }

                    clear_scratch_memory();
                } else {
                    // TODO(Jonny): Something _bad_ happened...
                }
            } break;
        }
    }

    return(res);
}

// TODO(Jonny): This eats a token. Should it?
Bool require_token(Tokenizer *tokenizer, TokenType desired_type) {
    Token token = get_token(tokenizer);
    Bool res = (token.type == desired_type);

    return(res);
}

Bool peak_require_token(Tokenizer *tokenizer, Char *str) {
    Bool res = false;
    Tokenizer cpy = *tokenizer;
    Token token = get_token(&cpy);

    if(string_compare(token.e, str, token.len)) { res = true; }

    return(res);
}

Bool is_stupid_class_keyword(Token t) {
    Char *keywords[] = { "private", "public", "protected" };
    for(Int i = 0; (i < array_count(keywords)); ++i) {
        if(string_compare(keywords[i], t.e, t.len)) { return(true); }
    }

    return(false);
}

struct FunctionData {
    String linkage;
    String ret_type;
    String name;
    Variable params[32];
    Int param_count;
};

enum StructType { StructType_unknown, StructType_struct, StructType_class, StructType_count };

struct StructData {
    String name;
    Int member_count;
    Variable *members;

    Int inherited_count;
    String *inherited;

    StructType struct_or_class;

    //FunctionData *func_data;
    //Int func_count;
};

Void skip_to_matching_bracket(Tokenizer *tokenizer) {
    Int brace_count = 1;
    Token token = {};
    Bool should_loop = true;
    while(should_loop) {
        token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_open_brace: { ++brace_count; } break;

            case TokenType_close_brace: {
                --brace_count;
                if(!brace_count) { should_loop = false; }
            } break;
        }
    }
}

Void parse_template(Tokenizer *tokenizer) {
    Int angle_bracket_count = 1;
    Token token;
    Bool should_loop = true;
    while(should_loop) {
        token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_open_angle_bracket: { ++angle_bracket_count; } break;

            case TokenType_close_angle_bracket: {
                --angle_bracket_count;
                if(!angle_bracket_count) { should_loop = false; }
            } break;
        }
    }
}

Variable parse_variable(Tokenizer *tokenizer, TokenType end_token_type_1, TokenType end_token_type_2 = TokenType_unknown) {
    Variable res = {};

    // Return type.
    Token token = get_token(tokenizer);
    res.type = token_to_string(token);

    // Is pointer?
    token = get_token(tokenizer);
    if(token.type == TokenType_asterisk) {
        res.is_ptr = true;
        token = get_token(tokenizer);
    }

    // Name.
    res.name = token_to_string(token);

    // Is array?
    token = peak_token(tokenizer);
    if((token.type != end_token_type_1) && (token.type != end_token_type_2)) {
        eat_token(tokenizer);
        if(token.type == TokenType_open_bracket) {
            token = get_token(tokenizer);
            ResultInt num = token_to_int(token);
            if(num.success) {
                res.array_count = num.e;
                eat_token(tokenizer); // Eat the second ']'.
            } else {
                push_error(ErrorType_failed_parsing_variable);
            }
        } else {
            push_error(ErrorType_failed_parsing_variable);
        }
    } else {
        res.array_count = 1;
    }

    // Skip over any assignment at the end.
    // TODO(Jonny): This won't work if a variable is assigned to a function.
    if(token.type == TokenType_equals) { eat_token(tokenizer); }

    return(res);
}

// TODO(Jonny): This needs some way to ignore member functions.

struct ParseStructResult {
    StructData sd;
    Bool success;
};
ParseStructResult parse_struct(Tokenizer *tokenizer, StructType struct_or_class) {
    ParseStructResult res = {};

    res.sd.struct_or_class = struct_or_class;

    Bool have_name = false;
    Token name = peak_token(tokenizer);
    if(name.type == TokenType_identifier) {
        have_name = true;
        res.sd.name = token_to_string(name);
        eat_token(tokenizer);
    }

    Token peaked_token = peak_token(tokenizer);
    if(peaked_token.type == TokenType_colon) {
        res.sd.inherited = alloc(String, 4);

        eat_token(tokenizer);

        Token next = get_token(tokenizer);
        while(next.type != TokenType_open_brace) {
            if(!(is_stupid_class_keyword(next)) && (next.type != TokenType_comma)) {
                if(res.sd.inherited_count + 1 >= cast(Int)(get_alloc_size(res.sd.inherited) / sizeof(String))) {
                    Void *p = realloc(res.sd.inherited);
                    if(p) { res.sd.inherited = cast(String *)p; }
                }

                res.sd.inherited[res.sd.inherited_count++] = token_to_string(next);
            }

            next = peak_token(tokenizer);
            if(next.type != TokenType_open_brace) { eat_token(tokenizer); }
        }
    }

    if(require_token(tokenizer, TokenType_open_brace)) {
        res.success = true;

        res.sd.member_count = 0;
        Char *member_pos[256] = {};
#if 0
        Int func_max = 8;
        res.sd.func_data = malloc_array(base_type(res.sd.func_data), func_max);
        if(!res.sd.func_data) {
            push_error(ErrorType_ran_out_of_memory);
        }
#endif
        for(;;) {
            Token token = get_token(tokenizer);
            if((!is_stupid_class_keyword(token))) {
                if((token.type != TokenType_colon) && (token.type != TokenType_tilde)) {
                    if(token.type == TokenType_close_brace) {
                        if(!have_name) {
                            name = get_token(tokenizer);
                            if(name.type == TokenType_identifier) { res.sd.name = token_to_string(name);                }
                            else                                  { push_error(ErrorType_could_not_detect_struct_name); }
                        }

                        break; // for
                    } else if(token.type == TokenType_hash) {
                        while(tokenizer->at[0] != '\n') { ++tokenizer->at; }
                    } else {
                        Bool is_func = false;

                        Tokenizer tokenizer_copy = *tokenizer;
                        Token temp = get_token(&tokenizer_copy);
                        while(temp.type != TokenType_semi_colon) {
                            if(temp.type == TokenType_open_paren) { is_func = true; }

                            if(temp.type == TokenType_open_brace) {
                                is_func = true;
                                break; // while
                            }

                            temp = get_token(&tokenizer_copy);
                        }

                        if(!is_func) { member_pos[res.sd.member_count++] = token.e;                                         }
                        else         { if(temp.type == TokenType_open_brace) { skip_to_matching_bracket(&tokenizer_copy); } }
                        /*
                        } else {
                            // This is commented out because I'm not sure I really _need_ member functions...
                            // TODO(Jonny): This fails for constructors (and probably destructors).
                            if(inline_func) {
                                skip_to_matching_bracket(&tokenizer_copy);
                            }

                            if(!token_compare(token, name)) {
                                // Get member function name and return type.
                                Tokenizer second_copy = *tokenizer;
                                FunctionData fd = {};
                                //fd.linkage = ;
                                fd.ret_type = token_to_string(token);
                                fd.name = token_to_string(get_token(&second_copy));

                                eat_token(&second_copy);

                                // Parse the parameters.
                                Token next = peak_token(&second_copy);
                                while(next.type != TokenType_close_param) {
                                    fd.params[fd.param_count++] = parse_variable(&second_copy, TokenType_comma, TokenType_close_param);

                                    next = peak_token(&second_copy);
                                    assert((next.type == TokenType_comma) || (next.type == TokenType_close_param));
                                    if(next.type == TokenType_comma) {
                                        eat_token(&second_copy);
                                    }
                                }

                                // Now store the function data.
                                res.sd.func_data[res.sd.func_count++] = fd;
                            }
                        }
                        */

                        *tokenizer = tokenizer_copy;
                    }
                }
            }
        }

        if(res.sd.member_count > 0) {
            res.sd.members = alloc(Variable, res.sd.member_count);
            if(res.sd.members) {
                for(Int i = 0; (i < res.sd.member_count); ++i) {
                    Tokenizer fake_tokenizer = { member_pos[i] };
                    res.sd.members[i] = parse_member(&fake_tokenizer);
                }
            }
        }
    }

    return(res);
}

struct EnumValue {
    String name;
    Int value;
};

struct EnumData {
    String name;
    String type;
    Bool is_struct;

    EnumValue *values;
    Int no_of_values;
};

struct ParseEnumResult {
    EnumData ed;
    Bool success;
};
ParseEnumResult parse_enum(Tokenizer *tokenizer) {
    ParseEnumResult res = {};

    Token name = get_token(tokenizer);
    Bool is_enum_struct = false;
    if((token_equals(name, "class")) || (token_equals(name, "struct"))) {
        is_enum_struct = true;
        name = get_token(tokenizer);
    }

    if(name.type == TokenType_identifier) {
        // If the enum has an underlying type, get it.
        Token underlying_type = {};
        Token next = get_token(tokenizer);
        if(next.type == TokenType_colon) {
            underlying_type = get_token(tokenizer);
            next = get_token(tokenizer);
        }

        if(next.type == TokenType_open_brace) {
            //res = add_token_to_enum(name, underlying_type, is_enum_struct, &tokenizer);
            assert(name.type == TokenType_identifier);
            assert((underlying_type.type == TokenType_identifier) || (underlying_type.type == TokenType_unknown));

            Token token = {};

            res.ed.is_struct = is_enum_struct;

            // If I call token_to_string here, Visual Studio 2010 ends up generating code which uses MOVAPS on unaligned memory
            // and crashes. So that's why I didn't...
            res.ed.name.e = name.e; res.ed.name.len = name.len;

            if(underlying_type.type == TokenType_identifier) { res.ed.type = token_to_string(underlying_type); }

            Tokenizer copy = *tokenizer;
            res.ed.no_of_values = 1;
            token = get_token(&copy);
            while(token.type != TokenType_close_brace) {
                // TODO(Jonny): It was stupid to count the number of commas. Instead, actually count
                //              the number of enums.
                if(token.type == TokenType_comma) {
                    Token tmp = get_token(&copy);
                    if(tmp.type == TokenType_identifier)       { ++res.ed.no_of_values; }
                    else if(tmp.type == TokenType_close_brace) { break;                 }
                }

                token = get_token(&copy);
            }

            res.ed.values = alloc(EnumValue, res.ed.no_of_values);
            if(res.ed.values) {
                for(Int i = 0, count = 0; (i < res.ed.no_of_values); ++i, ++count) {
                    EnumValue *ev = res.ed.values + i;

                    Token temp_token = {};
                    while(temp_token.type != TokenType_identifier) { temp_token = get_token(tokenizer); }

                    ev->name = token_to_string(temp_token);
                    if(peak_token(tokenizer).type == TokenType_equals) {
                        eat_token(tokenizer);
                        Token num = get_token(tokenizer);

                        ResultInt r = token_to_int(num);
                        if(r.success) { count = r.e;                                }
                        else          { push_error(ErrorType_failed_to_parse_enum); }
                    }

                    ev->value = count;
                }

                res.success = true;
            }
        }
    }


    return(res);
}

Void write_serialize_struct_implementation(Char *def_struct_code, OutputBuffer *ob) {
    Char *top =
        "// Function to serialize a struct to a char array buffer.\n"
        "template <typename T>static size_t\nserialize_struct_(void *var, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {\n"
        "    assert((name) && (buffer) && (buf_size > 0)); // Check params.\n"
        "\n"
        "    if(!indent) { memset(buffer + bytes_written, 0, buf_size - bytes_written); } // If this is the first time through, zero the buffer.\n"
        "\n"
        "    MemberDefinition *members_of_Something = get_members_of_<T>(); assert(members_of_Something); // Get the members_of pointer. \n"
        "    if(members_of_Something) {\n"
        "        // Setup the indent buffer.\n"
        "        char indent_buf[256] = {};\n"
        "        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }\n"
        "\n"
        "        // Write the name and the type.\n"
        "        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%s%%s %%s\", indent_buf, type_to_string(T), name);\n"
        "        indent += 4;\n"
        "\n"
        "        // Add 4 to the indent.\n"
        "        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }\n"
        "\n"
        "        int num_members = get_number_of_members_<T>(); assert(num_members != -1); // Get the number of members for the for loop.\n"
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
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(double *)member_ptr[j] : member_ptr[j]);\n"
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
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(float *)member_ptr[j] : member_ptr[j]);\n"
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
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(int *)member_ptr[j] : (int)member_ptr[j]);\n"
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
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%ld\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(long *)member_ptr[j] : (long)member_ptr[j]);\n"
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
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(short *)member_ptr[j] : (short)member_ptr[j]);\n"
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
        "                                size_t value_to_print = (member->is_ptr) ? **(bool **)(member_ptr + j) : member_ptr[j];\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool %%s%%s[%%d] = %%s\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (value_to_print) ? \"true\" : \"false\");\n"
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

struct ParseFunctionResult {
    FunctionData func_data;
    Bool success;
};
ParseFunctionResult attempt_to_parse_function(Tokenizer *tokenizer, Token token) {
    ParseFunctionResult res = {};

    // Try to parse as a function.
    Tokenizer copy_tokenizer = *tokenizer;
    Token linkage = {};
    Token return_type = {};
    if((token_equals(token, "static")) || (token_equals(token, "inline")) || (token_equals(token, "internal"))) { // TODO(Jonny): Having "internal" here is hacky...
        linkage = token;
        return_type = get_token(&copy_tokenizer);
    } else {
        return_type = token;
    }

    if(return_type.type == TokenType_identifier) {
        if((!token_equals(return_type, "if")) && (!token_equals(return_type, "do")) && (!token_equals(return_type, "while")) && (!token_equals(return_type, "switch"))) { // TODO(Jonny): Extra check...
            Token name = get_token(&copy_tokenizer);
            if(name.type == TokenType_identifier) {
                // Don't forward declare main.
                if((!token_equals(name, "main")) && (!token_equals(name, "WinMain")) && (!token_equals(name, "_mainCRTStartup")) && (!token_equals(name, "_WinMainCRTStartup")) && (!token_equals(name, "__DllMainCRTStartup"))) {
                    // Make sure we aren't parsing a if statement.
                    if((!token_equals(name, "if")) && (!token_equals(name, "do")) && (!token_equals(name, "while")) && (!token_equals(name, "for"))) {
                        if(((linkage.type == TokenType_identifier) && (!token_equals(linkage, "else"))) || (linkage.type == TokenType_unknown)) {
                            Token should_be_open_brace = get_token(&copy_tokenizer);
                            if(should_be_open_brace.type == TokenType_open_paren) {
                                res.success = true;

                                *tokenizer = copy_tokenizer;

                                if(linkage.type == TokenType_identifier) { res.func_data.linkage = token_to_string(linkage); }

                                res.func_data.ret_type = token_to_string(return_type);
                                res.func_data.name = token_to_string(name);

                                // Set the array size to 1 for all the variables...
                                for(Int i = 0; (i < array_count(res.func_data.params)); ++i) {
                                    res.func_data.params[i].array_count = 1;
                                }

                                Bool parsing = true;
                                Variable *var = res.func_data.params + res.func_data.param_count;

                                // If there aren't any parameters then just skip them.
                                {
                                    Tokenizer copy = *tokenizer;
                                    Token temp_token = get_token(&copy);
                                    if(token_equals(temp_token, "void")) {
                                        Token next = get_token(&copy);
                                        if(next.type == TokenType_close_param) { parsing = false; }
                                    }
                                }

                                // Parse the parameters.
                                while(parsing) {
                                    Token temp_token = get_token(tokenizer);
                                    switch(temp_token.type) {
                                        case TokenType_asterisk: { var->is_ptr = true; } break;

                                        case TokenType_comma: { ++var; } break;

                                        case TokenType_end_of_stream: case TokenType_open_brace: {
                                            parsing = false; // TODO(Jonny): Something baaaad happened...
                                        } break;

                                        case TokenType_open_bracket: {
                                            Token SizeToken = get_token(tokenizer);
                                            if(SizeToken.type == TokenType_number) {
                                                Char buffer[256] = {};
                                                token_to_string(SizeToken, buffer, array_count(buffer));
                                                ResultInt arr_count = string_to_int(buffer);
                                                if(arr_count.success) { var->array_count = arr_count.e; }
                                            }
                                        } break;

                                        case TokenType_identifier: {
                                            if(var->type.len == 0) {
                                                var->type = token_to_string(temp_token);
                                            } else {
                                                var->name = token_to_string(temp_token);
                                                ++res.func_data.param_count;
                                            }
                                        } break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

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
                               "\n"
                               "#include \"static_generated.h\"\n"
                               "\n",
                               name_buf, name_buf);

        clear_scratch_memory();

        // Forward declare structs.
        write_to_output_buffer(&ob,
                               "// Forward declared structs (these must be declared outside the namespace...)\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(sd->struct_or_class == StructType_struct)     { write_to_output_buffer(&ob, "struct %.*s;\n", sd->name.len, sd->name.e); }
            else if(sd->struct_or_class == StructType_class) { write_to_output_buffer(&ob, "class %.*s;\n", sd->name.len, sd->name.e); }
            else { assert(0); }
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "namespace pp { // PreProcessor\n");

        //
        // MetaTypes enum.
        //
        // Get the absolute max number of meta types. This will be significantly bigger than the
        // actual number of unique types...
        Int max_type_count = get_num_of_primitive_types();
        for(Int i = 0; (i < struct_count); ++i) { max_type_count += struct_data[i].member_count; }

        String *types = cast(String *)push_scratch_memory(sizeof(String) * max_type_count);

        Int type_count = set_primitive_type(types);

        // Fill out the enum meta type enum.
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(!is_meta_type_already_in_array(types, type_count, sd->name)) { types[type_count++] = sd->name; }

            for(Int j = 0; (j < sd->member_count); ++j) {
                Variable *md = sd->members + j;

                if(!is_meta_type_already_in_array(types, type_count, md->type)) { types[type_count++] = md->type; }
            }
        }

        // Write the meta type enum to file.
        write_to_output_buffer(&ob, "\n// Enum with field for every type detected.\n");
        write_to_output_buffer(&ob, "enum MetaType {\n");
        for(Int i = 0; (i < type_count); ++i) { write_to_output_buffer(&ob, "    MetaType_%.*s,\n", types[i].len, types[i].e); }

        write_to_output_buffer(&ob, "};");

        clear_scratch_memory();

        //
        // Struct Meta Data
        //

        // Recursive part for calling on members of structs.
        write_to_output_buffer(&ob, "\n\n");

        Int def_struct_code_size = scratch_memory_size;
        Char *def_struct_code = cast(Char *)push_scratch_memory(def_struct_code_size);
        if(def_struct_code) {
            Int index = 0;
            index = copy_literal_to_char_buffer(def_struct_code, index, "                    switch(member->type) {\n");
            for(Int i = 0; (i < struct_count); ++i) {
                StructData *sd = struct_data + i;
                Char *DefaultStructString =
                    "                        case MetaType_%.*s: {\n"
                    "                            // %.*s\n"
                    "                            if(member->is_ptr) {\n"
                    "                                bytes_written = serialize_struct_<%.*s *>(member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);\n"
                    "                            } else {\n"
                    "                                bytes_written = serialize_struct_<%.*s>(member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);\n"
                    "                            }\n"
                    "                        } break; // case MetaType_%.*s\n"
                    "\n";

                index += my_sprintf(def_struct_code + index, def_struct_code_size, DefaultStructString,
                                    sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e,
                                    sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e,
                                    sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e,
                                    sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e,
                                    sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            }

            index = copy_literal_to_char_buffer(def_struct_code, index, "                    } // switch(member->type)");
        }

        // Recreated structs.
        write_to_output_buffer(&ob, "// Recreated structs (Clang in std=C++98 complains if these are local).\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            write_to_output_buffer(&ob, "struct _%.*s", sd->name.len, sd->name.e);
            if(sd->inherited) {
                write_to_output_buffer(&ob, " :");

                for(Int j = 0; (j < sd->inherited_count); ++j) {
                    String *inherited = sd->inherited + j;

                    if(j) { write_to_output_buffer(&ob, ","); }

                    write_to_output_buffer(&ob, " public _%.*s", inherited->len, inherited->e);
                }
            }
            write_to_output_buffer(&ob, " { ");

            for(Int j = 0; (j < sd->member_count); ++j) {
                Variable *md = sd->members + j;
                Char *arr = cast(Char *)((md->array_count > 1) ? "[%u]" : "");
                Char arr_buffer[256] = {};
                if(md->array_count > 1) {
                    my_sprintf(arr_buffer, 256, arr, md->array_count);
                }

                write_to_output_buffer(&ob, " _%.*s %s%.*s%s; ",
                                       md->type.len, md->type.e,
                                       (md->is_ptr) ? "*" : "",
                                       md->name.len, md->name.e,
                                       (md->array_count > 1) ? arr_buffer : arr);

            }

            write_to_output_buffer(&ob, " };\n");
        }

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
                    write_to_output_buffer(&ob, "            {MetaType_%.*s, \"%.*s\", offset_of(&_%.*s::%.*s), %s, %d},\n",
                                           md->type.len, md->type.e,
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

                            write_to_output_buffer(&ob, "            {MetaType_%.*s, \"%.*s\", (size_t)&((_%.*s *)0)->%.*s, %s, %d},\n",
                                                   base_class_var->type.len, base_class_var->type.e,
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

        write_serialize_struct_implementation(def_struct_code, &ob);
        clear_scratch_memory();

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

        for(Int i = 0, written_count = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(sd->inherited_count) {
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


        write_to_output_buffer(&ob,
                               "    }\n"
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

            for(Int i = 0; (i < enum_count); ++i) {
                EnumData *ed = enum_data + i;
                write_to_output_buffer(&ob, "\n// Meta Data for %.*s.\n", ed->name.len, ed->name.e);

                Char type[32];
                if(ed->type.len) {
                    for(int i = 0; (i < ed->type.len); ++i) { type[i] = ed->type.e[i]; }
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
                    Int size = scratch_memory_size / 2;
                    Char *buf1 = cast(Char *)push_scratch_memory(size);
                    Char *buf2 = cast(Char *)push_scratch_memory(size);
                    Int index = 0;

                    for(int j = 0; (j < ed->no_of_values); ++j) {
                        index += my_sprintf(buf2 + index, size - index,
                                            "        case %d: { return(\"%.*s\"); } break;\n",
                                            ed->values[j].value,
                                            ed->values[j].name.len, ed->values[j].name.e);
                    }

                    Int bytes_written = my_sprintf(buf1, size,
                                                   "\nstatic char const *enum_to_string_%.*s(%s v) {\n"
                                                   "    switch(v) {\n"
                                                   "%s"
                                                   "    }\n"
                                                   "\n"
                                                   "    return(0); // v is out of bounds.\n"
                                                   "}\n",
                                                   ed->name.len, ed->name.e,
                                                   type,
                                                   buf2);
                    assert(bytes_written < size);

                    write_to_output_buffer(&ob, buf1);

                    clear_scratch_memory();
                }

                // string_to_enum.
                {
                    Int size = scratch_memory_size / 2;
                    Char *buf1 = cast(Char *)push_scratch_memory(size);
                    Char *buf2 = cast(Char *)push_scratch_memory(size);

                    Int index = 0;
                    for(int j = 0; (j < ed->no_of_values); ++j) {
                        if(!j) {
                            index += my_sprintf(buf2 + index, size - index,
                                                "        if(strcmp(str, \"%.*s\") == 0) { return(%d); }\n",
                                                ed->values[0].name.len, ed->values[0].name.e,
                                                ed->values[0].value);
                        } else {
                            index += my_sprintf(buf2 + index, size - index,
                                                "        else if(strcmp(str, \"%.*s\") == 0) { return(%d); }\n",
                                                ed->values[j].name.len, ed->values[j].name.e,
                                                ed->values[j].value);
                        }
                    }

                    my_sprintf(buf1, scratch_memory_size,
                               "static %s string_to_enum_%.*s(char const *str) {\n"
                               "    if(str) {\n"
                               "%s"
                               "    }\n"
                               "\n"
                               "    return(0);  // str didn't match.\n" // TODO(Jonny): Throw an error here?
                               "}\n",
                               type,
                               ed->name.len, ed->name.e, buf2);

                    write_to_output_buffer(&ob, buf1);

                    clear_scratch_memory();
                }
            }
        }

        //
        // # Guard macro.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "} // namespace pp\n"
                               "\n"
                               "#endif // Header guard.\n"
                               "\n");

        res.size = ob.index;
        res.data = ob.buffer;
    }

    return(res);
}

Bool should_write_to_file = false;

Void start_parsing(Char *fname, Char *file) {
    Int enum_count = 0;
    EnumData *enum_data = alloc(EnumData, 8);

    Int struct_count = 0;
    StructData *struct_data = alloc(StructData, 32);

    macro_data = alloc(MacroData, 32);

    if((enum_data)  && (struct_data) && (macro_data)) {
        Tokenizer tokenizer = { file };

        Bool parsing = true;
        while(parsing) {
            Token token = get_token(&tokenizer);
            switch(token.type) {
                case TokenType_end_of_stream: { parsing = false;                 } break;

                case TokenType_hash: {
                    if(peak_require_token(&tokenizer, "define")) {
                        eat_token(&tokenizer);

                        MacroData *md = macro_data + macro_count++;

                        md->iden = token_to_string(get_token(&tokenizer));
                        eat_whitespace(&tokenizer);
                        md->res.e = tokenizer.at;
                        while(!is_end_of_line(*tokenizer.at)) {
                            ++md->res.len;
                            ++tokenizer.at;
                        }
                    } else { skip_to_end_of_line(&tokenizer); }
                } break;

                case TokenType_identifier: {
                    // TODO(Jonny): I may need to keep the template header, so that the generated structs still work.
                    if(token_equals(token, "template")) {
                        eat_token(&tokenizer);
                        parse_template(&tokenizer);
                    } else if((token_equals(token, "struct")) || (token_equals(token, "class"))) {
                        StructType struct_or_class = token_equals(token, "struct") ? StructType_struct : StructType_class;
                        if(struct_count + 1 >= get_alloc_size_arr(struct_data)) {
                            Void *p = realloc(struct_data);
                            if(p) { struct_data = cast(StructData *)p; }
                        }

                        ParseStructResult r = parse_struct(&tokenizer, struct_or_class);

                        // TODO(Jonny): This fails at a struct declared within a struct/union.
                        if(r.success) { struct_data[struct_count++] = r.sd; }
                    } else if(token_equals(token, "enum")) {
                        if(enum_count + 1 >= get_alloc_size_arr(enum_data)) {
                            Void *p = realloc(enum_data);
                            if(p) { enum_data = cast(EnumData *)p; }
                        }

                        ParseEnumResult r = parse_enum(&tokenizer);
                        if(r.success) { enum_data[enum_count++] = r.ed; }
                    }
                } break;
            }
        }

        File file_to_write = write_data(fname, struct_data, struct_count, enum_data, enum_count);

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

        // Tidy up memory for the next pass. Can probably optimize this and reuse the memory.
        for(Int i = 0; (i < struct_count); ++i) { free(struct_data[i].members);   }
        for(Int i = 0; (i < struct_count); ++i) { free(struct_data[i].inherited); }
        free(struct_data);

        for(Int i = 0; (i < enum_count); ++i) { free(enum_data[i].values); }
        free(enum_data);

        free(macro_data);
    }
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
    ResultInt calc_res = calculator_string_to_int("1 + 2 * 3");
    if(calc_res.success) {
        int i = 0;
    }

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

        // Get the total amount of memory needed to store all files.


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
            free(global_scratch_memory);

            // Check memory leaks.
            MemList *next = mem_list_root;
            while(next) {
                if(!next->freed) { push_error_(ErrorType_memory_not_freed, next->file, next->line); }

                next = next->next;
            }
#endif
            // Output errors.
            if(global_error_count) {
                res = 255;

                if(should_log_errors) {
                    // TODO(Jonny): Write errors to disk.
                    fprintf(stderr, "\n\nList of errors:\n");
                    for(Int i = 0; (i < global_error_count); ++i) {
                        fprintf(stderr, "    Error %d:\n        Type = %s\n        File = %s\n        Line = %d\n",
                                i, ErrorTypeToString(global_errors[i].type), global_errors[i].file, global_errors[i].line);
                    }

                    if(system_check_for_debugger()) { assert(0); }
                }
            }
        }
    }

    Uint64 end_time = system_get_performance_counter();
    if(display_time_taken) { system_print_timer(end_time - start_time); }

    return(res);
}

//
// Tests
//
#if RUN_TESTS
#include "google_test/gtest.h"

//
// Test utils.
//
StructData parse_struct_test(Char *str, int ahead = 0) {
    Tokenizer tokenizer = {str};

    eat_token(&tokenizer);
    for(int i = 0; (i < ahead); ++i) {
        parse_struct(&tokenizer, StructType_struct);
        eat_token(&tokenizer);
        eat_token(&tokenizer);
    }

    return(parse_struct(&tokenizer, StructType_struct).sd);
}

enum StructCompareFailure {
    StructCompareFailure_success,

    StructCompareFailure_name,
    StructCompareFailure_member_count,
    StructCompareFailure_members,
    StructCompareFailure_inherited_count,
    StructCompareFailure_inherited,
    StructCompareFailure_func_data,
    StructCompareFailure_func_count,
};
Char *struct_compare_failure_to_string(StructCompareFailure scf) {
    Char *res = 0;
    if(scf == StructCompareFailure_success)           { res = "StructCompareFailure_success";      }
    else if(scf == StructCompareFailure_name)         { res = "StructCompareFailure_name";         }
    else if(scf == StructCompareFailure_member_count) { res = "StructCompareFailure_member_count"; }
    else if(scf == StructCompareFailure_members)      { res = "StructCompareFailure_members";      }
    else if(scf == StructCompareFailure_inherited)    { res = "StructCompareFailure_inherited";    }
    else if(scf == StructCompareFailure_func_data)    { res = "StructCompareFailure_func_data";    }
    else if(scf == StructCompareFailure_func_count)   { res = "StructCompareFailure_func_count";   }

    return(res);
};

StructCompareFailure compare_struct_data(StructData a, StructData b) {
    StructCompareFailure res = StructCompareFailure_success;

    if(!string_compare(a.name, b.name))                                         { res = StructCompareFailure_name;            }
    else if(a.member_count != b.member_count)                                   { res = StructCompareFailure_member_count;    }
    else if(!compare_variable_array(a.members, b.members, a.member_count))      { res = StructCompareFailure_members;         }
    else if(a.inherited_count != b.inherited_count)                             { res = StructCompareFailure_inherited_count; }
    else if(!string_compare_array(a.inherited, b.inherited, a.inherited_count)) { res = StructCompareFailure_inherited;       }

    return(res);
}

//
// Tests.
//

TEST(StructTest, basic_struct_test) {
    Char *basic_struct = "struct BasicStruct {\n"
                         "    int i;\n"
                         "    float *f;\n"
                         "    bool b[10];\n"
                         "    double *d[12];\n"
                         "};\n";

    StructData hardcoded = {};
    hardcoded.name = create_string("BasicStruct");
    hardcoded.member_count = 4;
    hardcoded.members = cast(Variable *)malloc(sizeof(Variable) * hardcoded.member_count);
    Int member_index = 0;
    hardcoded.members[member_index++] = create_variable("int", "i");
    hardcoded.members[member_index++] = create_variable("float", "f", true);
    hardcoded.members[member_index++] = create_variable("bool", "b", false, 10);
    hardcoded.members[member_index++] = create_variable("double", "d", true, 12);

    StructData generated = parse_struct_test(basic_struct);
    StructCompareFailure struct_compare_failure = compare_struct_data(hardcoded, generated);
    ASSERT_TRUE(struct_compare_failure == StructCompareFailure_success)
            << "Failed because struct_compare_failure == " << struct_compare_failure_to_string(struct_compare_failure);
}

TEST(StructTest, inhertiance_struct_test) {
    Char *inheritance_struct = "struct BaseOne { int a; };\n"
                               "struct BaseTwo { int b; };\n"
                               "struct Sub : public BaseOne, public BaseTwo { int c; };";

    StructData hardcoded = {};
    hardcoded.name = create_string("Sub");
    hardcoded.member_count = 1;
    hardcoded.members = cast(Variable *)malloc(sizeof(Variable));
    *hardcoded.members = create_variable("int", "c");
    hardcoded.inherited_count = 2;
    hardcoded.inherited = alloc(String, hardcoded.inherited_count);
    hardcoded.inherited[0] = create_string("BaseOne");
    hardcoded.inherited[1] = create_string("BaseTwo");

    StructData generated = parse_struct_test(inheritance_struct, 2);
    StructCompareFailure struct_compare_failure = compare_struct_data(hardcoded, generated);
    ASSERT_TRUE(struct_compare_failure == StructCompareFailure_success)
            << "Failed because struct_compare_failure == " << struct_compare_failure_to_string(struct_compare_failure);
}

TEST(StructTest, number_of_members_test) {
    Char *str = "struct A { int a; int b; int c; };";
    StructData gen = parse_struct_test(str);
    ASSERT_TRUE(gen.member_count == 3) << "Error: Number of members in struct not correct";
}

TEST(StructTest, struct_name) {
    Char *str = "struct my_name {};";
    StructData gen = parse_struct_test(str);
    ASSERT_TRUE(string_compare("my_name", gen.name.e, gen.name.len)) << "Error: Failed to properly generate struct name.";
}

EnumData parse_enum_test(Char *str) {
    Tokenizer tokenizer = {str};

    eat_token(&tokenizer);
    return(parse_enum(&tokenizer).ed);
}

TEST(EnumTest, enum_name_test) {
    Char *str = "enum MyName {};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(string_compare("MyName", gen.name.e, gen.name.len)) << "Error: Failed to properly generate enum name.";
}

TEST(EnumTest, enum_type_test) {
    Char *str = "enum Enum : short {};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(string_compare("short", gen.type.e, gen.type.len)) << "Error: Failed to properly handle enum type.";
}

TEST(EnumTest, enum_class_test) {
    Char *str = "enum class Enum {};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(gen.is_struct) << "Error: Failed to properly handle an enum class.";
}

TEST(EnumTest, enum_number_of_values_test) {
    Char *str = "enum Nums {one, two, three};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(gen.no_of_values == 3) << "Error: Did not generate the correct number of values for an enum.";
}

Int run_tests(void) {
    Int res = 0;
    // Google test uses so much memory, it's difficult to run in x86.
    if(sizeof(PtrSize) == 8) {
        Char *flags[] = {"--gtest_break_on_failure", "--gtest_catch_exceptions=0"};
        Int number_of_flags = array_count(flags);

        testing::InitGoogleTest(&number_of_flags, flags);
        res = RUN_ALL_TESTS();
    }

    return(res);
}

#endif


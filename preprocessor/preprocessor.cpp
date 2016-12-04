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
    - Completly skip over member functions!
    - Struct meta data.
        - Multiple inheritance.
    - Enum meta data.
        - Way to find count.
        - string_to_enum and enum_to_string functions.
    - Union meta data.
        - Similar to struct.
    - Function meta data.
        - Get param type as typedef and string.
        - Get return type as typedef and string.
    - References.
    - Templates.
    - Macros.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

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

typedef Int32 Int; // Int guaranteed to be 32-bits.

typedef Uint8 Byte;
typedef intptr_t PtrSize;

typedef float Float;
typedef double Float64;

#define internal static
#define persist static
#define global static

#define cast(type) (type)

#define array_count(arr) (sizeof(arr) / (sizeof((arr)[0])))

//
// Error stuff.
//
enum ErrorType {
    ErrorType_ran_out_of_memory,
    ErrorType_assert_failed,
    ErrorType_no_parameters,
    ErrorType_cannot_find_file,
    ErrorType_could_not_write_to_disk,
    ErrorType_no_files_pass_in,
    ErrorType_could_not_find_mallocd_ptr,
    ErrorType_memory_not_freed,

    ErrorType_count,
};
internal Char *
ErrorTypeToString(ErrorType e)
{
    Char *res = 0;
    switch(e) {
        case ErrorType_ran_out_of_memory:          { res = "ErrorType_ran_out_of_memory";          } break;
        case ErrorType_assert_failed:              { res = "ErrorType_assert_failed";              } break;
        case ErrorType_no_parameters:              { res = "ErrorType_no_parameters";              } break;
        case ErrorType_cannot_find_file:           { res = "ErrorType_cannot_find_file";           } break;
        case ErrorType_could_not_write_to_disk:    { res = "ErrorType_could_not_write_to_disk";    } break;
        case ErrorType_no_files_pass_in:           { res = "ErrorType_no_files_pass_in";           } break;
        case ErrorType_could_not_find_mallocd_ptr: { res = "ErrorType_could_not_find_mallocd_ptr"; } break;
        case ErrorType_memory_not_freed:           { res = "ErrorType_memory_not_freed";           } break;
    }

    return(res);
}

struct Error {
    ErrorType type;
    Char *file;
    Int line;
};

global Int const error_max = 256;
global Error global_errors[error_max] = {};
global Int global_error_count = 0;

#if ERROR_LOGGING
    #define push_error(type) push_error_(type, __FILE__, __LINE__)
#else
    #define push_error(type) {}
#endif

internal Void
push_error_(ErrorType type, Char *file, Int line)
{
    if(global_error_count + 1 < error_max) {
        Error *e = global_errors + global_error_count;

        e->type = type;
        e->file = file;
        e->line = line;

        ++global_error_count;
    }
}

#if defined(assert)
    #undef assert
#endif
#if INTERNAL
    #define assert(Expression, ...) do { persist Bool Ignore = false; if(!Ignore) { if(!(Expression)) { push_error(ErrorType_assert_failed); *cast(int volatile *)0 = 0; } } } while(0)
#else
    #define assert(Expression, ...) { if(!(Expression)) { push_error(ErrorType_assert_failed); } }
#endif

internal Uint32
safe_truncate_size_64(Uint64 value)
{
    assert(value <= 0xFFFFFFFF);
    Uint32 res = cast(Uint32)value;

    return(res);
}

//
// Memory stuff.
//
#if INTERNAL
struct MemList {
    Void *ptr;
    PtrSize size;

    MemList *next;
    Bool freed;

    Char *file;
    Int line;
};
global MemList *mem_list_root = 0;
#endif

internal PtrSize
get_alloc_size(Void *ptr)
{
    PtrSize res = 0;
    if(ptr) {
        PtrSize *raw_ptr = cast(PtrSize *)ptr;
        --raw_ptr;
        res = *raw_ptr;
    }

    return(res);
}

internal Void *
get_raw_pointer(Void *ptr)
{
    PtrSize *raw_ptr = cast(PtrSize *)ptr;
    --raw_ptr;
    Void *res = cast(Void *)raw_ptr;

    return(res);
}

// malloc
internal Void *
malloc_(PtrSize size, Char *file, Int line)
{
    Void *res = 0;
    PtrSize *raw_ptr = cast(PtrSize *)calloc(size + sizeof(PtrSize), 1);
    if(!raw_ptr) {
        push_error_(ErrorType_ran_out_of_memory, file, line);
    } else {
        *raw_ptr = size;
        res = ++raw_ptr;
    }
#if INTERNAL
    if(res) {
        MemList *cur = cast(MemList *)calloc(sizeof(MemList), 1);

        cur->ptr = res;
        cur->size = size;
        cur->file = file;
        cur->line = line;

        if(!mem_list_root) {
            mem_list_root = cur;
        } else {
            MemList *next = mem_list_root;
            while(next->next) {
                next = next->next;
            }

            next->next = cur;
        }
    }
#endif

    return(res);
}
#define malloc_array(Type, size) cast(Type *)malloc_(sizeof(Type) * (size), __FILE__, __LINE__)
#define malloc_type(Type) cast(Type *)malloc_(sizeof(Type), __FILE__, __LINE__)

// free
internal Void
free_(Void *ptr, Char *file, Int line)
{
#if INTERNAL
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
internal Void *
realloc_(Void *ptr, PtrSize size, Char *file, Int line)
{
    Void *res = 0;
#if INTERNAL
    if(ptr) {
        MemList *next = mem_list_root;
        while(next) {
            if(next->ptr == ptr) {
                break; // while
            }

            next = next->next;
        }

        if(!next) {
            push_error_(ErrorType_could_not_find_mallocd_ptr, file, line);
        } else {
            PtrSize *old_raw_ptr = cast(PtrSize *)get_raw_pointer(ptr);
            PtrSize old_size = *old_raw_ptr;

            PtrSize *new_raw_ptr = cast(PtrSize *)realloc(old_raw_ptr, size);
            if(!new_raw_ptr) {
                push_error(ErrorType_ran_out_of_memory);
            } else {
                ++new_raw_ptr;
                res = cast(Void *)new_raw_ptr;
                memset(new_raw_ptr + old_size, 0, size - old_size);

                next->ptr = res;
                next->size = size;

                // TODO(Jonny): Should I do this?
                next->file = file;
                next->line = line;
            }
        }
    } else {
        res = malloc_(size, file, line);
    }
#else
    res = realloc(ptr, size);
    if(!res) {
        push_error(ErrorType_ran_out_of_memory);
    }

#endif
    return(res);
}

#if defined(malloc)
    #undef malloc
#endif
#define malloc(size) malloc_(size, __FILE__, __LINE__)

#if defined(free)
    #undef free
#endif

#define free(ptr) free_(ptr, __FILE__, __LINE__)
#if defined(realloc)
    #undef realloc
#endif

#define realloc(ptr, size) realloc_(ptr, size, __FILE__, __LINE__)
#if defined(calloc)
    #undef calloc
#endif
#define calloc(size, stride) malloc_((size) * (stride), __FILE__, __LINE__)

//
// Utils.
//
internal Bool
is_end_of_line(Char c)
{
    Bool res = ((c == '\n') || (c == '\r'));

    return(res);
}

internal Bool
is_whitespace(Char c)
{
    Bool res = ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\f') || (is_end_of_line(c)));

    return(res);
}

internal Int
string_length(Char *str)
{
    assert(str);

    Int res = 0;
    while(*str) {
        ++res;
        ++str;
    }

    return(res);
}

internal Bool
string_concat(Char *dest, Int len, Char *a, Int a_len, Char *b, Int b_len)
{
    assert((dest) && (a) && (b));

    Bool res = false;

    if(len > a_len + b_len) {
        for(Int a_index = 0; (a_index < a_len); ++a_index) { *dest++ = *a++; }
        for(Int b_index = 0; (b_index < b_len); ++b_index) { *dest++ = *b++; }

        res = true;
    }

    return(res);
}

internal Bool
string_compare(Char *a, Char *b, Int len = 0)
{
    assert((a) && (b));

    Bool res = true;

    // TODO(Jonny): Hacky.
    if(!len) {
        len = string_length(a);
    }

    for(Int string_index = 0; (string_index < len); ++string_index) {
        if(a[string_index] != b[string_index]) {
            res = false;
            break; // while
        }
    }

    return(res);
}

enum SwitchType {
    SwitchType_unknown,

    SwitchType_silent,
    SwitchType_log_errors,
    SwitchType_run_tests,
    SwitchType_source_file,

    SwitchType_count,
};

internal SwitchType
get_switch_type(Char *str)
{
    assert(str);

    SwitchType res = SwitchType_unknown;

    Int len = string_length(str);
    // TODO(Jonny): Do this properly...
    if(str[0] == '-') {
        switch(str[1]) {
            case 's': { res = SwitchType_silent;     } break;
            case 'e': { res = SwitchType_log_errors; } break;
#if INTERNAL
            case 't': { res = SwitchType_run_tests;  } break;
#endif

            default: { assert(0); } break;
        }
    } else if((str[len - 1] == 'c') && (str[len - 2] == '.')) {
        res = SwitchType_source_file;
    } else if((str[len - 1] == 'p') && (str[len - 2] == 'p') && (str[len - 3] == 'c') && (str[len - 4] == '.') ) {
        res = SwitchType_source_file;
    }

    return(res);
}

internal Char *
get_static_file(void)
{
    Char *res = "/*\n"
                "    Preprocessor API.\n"
                "*/\n"
                "\n"
                "/*  Quick Reference.\n"
                "\n"
                "    - Serialize a struct for output.\n"
                "    size_t serialize_struct(void *var, Type var_type, char *buffer, size_t buf_size);\n"
                "\n"
                "    - Get the number of members of a struct/class.\n"
                "    int get_num_of_members(TYPE type);\n"
                "\n"
                "    - Convert an enum index to a string.\n"
                "    char const *enum_to_string(EnumType, EnumType value);\n"
                "\n"
                "    - Convert a string to an enum index.\n"
                "    int string_to_enum(EnumType, char const *str);\n"
                "\n"
                "    - Get the total number of elements for an enum.\n"
                "    size_t get_number_of_enum_elements(EnumType);\n"
                "*/\n"
                "\n"
                "\n"
                "/*  Detailed Reference.\n"
                "\n"
                "    ================================================================================\n"
                "\n"
                "    size_t serialize_struct(void *var, Type var_type, char *buffer, size_t buf_size);\n"
                "     - Serialize a struct for outputting. This is more for debugging data in real time,\n"
                "       rather writing data to disk.\n"
                "\n"
                "    Parameters\n"
                "     - void *var       - The variable to be serialized.\n"
                "     - TYPE var_type   - The literal type of the variable to be serialized. NOTE - Does not work with decltype\n"
                "     - char *buffer    - The buffer to write the serialized data into.\n"
                "     - size_t buf_size - The size of the butt to write the data into.\n"
                "\n"
                "    Return Value\n"
                "     - size_t - The number of bytes written into buffer.\n"
                "\n"
                "    ================================================================================\n"
                "\n"
                "    int get_num_of_members(TYPE type);\n"
                "     - Get the number of member variables in a struct/class.\n"
                "\n"
                "    Parameters\n"
                "     - TYPE type - The type of the struct/class you want to get the members for.\n"
                "\n"
                "    Return Value\n"
                "     - int - The number of member variables in the stuct/class.\n"
                "\n"
                "    ================================================================================\n"
                "\n"
                "    char const *enum_to_string(EnumType, EnumType value);\n"
                "     - Convert an enum value into a string.\n"
                "\n"
                "    Parameters\n"
                "    - EnumType       - The type of the enum.\n"
                "    - EnumType value - The value of the enum.\n"
                "\n"
                "\n"
                "    Return Value\n"
                "     - char const * - A string literal of the enum index name.\n"
                "\n"
                "    ================================================================================\n"
                "\n"
                "    int string_to_enum(EnumType, char const *str);\n"
                "    - Convert a string to an enum value.\n"
                "\n"
                "    Parameters\n"
                "     - EnumType        - The type of the enum.\n"
                "     - char const *str - A string version of the enum index.\n"
                "\n"
                "    Return Value\n"
                "    - int - The index version of the string passed in.\n"
                "\n"
                "    ================================================================================\n"
                "\n"
                "    size_t get_number_of_enum_elements(EnumType);\n"
                "    - Get the total number of elements in an enum.\n"
                "\n"
                "    Parameters\n"
                "    - EnumType - The type of the enum you want.\n"
                "\n"
                "    Return Value\n"
                "     - size_t - The total number of elements in the enum.\n"
                "\n"
                "    ================================================================================\n"
                "*/\n"
                "\n"
                "\n"
                "/* Code shared between generated files. */\n"
                "#if !defined(STATIC_GENERATED)\n"
                "\n"
                "#include <stdio.h>\n"
                "#include <string.h>\n"
                "#include <assert.h>\n"
                "\n"
                "typedef char _char;\n"
                "typedef short _short;\n"
                "typedef int _int;\n"
                "typedef long _long;\n"
                "typedef float _float;\n"
                "typedef double _double;\n"
                "#if defined(__cplusplus)\n"
                "    typedef bool _bool;\n"
                "#else\n"
                "    typedef int _bool;\n"
                "#endif\n"
                "\n"
                "typedef struct MemberDefinition {\n"
                "    int/*MetaType*/ type;\n"
                "    char const *name;\n"
                "    size_t offset;\n"
                "    int is_ptr;\n"
                "    int arr_size;\n"
                "} MemberDefinition;\n"
                "\n"
                "typedef struct Variable {\n"
                "    char const *ret_type;\n"
                "    char const *name;\n"
                "} Variable;\n"
                "\n"
                "/* get_num_of_members(TYPE type); */\n"
                "#define get_num_of_members(type) num_members_for_##type\n"
                "\n"
                "/* size_t serialize_struct(void *var, Type var_type, char *buffer, size_t buf_size); */\n"
                "#define serialize_struct(var, type, buffer, buf_size) serialize_struct_(var, type, #var, 0, buffer, buf_size, 0)\n"
                "#define serialize_struct_(var, type, name, indent, buffer, buf_size, bytes_written) serialize_struct__((void *)&var, members_of_##type, name, #type, indent, get_num_of_members(type), buffer, buf_size, bytes_written)\n"
                "static size_t serialize_struct__(void *var, MemberDefinition members_of_Something[], char const *name, char const *type, int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written);\n"
                "\n"
                "/* char const *enum_to_string(EnumType, EnumType value); */\n"
                "#define enum_to_string(Type, v) enum_to_string_##Type(v)\n"
                "\n"
                "/* int string_to_enum(EnumType, char const *str); */\n"
                "#define string_to_enum(Type, str) string_to_enum_##Type(str)\n"
                "\n"
                "/* size_t get_number_of_enum_elements(EnumType); */\n"
                "#define get_number_of_enum_elements(Type) number_of_elements_in_enum_##Type\n"
                "\n"
                "#define STATIC_GENERATED\n"
                "#endif /* !defined(STATIC_GENERATED) */"
                "\n";

    return(res);
}

//
// Start Parsing function.
//
struct File {
    Char *data;
    Int size;
};

internal File
read_entire_file_and_null_terminate(Char *filename, Void *memory)
{
    assert((filename) &&(memory));

    File res = {};

    FILE *file = fopen(filename, "r");
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

internal Int
get_digit_count(Int value)
{
    Int res = 1;
    while((value /= 10) > 0) {
        ++res;
    }

    return(res);
}

internal Void
copy_int(Char *dest, Int value, Int start, Int count)
{
    assert(dest);

    Int end = start + count;
    for(Int index = end - 1; (index >= start); --index, value /= 10) {
        *(dest + index) = cast(Char)(value % 10 + 48);
    }

    dest[end] = 0;
}

internal Char *
int_to_string(Int value, Char *buf)
{
    assert(buf);

    Bool is_neg = (value < 0);
    Int abs_value = (is_neg) ? -value : value;
    Int num_digits = get_digit_count(abs_value);
    if(is_neg) {
        Char *ptr = buf;
        *ptr = '-';
        copy_int(ptr, abs_value, 1, num_digits);
    } else {
        Char *ptr = buf;
        copy_int(ptr, abs_value, 0, num_digits);
    }

    return(buf);
}

internal Char *
float_to_string(Float value, Int dec_accuracy, Char *buf)
{
    assert(buf);

    Bool is_neg = (value < 0);
    Float abs_value = (is_neg) ? -value : value;

    Int mul = 1;
    for(Int dec_index = 0; (dec_index < dec_accuracy); ++dec_index) {
        mul *= 10;
    }

    Int num_as_whole = cast(Int)(abs_value * mul);
    Int num_before_dec = num_as_whole / mul;
    Int num_after_dec = num_as_whole % mul;
    Int digit_count_before_dec = get_digit_count(num_before_dec);
    Int digit_count_after_dec = get_digit_count(num_after_dec);

    if(is_neg) {
        Char *ptr = buf;
        *ptr = '-';
        copy_int(ptr, num_before_dec, 1, digit_count_before_dec);
        *(ptr + digit_count_before_dec + 1) = '.';
        copy_int(ptr, num_after_dec, digit_count_before_dec + 2, digit_count_after_dec);
    } else {
        Char *ptr = buf;
        copy_int(ptr, num_before_dec, 0, digit_count_before_dec);
        *(ptr + digit_count_before_dec) = '.';
        copy_int(ptr, num_after_dec, digit_count_before_dec + 1, digit_count_after_dec);
    }

    return(buf);
}


internal Char *
bool_to_string(Bool b)
{
    Char *res = cast(Char *)((b) ? "true" : "false");

    return(res);
}

internal Bool
is_numeric(Char input)
{
    Bool res = ((input >= '0') && (input <= '9'));

    return(res);
}

// Printf replacement.
// %s     - Nul terminated string.
// %S     - String: Len and string.
// %d, %i - Integer.
// %u     - Unsigned Integer.
// %c     - Char
// %b     - Boolean
// %f     - Float
// TODO(Jonny): Print hex numbers for pointers.
internal Int
format_string_varargs(Char *buf, Int buf_len, Char *format, va_list args)
{
    assert((buf) && (buf_len) && (format));

    Char *dest = cast(Char *)buf;
    Int bytes_written = 0;
    Int float_precision = 1;
    Int next_fractional_digit = float_precision;

    // TODO(Jonny): Remove shadowing of temp_buffer.
    while(*format) {
        Char temp_buffer[1024] = {};
        Char c = *format;
        if(c == '%') {
            Char type = format[1];
            if(type == 'c') {
                *dest++ = cast(Char)va_arg(args, int);
                bytes_written++;
            } else {
                if(is_numeric(type)) {
                    next_fractional_digit = type - 48;
                    assert(format[2] == 'f');
                    type = 'f';
                    format++;
                }

                Char *replacement = 0;
                switch(type) {
                    case 'b': {
                        int boolean = va_arg(args, int);
                        replacement = bool_to_string(boolean != 0);
                    } break;

                    case 'd': case 'i': {
                        Int integer = va_arg(args, Int);
                        Char temp_buffer_2[1024] = {};
                        replacement = int_to_string(integer, temp_buffer_2);
                    } break;

                    case 'u': {
                        Uint32 unsigned_int = va_arg(args, Uint32);
                        Char temp_buffer_2[1024] = {};
                        replacement = int_to_string(unsigned_int, temp_buffer_2);
                    } break;

                    case 'f': {
                        Float float_num = cast(Float)va_arg(args, Float64);
                        Char temp_buffer_2[1024] = {};
                        replacement = float_to_string(float_num, next_fractional_digit, temp_buffer_2);
                        next_fractional_digit = float_precision;
                    } break;

                    case 's': {
                        Char *str = va_arg(args, Char *);
                        replacement = str;
                    } break;

                    case 'S': {
                        Int len = va_arg(args, Int);
                        Char *str = va_arg(args, Char *);

                        assert(len < array_count(temp_buffer));
                        Char *at = temp_buffer;
                        for(Int str_index = 0; (str_index < len); ++str_index, ++at) {
                            *at = str[str_index];
                        }

                        *at = 0;

                        replacement = temp_buffer;
                    } break;

                    case '%': {
                        temp_buffer[0] = '%';
                        replacement = temp_buffer;
                    }
                }

                if(replacement) {
                    while(*replacement) {
                        *dest++ = *replacement++;
                        bytes_written++;
                    }
                }
            }

            format++;
        } else {
            *dest++ = c;
            bytes_written++;
        }

        format++;
    }

    *dest = 0;

    assert(bytes_written < buf_len);

    return(bytes_written);
}

internal Int
format_string(Char *buf, Int buf_len, Char *format, ...)
{
    assert((buf) && (buf_len) && (format));

    va_list args;
    va_start(args, format);
    Int bytes_written = format_string_varargs(buf, buf_len, format, args);
    assert((bytes_written > 0) && (bytes_written < buf_len));
    va_end(args);

    return(bytes_written);
}

struct OutputBuffer {
    Char *buffer;
    Int index;
    Int size;
};

internal Void
write_to_output_buffer(OutputBuffer *ob, Char *format, ...)
{
    assert((ob) && (ob->buffer) && (ob->size) && (ob->index < ob->size));
    assert(format);

    va_list args;
    va_start(args, format);
    ob->index += format_string_varargs(ob->buffer + ob->index, ob->size - ob->index, format, args);
    va_end(args);
}
#if 0
internal OutputBuffer
create_output_buffer(Int size)
{
    assert(size);

    OutputBuffer res = {};
    res.buffer = malloc_array(Char, size);
    if(res.buffer) {
        res.size = size;
    }

    return(res);
}

internal Void
free_output_buffer(OutputBuffer *ob)
{
    free(ob->buffer);
}
#endif
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
    TokenType_var_args,

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

struct Tokenizer {
    Char *at;
};

struct String {
    Char *e;
    Int len;
};

internal String
create_string(Char *str, Int len = 0)
{
    String res;
    res.e = str;
    res.len = (len) ? len : string_length(str);

    return(res);
}

internal String
token_to_string(Token token)
{
    String res = create_string(token.e, token.len);

    return(res);
}

internal Char *
token_to_string(Token token, Char *buffer, Int size)
{
    assert((token.type) && (buffer) && (size >= token.len));

    memset(buffer, 0, size);
    for(Int str_index = 0; (str_index < token.len); ++str_index) {
        buffer[str_index] = token.e[str_index];
    }

    return(buffer);
}

internal Bool
token_compare(Token a, Token b)
{
    assert((a.len) && (b.len));

    Bool res = false;

    if(a.len == b.len) {
        res = true;

        for(Int string_index = 0; (string_index < a.len); ++string_index) {
            if(a.e[string_index] != b.e[string_index]) {
                res = false;
                break; // for
            }
        }
    }

    return(res);
}

internal Bool
string_compare(String a, String b)
{
    Bool res = false;

    if(a.len == b.len) {
        res = true;

        for(Int string_index = 0; (string_index < a.len); ++string_index) {
            if(a.e[string_index] != b.e[string_index]) {
                res = false;
                break; // for
            }
        }
    }

    return(res);
}

internal Void
eat_whitespace(Tokenizer *tokenizer)
{
    assert(tokenizer);

    for(;;) {
        if(is_whitespace(tokenizer->at[0])) { // Whitespace
            ++tokenizer->at;
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '/')) { // C++ comments.
            tokenizer->at += 2;
            while((tokenizer->at[0]) && (!is_end_of_line(tokenizer->at[0]))) {
                ++tokenizer->at;
            }
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '*')) { // C comments.
            tokenizer->at += 2;
            while((tokenizer->at[0]) && !((tokenizer->at[0] == '*') && (tokenizer->at[1] == '/'))) {
                ++tokenizer->at;
            }

            if(tokenizer->at[0] == '*') {
                tokenizer->at += 2;
            }
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

internal Bool
is_alphabetical(Char c)
{
    Bool res = (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));

    return(res);
}

internal Bool
is_num(Char c)
{
    Bool res = ((c >= '0') && (c <= '9'));

    return(res);
}

internal Void
parse_number(Tokenizer *tokenizer)
{
    assert(tokenizer);

    // TODO(Jonny): Implement.
}

internal Token get_token(Tokenizer *tokenizer); // Because C++...

#define eat_token(tokenizer) eat_tokens(tokenizer, 1);
internal Void
eat_tokens(Tokenizer *tokenizer, Int num_tokens_to_eat)
{
    assert(tokenizer);

    for(Int token_index = 0; (token_index < num_tokens_to_eat); ++token_index) {
        get_token(tokenizer);
    }
}

internal Token
get_token(Tokenizer *tokenizer)
{
    assert(tokenizer);

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

            if(!var_args) {
                res.type = TokenType_period;
            }
        } break;

        case '"': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '"')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { // TODO(Jonny): Is this right??
                    ++tokenizer->at;
                }

                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '"') {
                ++tokenizer->at;
            }
        } break;

        case '\'': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '\'')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { // TODO(Jonny): Is this right??
                    ++tokenizer->at;
                }

                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '\'') {
                ++tokenizer->at;
            }
        } break;

        default: {
            if((is_alphabetical(c)) || (tokenizer->at[0] == '_')) {
                while((is_alphabetical(tokenizer->at[0])) || (is_num(tokenizer->at[0])) || (tokenizer->at[0] == '_')) {
                    ++tokenizer->at;
                }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_identifier;
            } else if(is_num(c)) {
                while(is_num(tokenizer->at[0])) {
                    ++tokenizer->at;
                }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_number;
            } else {
                res.type = TokenType_unknown;
            }
        } break;
    }

    return(res);
}

internal Token
peak_token(Tokenizer *tokenizer)
{
    assert(tokenizer);

    Tokenizer cpy = *tokenizer;
    Token res = get_token(&cpy);

    return(res);
}

// TODO(Jonny): Create a token_equals_keyword function. This could also test macro'd aliases for keywords, as well as the actual keyword.

internal Bool
token_equals(Token token, Char *str)
{
    assert(str);

    Bool res = false;

    Char *at = str;
    for(Int str_index = 0; (str_index < token.len); ++str_index, ++at) {
        if((*at == 0) == (*at == token.e[str_index])) {
            goto exit_func;
        }
    }

    res = (*at == 0);

exit_func:

    return(res);
}

struct ResultInt {
    Int e;
    Bool success;
};

internal ResultInt
char_to_int(Char C)
{
    ResultInt res = {};
    switch(C) {
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

        default: { assert(0); } break;
    }

    return(res);
}

internal ResultInt
string_to_int(String str)
{
    ResultInt res = {};

    for(Int str_index = 0; (str_index < str.len); ++str_index) {
        ResultInt temp_int = char_to_int(str.e[str_index]);
        if(!temp_int.success) {
            break; // for
        }

        res.e *= 10;
        res.e += temp_int.e;

        if(str_index == str.len - 1) {
            res.success = true;
        }
    }

    assert(res.success);
    return(res);
}

internal ResultInt
token_to_int(Token t)
{
    String str = token_to_string(t);
    ResultInt res = string_to_int(str);

    return(res);
}

internal ResultInt
string_to_int(Char *str)
{
    String string;
    string.e = str;
    string.len = string_length(str);
    ResultInt res = string_to_int(string);

    return(res);
}

struct Variable {
    String type;
    String name;
    Bool is_ptr;
    Int array_count; // This is 1 if it's not an array.
};

internal Variable
create_variable(Char *type, Char *name, Bool is_ptr = false, Int array_count = 1)
{
    Variable res;
    res.type = create_string(type);
    res.name = create_string(name);
    res.is_ptr = is_ptr;
    res.array_count = array_count;

    return(res);
}

internal Bool
compare_variable(Variable a, Variable b)
{
    Bool res = true;

    if(0) {}
    else if(!string_compare(a.type, b.type)) { res = false; }
    else if(!string_compare(a.name, b.name)) { res = false; }
    else if(a.is_ptr != b.is_ptr)            { res = false; }
    else if(a.array_count != b.array_count)  { res = false; }

    return(res);
}

internal Bool
compare_variable_array(Variable *a, Variable *b, Int count)
{
    assert((a) && (b) && (count));

    for(Int array_index = 0; (array_index < count); ++array_index) {
        if(!compare_variable(a[array_index], b[array_index])) {
            return(false);
        }
    }

    return(true);
}

internal Variable
parse_member(Tokenizer *tokenizer)
{
    assert(tokenizer);

    Variable res = {};
    res.array_count = 1;
    res.type = token_to_string(get_token(tokenizer));

    Bool parsing = true;
    while(parsing) {
        Token token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_asterisk: {
                res.is_ptr = true;
            } break;

            case TokenType_open_bracket: {
                Token size_token = get_token(tokenizer);
                if(size_token.type == TokenType_number) {
                    Char buffer[256] = {};
                    token_to_string(size_token, buffer, array_count(buffer));
                    ResultInt arr_coount = string_to_int(buffer);
                    if(arr_coount.success) {
                        res.array_count = arr_coount.e;
                    }
                }
            } break;

            case TokenType_identifier: {
                res.name = token_to_string(token);
            } break;

            case TokenType_semi_colon: case TokenType_end_of_stream: {
                parsing = false;
            } break;
        }
    }

    return(res);
}

internal Bool
require_token(Tokenizer *tokenizer, TokenType desired_type)
{
    assert(tokenizer);

    Token token = get_token(tokenizer);
    Bool res = (token.type == desired_type);

    return(res);
}

internal Bool
is_stupid_class_keyword(Token t)
{
    assert(t.type != TokenType_unknown);
    Bool result = false;

    Char *keywords[] = { "private", "public", "protected" };
    for(Int keyword_index = 0, num_keywords = array_count(keywords); (keyword_index < num_keywords); ++keyword_index) {
        if(string_compare(keywords[keyword_index], t.e, t.len)) {
            result = true;
        }
    }

    return(result);
}

struct FunctionData {
    String linkage;
    String ret_type;
    String name;
    Variable params[32];
    Int param_count;
};

struct StructData {
    String name;
    Int member_count;
    Variable *members;
    String inherited;

    FunctionData *func_data;
    Int func_count;
};

internal Void
skip_to_matching_bracket(Tokenizer *tokenizer)
{
    assert(tokenizer);

    Int brace_count = 1;
    Token token = {};
    Bool should_loop = true;
    while(should_loop) {
        token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_close_brace: {
                --brace_count;
                if(!brace_count) {
                    should_loop = false;
                }
            } break;

            case TokenType_open_brace: {
                ++brace_count;
            } break;
        }
    }
}

internal Void
parse_template(Tokenizer *tokenizer)
{
    assert(tokenizer);

    Int angle_bracket_count = 1;
    Token token;
    Bool should_loop = true;
    while(should_loop) {
        token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_close_angle_bracket: {
                --angle_bracket_count;
                if(!angle_bracket_count) {
                    should_loop = false;
                }
            } break;

            case TokenType_open_angle_bracket: {
                ++angle_bracket_count;
            } break;
        }
    }
}

internal Variable
parse_variable(Tokenizer *tokenizer, TokenType end_token_type_1, TokenType end_token_type_2 = TokenType_unknown)
{
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
                // TODO(Jonny): Error case.
            }
        } else {
            // TODO(Jonny): Error case.
        }
    } else {
        res.array_count = 1;
    }

    // Skip over any assignment at the end.
    if(token.type == TokenType_equals) {
        eat_token(tokenizer); // TODO(Jonny): This won't work if a variable is assigned to a function.
    }

    return(res);
}

// TODO(Jonny): This needs some way to ignore member functions.

struct ParseStructResult {
    StructData sd;
    Bool success;
};
internal ParseStructResult
parse_struct(Tokenizer *tokenizer)
{
    assert(tokenizer);

    ParseStructResult res = {};

    Bool have_name = false;
    Token name = peak_token(tokenizer);
    if(name.type == TokenType_identifier) {
        have_name = true;
        res.sd.name = token_to_string(name);
        eat_token(tokenizer);
    }

    Bool inherited = false;
    Token inherited_from = {};
    Token peaked_token = peak_token(tokenizer);
    if(peaked_token.type == TokenType_colon) {
        eat_tokens(tokenizer, 2);
        inherited_from = get_token(tokenizer);
        inherited = true;
    }

    if(require_token(tokenizer, TokenType_open_brace)) {
        res.success = true;
        if(inherited) {
            res.sd.inherited = token_to_string(inherited_from);
        }

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
                            if(name.type == TokenType_identifier) {
                                res.sd.name = token_to_string(name);
                            } else {
                                push_error(ErrorType_could_not_detect_struct_name);
                            }
                        }

                        break; // for
                    } else if(token.type == TokenType_hash) {
                        while(tokenizer->at[0] != '\n') {
                            ++tokenizer->at;
                        }
                    } else {
                        Bool is_func = false;

                        Tokenizer tokenizer_copy = *tokenizer;
                        Token temp = get_token(&tokenizer_copy);
                        while(temp.type != TokenType_semi_colon) {
                            if(temp.type == TokenType_open_paren) {
                                is_func = true;
                            }

                            if(temp.type == TokenType_open_brace) {
                                is_func = true;
                                break; // while
                            }

                            temp = get_token(&tokenizer_copy);
                        }

                        if(!is_func) {
                            member_pos[res.sd.member_count++] = token.e;
                        } else {
                            // This is commented out because I'm not sure I really _need_ member functions...
#if 0
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
#endif
                        }

                        *tokenizer = tokenizer_copy;
                    }
                }
            }
        }

        if(res.sd.member_count > 0) {
            res.sd.members = malloc_array(Variable, res.sd.member_count);
            if(res.sd.members) {
                for(Int member_index = 0; (member_index < res.sd.member_count); ++member_index) {
                    Tokenizer fake_tokenizer = { member_pos[member_index] };
                    res.sd.members[member_index] = parse_member(&fake_tokenizer);
                }
            }
        }
    }

    return(res);
}

internal Void
write_serialize_struct_implementation(Char *def_struct_code, OutputBuffer *ob)
{
    assert((def_struct_code) && (ob));

    // TODO(Jonny): This will currently flop with an array of pointers.
    Char *top_part = "/* Function to serialize a struct to a char array buffer. */\n"
                     "static size_t\n"
                     "serialize_struct__(void *var, MemberDefinition members_of_Something[], char const *name, char const *type, int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written)\n"
                     "{\n"
                     "    char indent_buf[256];\n"
                     "    int i = 0, j = 0, is_null = 0;\n"
                     "    MemberDefinition *member = 0;\n"
                     "    void *member_ptr = 0;\n"
                     "    size_t *value = 0;\n"
                     "\n"
                     "    memset(indent_buf, 0, 256);\n"
                     "\n"
                     "    assert((var) && (members_of_Something) && (num_members > 0) && (buffer) && (buf_size > 0));\n"
                     "    memset(buffer + bytes_written, 0, buf_size - bytes_written);\n"
                     "    for(i = 0; (i < indent); ++i) {\n"
                     "        indent_buf[i] = ' ';\n"
                     "    }\n"
                     "\n"
                     "    bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%s%%s %%s\", indent_buf, type, name);\n"
                     "    indent += 4;\n"
                     "\n"
                     "    for(i = 0; (i < indent); ++i) {\n"
                     "        indent_buf[i] = ' ';\n"
                     "    }\n"
                     "\n"
                     "    for(i = 0; (i < num_members); ++i) {\n"
                     "         member = members_of_Something + i;\n"
                     "\n"
                     "         member_ptr = (char *)var + member->offset;\n"
                     "         switch(member->type) {\n"
                     "            case meta_type_double: {\n"
                     "                if(member->arr_size > 1) {\n"
                     "                    value = (size_t *)member_ptr;\n"
                     "                    for(j = 0; (j < member->arr_size); ++j) {\n"
                     "                        is_null = (member->is_ptr) ? !(*(double **)(value + j)) : 0;\n"
                     "                        if(!is_null) {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sdouble %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(double *)value[j] : value[j]);\n"
                     "                        } else {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sdouble %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
                     "                        }\n"
                     "                    }\n"
                     "                } else {\n"
                     "                    double *double_value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;\n"
                     "                    if(double_value) {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sdouble %%s%%s = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *double_value);\n"
                     "                    } else {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sdouble *%%s = (null)\", indent_buf, member->name);\n"
                     "                    }\n"
                     "                }\n"
                     "            } break;\n"
                     "\n"
                     "            case meta_type_float: {\n"
                     "                if(member->arr_size > 1) {\n"
                     "                    value = (size_t *)member_ptr;\n"
                     "                    for(j = 0; (j < member->arr_size); ++j) {\n"
                     "                        is_null = (member->is_ptr) ? !(*(float **)(value + j)) : 0;\n"
                     "                        if(!is_null) {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(float *)value[j] : value[j]);\n"

                     "                        } else {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
                     "                        }\n"
                     "                    }\n"
                     "                } else {\n"
                     "                    float *float_value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;\n"
                     "                    if(float_value) {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat %%s%%s = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *float_value);\n"
                     "                    } else {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat *%%s = (null)\", indent_buf, member->name);\n"
                     "                    }\n"
                     "                }\n"
                     "            } break;\n"
                     "\n"
                     "            case meta_type_int: {\n"
                     "                if(member->arr_size > 1) {\n"
                     "                    value = (size_t *)member_ptr;\n"
                     "                    for(j = 0; (j < member->arr_size); ++j) {\n"
                     "                        is_null = (member->is_ptr) ? !(*(int **)(value + j)) : 0;\n"
                     "                        if(!is_null) {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(int *)value[j] : (int)value[j]);\n"
                     "                        } else {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
                     "                        }\n"
                     "                    }\n"
                     "                } else {\n"
                     "                    int *int_value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;\n"
                     "                    if(int_value) {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *int_value);\n"
                     "                    } else {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
                     "                    }\n"
                     "                }\n"
                     "            } break;\n"
                     "\n"
                     "            case meta_type_long: {\n"
                     "                if(member->arr_size > 1) {\n"
                     "                    value = (size_t *)member_ptr;\n"
                     "                    for(j = 0; (j < member->arr_size); ++j) {\n"
                     "                        is_null = (member->is_ptr) ? !(*(long **)(value + j)) : 0;\n"
                     "                        if(!is_null) {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(long *)value[j] : (long)value[j]);\n"
                     "                        } else {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
                     "                        }\n"
                     "                    }\n"
                     "                } else {\n"
                     "                    long *long_value = (member->is_ptr) ? *(long **)member_ptr : (long *)member_ptr;\n"
                     "                    if(long_value) {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *long_value);\n"
                     "                    } else {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
                     "                    }\n"
                     "                }\n"
                     "            } break;\n"
                     "\n"
                     "            case meta_type_short: {\n"
                     "                if(member->arr_size > 1) {\n"
                     "                    value = (size_t *)member_ptr;\n"
                     "                    for(j = 0; (j < member->arr_size); ++j) {\n"
                     "                        is_null = (member->is_ptr) ? !(*(short **)(value + j)) : 0;\n"
                     "                        if(!is_null) {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (member->is_ptr) ? *(short *)value[j] : (short)value[j]);\n"
                     "                        } else {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
                     "                        }\n"
                     "                    }\n"
                     "                } else {\n"
                     "                    short *short_value = (member->is_ptr) ? *(short **)member_ptr : (short *)member_ptr;\n"
                     "                    if(short_value) {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s%%s = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *short_value);\n"
                     "                    } else {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
                     "                    }\n"
                     "                }\n"
                     "            } break;\n"
                     "\n"
                     "#if defined(__cplusplus)\n"
                     "            case meta_type_bool: {\n"
                     "                if(member->arr_size > 1) {\n"
                     "                    value = (size_t *)member_ptr;\n"
                     "                    for(j = 0; (j < member->arr_size); ++j) {\n"
                     "                        is_null = (member->is_ptr) ? !(*(bool **)(value + j)) : 0;\n"
                     "                        if(is_null) {\n"
                     "                            int value_to_print = (member->is_ptr) ? **(bool **)(value + j) : value[j];\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sbool %%s%%s[%%d] = %%s\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (value_to_print) ? \"true\" : \"false\");\n"
                     "                        } else {\n"
                     "                            bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sbool %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
                     "                        }\n"
                     "                    }\n"
                     "                } else {\n"
                     "                    bool *bool_value = (member->is_ptr) ? *(bool **)member_ptr : (bool *)member_ptr;\n"
                     "                    if(bool_value) {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sbool %%s%%s = %%s\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, (bool_value) ? \"true\" : \"false\");\n"
                     "                    } else {\n"
                     "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sbool *%%s = (null)\", indent_buf, member->name);\n"
                     "                    }\n"
                     "                }\n"
                     "            } break;\n"
                     "#endif /* #if defined(__cplusplus) */\n"
                     "\n"
                     "            case meta_type_char: {\n"
                     "                value = (member->is_ptr) ? *(size_t **)member_ptr : (size_t *)member_ptr;\n"
                     "                if(value) {\n"
                     "                    if(member->is_ptr) {\n"
                     "                        bytes_written += sprintf(buffer + bytes_written, \"\\n%%schar *%%s = \\\"%%s\\\"\", indent_buf, member->name, (char *)value);\n"
                     "                    } else {\n"
                     "                        bytes_written += sprintf(buffer + bytes_written, \"\\n%%schar %%s = %%c\", indent_buf, member->name, *(char *)value);\n"
                     "                    }\n"
                     "                } else {\n"
                     "                    bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%schar *%%s = (null)\", indent_buf, member->name);\n"
                     "                }\n"
                     "            } break;\n"
                     "\n"
                     "            default: {\n";
    Char *bottom_part = "\n"
                        "            } break; /* default */\n"
                        "        }\n"
                        "    }\n"
                        "\n"
                        "    return(bytes_written);\n"
                        "}\n";

    write_to_output_buffer(ob, top_part);
    write_to_output_buffer(ob, def_struct_code);
    write_to_output_buffer(ob, bottom_part);
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

internal EnumData
add_token_to_enum(Token name, Token type, Bool is_enum_struct, Tokenizer *tokenizer)
{
    assert(name.type == TokenType_identifier);
    assert((type.type == TokenType_identifier) || (type.type == TokenType_unknown));
    assert(tokenizer);

    Token token = {};
    EnumData res = {};

    res.is_struct = is_enum_struct;
    res.name = token_to_string(name);
    if(type.type == TokenType_identifier) {
        res.type = token_to_string(type);
    }

    Tokenizer copy = *tokenizer;
    token = get_token(&copy);
    while(token.type != TokenType_close_brace) {
        // TODO(Jonny): It was stupid to count the number of commas. Instead, actually count
        //              the number of enums.
        if(token.type == TokenType_comma) {
            ++res.no_of_values;
        }

        token = get_token(&copy);
    }

    if(res.no_of_values) {
        ++res.no_of_values;
    }

    res.values = malloc_array(EnumValue, res.no_of_values);
    if(res.values) {
        for(Int index = 0; (index < res.no_of_values); ++index) {
            EnumValue *ev = res.values + index;

            Token temp_token = {};
            while(temp_token.type != TokenType_identifier) {
                temp_token = get_token(tokenizer);
            }

            ev->name = token_to_string(temp_token);
            ev->value = index; // TODO(Jonny): Doesn't work for enums with an assignment in them.
        }
    }

    return(res);
}

internal Bool
is_meta_type_already_in_array(String *array, Int len, String test)
{
    assert(array);

    Bool res = false;

    for(Int arr_index = 0; (arr_index < len); ++arr_index) {
        if(string_compare(array[arr_index], test)) {
            res = true;
            break; // for
        }
    }

    return(res);
}

global Char *primitive_types[] = {"char", "short", "int", "long", "float", "double", "bool"};

#define get_num_of_primitive_types() array_count(primitive_types)

internal Int
set_primitive_type(String *array)
{
    assert(array);

    Int res = array_count(primitive_types);

    for(int i = 0; (i < res); ++i) {
        array[i].e = primitive_types[i];
        array[i].len = string_length(primitive_types[i]);
    }

    return(res);
}

// TODO(Jonny): I don't like this...
#define copy_literal_to_char_buffer(buf, index, lit) copy_literal_to_char_buffer_(buf, index, lit, sizeof(lit) - 1)
internal Int
copy_literal_to_char_buffer_(Char *buf, Int index, Char *literal, Int literal_len)
{
    assert((buf) && (literal) && (literal_len));

    buf += index;

    for(Int str_index = 0; (str_index < literal_len); ++str_index) {
        buf[str_index] = literal[str_index];
    }

    Int res = index + literal_len;
    return(res);
}

internal Char *
get_default_struct_string(void)
{
    Char *res = "                    case meta_type_%S: {\n"
                "                        if(member->is_ptr) {\n"
                "                            bytes_written = serialize_struct_(**(char **)member_ptr, %S, member->name, indent, buffer, buf_size - bytes_written, bytes_written);\n"
                "                        } else {\n"
                "                            bytes_written = serialize_struct_(*(char *)member_ptr, %S, member->name, indent, buffer, buf_size - bytes_written, bytes_written);\n"
                "                        }\n"
                "                    } break;\n"
                "\n";

    return(res);
}

internal Void
skip_to_end_of_line(Tokenizer *tokenizer)
{
    while(*tokenizer->at != '\n') {
        ++tokenizer->at;
    }
}

struct ParseFunctionResult {
    FunctionData func_data;
    Bool success;
};
internal ParseFunctionResult
attempt_to_parse_function(Tokenizer *tokenizer, Token token)
{
    assert((tokenizer) && (token.type));

    ParseFunctionResult res = {};

    // Try to parse as a function.
    Tokenizer copy_tokenizer = *tokenizer;
    Token linkage = {};
    Token return_type = {};
    if((token_equals(token, "static")) || (token_equals(token, "inline")) || (token_equals(token, "internal"))) {
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

                                if(linkage.type == TokenType_identifier) {
                                    res.func_data.linkage = token_to_string(linkage);
                                }

                                res.func_data.ret_type = token_to_string(return_type);
                                res.func_data.name = token_to_string(name);

                                // Set the array size to 1 for all the variables...
                                for(Int param_index = 0; (param_index < array_count(res.func_data.params)); ++param_index) {
                                    res.func_data.params[param_index].array_count = 1;
                                }

                                Bool parsing = true;
                                Variable *var = res.func_data.params + res.func_data.param_count;

                                // If there aren't any parameters then just skip them.
                                {
                                    Tokenizer copy = *tokenizer;
                                    Token temp_token = get_token(&copy);
                                    if(token_equals(temp_token, "void")) {
                                        Token next = get_token(&copy);
                                        if(next.type == TokenType_close_param) {
                                            parsing = false;
                                        }
                                    }
                                }

                                // Parse the parameters.
                                while(parsing) {
                                    Token temp_token = get_token(tokenizer);
                                    switch(temp_token.type) {
                                        case TokenType_asterisk: {
                                            var->is_ptr = true;
                                        } break;

                                        case TokenType_open_bracket: {
                                            Token SizeToken = get_token(tokenizer);
                                            if(SizeToken.type == TokenType_number) {
                                                Char buffer[256] = {};
                                                token_to_string(SizeToken, buffer, array_count(buffer));
                                                ResultInt arr_count = string_to_int(buffer);
                                                if(arr_count.success) {
                                                    var->array_count = arr_count.e;
                                                }
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

                                        case TokenType_comma: {
                                            ++var;
                                        } break;

                                        case TokenType_end_of_stream: case TokenType_open_brace: {
                                            parsing = false; // TODO(Jonny): Something baaaad happened...
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

internal StructData *
find_struct(String str, StructData *structs, Int struct_count)
{
    StructData *res = 0;

    if(str.len) {
        for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
            StructData *sd = structs + struct_index;

            if(string_compare(str, sd->name)) {
                res = sd;
                break; // for
            }
        }
    }

    return(res);
}

internal File
write_data(StructData *struct_data, Int struct_count, EnumData *enum_data, Int enum_count)
{
    assert((struct_data) && (enum_data));

    File res = {};

    OutputBuffer ob = {};//create_output_buffer(256 * 256);
    ob.size = 256 * 256;
    ob.buffer = malloc_array(Char, ob.size);
    if(ob.buffer) {
        //
        // Header Info.
        //
        write_to_output_buffer(&ob, "#if !defined(GENERATED_H) /* TODO(Jonny): Add the actual filename in here? */\n\n#include \"static_generated.h\"\n");

        //
        // MetaTypes enum.
        //
        if(struct_count) {
            // Get the absolute max number of meta types. This will be significantly bigger than the
            // actual number of unique types...
            Int max_type_count = get_num_of_primitive_types();
            for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
                ++max_type_count;

                for(Int member_index = 0; (member_index < struct_data[struct_index].member_count); ++member_index) {
                    ++max_type_count;
                }
            }

            String *types = malloc_array(String, max_type_count);
            if(types) {
                Int type_count = set_primitive_type(types);

                // Fill out the enum meta type enum.
                for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
                    StructData *sd = struct_data + struct_index;

                    if(!is_meta_type_already_in_array(types, type_count, sd->name)) {
                        types[type_count++] = sd->name;
                    }

                    for(Int member_index = 0; (member_index < sd->member_count); ++member_index) {
                        Variable *md = sd->members + member_index;

                        if(!is_meta_type_already_in_array(types, type_count, md->type)) {
                            types[type_count++] = md->type;
                        }
                    }
                }

                // Write the meta type enum to file.
                write_to_output_buffer(&ob, "\n/* Enum with field for every type detected. */\n");
                write_to_output_buffer(&ob, "typedef enum MetaType {\n");
                for(Int type_index = 0; (type_index < type_count); ++type_index) {
                    String *type = types + type_index;
                    write_to_output_buffer(&ob, "    meta_type_%S,\n", type->len, type->e);
                }
                write_to_output_buffer(&ob, "} MetaType;\n");

                free(types);
            }
        }

        //
        // Struct Meta Data
        //
        write_to_output_buffer(&ob, "\n/* Struct meta data. */\n\n/* Struct typedefs. */\n");
        for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
            StructData *sd2 = struct_data + struct_index;

            write_to_output_buffer(&ob, "typedef struct _%S _%S;\n",
                                   sd2->name.len, sd2->name.e, sd2->name.len, sd2->name.e);
        }

        write_to_output_buffer(&ob, "\n/* Recreated structs. */\n");
        for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
            StructData *sd2 = struct_data + struct_index;

            write_to_output_buffer(&ob, "struct _%S", sd2->name.len, sd2->name.e);
            if(sd2->inherited.len) {
                write_to_output_buffer(&ob, " : public _%S", sd2->inherited.len, sd2->inherited.e);
            }
            write_to_output_buffer(&ob, " { ");

            for(Int member_index = 0; (member_index < sd2->member_count); ++member_index) {
                Variable *md = sd2->members + member_index;
                Char *arr = cast(Char *)((md->array_count > 1) ? "[%u]" : "");
                Char arr_buffer[256] = {};
                if(md->array_count > 1) {
                    format_string(arr_buffer, 256, arr, md->array_count);
                }

                write_to_output_buffer(&ob, " _%S %s%S%s; ",
                                       md->type.len, md->type.e,
                                       (md->is_ptr) ? "*" : "",
                                       md->name.len, md->name.e,
                                       (md->array_count > 1) ? arr_buffer : arr);

            }

            write_to_output_buffer(&ob, " };\n");
        }

        for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
            StructData *sd = struct_data + struct_index;

            write_to_output_buffer(&ob, "\n/* Meta data for: %S. */\n", sd->name.len, sd->name.e);

            Int member_count = sd->member_count;
            StructData *inherited = find_struct(sd->inherited, struct_data, struct_count);
            if(inherited) {
                member_count += inherited->member_count;
            }
            write_to_output_buffer(&ob, "static int num_members_for_%S = %u;\n",
                                   sd->name.len, sd->name.e, member_count);

            write_to_output_buffer(&ob, "static MemberDefinition members_of_%S[] = {\n", sd->name.len, sd->name.e);
            write_to_output_buffer(&ob, "    /* Members. */\n");
            for(Int member_index = 0; (member_index < sd->member_count); ++member_index) {
                Variable *md = sd->members + member_index;
                write_to_output_buffer(&ob, "    {meta_type_%S, \"%S\", (size_t)&((_%S *)0)->%S, %d, %d},\n",
                                       md->type.len, md->type.e,
                                       md->name.len, md->name.e,
                                       sd->name.len, sd->name.e,
                                       md->name.len, md->name.e,
                                       md->is_ptr,
                                       md->array_count);
            }
            if(sd->inherited.len) {
                StructData *base_class = find_struct(sd->inherited, struct_data, struct_count);
                assert(base_class);

                write_to_output_buffer(&ob, "\n    /* Inherited Members. */\n");
                for(Int member_index = 0; (member_index < base_class->member_count); ++member_index) {
                    Variable *base_class_var = base_class->members + member_index;

                    write_to_output_buffer(&ob, "    {meta_type_%S, \"%S\", (size_t)&((_%S *)0)->%S, %d, %d},\n",
                                           base_class_var->type.len, base_class_var->type.e,
                                           base_class_var->name.len, base_class_var->name.e,
                                           sd->name.len, sd->name.e,
                                           base_class_var->name.len, base_class_var->name.e,
                                           base_class_var->is_ptr,
                                           base_class_var->array_count);
                }
            }

            write_to_output_buffer(&ob, "};");
        }

        // Recursive part for calling on members of structs.
        write_to_output_buffer(&ob, "\n\n");

        Int def_struct_code_size = 256 * 256;
        Char *def_struct_code = malloc_array(Char, def_struct_code_size);
        if(def_struct_code) {
            Int index = 0;
            index = copy_literal_to_char_buffer(def_struct_code, index, "                switch(member->type) {\n");
            for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
                StructData *sd = struct_data + struct_index;
                Char *DefaultStructString = get_default_struct_string();
                index += format_string(def_struct_code + index, def_struct_code_size, DefaultStructString,
                                       sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            }

            index = copy_literal_to_char_buffer(def_struct_code, index, "                }");
        }



        write_serialize_struct_implementation(def_struct_code, &ob);
        free(def_struct_code);
        //write_to_output_buffer(&ob, "%s", serialize_struct_implementation);
        //free(serialize_struct_implementation);

        //
        // Enum Meta data.
        //
        if(enum_count) {
            write_to_output_buffer(&ob, "\n/* Enum meta data. */\n");

            Int buf_size = 255 * 255;
            Char *buf = malloc_array(Char, buf_size); // Random size;
            if(buf) {
                for(Int enum_index = 0; (enum_index < enum_count); ++enum_index) {
                    EnumData *ed = enum_data + enum_index;
                    write_to_output_buffer(&ob, "\n/* Meta Data for: %S. */\n", ed->name.len, ed->name.e);

                    // Enum size.
                    {
                        memset(buf, 0, buf_size);
                        int bytes_written = format_string(buf, buf_size,
                                                          "static size_t number_of_elements_in_enum_%S = %d;",
                                                          ed->name.len, ed->name.e, ed->no_of_values);
                        assert(bytes_written < buf_size);

                        write_to_output_buffer(&ob, buf);
                    }

                    // enum_to_string.
                    {
                        memset(buf, 0, buf_size);
                        Char small_buf[1024] = {};
                        Int index = 0;

                        for(int enum_value_index = 0; (enum_value_index < ed->no_of_values); ++enum_value_index) {
                            index += format_string(small_buf + index, array_count(small_buf) - index,
                                                   "        case %d: { return(\"%S\"); } break;\n",
                                                   ed->values[enum_value_index].value,
                                                   ed->values[enum_value_index].name.len, ed->values[enum_value_index].name.e);
                        }



                        Char *enum_to_string_base = "\nstatic char const *\n"
                                                    "enum_to_string_%S(int v)\n"
                                                    "{\n"
                                                    "    switch(v) {\n"
                                                    "%s"
                                                    "\n"
                                                    "        default: { return(0); } break; /* v is out of bounds. */\n"
                                                    "    }\n"
                                                    "}\n";
                        Int bytes_written = format_string(buf, buf_size, enum_to_string_base,
                                                          ed->name.len, ed->name.e, small_buf);
                        assert(bytes_written < buf_size);

                        write_to_output_buffer(&ob, buf);
                    }

                    write_to_output_buffer(&ob, "\n");

                    // string_to_enum.
                    {
                        memset(buf, 0, buf_size);
                        Char small_buf[1024] = {};
                        Int index = 0;

                        for(int enum_value_index = 0; (enum_value_index < ed->no_of_values); ++enum_value_index) {
                            index += format_string(small_buf + index, array_count(small_buf) - index,
                                                   "    else if(strcmp(str, \"%S\") == 0) { return(%d); }\n",
                                                   ed->values[enum_value_index].name.len, ed->values[enum_value_index].name.e,
                                                   ed->values[enum_value_index].value);
                        }


                        format_string(buf, buf_size,
                                      "static int\n"
                                      "string_to_enum_%S(char const *str)\n"
                                      "{\n"
                                      "    if(0) {}\n"
                                      "%s"
                                      "\n"
                                      "    else { return(0); } /* str didn't match. TODO(Jonny): Throw an error here? */\n"
                                      "}\n",
                                      ed->name.len, ed->name.e, small_buf);

                        write_to_output_buffer(&ob, buf);
                    }

                }

                free(buf);
            }

        }

        //
        // # Guard macro.
        //
        write_to_output_buffer(&ob, "\n#define GENERATED_H\n#endif /* !defined(GENERATED_H) */\n");

        res.size = ob.index;
        res.data = ob.buffer;
    }

    return(res);
}

global Bool should_write_to_file;

internal Void
start_parsing(Char *filename, Char *file)
{
    Int enum_max = 32, enum_count = 0;
    EnumData *enum_data = malloc_array(EnumData, enum_max);

    Int struct_max = 32, struct_count = 0;
    StructData *struct_data = malloc_array(StructData, struct_max);

    Int union_max = 32, union_count = 0;
    String *union_data = malloc_array(String, union_max);

    //Int func_max = 32, func_count = 0;
    //FunctionData *func_data = malloc_array(FunctionData, func_max);

    if((enum_data)  && (struct_data) && (union_data)) {

        Tokenizer tokenizer = { file };

        Bool parsing = true;
        while(parsing) {
            Token token = get_token(&tokenizer);
            switch(token.type) {
                case TokenType_end_of_stream: { parsing = false;                 } break;
                case TokenType_hash:          { skip_to_end_of_line(&tokenizer); } break;

                case TokenType_identifier: {
                    // TODO(Jonny): I may need to keep the template header, so that the generated structs still work.
                    if(token_equals(token, "template")) {
                        eat_token(&tokenizer);
                        parse_template(&tokenizer);
                    } else if((token_equals(token, "struct")) || (token_equals(token, "class"))) { // TODO(Jonny): Support typedef sturcts.
                        if(struct_count + 1 >= struct_max) {
                            struct_max *= 2;
                            Void *p = realloc(struct_data, struct_max * sizeof(StructData));
                            if(p) {
                                struct_data = cast(StructData *)p;
                            }
                        }

                        ParseStructResult r = parse_struct(&tokenizer);
                        if(r.success) {
                            struct_data[struct_count++] = r.sd; // TODO(Jonny): This fails at a struct declared within a struct/union.
                        }
                    } else if((token_equals(token, "union"))) {
                        Token name = get_token(&tokenizer);

                        if(union_count + 1 >= union_max) {
                            union_max *= 2;
                            Void *p = realloc(union_data, union_max * sizeof(String));
                            if(p) {
                                union_data = cast(String *)p;
                            }
                        }

                        union_data[union_count++] = token_to_string(name);

                    } else if((token_equals(token, "enum"))) {
                        Token name = get_token(&tokenizer);
                        Bool is_enum_struct = false;
                        if((token_equals(name, "class")) || (token_equals(name, "struct"))) {
                            is_enum_struct = true;
                            name = get_token(&tokenizer);
                        }

                        if(name.type == TokenType_identifier) {
                            // If the enum has an underlying type, get it.
                            Token underlying_type = {};
                            Token next = get_token(&tokenizer);
                            if(next.type == TokenType_colon) {
                                underlying_type = get_token(&tokenizer);
                                next = get_token(&tokenizer);
                            }

                            if(next.type == TokenType_open_brace) {
                                if(enum_count + 1 >= enum_max) {
                                    enum_max *= 2;
                                    Void *p = realloc(enum_data, sizeof(enum_data) * enum_max);
                                    if(p) {
                                        enum_data = cast(EnumData *)p;
                                    }
                                }

                                enum_data[enum_count++] = add_token_to_enum(name, underlying_type, is_enum_struct, &tokenizer);
                            }
                        }
                    } else {
                        // This is a bit funny looking because functions don't have keyword to look for, like structs.
#if 0
                        ParseFunctionResult pfr = attempt_to_parse_function(&tokenizer, token);
                        if(pfr.success) {
                            if(func_count + 1 > func_max) {
                                func_max *= 2;
                                Void *p = realloc(func_data, sizeof(FunctionData) * func_max);
                                if(p) {
                                    func_data = (FunctionData *)p;
                                }
                            }

                            func_data[func_count++] = pfr.func_data;
                        }
#endif
                    }
                } break;
            }
        }

        File file_to_write = write_data(struct_data, struct_count, enum_data, enum_count);

        if(should_write_to_file) {
            Char generated_file_name[256] = {};
            Char *generated_extension = "_generated.h";

            if(string_concat(generated_file_name, array_count(generated_file_name),
                             filename, string_length(filename) - 4, // TODO(Jonny): Hacky, actually detect the extension properly.
                             generated_extension, string_length(generated_extension))) {

                Bool header_write_success = write_to_file(generated_file_name, file_to_write.data, file_to_write.size);
                if(!header_write_success) {
                    push_error(ErrorType_could_not_write_to_disk);
                }

                free(file_to_write.data);
            }
        }

        //free(func_data);

        free(union_data);

        for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) { free(struct_data[struct_index].members); }
        free(struct_data);

        for(Int enum_index = 0; (enum_index < enum_count); ++enum_index) { free(enum_data[enum_index].values); }
        free(enum_data);
    }
}

Int
main(Int argc, Char **argv)
{
    Int res = 0;

    if(argc <= 1) {
        push_error(ErrorType_no_parameters);
    } else {
        Bool should_log_errors = false;
        Bool should_run_tests = false;
        should_write_to_file = true;

        // Get the total amount of memory needed to store all files.
        PtrSize largest_source_file_size = 0;
        Int number_of_files = 0;
        for(Int file_index = 1; (file_index < argc); ++file_index) {
            Char *switch_name = argv[file_index];

            SwitchType type = get_switch_type(switch_name);
            switch(type) {
                case SwitchType_silent:     { should_write_to_file = false; } break;
                case SwitchType_log_errors: { should_log_errors = true;     } break;
                case SwitchType_run_tests:  { should_run_tests = true;      } break;

                case SwitchType_source_file: {
                    PtrSize file_size = get_file_size(switch_name);
                    if(file_size) {
                        ++number_of_files;
                        if(file_size > largest_source_file_size) {
                            largest_source_file_size = file_size;
                        }
                    } else {
                        push_error(ErrorType_cannot_find_file);
                    }
                } break;
            }
        }

        if(should_run_tests) {
            Int run_tests(void);
            res = run_tests();
        } else {
            if(!number_of_files) {
                push_error(ErrorType_no_files_pass_in);
            } else {
                Byte *file_memory = malloc_array(Byte, largest_source_file_size);
                if(file_memory) {
                    // Write static file to disk.
                    if(should_write_to_file) {
                        Char *static_file_data = get_static_file();
                        Int static_file_len = string_length(static_file_data);
                        Bool static_write_success = write_to_file("static_generated.h", static_file_data, static_file_len);
                        if(!static_write_success) {
                            push_error(ErrorType_could_not_write_to_disk);
                        }
                    }

                    // Parse files
                    for(Int file_index = 1; (file_index < argc); ++file_index) {
                        memset(file_memory, 0, largest_source_file_size);

                        Char *file_name = argv[file_index];

                        SwitchType type = get_switch_type(file_name);
                        if(type == SwitchType_source_file) {
                            File file = read_entire_file_and_null_terminate(file_name, file_memory);
                            if(file.data) {
                                start_parsing(file_name, file.data);
                            }
                        }
                    }

                    free(file_memory);
                }
            }

#if INTERNAL
            // Check memory leaks.
            MemList *next = mem_list_root;
            while(next) {
                if(!next->freed) {
                    push_error_(ErrorType_memory_not_freed, next->file, next->line);
                }

                next = next->next;
            }
#endif
            // Output errors.
            if(global_error_count) {
                res = 255;

                if(should_log_errors) {
                    // TODO(Jonny): Write errors to disk.
                    printf("\n\nList of errors:\n");
                    for(Int error_index = 0; (error_index < global_error_count); ++error_index) {
                        Error *e = global_errors + error_index;

                        Char *error_type = ErrorTypeToString(e->type);
                        assert(error_type);

                        printf("    Error %d:\n        Type = %s\n        File = %s\n        Line = %d\n",
                               error_index, error_type, e->file, e->line);
                    }
                }

                assert(0, "Errors Found");
            }
        }
    }


    return(res);
}

#include "tests.h"

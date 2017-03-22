/*===================================================================================================
  File:                    lexer.h
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#if !defined(_UTILS_H)

#include "shared.h"

// TODO(Jonny): This should probably be a flag, rather than compiled into the preprocessor.
#if COMPILER_MSVC
    #define GUID__(file, seperator, line) file seperator line ")"
    #define GUID_(file, line) GUID__(file, "(", #line)
    #define GUID(file, line) GUID_(file, line)
    #define MAKE_GUID GUID(__FILE__, __LINE__)
#else
    #define GUID__(file, seperator, line) file seperator line ":1: error:"
    #define GUID_(file, line) GUID__(file, ":", #line)
    #define GUID(file, line) GUID_(file, line)
    #define MAKE_GUID GUID(__FILE__, __LINE__)
#endif

#define dir_name "pp_generated" // The directory the generated code goes in.

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
    ErrorType_did_not_write_entire_file,
    ErrorType_did_not_read_entire_file,
    ErrorType_could_not_create_directory,
    ErrorType_incorrect_number_of_members_for_struct,
    ErrorType_incorrect_struct_name,
    ErrorType_incorrect_number_of_base_structs,

    ErrorType_count,
};

struct Error {
    ErrorType type;
    Char const *guid;
};

#define push_error(type) push_error_(type, MAKE_GUID)

Void push_error_(ErrorType type, Char const *guid);
Char const *ErrorTypeToString(ErrorType e);
Bool print_errors(void);

// Google Test compains...
#if defined(assert)
    #undef assert
#endif

#if INTERNAL
    #define assert(Expression) do { static Bool Ignore = false; if(!Ignore) { if(!(Expression)) { push_error(ErrorType_assert_failed); *cast(int volatile *)0 = 0; } } } while(0)
#else
    #define assert(Expression) {}
#endif

struct File {
    Char *data;
    PtrSize size;
};

//
// Scratch memory
//
// A quick-to-access temp region of memory. Should be frequently cleared.
static Int const scratch_memory_size = 256 * 256;
Void *push_scratch_memory(Int size = scratch_memory_size);
Void clear_scratch_memory(void);
Void free_scratch_memory();

//
// String
//
struct String {
    Char const *e;
    Int len;
};

String create_string(Char const *str, Int len = 0);
Int string_length(Char const *str);
Bool string_concat(Char *dest, Int len, Char const *a, Int a_len, Char const *b, Int b_len);
Bool string_compare(Char const *a, Char const *b, Int len);
Bool string_compare(Char const *a, Char const *b);
Void string_copy(Char *dest, Char const *src);
Bool string_compare(String a, String b);
Bool string_compare_array(String *a, String *b, Int cnt);

Bool string_contains(String str, Char const *target);
Bool string_contains(Char const *str, Char const *target);

Bool is_in_string_array(String target, String *arr, Int arr_cnt);

//
// Maths.
//
struct ResultInt {
    Int e;
    Bool success;
};

ResultInt char_to_int(Char c);
ResultInt string_to_int(String str);
ResultInt string_to_int(Char *str);

Uint32 safe_truncate_size_64(Uint64 v);

//
// Variable.
//
enum Access {
    Access_public,
    Access_private,
    Access_protected,

    Access_count,
};

struct Variable {
    String type;
    String name;
    Access access;
    Int ptr;
    Int array_count; // This is 1 if it's not an array. TODO(Jonny): Is this true anymore?
    Bool is_inside_anonymous_struct;
};

Variable create_variable(Char const *type, Char const *name, Int ptr = 0, Int array_count = 1);
Bool compare_variable(Variable a, Variable b);
Bool compare_variable_array(Variable *a, Variable *b, Int count);

//
// Utils.
//
Char to_caps(Char c);

const Int max_ptr_size = 4;

//
// memset and memcpy
//

Void copy(Void *dst, Void *src, PtrSize size);
#define zero(dst, size) set(dst, 0, size)
Void set(Void *dst, Byte v, PtrSize size);

#define _UTILS_H
#endif

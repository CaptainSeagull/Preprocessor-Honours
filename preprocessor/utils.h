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

    ErrorType_count,
};

struct Error {
    ErrorType type;
    Char *guid;
};

#define push_error(type) push_error_(type, MAKE_GUID)

Void push_error_(ErrorType type, Char *guid);
Char *ErrorTypeToString(ErrorType e);
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
// Memory stuff.
//

// These are implemented in Platform code... but defined here.
Void *system_malloc(PtrSize size, PtrSize cnt = 1);
Bool system_free(Void *ptr);
Void *system_realloc(Void *ptr, PtrSize size);

#if defined(malloc)
    #undef malloc
#endif
#define malloc system_malloc

#if defined(calloc)
    #undef calloc
#endif
#define calloc system_malloc

#if defined(realloc)
    #undef realloc
#endif
#define realloc system_realloc

#if defined(free)
    #undef free
#endif
#define free(x) system_free(x);

#if defined(alloc)
    #undef alloc
#endif
#define alloc(Type, ...) (Type *)system_malloc(sizeof(Type), ##__VA_ARGS__)

#if MEM_CHECK
struct MemList {
    Void *ptr;
    MemList *next;
    Char *guid;
    Bool freed;
};
#if defined(MEM_ROOT_FILE)
    MemList *mem_list_root = 0;
#else
    extern MemList *mem_list_root;
#endif

// malloc.
static Void *malloc_(PtrSize size, Char *guid, PtrSize cnt = 1) {
    Void *res = system_malloc(size * cnt);

    if(res) {
        MemList *cur = cast(MemList *)system_malloc(sizeof(MemList));
        if(!cur) {
            push_error_(ErrorType_ran_out_of_memory, guid);
        } else {
            cur->ptr = res;
            cur->guid = guid;

            if(!mem_list_root) {
                mem_list_root = cur;
            } else {
                MemList *next = mem_list_root;
                while(next->next) next = next->next;

                next->next = cur;
            }
        }
    }

    return(res);
}

// free
static Void free_(Void *ptr) {
    system_free(ptr);
    if(ptr) {
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
}

// realloc
static Void *realloc_(Void *ptr, PtrSize size, Char *guid) {
    Void *res = system_realloc(ptr, size);
    if(ptr) {
        MemList *next = mem_list_root;
        while(next) {
            if(next->ptr == ptr) break;
            next = next->next;
        }

        if(next) next->ptr = res;
        else     push_error_(ErrorType_could_not_find_mallocd_ptr, guid);
    }
    return(res);
}

// malloc
#if defined(malloc)
    #undef malloc
#endif
#define malloc(size) malloc_(size, MAKE_GUID)

// calloc
#if defined(calloc)
    #undef calloc
#endif
#define calloc(size, cnt) malloc_(size, MAKE_GUID, cnt)

// realloc
#if defined(realloc)
    #undef realloc
#endif
#define realloc(ptr, size) realloc_(ptr, size, MAKE_GUID)

// free
#if defined(free)
    #undef free
#endif
#define free(ptr) free_(ptr)

// alloc
#if defined(alloc)
    #undef alloc
#endif
#define alloc(Type, ...) (Type *)malloc_(sizeof(Type), MAKE_GUID, ##__VA_ARGS__)

#endif // MEM_CHECK

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
    Char *e;
    Int len;
};

String create_string(Char *str, Int len = 0);
Int string_length(Char *str);
Bool string_concat(Char *dest, Int len, Char *a, Int a_len, Char *b, Int b_len);
Bool string_compare(Char *a, Char *b, Int len);
Bool string_compare(Char *a, Char *b);
Void string_copy(Char *dest, Char *src);
Bool string_compare(String a, String b);
Bool string_compare_array(String *a, String *b, Int cnt);

Bool string_contains(String str, Char *target);
Bool string_contains(Char *str, Char *target);

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
ResultInt calculator_string_to_int(Char *str);

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
    Bool is_ptr;
    Int array_count; // This is 1 if it's not an array. TODO(Jonny): Is this true anymore?
    Bool is_inside_anonymous_struct;
};

Variable create_variable(Char *type, Char *name, Bool is_ptr = false, Int array_count = 1);
Bool compare_variable(Variable a, Variable b);
Bool compare_variable_array(Variable *a, Variable *b, Int count);

//
// Utils.
//
Char to_caps(Char c);


//
// memset and memcpy
//

Void copy(Void *dst, Void *src, PtrSize size);
#define zero(dst, size) set(dst, 0, size)
Void set(Void *dst, Byte v, PtrSize size);

#if 0
    #if !RUN_TESTS
        #if OS_WIN32
            extern "C" void   *__cdecl memcpy(_Out_writes_bytes_all_(_Size) void *_Dst, _In_reads_bytes_(_Size) const void *_Src, _In_ size_t _Size);
            extern "C" void   *__cdecl memset(_Out_writes_bytes_all_(_Size) void *_Dst, _In_ int _Val, _In_ size_t _Size);
        #else
            extern "C" void *memcpy(void *Dest, void const *Source, PtrSize Size);
            extern "C" void *memset(void *Dest, int Value, PtrSize NumBytesToSet);
        #endif

    #endif
#endif

#define _UTILS_H
#endif

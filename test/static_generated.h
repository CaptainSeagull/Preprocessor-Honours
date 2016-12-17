// Preprocessor API.

// Reference.

// Structs
//     size_t pp::serialize(TYPE var, char *buffer, size_t buf_size);   - Serialize a struct for output.
//     bool pp::print(TYPE var, char *buffer = 0, size_t buf_size = 0); - Print a struct to the console.
//     int pp::get_num_of_members(TYPE type);                           - Get the number of members of a struct/class.
//     char const *pp::type_to_string(TYPE t);                          - Turn type t into a string literal.

// Enums
//     char const *pp::enum_to_string(EnumType, EnumType value);        - Convert an enum index to a string.
//     int pp::string_to_enum(EnumType, char const *str);               - Convert a string to an enum index.
//     size_t pp::get_number_of_enum_elements(EnumType);                - Get the total number of elements for an enum.

// Misc.
//     bool pp::type_compare(TYPE a, TYPE b);                           - Tests whether two types are the same.

//
// Code shared between generated files.
#if !defined(STATIC_GENERATED_H)

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

// Overloadable malloc/free.
#if !defined(pp_alloc)
    #define pp_alloc malloc
#endif
#if !defined(pp_free)
    #define pp_free free
#endif
#if !defined(pp_print)
    #define pp_print printf
#endif

namespace pp { // PreProcessor

typedef char _char;
typedef short _short;
typedef int _int;
typedef long _long;
typedef float _float;
typedef double _double;
typedef bool _bool;

struct MemberDefinition {
    int/*MetaType*/ type;
    char const *name;
    size_t offset;
    int is_ptr;
    int arr_size;
};

struct Variable {
    char const *ret_type;
    char const *name;
};

#define get_num_of_members(type) get_number_of_members_<type>()

#define serialize(var, buf, size) serialize_struct_<decltype(var)>(var, #var, 0, buf, size, 0)

// TODO(Jonny): Maybe make malloc/free/printf default parameters?
#define print(var, ...) print_<decltype(var)>(var, #var, ##__VA_ARGS__)
template<typename T>static bool print_(T var, char const *name, char *buf = 0, size_t size = 0)
{
    bool res = false, custom_buf = false;

    if(!buf) {
        size = 256 * 256;
        buf = (char *)pp_alloc(size);
        custom_buf = true;
    }

    if(buf) {
        memset(buf, 0, size);
        size_t bytes_written = serialize_struct_<T>(var, name, 0, buf, size, 0);
        if(bytes_written < size) {
            printf("%s", buf);
            res = true;
        }

        if(custom_buf) { pp_free(buf); }
    }

    return(res);
}

#define enum_to_string(Type, v) enum_to_string_##Type(v)

#define string_to_enum(Type, str) string_to_enum_##Type(str)

#define get_number_of_enum_elements(Type) number_of_elements_in_enum_##Type

template<class T, class U>struct TypeCompare_{ enum {e = 0}; };
template<class T>struct TypeCompare_<T, T>{ enum {e = 1}; };
#define type_compare(a, b) TypeCompare_<a, b>::e

#define type_to_string(Type) type_to_string_<Type>()

#define get_base_type_count(Type) get_base_type_count_<Type>()
#define get_base_type_as_string(Type, ...) get_base_type_as_string_<Type>(##__VA_ARGS__)

#define fuzzy_type_compare(A, B) fuzzy_type_compare_<A, B>()
template<typename T, typename U> bool fuzzy_type_compare_(void)
{
    char const *a_str = type_to_string(T);
    char const *b_str = type_to_string(U);
    if((a_str) && (b_str)) {
        if(strcmp(a_str, b_str) == 0) {
            return(true);
        } else {
            int base_count = get_base_type_count(T);
            for(int base_index = 0; (base_index < base_count); ++base_index) {
                char const *str = get_base_type_as_string(T);
                if(strcmp(b_str, str)) { return(true); }
            }
            
            for(int base_index = 0; (base_index < base_count); ++base_index) {
                char const *str = get_base_type_as_string(U);
                if(strcmp(a_str, str)) { return(true); }
            }
        }
    }

    return(false);
}

// TODO(Jonny): MSVC sucks. Use stb_sprintf?...
#if defined(_MSC_VER)
    #define my_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)
#else
    #define my_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)
#endif

} // namespace pp

// TODO(Jonny): Make sure I #undef all internal macros at end.
#define STATIC_GENERATED
#endif // !defined(STATIC_GENERATED_H)

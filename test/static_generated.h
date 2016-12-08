// Preprocessor API.

// Reference.

// Structs
//     size_t serialize_struct(void *var, char *buffer, size_t buf_size);         - Serialize a struct for output (requires decltype).
//     size_t serialize_struct(void *var, TYPE t, char *buffer, size_t buf_size); - Serialize a struct for output.
//     int get_num_of_members(TYPE type);                                         - Get the number of members of a struct/class.
//     char const *type_to_string(TYPE t);                                        - Turn type t into a string literal.

// Enums
//     char const *enum_to_string(EnumType, EnumType value);                      - Convert an enum index to a string.
//     int string_to_enum(EnumType, char const *str);                             - Convert a string to an enum index.
//     size_t get_number_of_enum_elements(EnumType);                              - Get the total number of elements for an enum.

// Misc.
//     bool type_compare(TYPE a, TYPE b);                                         - Tests whether two types are the same.

//
// Code shared between generated files.
#if !defined(STATIC_GENERATED)

#include <stdio.h>
#include <string.h>
#include <assert.h>

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

#define serialize_struct_with_type(var, type, buffer, size) serialize_struct_<type>(&var, #var, 0, buffer, size, 0)
#define serialize_struct(var, buffer, size) serialize_struct_with_type(var, decltype(var), buffer, size)

#define enum_to_string(Type, v) enum_to_string_##Type(v)

#define string_to_enum(Type, str) string_to_enum_##Type(str)

#define get_number_of_enum_elements(Type) number_of_elements_in_enum_##Type

template<class T, class U>struct TypeCompare_{ enum {e = 0}; };
template<class T>struct TypeCompare_<T, T>{ enum {e = 1}; };
#define type_compare(a, b) TypeCompare_<a, b>::e

#define type_to_string(Type) type_to_string_<Type>()

// TODO(Jonny): MSVC sucks. Use stb_sprintf?...
#if defined(_MSC_VER)
    #define my_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)
#else
    #define my_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)
#endif

#define STATIC_GENERATED
#endif // !defined(STATIC_GENERATED)

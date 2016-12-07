/*
    Preprocessor API.
*/

/*  Quick Reference.

    - Serialize a struct for output.
    size_t serialize_struct(void *var, Type var_type, char *buffer, size_t buf_size);

    - Get the number of members of a struct/class.
    int get_num_of_members(TYPE type);

    - Convert an enum index to a string.
    char const *enum_to_string(EnumType, EnumType value);

    - Convert a string to an enum index.
    int string_to_enum(EnumType, char const *str);

    - Get the total number of elements for an enum.
    size_t get_number_of_enum_elements(EnumType);
*/


/*  Detailed Reference.

    ================================================================================

    size_t serialize_struct(void *var, Type var_type, char *buffer, size_t buf_size);
     - Serialize a struct for outputting. This is more for debugging data in real time,
       rather writing data to disk.

    Parameters
     - void *var       - The variable to be serialized.
     - TYPE var_type   - The literal type of the variable to be serialized. NOTE - Does not work with decltype
     - char *buffer    - The buffer to write the serialized data into.
     - size_t buf_size - The size of the butt to write the data into.

    Return Value
     - size_t - The number of bytes written into buffer.

    ================================================================================

    int get_num_of_members(TYPE type);
     - Get the number of member variables in a struct/class.

    Parameters
     - TYPE type - The type of the struct/class you want to get the members for.

    Return Value
     - int - The number of member variables in the stuct/class.

    ================================================================================

    char const *enum_to_string(EnumType, EnumType value);
     - Convert an enum value into a string.

    Parameters
    - EnumType       - The type of the enum.
    - EnumType value - The value of the enum.


    Return Value
     - char const * - A string literal of the enum index name.

    ================================================================================

    int string_to_enum(EnumType, char const *str);
     - Convert a string to an enum value.

    Parameters
     - EnumType        - The type of the enum.
     - char const *str - A string version of the enum index.

    Return Value
    - int - The index version of the string passed in.

    ================================================================================

    size_t get_number_of_enum_elements(EnumType);
    - Get the total number of elements in an enum.

    Parameters
    - EnumType - The type of the enum you want.

    Return Value
     - size_t - The total number of elements in the enum.

    ================================================================================
*/


/* Code shared between generated files. */
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
#if defined(__cplusplus)
    typedef bool _bool;
#else
    typedef int _bool;
#endif

typedef struct MemberDefinition {
    int/*MetaType*/ type;
    char const *name;
    size_t offset;
    int is_ptr;
    int arr_size;
} MemberDefinition;

typedef struct Variable {
    char const *ret_type;
    char const *name;
} Variable;

/* get_num_of_members(TYPE type); */
#define get_num_of_members(type) num_members_for_##type

/* size_t serialize_struct(void *var, char *buffer, size_t buf_size); */

/* char const *enum_to_string(EnumType, EnumType value); */
#define enum_to_string(Type, v) enum_to_string_##Type(v)

/* int string_to_enum(EnumType, char const *str); */
#define string_to_enum(Type, str) string_to_enum_##Type(str)

/* size_t get_number_of_enum_elements(EnumType); */
#define get_number_of_enum_elements(Type) number_of_elements_in_enum_##Type

/* TODO(Jonny): Document this! */
#define get_struct_member_type_(Struct, member) Struct##member
#define get_struct_member_type(Struct, member) get_struct_member_type_(Struct, member)

/* TODO(Jonny): Document this! */
template<class T, class U>struct TypeCompare_{ enum {e = 0}; };
template<class T>struct TypeCompare_<T, T>{ enum {e = 1}; };
#define type_compare(a, b) TypeCompare_<a, b>::e

/* TODO(Jonny): Document this! */
#define type_to_string(Type) type_to_string_<Type>()

/* Because MSVC sucks. TODO(Jonny): Use stb_sprintf?... */
#if defined(_MSC_VER)
    #define my_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)
#else
    #define my_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)
#endif

#define STATIC_GENERATED
#endif /* !defined(STATIC_GENERATED) */

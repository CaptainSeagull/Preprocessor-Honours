#if !defined(STATIC_GENERATED)

#include <stdio.h>

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

#define get_num_of_members(type) num_members_for_##type

/* size_t serialize_struct(void *var, Type var_type, char *buffer, size_t buf_size); */
#define serialize_struct(var, type, buffer, buf_size) serialize_struct_(var, type, #var, 0, buffer, buf_size, 0)
#define serialize_struct_(var, type, name, indent, buffer, buf_size, bytes_written) serialize_struct__((void *)&var, members_of_##type, name, indent, get_num_of_members(type), buffer, buf_size, bytes_written)
size_t serialize_struct__(void *var, MemberDefinition members_of_Something[], char const *name, int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written);


/* char const *enum_to_string(EnumType, EnumType value); */
#define enum_to_string(Type, v) enum_to_string_##Type(v)

/* size_t get_number_of_enum_elements(EnumType); */
#define get_number_of_enum_elements(Type) number_of_elements_in_enum_##Type


#define STATIC_GENERATED
#endif
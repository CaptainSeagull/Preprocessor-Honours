#if !defined(GENERATED_H) /* TODO(Jonny): Add the actual filename in here? */

#include "static_generated.h"

/* Enum with field for every type detected. */
typedef enum MetaType {
    meta_type_char,
    meta_type_short,
    meta_type_int,
    meta_type_long,
    meta_type_float,
    meta_type_double,
    meta_type_bool,
    meta_type_V2,
    meta_type_Bar,
    meta_type_Foo,
} MetaType;

/* Struct meta data. */

/* Struct typedefs. */
typedef struct _V2 _V2;
typedef struct _Bar _Bar;
typedef struct _Foo _Foo;

/* Recreated structs. */
struct _V2 {  _int x;  _int y;  };
struct _Bar {  _int i;  _float f;  _double d;  _V2 v2;  };
struct _Foo : public _Bar {  _char *str;  _int *ip;  _float *fp;  _bool *b;  _double *p_array[5];  };

/* Meta data for: V2. */
static int num_members_for_V2 = 2;
static MemberDefinition members_of_V2[] = {
    /* Members. */
    {meta_type_int, "x", (size_t)&((_V2 *)0)->x, 0, 1},
    {meta_type_int, "y", (size_t)&((_V2 *)0)->y, 0, 1},
};
/* Meta data for: Bar. */
static int num_members_for_Bar = 4;
static MemberDefinition members_of_Bar[] = {
    /* Members. */
    {meta_type_int, "i", (size_t)&((_Bar *)0)->i, 0, 1},
    {meta_type_float, "f", (size_t)&((_Bar *)0)->f, 0, 1},
    {meta_type_double, "d", (size_t)&((_Bar *)0)->d, 0, 1},
    {meta_type_V2, "v2", (size_t)&((_Bar *)0)->v2, 0, 1},
};
/* Meta data for: Foo. */
static int num_members_for_Foo = 9;
static MemberDefinition members_of_Foo[] = {
    /* Members. */
    {meta_type_char, "str", (size_t)&((_Foo *)0)->str, 1, 1},
    {meta_type_int, "ip", (size_t)&((_Foo *)0)->ip, 1, 1},
    {meta_type_float, "fp", (size_t)&((_Foo *)0)->fp, 1, 1},
    {meta_type_bool, "b", (size_t)&((_Foo *)0)->b, 1, 1},
    {meta_type_double, "p_array", (size_t)&((_Foo *)0)->p_array, 1, 5},

    /* Inherited Members. */
    {meta_type_int, "i", (size_t)&((_Foo *)0)->i, 0, 1},
    {meta_type_float, "f", (size_t)&((_Foo *)0)->f, 0, 1},
    {meta_type_double, "d", (size_t)&((_Foo *)0)->d, 0, 1},
    {meta_type_V2, "v2", (size_t)&((_Foo *)0)->v2, 0, 1},
};

/* Function to serialize a struct to a char array buffer. */
static size_t
serialize_struct__(void *var, MemberDefinition members_of_Something[], char const *name, int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written)
{
    char indent_buf[256];
    int unsigned indent_index = 0, member_index = 0, arr_index = 0;

    memset(indent_buf, 0, 256);

    assert((var) && (members_of_Something) && (num_members > 0) && (buffer) && (buf_size > 0));
    memset(buffer + bytes_written, 0, buf_size - bytes_written);
    for(indent_index = 0; (indent_index < indent); ++indent_index) {
        indent_buf[indent_index] = ' ';
    }

    bytes_written += sprintf((char *)buffer + bytes_written, "\n%s%s", indent_buf, name);
    indent += 4;

    for(indent_index = 0; (indent_index < indent); ++indent_index) {
        indent_buf[indent_index] = ' ';
    }

    for(member_index = 0; (member_index < num_members); ++member_index) {
         MemberDefinition *member = members_of_Something + member_index;

         void *member_ptr = (char *)var + member->offset;
         switch(member->type) {
            case meta_type_float: {
                if(member->arr_size > 1) {
                    size_t *value = (size_t *)member_ptr;
                    for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                        int is_null = (member->is_ptr) ? !(*(float **)(value + arr_index)) : 0;
                        if(!is_null) {
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (member->is_ptr) ? **(float **)(value + arr_index) : value[arr_index]);
                        } else {
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index);
                        }
                    }
                } else {
                    float *value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;
                    if(value) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s%s = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat *%s = (null)", indent_buf, member->name);
                    }
                }
            } break;

            case meta_type_short: case meta_type_int: case meta_type_long: {
                if(member->arr_size > 1) {
                    size_t *value = (size_t *)member_ptr;
                    for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                        int is_null = (member->is_ptr) ? !(*(int **)(value + arr_index)) : 0;
                        if(!is_null) {
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (member->is_ptr) ? *(int *)value[arr_index] : (int)value[arr_index]);
                        } else {
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index);
                        }
                    }
                } else {
                    int *value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;
                    if(value) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s%s = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint *%s = (null)", indent_buf, member->name);
                    }
                }
            } break;

#if defined(__cplusplus)
            case meta_type_bool: {
                if(member->arr_size > 1) {
                    size_t *value = (size_t *)member_ptr;
                    for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                        int is_null = (member->is_ptr) ? !(*(bool **)(value + arr_index)) : 0;
                        if(is_null) {
                            int value_to_print = (member->is_ptr) ? **(bool **)(value + arr_index) : value[arr_index];
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sbool %s%s[%d] = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (value_to_print) ? "true" : "false");
                        } else {
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sbool %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index);
                        }
                    }
                } else {
                    bool *value = (member->is_ptr) ? *(bool **)member_ptr : (bool *)member_ptr;
                    if(value) {
                        int value_to_print = value[arr_index];
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sbool %s%s = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, (value[arr_index]) ? "true" : "false");
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sbool *%s = (null)", indent_buf, member->name);
                    }
                }
            } break;
#endif /* #if defined(__cplusplus) */

            case meta_type_char: {
                char *value = (member->is_ptr) ? *(char **)member_ptr : (char *)member_ptr;
                if(value) {
                    if(member->is_ptr) {
                        bytes_written += sprintf(buffer + bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, value);
                    } else {
                        bytes_written += sprintf(buffer + bytes_written, "\n%schar %s = %c", indent_buf, member->name, *value);
                    }
                } else {
                    bytes_written += sprintf((char *)buffer + bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                }
            } break;

            case meta_type_double: {
                if(member->arr_size > 1) {
                    size_t *value = (size_t *)member_ptr;
                    for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                        int is_null = (member->is_ptr) ? !(*(double **)(value + arr_index)) : 0;
                        if(!is_null) {
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sdouble %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (member->is_ptr) ? **(double **)(value + arr_index) : value[arr_index]);
                        } else {
                            bytes_written += sprintf((char *)buffer + bytes_written, "\n%sdouble %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index);
                        }
                    }
                } else {
                    double *value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;
                    if(value) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sdouble %s%s = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sdouble *%s = (null)", indent_buf, member->name);
                    }
                }
            } break;

            default: {
                switch(member->type) {
                    case meta_type_V2: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, V2, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, V2, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_Bar: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, Bar, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, Bar, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_Foo: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, Foo, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, Foo, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                }
            } break; /* default */
        }
    }

    return(bytes_written);
}

/* Enum meta data. */

/* Meta Data for: Letters. */
static size_t number_of_elements_in_enum_Letters = 4;
static char const *
enum_to_string_Letters(int v)
{
    switch(v) {
        case 0: { return("letter_a"); } break;
        case 1: { return("letter_b"); } break;
        case 2: { return("letter_c"); } break;
        case 3: { return("void"); } break;

        default: { return(0); } break; /* v is out of bounds. */
    }
}

static int
string_to_enum_Letters(char const *str)
{
    if(0) {}
    else if(strcmp(str, "letter_a") == 0) { return(0); }
    else if(strcmp(str, "letter_b") == 0) { return(1); }
    else if(strcmp(str, "letter_c") == 0) { return(2); }
    else if(strcmp(str, "void") == 0) { return(3); }

    else { return(0); } /* str didn't match. TODO(Jonny): Throw an error here? */
}

#define GENERATED_H
#endif /* !defined(GENERATED_H) */

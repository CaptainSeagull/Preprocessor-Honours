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
    meta_type_foo,
} MetaType;

/* Struct meta data. */

/* Recreated structs. */
typedef struct _foo {  _int x;  _int y;  } _foo;

/* Meta data for: foo. */
static int num_members_for_foo = 2;
static MemberDefinition members_of_foo[] = {
    {meta_type_int, "x", (size_t)&((_foo *)0)->x, 0, 1},
    {meta_type_int, "y", (size_t)&((_foo *)0)->y, 0, 1},
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
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (member->is_ptr) ? **(float **)(value + arr_index) : value[arr_index]);
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
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (member->is_ptr) ? *(int *)value[arr_index] : (int)value[arr_index]);
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

            case meta_type_bool: {
                if(member->arr_size > 1) {
                    size_t *value = (size_t *)member_ptr;
                    for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                        int value_to_print = (member->is_ptr) ? **(_bool **)(value + arr_index) : value[arr_index];
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sbool %s%s[%d] = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (value_to_print) ? "true" : "false");
                    }
                } else {
                    _bool *value = (member->is_ptr) ? *(_bool **)member_ptr : (_bool *)member_ptr;
                    if(value) {
                        int value_to_print = value[arr_index];
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sbool %s%s = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, (value[arr_index]) ? "true" : "false");
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sbool *%s = (null)", indent_buf, member->name);
                    }
                }
            } break;

            case meta_type_char: {
                char *value = (member->is_ptr) ? *(char **)member_ptr : (char *)member_ptr;
                if(value) {                    if(member->is_ptr) {
                        bytes_written += sprintf(buffer + bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, *(char **)value);
                    } else {
                        bytes_written += sprintf(buffer + bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)value);
                    }
                } else {
                    bytes_written += sprintf((char *)buffer + bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                }
            } break;

            case meta_type_double: {
                if(member->arr_size > 1) {
                    size_t *value = (size_t *)member_ptr;
                    for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sdouble %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, arr_index, (member->is_ptr) ? **(double **)(value + arr_index) : value[arr_index]);
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
                    case meta_type_foo: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, foo, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, foo, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                }
            } break; /* default */
        }
    }

    return(bytes_written);
}

#define GENERATED_H
#endif /* !defined(GENERATED_H) */

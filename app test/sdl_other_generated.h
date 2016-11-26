#if !defined(GENERATED_H)

#include "static_generated.h"

/* Enum with field for every type detected. */
typedef enum MetaType {
    meta_type_char,
    meta_type_short,
    meta_type_int,
    meta_type_long,
    meta_type_float,
    meta_type_double,
    meta_type_foo,
} MetaType;


/* Struct meta data. */

/* Meta data for: foo. */
static int const num_members_for_foo = 2;
static MemberDefinition *
get_members_of_foo(void)
{
    typedef struct foo {  int x;  int y;  } foo;

    static MemberDefinition res[] = {
        {meta_type_int, "x", (size_t)&((foo *)0)->x, 0, 1},
        {meta_type_int, "y", (size_t)&((foo *)0)->y, 0, 1},
    };

    return(res);
}


/* Function to serialize a struct to a char array buffer. */
static size_t
serialize_struct__(void *var, MemberDefinition members_of_Something[], char const *name, int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written)
{
    char indent_buf[256];
    unsigned indent_index = 0, member_index = 0, arr_index = 0;

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
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    float *value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s[%d] = %f", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s = %f", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            case meta_type_short: case meta_type_int: case meta_type_long: {
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    int *value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s[%d] = %d", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s = %d", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            case meta_type_char: {
                if(member->is_ptr) {
                    bytes_written += sprintf(buffer + bytes_written, "\n%schar * %s = \"%s\"", indent_buf, member->name, *(char **)member_ptr);
                } else {
                    bytes_written += sprintf(buffer + bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)member_ptr);
                }
            } break;

            case meta_type_double: {
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    double *value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s[%d] = %f", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s = %f", indent_buf, member->name, value[arr_index]);
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

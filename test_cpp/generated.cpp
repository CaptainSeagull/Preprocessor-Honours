#if !defined(GENERATED_CPP)

#include "generated.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

//
// Recreated structs.
//
typedef struct Position {
    float x;
    float y;
} Position;

typedef struct test {
    int sixteen[16];
    float float_four[4];
    double double_four[4];
    int one;
    Position *pos;
    char *str;
} test;

typedef struct FooOne {
    int one;
    int two;
    int three;
} FooOne;

typedef struct SomeStruct {
    int a;
    int b;
} SomeStruct;

//
// Struct meta data.
//
// Meta data for: Position
MemberDefinition members_of_Position[] = {
    {meta_type_float, "x", (size_t)&((Position *)0)->x, 0, 1},
    {meta_type_float, "y", (size_t)&((Position *)0)->y, 0, 1},
};
// Meta data for: test
MemberDefinition members_of_test[] = {
    {meta_type_int, "sixteen", (size_t)&((test *)0)->sixteen, 0, 16},
    {meta_type_float, "float_four", (size_t)&((test *)0)->float_four, 0, 4},
    {meta_type_double, "double_four", (size_t)&((test *)0)->double_four, 0, 4},
    {meta_type_int, "one", (size_t)&((test *)0)->one, 0, 1},
    {meta_type_Position, "pos", (size_t)&((test *)0)->pos, 1, 1},
    {meta_type_char, "str", (size_t)&((test *)0)->str, 1, 1},
};
// Meta data for: FooOne
MemberDefinition members_of_FooOne[] = {
    {meta_type_int, "one", (size_t)&((FooOne *)0)->one, 0, 1},
    {meta_type_int, "two", (size_t)&((FooOne *)0)->two, 0, 1},
    {meta_type_int, "three", (size_t)&((FooOne *)0)->three, 0, 1},
};
// Meta data for: SomeStruct
MemberDefinition members_of_SomeStruct[] = {
    {meta_type_int, "a", (size_t)&((SomeStruct *)0)->a, 0, 1},
    {meta_type_int, "b", (size_t)&((SomeStruct *)0)->b, 0, 1},
};

//
// Function meta data.
//
FunctionMetaData function_data_foo = {
    "static",
    "BarFoo",
    "foo",
    2,
    {
        {"char", "str"},
        {"int", "len"}
    }
};

FunctionMetaData function_data_some_function = {
    0,
    "void",
    "some_function",
    1,
    {
        {"SomeStruct", "some_struct"}
    }
};


//
// Method meta data.
//
// FooOne's methods.
FunctionMetaData method_data_FooOneinline_func = {
    0,
    "void",
    "inline_func",
    2,
    {
        {"int", "one"},
        {"int", "two"}
    }
};


FunctionMetaData method_data_FooOnemember_func = {
    0,
    "void",
    "member_func",
    3,
    {
        {"int", "one"},
        {"int", "two"},
        {"int", "three"}
    }
};



// TODO(Jonny): At some point, I'd like to replace memset, assert, and sprintf with my own versions. 
size_t
serialize_struct__(void *var, MemberDefinition members_of_Something[], int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written)
{
    char indent_buf[256] = {0};
    int indent_index = 0, member_index = 0, arr_index = 0;

    assert((var) && (members_of_Something) && (num_members > 0) && (buffer) && (buf_size > 0));
    memset(buffer + bytes_written, 0, buf_size - bytes_written);/* TODO(Jonny): Implement my own memset. */
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
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s[%d] : %f", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s : %f", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            case meta_type_short: case meta_type_int: case meta_type_long: {
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    int *value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s[%d] : %d", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s : %d", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            case meta_type_char: {
                if(member->is_ptr) {
                    bytes_written += sprintf(buffer + bytes_written, "\n%schar * %s : %s", indent_buf, member->name, *(char **)member_ptr);
                } else {
                    bytes_written += sprintf(buffer + bytes_written, "\n%schar %s : %c", indent_buf, member->name, *(char *)member_ptr);
                }
            } break;

            case meta_type_double: {
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    double *value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s[%d] : %f", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s : %f", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            default: {
                switch(member->type) {
                    case meta_type_Position: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, Position, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, Position, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;
                     case meta_type_test: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, test, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, test, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;
                     case meta_type_FooOne: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, FooOne, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, FooOne, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;
                     case meta_type_SomeStruct: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, SomeStruct, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, SomeStruct, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;
                 }
            } break; // default
        }
    }

    return(bytes_written);
}

size_t
serialize_function_(FunctionMetaData func, char *buf, size_t buf_size)
{
    size_t bytes_written = 0;
    int param_index = 0;

    bytes_written = sprintf(buf, "Function %s\n    Linkage: %s\n    Return Type: %s\n    Param Count: %u\n",
                            func.name, (func.linkage) ? func.linkage : "normal", func.ret_type, func.param_count);

    for(param_index = 0; (param_index < func.param_count); ++param_index) {
        Variable *param = func.params + param_index;
        bytes_written += sprintf(buf + bytes_written, "Param %u : %s %s", param_index + 1, param->ret_type, param->name);
    }

    assert(bytes_written <  buf_size);
    return(bytes_written);
}


#define GENERATED_CPP
#endif // #if !defined(GENERATED_CPP)

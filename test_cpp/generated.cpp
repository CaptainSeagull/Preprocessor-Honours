#if !defined(GENERATED_CPP)

#include "generated.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

//
// Recreated structs.
//
typedef struct Base {
    int a;
    int b;
    int c;
} Base;

typedef struct Sub {
    int x;
    int y;
    int z;
} Sub;

typedef struct DemoString {
    char *str;
    int len;
} DemoString;

typedef struct StructTest {
    int i;
    float f;
    DemoString str;
} StructTest;

typedef struct SomeStruct {
    int a;
    int b;
} SomeStruct;

//
// Struct meta data.
//
// Meta data for: Base
MemberDefinition members_of_Base[] = {
    {meta_type_int, "a", (size_t)&((Base *)0)->a, 0, 1},
    {meta_type_int, "b", (size_t)&((Base *)0)->b, 0, 1},
    {meta_type_int, "c", (size_t)&((Base *)0)->c, 0, 1},
};
// Meta data for: Sub
MemberDefinition members_of_Sub[] = {
    {meta_type_int, "x", (size_t)&((Sub *)0)->x, 0, 1},
    {meta_type_int, "y", (size_t)&((Sub *)0)->y, 0, 1},
    {meta_type_int, "z", (size_t)&((Sub *)0)->z, 0, 1},
};
// Meta data for: DemoString
MemberDefinition members_of_DemoString[] = {
    {meta_type_char, "str", (size_t)&((DemoString *)0)->str, 1, 1},
    {meta_type_int, "len", (size_t)&((DemoString *)0)->len, 0, 1},
};
// Meta data for: StructTest
MemberDefinition members_of_StructTest[] = {
    {meta_type_int, "i", (size_t)&((StructTest *)0)->i, 0, 1},
    {meta_type_float, "f", (size_t)&((StructTest *)0)->f, 0, 1},
    {meta_type_DemoString, "str", (size_t)&((StructTest *)0)->str, 0, 1},
};
// Meta data for: SomeStruct
MemberDefinition members_of_SomeStruct[] = {
    {meta_type_int, "a", (size_t)&((SomeStruct *)0)->a, 0, 1},
    {meta_type_int, "b", (size_t)&((SomeStruct *)0)->b, 0, 1},
};

//
// Function meta data.
//
FunctionMetaData function_data_function_test = {
    0,
    "int",
    "function_test",
    3,
    {
        {"float", "f"},
        {"int", "i"},
        {"char", "str"}
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
                    case meta_type_Base: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, Base, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, Base, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;
                     case meta_type_Sub: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, Sub, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, Sub, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;
                     case meta_type_DemoString: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, DemoString, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, DemoString, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;
                     case meta_type_StructTest: {
                        if(member->is_ptr) {
                            bytes_written += serialize_struct_(**(char **)member_ptr, StructTest, indent + 4, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written += serialize_struct_(*(char *)member_ptr, StructTest, indent + 4, buffer, buf_size - bytes_written, bytes_written);
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

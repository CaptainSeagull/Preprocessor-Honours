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

/* size_t serialize_struct(void *var, type VariableType, char *buffer, size_t buf_size); */
#define serialize_struct(var, type, buffer, buf_size) serialize_struct_(var, type, 0, buffer, buf_size, 0)
#define serialize_struct_(var, type, indent, buffer, buf_size, bytes_written) serialize_struct__((void *)&var, members_of_##type, indent, get_num_of_members(type), buffer, buf_size, bytes_written)
size_t serialize_struct__(void *var, MemberDefinition members_of_Something[], int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written);

#define MAX_NUMBER_OF_PARAMS (32)
typedef struct FunctionMetaData {
    char const *linkage;
    char const *ret_type;
    char const *name;
    int param_count;
    Variable params[MAX_NUMBER_OF_PARAMS];
} FunctionMetaData;

/* FunctionMetaData get_func_meta_data(function_name); */
#define get_func_meta_data(func) function_data_##func
#define get_method_meta_data__(macro, method) macro##method

#define serialize_function(func, buf, buf_size) serialize_function_(get_func_meta_data(func), buf, buf_size)
size_t serialize_function_(FunctionMetaData func, char *buf, size_t buf_size);

#define get_method_meta_data__(macro, method) macro##method
#define get_method_meta_data_(macro, StructType, method) get_method_meta_data__(macro##StructType, method)
#define get_method_meta_data(StructType, method) get_method_meta_data_(method_data_, StructType, method)

#define STATIC_GENERATED
#endif
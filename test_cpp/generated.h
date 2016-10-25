#if !defined(GENERATED_H)

#include <stdio.h>

typedef enum MetaType {
    meta_type_char,
    meta_type_short,
    meta_type_int,
    meta_type_long,
    meta_type_float,
    meta_type_double,
    meta_type_Base,
    meta_type_Sub,
    meta_type_DemoString,
    meta_type_StructTest,
    meta_type_SomeStruct,
} MetaType;

//
// Struct meta data.
//
typedef struct MemberDefinition {
    MetaType type;
    char const *name;
    size_t offset;
    int is_ptr;
    int arr_size;
} MemberDefinition;

#define get_num_of_members(type) num_members_for_##type

// Meta Data for: Base
extern MemberDefinition members_of_Base[];
static size_t const num_members_for_Base = 3;

// Meta Data for: Sub
extern MemberDefinition members_of_Sub[];
static size_t const num_members_for_Sub = 3;

// Meta Data for: DemoString
extern MemberDefinition members_of_DemoString[];
static size_t const num_members_for_DemoString = 2;

// Meta Data for: StructTest
extern MemberDefinition members_of_StructTest[];
static size_t const num_members_for_StructTest = 3;

// Meta Data for: SomeStruct
extern MemberDefinition members_of_SomeStruct[];
static size_t const num_members_for_SomeStruct = 2;


// size_t serialize_struct(void *var, type VariableType, char *buffer, size_t buf_size);
#define serialize_struct(var, type, buffer, buf_size) serialize_struct_(var, type, 0, buffer, buf_size, 0)
#define serialize_struct_(var, type, indent, buffer, buf_size, bytes_written) serialize_struct__((void *)&var, members_of_##type, indent, get_num_of_members(type), buffer, buf_size, bytes_written)
size_t serialize_struct__(void *var, MemberDefinition members_of_Something[], int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written);

//
// Function meta data.
//
typedef struct Variable {
    char const *ret_type;
    char const *name;
} Variable;

#define MAX_NUMBER_OF_PARAMS (32)
typedef struct FunctionMetaData {
    char const *linkage;
    char const *ret_type;
    char const *name;
    int param_count;
    Variable params[MAX_NUMBER_OF_PARAMS];
} FunctionMetaData;

// FunctionMetaData get_func_meta_data(function_name);
#define get_func_meta_data(func) function_data_##func
extern FunctionMetaData function_data_function_test;
extern FunctionMetaData function_data_some_function;


//
// Member function meta data.
//
#define get_method_meta_data__(macro, method) macro##method
#define get_method_meta_data_(macro, StructType, method) get_method_meta_data__(macro##StructType, method)
#define get_method_meta_data(StructType, method) get_method_meta_data_(method_data_, StructType, method)



// size_t serialize_function(function_name, char *buf, size_t buf_size);
#define serialize_function(func, buf, buf_size) serialize_function_(get_func_meta_data(func), buf, buf_size)
size_t serialize_function_(FunctionMetaData func, char *buf, size_t buf_size);


#define GENERATED_H
#endif // !defined(GENERATED_H)

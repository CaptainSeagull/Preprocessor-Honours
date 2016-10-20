#if !defined(GENERATED_H)

#include <stdio.h>

typedef enum MetaType {
    meta_type_char,
    meta_type_short,
    meta_type_int,
    meta_type_long,
    meta_type_float,
    meta_type_double,
    meta_type_Position,
    meta_type_test,
    meta_type_FooOne,
    meta_type_SomeStruct,
} MetaType;

//
// Struct meta data.
//
typedef struct MemberDefinition {
    MetaType type;
    char *name;
    size_t offset;
    int is_ptr;
    unsigned arr_size;
} MemberDefinition;

#define get_num_of_members(type) num_members_for_##type

// Meta Data for: Position
extern MemberDefinition members_of_Position[];
static size_t const num_members_for_Position = 2;

// Meta Data for: test
extern MemberDefinition members_of_test[];
static size_t const num_members_for_test = 6;

// Meta Data for: FooOne
extern MemberDefinition members_of_FooOne[];
static size_t const num_members_for_FooOne = 3;

// Meta Data for: SomeStruct
extern MemberDefinition members_of_SomeStruct[];
static size_t const num_members_for_SomeStruct = 2;


// size_t serialize_struct(void *var, type VariableType, char *buffer, size_t buf_size);
#define serialize_struct(var, type, buffer, buf_size) serialize_struct_(var, type, 0, buffer, buf_size, 0)
#define serialize_struct_(var, type, indent, buffer, buf_size, bytes_written) serialize_struct__((void *)&var, members_of_##type, indent, get_num_of_members(type), buffer, buf_size, bytes_written)
size_t serialize_struct__(void *var, MemberDefinition members_of_Something[], unsigned indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written);

//
// Function meta data.
//
typedef struct Variable {
    char *ret_type;
    char *name;
} Variable;

#define MAX_NUMBER_OF_PARAMS (32)
typedef struct FunctionMetaData {
    char *linkage;
    char *ret_type;
    char *name;
    unsigned param_count;
    Variable params[MAX_NUMBER_OF_PARAMS];
} FunctionMetaData;

// FunctionMetaData get_func_meta_data(function_name);
#define get_func_meta_data(func) function_data_##func
extern FunctionMetaData function_data_foo;
extern FunctionMetaData function_data_some_function;

// size_t serialize_function(function_name, char *buf, size_t buf_size);
#define serialize_function(func, buf, buf_size) serialize_function_(get_func_meta_data(func), buf, buf_size)
size_t serialize_function_(FunctionMetaData func, char *buf, size_t buf_size);


#define GENERATED_H
#endif // !defined(GENERATED_H)

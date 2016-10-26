#if !defined(GENERATED_H)

#include "static_generated.h"
#include <stdio.h>

/* Enum with field for every type detected. */
typedef enum MetaType {
    meta_type_char,
    meta_type_short,
    meta_type_int,
    meta_type_long,
    meta_type_float,
    meta_type_double,
    meta_type_SomeStruct2,
    meta_type_Base,
    meta_type_Sub,
    meta_type_DemoString,
    meta_type_StructTest,
    meta_type_SomeStruct,
} MetaType;

/* Struct meta data. */

/* Meta Data for: SomeStruct2 */
extern MemberDefinition members_of_SomeStruct2[];
static size_t const num_members_for_SomeStruct2 = 2;

/* Meta Data for: Base */
extern MemberDefinition members_of_Base[];
static size_t const num_members_for_Base = 3;

/* Meta Data for: Sub */
extern MemberDefinition members_of_Sub[];
static size_t const num_members_for_Sub = 3;

/* Meta Data for: DemoString */
extern MemberDefinition members_of_DemoString[];
static size_t const num_members_for_DemoString = 2;

/* Meta Data for: StructTest */
extern MemberDefinition members_of_StructTest[];
static size_t const num_members_for_StructTest = 3;

/* Meta Data for: SomeStruct */
extern MemberDefinition members_of_SomeStruct[];
static size_t const num_members_for_SomeStruct = 2;


/* Function meta data. */

/* Meta Data for: function_test */
extern FunctionMetaData function_data_function_test;
/* Meta Data for: some_function */
extern FunctionMetaData function_data_some_function;


#define GENERATED_H
#endif /* !defined(GENERATED_H) */

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
    meta_type_Position,
    meta_type_Test,
    meta_type_FooOne,
} MetaType;

/* Struct meta data. */

/* Meta Data for: Position */
extern MemberDefinition members_of_Position[];
static size_t const num_members_for_Position = 2;

/* Meta Data for: Test */
extern MemberDefinition members_of_Test[];
static size_t const num_members_for_Test = 6;

/* Meta Data for: FooOne */
extern MemberDefinition members_of_FooOne[];
static size_t const num_members_for_FooOne = 3;


/* Function meta data. */

/* Meta Data for: foo */
extern FunctionMetaData function_data_foo;


#define GENERATED_H
#endif /* !defined(GENERATED_H) */

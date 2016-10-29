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
    meta_type_V2,
    meta_type_Transform,
    meta_type_Paddle,
} MetaType;

/* Struct meta data. */

/* Meta Data for: V2 */
extern MemberDefinition members_of_V2[];
static size_t const num_members_for_V2 = 2;

/* Meta Data for: Transform */
extern MemberDefinition members_of_Transform[];
static size_t const num_members_for_Transform = 2;

/* Meta Data for: Paddle */
extern MemberDefinition members_of_Paddle[];
static size_t const num_members_for_Paddle = 2;


/* Function meta data. */

/* Meta Data for: create_rect */
extern FunctionMetaData function_data_create_rect;
/* Meta Data for: draw_paddle */
extern FunctionMetaData function_data_draw_paddle;
/* Meta Data for: paddle_clicked */
extern FunctionMetaData function_data_paddle_clicked;


#define GENERATED_H
#endif /* !defined(GENERATED_H) */

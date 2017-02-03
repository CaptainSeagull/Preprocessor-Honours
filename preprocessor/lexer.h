/*===================================================================================================
  File:                    lexer.h
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#if !defined(_LEXER_H)

#include "shared.h"
#include "utils.h"

enum StructType {
    StructType_unknown,
    StructType_struct,
    StructType_class,
    StructType_union,

    StructType_count
};

struct StructData {
    String name;
    Int member_count;
    Variable *members;

    Int inherited_count;
    String *inherited;

    StructType struct_type;
};

struct EnumValue {
    String name;
    Int value;
};

struct EnumData {
    String name;
    String type;
    Bool is_struct;

    EnumValue *values;
    Int no_of_values;
};

struct ParseResult {
    Int enum_cnt;
    EnumData *enum_data;

    Int struct_cnt;
    StructData *struct_data;
};

ParseResult parse_stream(Char *stream);

#define _LEXER_H
#endif

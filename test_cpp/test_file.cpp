#include "generated.h"

struct SomeStruct {
    int a;
    int b;
};

SomeStruct s = {10, 20};

FunctionMetaData function_data_function_test2 = {
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

void some_function(SomeStruct *some_struct)
{
    // Do stuff.

    int i = 0;

    if(i == 4) {

    }
}
#include "generated.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Position {
    float x;
    float y;
} Position;

typedef struct Test {
    int sixteen[16];
    float float_four[4];
    double double_four[4];
    int one;
    Position *pos;
    char *str;
} Test;

typedef enum FooBar {
    a,
    b,
    c
} FooBar;

typedef enum BarFoo {
    x,
    y,
    z
} BarFoo;

typedef union V2 {
    float e[2];
} V2;

static BarFoo
foo(char *str, int len, ...)
{
    BarFoo res = x;
    return(res);
}

typedef struct FooOne {
    int one;
    int two;
    int three;
} FooOne;

/*  Should return:
    "Linkage: static,
    return type: BarFoo,
    name: foo,
    param 1: char *str,
    param 2: var_args */

int
main(int argc, char *argv[])
{
    size_t buf_size = 1024  * 1024;
    char buf[256] = {0};
    {
        FunctionMetaData foo_meta_data = get_func_meta_data(foo);
        char const *ReturnType = foo_meta_data.ret_type;

        serialize_function(foo, buf, 256);

        printf("%s", buf);


        printf("%s", ReturnType);
    }

    foo("Hello", 3);

    {
        char *buf = (char *)malloc(buf_size);
        unsigned Index = 0;
        Test test;
        memset(&test, 0, sizeof(Test));

        for(Index = 0; (Index < 16); ++Index) {
            test.sixteen[Index] = Index * 2;
        }

        test.double_four[0] = 1.1f;
        test.double_four[1] = 2.2f;
        test.double_four[2] = 3.3f;
        test.double_four[3] = 4.4f;

        test.float_four[0] = 1.1f;
        test.float_four[1] = 2.2f;
        test.float_four[2] = 3.3f;
        test.float_four[3] = 4.4f;

        test.one = 1;

        test.pos = (Position *)malloc(sizeof(Position));

        test.pos->x = 3.3f;
        test.pos->y = 2.2f;

        serialize_struct(test, Test, buf, buf_size);

        printf("%s", buf);
        printf("\n");
    }

    return(0);
}

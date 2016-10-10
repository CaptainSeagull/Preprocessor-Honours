#include "generated.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Position {
    float x;
    float y;
};

struct test {
    int sixteen[16];
    float float_four[4];
    double double_four[4];
    int one;
    Position *pos;
    char *str;
};

enum struct FooBar : short {
    a,
    b,
    c
};

enum BarFoo : long {
    x,
    y,
    z
};

union V2 {
    float e[2];
};

static BarFoo
foo(char *str, ...)
{
    BarFoo res = {};
    return(res);
}

struct FooOne {
    int one;
    int two;
    int three;
};

int main(int argc, char *argv[])
{
    size_t buf_size = 1024  * 1024;

    auto foo_meta_data = get_func_meta_data(foo);

    char *ReturnType = foo_meta_data.ret_type;
    printf(ReturnType);

    char *buf = (char *)malloc(buf_size);
    unsigned Index = 0;

    test Test = {};
    for(Index = 0; (Index < 16); ++Index) {
        Test.sixteen[Index] = Index * 2;
    }

    Test.double_four[0] = 1.1f;
    Test.double_four[1] = 2.2f;
    Test.double_four[2] = 3.3f;
    Test.double_four[3] = 4.4f;

    Test.float_four[0] = 1.1f;
    Test.float_four[1] = 2.2f;
    Test.float_four[2] = 3.3f;
    Test.float_four[3] = 4.4f;

    Test.one = 1;

    Test.pos = (Position *)malloc(sizeof(Position));

    Test.pos->x = 3.3f;
    Test.pos->y = 2.2f;

    Test.str = "Hello";

    serialize_struct(Test, test, buf, buf_size);

    printf(buf);
    printf("\n");

    return(0);
}

#include "generated.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


class Base
{
public:
    int a;
    int b;
    int c;
};

class Sub : public Base
{
public:
    int x;
    int y;
    int z;
};

int function_test(float f, int i, char *str)
{
    printf("%f", f);
    printf("%d", i);
    printf("%s", str);

    return(2);
}

struct DemoString {
    char const *str;
    int len;
};

struct StructTest {
    int i;
    float f;
    DemoString str;
};

int
main(int argc, char *argv[])
{
#if 0
    Sub s = {};

    printf("\n%u", (unsigned)((size_t)&s.a - (size_t)&s));
    printf("\n%u", (unsigned)((size_t)&s.b - (size_t)&s));
    printf("\n%u", (unsigned)((size_t)&s.c - (size_t)&s));

    printf("\n%u", (unsigned)((size_t)&s.x - (size_t)&s));
    printf("\n%u", (unsigned)((size_t)&s.y - (size_t)&s));
    printf("\n%u", (unsigned)((size_t)&s.z - (size_t)&s));
#endif
    // Struct test.
    {
        StructTest st;
        st.i = 45;
        st.f = 3.1415;
        st.str.str = "Hello\0";
        st.str.len = 5;

        int const size = 1024;
        char buf[size] = {};

        serialize_struct(st, StructTest, buf, size);
        printf("%s\n\n", buf);
    }
#if 1
    // Function test.
    {
        FunctionMetaData get_func_meta_data(function_test);

        int const size = 1024;
        char buf[size] = {};
        serialize_function(function_test, buf, size);

        //printf("%s", buf);
    }
#endif
    return(0);
}

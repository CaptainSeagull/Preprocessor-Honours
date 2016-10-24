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

int
main(int argc, char *argv[])
{
    Sub s = {};

    printf("\n%ull", (size_t)&s.a - (size_t)&s);
    printf("\n%ull", (size_t)&s.b - (size_t)&s);
    printf("\n%ull", (size_t)&s.c - (size_t)&s);

    printf("\n%ull", (size_t)&s.x - (size_t)&s);
    printf("\n%ull", (size_t)&s.y - (size_t)&s);
    printf("\n%ull", (size_t)&s.z - (size_t)&s);

    return(0);
}

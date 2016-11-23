#Preprocessor


#Overview

This is a simple project which aims to provide some meta programming functionality not currently in C++. The utility generates code, which should be included in the relevant .cpp file.

#Build instructions

Windows: Call win32_build.bat from the command line, which should generate the exe inside /builds/win32_msvc/.

Linux: Call build_clang.sh from the command line This should generate the app file inside /builds/linux_clang/.

Mac: N/A.

#Contact

Any bugs, suggestions, complaints, or just general feedback, should be emailed to: seagull127@ymail.com.

#LICENSE

This software is dual-licensed to the public domain and under the following license: you are granted a perpetual, irrevocable license to copy, modify, publish, and distribute this file as you see fit.

#Examples

##Struct serialization
```C++
#include "generated.h"

typedef struct Two {
    int c;
    int d;
} Two;

typedef struct One {
    int a;
    int b;
    Two two;
} One;

int main(int argc, char **argv)
{
    char buffer[1024];
    One one;
    one.a = 0;
    one.b = 1;
    one.two.c = 2;
    one.two.d = 4;

    serialize_struct(one, One, buffer, 1024);
    printf("%s", buffer);

    return(0);
}
```

and that will output:
```
one
    int a = 0
    int b = 1
    two
        int c = 2
        int d = 4
```

##Enums
```
#include "generated.h"

typedef enum Letters { Letter_a, Letter_b, Letter_c } Letters;

int main(int argc, char **argv)
{
    Letters a = Letter_a;
    Letters b = Letter_b;
    Letters c = Letter_c;

    /* Convert all the enum values to a string. */
    char const *a_as_string = enum_to_string(Letters, a);
    char const *b_as_string = enum_to_string(Letters, Letter_b);
    char const *c_as_string = enum_to_string(Letters, 2);

    printf("a = %s\n", a_as_string);
    printf("b = %s\n", b_as_string);
    printf("c = %s\n", c_as_string);

    /* Print out the number of items in the enum. */
    if(get_number_of_enum_elements(Letters) == 3) { printf("\nThe number of elements is 3!\n"); }

    /* Convert the string back to a enum index. */
    int num_a = string_to_enum(Letters, a_as_string);
    int num_b = string_to_enum(Letters, "Letter_b");
    int num_c = string_to_enum(Letters, c_as_string);

    if(num_a == Letter_a) { printf("\nnum_a == Letter_a"); }
    if(num_b == Letter_b) { printf("\nnum_b == Letter_b"); }
    if(num_c == Letter_c) { printf("\nnum_c == Letter_c"); }

    return(0);
}
```
And the output would be:
```
a = Letter_a
b = Letter_b
c = Letter_c

The number of elements is 3!

num_a == Letter_a
num_b == Letter_b
num_c == Letter_c
```

#Current Limitations
- Overloaded functions.
- Structs with the same name (even in different files).
- Inheritance.
- Templates.

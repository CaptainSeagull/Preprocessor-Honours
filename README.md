#Preprocessor


#Overview

This is a simple project in order to allow more complex meta programming in C/C++. The utility generates code, which should be included in the relavent .cpp file, which will allow more advanced introspection than C/C++ currently allows.
Build instructions

Windows: Simple call the build.bat file from the command line (after calling vcvarsall.bat). This will generate the .exe, which should be completely portable (not even requiring the win32 crt).

Linux: Instructions are very similar, but sadly I haven't had time to properly test them yet.

Mac: N/A.

#Contact

Any bugs, suggestions, complaints, or just general feedback, should be emailed to: seagull127@ymail.com.

#LICENSE

This software is dual-licensed to the public domain and under the following license: you are granted a perpetual, irrevocable license to copy, modify, publish, and distribute this file as you see fit.

#Example

Simply call the application with all the relevant files eg:
```bash
preprocessor main_file.cpp other_file.cpp
```
and that will generate 3 files, generated.h, generated.cpp, and static_generated.h.

You should add generated.cpp into the list of files build, and in all the source files you should include generated.h. Then you can do something like the following:

```C++
#include "generated.h"

struct Two {
    int c;
    int d;
};

struct One {
    int a;
    int b;
    Two two;
};

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

# Current Limitations
- Overloaded functions.
- Structs with the same name (even in different files).
- Inheritance.
- Templates.

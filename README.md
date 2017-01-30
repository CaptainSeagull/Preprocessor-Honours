#Preprocessor


#Overview

This is a simple project which aims to provide some meta programming functionality not currently in C++. The utility generates code, which should be included in the relevant .cpp file.

The reason for doing C++ this way, as opposed to some other ways, include.
- The ability to target multiple compilers with the output.

All generate code strictly follows the C++11 specification, and should compile correctly under MSVC, Clang, or GCC, even with `-Wall` enabled. If you're using a pre-C++11 compiler, then the preprocessor can still be used, but some functions will not compile. They, however, have alternatives which can be used.

#Build instructions

##Windows
Call win32_build.bat from the command line, which should generate the exe inside the `build` directory. This uses Visual Studio 2013 to build (MSVC 12), so if you're using a different version of visual studio then change the line `set VISUAL_STUDIO_VERSION=12` to whatever version of Visual Studio you're using.

##Linux
Call build_clang.sh from the command line This should generate the app file inside the `build` directory. This uses Clang version 3.8, so if you don't have that version installed on our computer, you'll need to change all the lines that say `Clang++-3.8` to match the version you've got.

There is currently no build version which uses GCC, but in order to build all you have to do if build all the files located in the `preprocessor` directory, excluding `platform_win32.cpp`.

##Mac
N/A

#Contact

Any bugs, suggestions, complaints, or just general feedback, should be emailed to: seagull127@ymail.com.

#LICENSE

This software is dual-licensed to the public domain and under the following license: you are granted a perpetual, irrevocable license to copy, modify, publish, and distribute this file as you see fit.

#Functions.
Get the number of elements in a struct. This also counts members added through inheritance.
```C++
size_t pp::get_num_of_members(TYPE);
```

Convert a type into a string. This keeps information about the type, like if it's a pointer.
```C++
char const * pp::type_to_string(TYPE);
```

Convert a type into a string. This ignores information about the type, like if it's a pointer.
```C++
char const * pp::weak_type_to_string(TYPE);
```

Print a completely serialized struct to the console. The parameters `buffer` and `buffer_size` can be used to pass memory into the function for it to use. Otherwise, the function allocates, and frees, it's own memory.

This function requires a C++11-compliant compiler to use. If you're using an older compiler, you should use `pp::print_type`.
```C++
size_t pp::print(TYPE variable, char *buffer = NULL, size_t buffer_size = 0);
```

Print a completely serialized struct to the console. The parameters `buffer` and `buffer_size` can be used to pass memory into the function for it to use. Otherwise, the function allocates, and frees, it's own memory.

If you're using a C++11-compliant compiler, you should consider using `pp::print`.
```C++
size_t pp::print_type(TYPE variable, TYPE, char *buffer = NULL, size_t buffer_size = 0);
```

Serialize a struct into a buffer.

This function requires a C++11-compliant compiler to use. If you're using an older compiler, you should use `pp::serialize_type`.
```C++
size_t serialize(TYPE variable, char *buffer, size_t buffer_size);
```
Serialize a struct into a buffer.

If you're using a C++11-compliant compiler, you should consider using `pp::serialize`.
```C++
size_t serialize_type(TYPE variable, TYPE, char *buffer, size_t buffer_size);
```

Get the number of base-types the struct inherits from.
```C++
size_t pp::get_base_type_count(TYPE);
```

Get the base type for the struct as a string.
```C++
char const * pp::get_base_type_as_string(TYPE);
```

Get the base type for the struct, as a specific index, as a string.
```C++
char const * pp::get_base_type_as_string_index(TYPE, index);
```

Compare two types to see if they're the same or not. Works the same as a `std::is_same`.
```C++
bool pp::type_compare(TYPE_A, TYPE_B);
```

Compare two types to see if they're the same or not. If one type is a base class of another, then this function will return `true`.
```C++
bool pp::fuzzy_type_compare(TYPE_A, TYPE_B);
```

Compare two types to see if they're the same or not. If one type is a pointer and one isn't, like comparing `int *` and `int`, then this function will return `true`.
```C++
bool pp::weak_type_compare(TYPE_A, TYPE_B);
```

Get the number of elements an enum stores.
```C++
size_t pp::get_number_of_enum_elements(TYPE);
```

Convert an element in an enum into a string.
```C++
char const * pp::enum_to_string(TYPE, element);
```

Convert a string into an element in an enum.
```C++
TYPE pp::string_to_enum(TYPE, char const *element_as_string);
```

#Examples

##Member count.
```C++
struct V2 {
    int x;
    int y;
};

int num = pp::get_num_of_members(V2); // Returns 2.
```

##Type Comparison
```C++

pp::type_compare(int, int);   // returns true
pp::type_compare(int, float); // returns false
pp::type_compare(int, short); // returns false
```

##Type to String
```C++

char const *str1 = pp::type_to_string(int *); // Returns "int *"
char const *str2 = pp::type_to_string(int *); // Returns "int"
```

##Base Type
```C++
struct Base {};
struct Sub : public Base {};

char const *str = pp::get_base_type_as_string(Sub); // Returns "Base".
```

##Print
```C++
struct V2 { int x, y; };
```
...
```C++
V2 v;
v.x = 1;
v.y = 2;

pp::print(v);
/* Prints:
    "V2 v"
    "    int x = 1"
    "    int y = 2"
*/
```

##Get number of elements in enum
```C++
enum Letters { a, b, c };

int n = pp::get_number_of_enum_elements(Letters);
```

##Enum to string
```C++
enum Letters { a, b, c };

char const *str = pp::enum_to_string(NUmbers, a); // Returns "a"
```

##String to enum
```C++
enum Letters { a, b, c };

Letters l = pp::string_to_enum("a"); // returns b (1).
```

#Current Limitations
- It doesn't support templates.
- There is currently no introspection support for functions.
- Only limited support for introspection of C++ STL containers.

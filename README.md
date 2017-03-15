# Preprocessor


# Overview

This is a simple project which aims to provide some meta programming functionality not currently avaiable in C++. The utility generates code, which should be included in the relevant .cpp files.

All generated code strictly follows the C++11 specification, and should compile correctly under MSVC, Clang, or GCC, even with `-Wall` enabled. If you're using a pre-C++11 compiler, then the preprocessor can still be used, but some functions will not compile. All the functions which require C++11 features have alternatives which can be used and are compiant with the C++98 specification.

# Build instructions

## Windows
Call `win32_msvc.bat` from a command line that has previously called 'vcvarsal.bat' in your favourite version of Visual Studio. This will generate the executable inside the `build` directory. It has not ever been tested with GCC or Clang on Windows, and there are currently no plans to easily support them.

## Linux
Call `linux_clang.sh` from the command line, which should generate the app file inside the `build` directory. This uses Clang version 3.8, so if you don't have that version installed on your computer, then you'll need to change the line that says `CLANG_VERSION=3.8` to match the version you've got.

There is currently no simple way to build using GCC on Linux, but there are plans to support this soon.

## Mac
N/A

# Contact

Any bugs, suggestions, complaints, or just general feedback, should be emailed to: seagull127@ymail.com.

# LICENSE

This software is dual-licensed to the public domain and under the following license: you are granted a perpetual, irrevocable license to copy, modify, publish, and distribute this file as you see fit.

# API
Get compile-time information on a type. The generated code specialises this struct for each type in the code.
```C++
template<typename T> pp::TypeInfo::type {
    using type;                   // Type.
    using weak_type;              // Type without modifiers.
    using base;                   // Base type (defaults to void).

    char const * name;            // Name as string.
    char const * weak_name;       // Name as string, without modifiers.

    size_t member_count;          // Number of members.

    bool is_ptr;                  // Is a pointer?
    bool is_ref;                  // Is a reference?

    size_t base_count;            // Number of structs inherited from.

    bool is_primitive;            // Is a primitive?
    bool is_class;                // Is a class/struct?
    bool is_enum;                 // Is an enum?
};
```

Access a member of a struct at an index. The return type of this is dependent on the type of parameter `var` and the index of parameter `index`.
```C++
MEMBER_TYPE * pp::get_member(CLASS_TYPE *variable, size_t index);
```

Print a completely serialized struct to the console. The parameters `buffer` and `buffer_size` can be used to pass memory into the function for it to use. Otherwise, the function allocates, and frees, it's own memory.
```C++
size_t pp::print(TYPE variable, char *buffer = NULL, size_t buffer_size = 0);
```

Serialize a struct into a buffer. Basic just `pp::print` without printing to the console.
`pp::serialize_type`.
```C++
size_t serialize(TYPE variable, char *buffer, size_t buffer_size);
```

Compare two types to see if they're the same or not. Works the same as a `std::is_same`.
```C++
bool pp::type_compare(TYPE_A, TYPE_B);
```

Convert an element in an enum into a string.
```C++
template<typename T> char const *pp::enum_to_string(T element);
```

Convert a string into an element in an enum.
```C++
template<typename T> T pp::string_to_enum(char const *str);
```

# Current Limitations
- It doesn't support templates.
- There is currently no introspection support for functions.
- Only limited support for introspection of C++ STL containers. These are:
    - std::vector
    - std::list
    - std::forward_list
    - std::deque.

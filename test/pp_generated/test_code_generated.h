#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

// Forward declared structs (these must be declared outside the namespace...)
class Struct;
class Vector2d;
class Test;
struct Foo;

#define _std std // TODO(Jonny): This is really stupid...

// Enum with field for every type detected.
namespace pp { enum Type {
    Type_char,
    Type_short,
    Type_int,
    Type_long,
    Type_float,
    Type_double,
    Type_bool,
    Type_Struct,
    Type_Vector2d,
    Type_Test,
    Type_Foo,
}; }

#include "static_generated.h"
namespace pp { // PreProcessor

//
// Meta type specialization
//

// char
template<> struct TypeInfo<char> {
    using type = char;
    using weak_type = char;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<char> operator=(TypeInfo<char> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<char>::name = "char";
char const * const TypeInfo<char>::weak_name = "char";

template<> struct TypeInfo<char *> {
    using type = char *;
    using weak_type = char;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<char *> operator=(TypeInfo<char *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<char *>::name = "char *";
char const * const TypeInfo<char *>::weak_name = "char";

template<> struct TypeInfo<char **> {
    using type = char **;
    using weak_type = char;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<char **> operator=(TypeInfo<char **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<char **>::name = "char **";
char const * const TypeInfo<char **>::weak_name = "char";


// short
template<> struct TypeInfo<short> {
    using type = short;
    using weak_type = short;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<short> operator=(TypeInfo<short> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<short>::name = "short";
char const * const TypeInfo<short>::weak_name = "short";

template<> struct TypeInfo<short *> {
    using type = short *;
    using weak_type = short;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<short *> operator=(TypeInfo<short *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<short *>::name = "short *";
char const * const TypeInfo<short *>::weak_name = "short";

template<> struct TypeInfo<short **> {
    using type = short **;
    using weak_type = short;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<short **> operator=(TypeInfo<short **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<short **>::name = "short **";
char const * const TypeInfo<short **>::weak_name = "short";


// int
template<> struct TypeInfo<int> {
    using type = int;
    using weak_type = int;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<int> operator=(TypeInfo<int> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<int>::name = "int";
char const * const TypeInfo<int>::weak_name = "int";

template<> struct TypeInfo<int *> {
    using type = int *;
    using weak_type = int;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<int *> operator=(TypeInfo<int *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<int *>::name = "int *";
char const * const TypeInfo<int *>::weak_name = "int";

template<> struct TypeInfo<int **> {
    using type = int **;
    using weak_type = int;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<int **> operator=(TypeInfo<int **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<int **>::name = "int **";
char const * const TypeInfo<int **>::weak_name = "int";


// long
template<> struct TypeInfo<long> {
    using type = long;
    using weak_type = long;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<long> operator=(TypeInfo<long> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<long>::name = "long";
char const * const TypeInfo<long>::weak_name = "long";

template<> struct TypeInfo<long *> {
    using type = long *;
    using weak_type = long;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<long *> operator=(TypeInfo<long *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<long *>::name = "long *";
char const * const TypeInfo<long *>::weak_name = "long";

template<> struct TypeInfo<long **> {
    using type = long **;
    using weak_type = long;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<long **> operator=(TypeInfo<long **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<long **>::name = "long **";
char const * const TypeInfo<long **>::weak_name = "long";


// float
template<> struct TypeInfo<float> {
    using type = float;
    using weak_type = float;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<float> operator=(TypeInfo<float> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<float>::name = "float";
char const * const TypeInfo<float>::weak_name = "float";

template<> struct TypeInfo<float *> {
    using type = float *;
    using weak_type = float;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<float *> operator=(TypeInfo<float *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<float *>::name = "float *";
char const * const TypeInfo<float *>::weak_name = "float";

template<> struct TypeInfo<float **> {
    using type = float **;
    using weak_type = float;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<float **> operator=(TypeInfo<float **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<float **>::name = "float **";
char const * const TypeInfo<float **>::weak_name = "float";


// double
template<> struct TypeInfo<double> {
    using type = double;
    using weak_type = double;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<double> operator=(TypeInfo<double> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<double>::name = "double";
char const * const TypeInfo<double>::weak_name = "double";

template<> struct TypeInfo<double *> {
    using type = double *;
    using weak_type = double;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<double *> operator=(TypeInfo<double *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<double *>::name = "double *";
char const * const TypeInfo<double *>::weak_name = "double";

template<> struct TypeInfo<double **> {
    using type = double **;
    using weak_type = double;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<double **> operator=(TypeInfo<double **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<double **>::name = "double **";
char const * const TypeInfo<double **>::weak_name = "double";


// bool
template<> struct TypeInfo<bool> {
    using type = bool;
    using weak_type = bool;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<bool> operator=(TypeInfo<bool> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<bool>::name = "bool";
char const * const TypeInfo<bool>::weak_name = "bool";

template<> struct TypeInfo<bool *> {
    using type = bool *;
    using weak_type = bool;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<bool *> operator=(TypeInfo<bool *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<bool *>::name = "bool *";
char const * const TypeInfo<bool *>::weak_name = "bool";

template<> struct TypeInfo<bool **> {
    using type = bool **;
    using weak_type = bool;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<bool **> operator=(TypeInfo<bool **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<bool **>::name = "bool **";
char const * const TypeInfo<bool **>::weak_name = "bool";


// Struct
template<> struct TypeInfo<Struct> {
    using type = Struct;
    using weak_type = Struct;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Struct> operator=(TypeInfo<Struct> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Struct>::name = "Struct";
char const * const TypeInfo<Struct>::weak_name = "Struct";

template<> struct TypeInfo<Struct *> {
    using type = Struct *;
    using weak_type = Struct;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Struct *> operator=(TypeInfo<Struct *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Struct *>::name = "Struct *";
char const * const TypeInfo<Struct *>::weak_name = "Struct";

template<> struct TypeInfo<Struct **> {
    using type = Struct **;
    using weak_type = Struct;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Struct **> operator=(TypeInfo<Struct **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Struct **>::name = "Struct **";
char const * const TypeInfo<Struct **>::weak_name = "Struct";


// Vector2d
template<> struct TypeInfo<Vector2d> {
    using type = Vector2d;
    using weak_type = Vector2d;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Vector2d> operator=(TypeInfo<Vector2d> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Vector2d>::name = "Vector2d";
char const * const TypeInfo<Vector2d>::weak_name = "Vector2d";

template<> struct TypeInfo<Vector2d *> {
    using type = Vector2d *;
    using weak_type = Vector2d;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Vector2d *> operator=(TypeInfo<Vector2d *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Vector2d *>::name = "Vector2d *";
char const * const TypeInfo<Vector2d *>::weak_name = "Vector2d";

template<> struct TypeInfo<Vector2d **> {
    using type = Vector2d **;
    using weak_type = Vector2d;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Vector2d **> operator=(TypeInfo<Vector2d **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Vector2d **>::name = "Vector2d **";
char const * const TypeInfo<Vector2d **>::weak_name = "Vector2d";


// Test
template<> struct TypeInfo<Test> {
    using type = Test;
    using weak_type = Test;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 4;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Test> operator=(TypeInfo<Test> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Test>::name = "Test";
char const * const TypeInfo<Test>::weak_name = "Test";

template<> struct TypeInfo<Test *> {
    using type = Test *;
    using weak_type = Test;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 4;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Test *> operator=(TypeInfo<Test *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Test *>::name = "Test *";
char const * const TypeInfo<Test *>::weak_name = "Test";

template<> struct TypeInfo<Test **> {
    using type = Test **;
    using weak_type = Test;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 4;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Test **> operator=(TypeInfo<Test **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Test **>::name = "Test **";
char const * const TypeInfo<Test **>::weak_name = "Test";


// Foo
template<> struct TypeInfo<Foo> {
    using type = Foo;
    using weak_type = Foo;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Foo> operator=(TypeInfo<Foo> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Foo>::name = "Foo";
char const * const TypeInfo<Foo>::weak_name = "Foo";

template<> struct TypeInfo<Foo *> {
    using type = Foo *;
    using weak_type = Foo;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Foo *> operator=(TypeInfo<Foo *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Foo *>::name = "Foo *";
char const * const TypeInfo<Foo *>::weak_name = "Foo";

template<> struct TypeInfo<Foo **> {
    using type = Foo **;
    using weak_type = Foo;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Foo **> operator=(TypeInfo<Foo **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Foo **>::name = "Foo **";
char const * const TypeInfo<Foo **>::weak_name = "Foo";

static bool is_meta_type_container(int type) {
    if(type == Type_char) {return(false);} // false
    else if(type == Type_short) {return(false);} // false
    else if(type == Type_int) {return(false);} // false
    else if(type == Type_long) {return(false);} // false
    else if(type == Type_float) {return(false);} // false
    else if(type == Type_double) {return(false);} // false
    else if(type == Type_bool) {return(false);} // false
    else if(type == Type_Struct) {return(false);} // false
    else if(type == Type_Vector2d) {return(false);} // false
    else if(type == Type_Test) {return(false);} // false
    else if(type == Type_Foo) {return(false);} // false

    // Should not be reached.
    assert(0);
    return(0);
}
static char const * meta_type_to_name(Type mt, bool is_ptr) {
    if(mt == Type_Struct) {
        if(is_ptr) {return("Struct *");}
        else       {return("Struct");  }
    } else if(mt == Type_Vector2d) {
        if(is_ptr) {return("Vector2d *");}
        else       {return("Vector2d");  }
    } else if(mt == Type_Test) {
        if(is_ptr) {return("Test *");}
        else       {return("Test");  }
    } else if(mt == Type_Foo) {
        if(is_ptr) {return("Foo *");}
        else       {return("Foo");  }
    }

    assert(0); 
    return(0); // Not found
}
// Function to serialize a struct to a char array buffer.
static size_t
serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    assert((buffer) && (buf_size > 0)); // Check params.

    if(!bytes_written) {memset(buffer, 0, buf_size);} // If this is the first time through, zero the buffer.

    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); assert(members_of_Something); // Get the members_of pointer. 
    if(members_of_Something) {
        // Setup the indent buffer.
        char indent_buf[256] = {};
        for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}

        // Write the name and the type.
        if((name) && (strlen(name) > 0)) {
            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, type_as_str, name);
        }
        indent += 4;

        // Add 4 to the indent.
        for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}

        int num_members = get_number_of_members_str(type_as_str); assert(num_members != -1); // Get the number of members for the for loop.
        for(int i = 0; (i < num_members); ++i) {
            MemberDefinition *member = members_of_Something + i; // Get the member pointer with meta data.
            size_t *member_ptr = (size_t *)((char *)var + member->offset); // Get the actual pointer to the memory address.
            switch(member->type) {
                // This is a little verbose so I can get the right template overload for serialize_primitive. I should just
                // make it a macro though.
                case Type_double: { // double.
                    bytes_written = serialize_primitive_((double *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_float: { // float.
                    bytes_written = serialize_primitive_((float *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_int: { // int.
                    bytes_written = serialize_primitive_((int *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_long: { // long.
                    bytes_written = serialize_primitive_((long *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_short: { // short.
                    bytes_written = serialize_primitive_((short *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_bool: { // bool.
                    bytes_written = serialize_primitive_((bool *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                // char (special case).
                case Type_char: {
                    if(member_ptr) {
                        if(member->is_ptr) {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, (char *)(*(size_t *)member_ptr));
                        } else {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)((size_t *)member_ptr));
                        }
                    } else {
                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                    }
                } break; // case Type_char

                default: {
                    if(is_meta_type_container(member->type)) {

                    } else {
                        char const *struct_name = meta_type_to_name(member->type, member->is_ptr != 0);
                        bytes_written = serialize_struct_(member_ptr, member->name, struct_name, indent, buffer, buf_size - bytes_written, bytes_written);
                    }
                } break; // default 
            }
        }
    }

    return(bytes_written);
}

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // Recreated structs.
    struct _Struct {  _char *text;  _int length;  };
    struct _Vector2d {  _int x;  _int y;  };
    struct _Test {  _int a;  _int b;  _float c;  _Vector2d d;  };
    struct _Foo {  };
    // Struct
    if(type_compare(T, Struct)) {
        static MemberDefinition members_of_Struct[] = {
            {Type_char, "text", offset_of(&_Struct::text), true, 1},
            {Type_int, "length", offset_of(&_Struct::length), false, 1},
        };
        return(members_of_Struct);

    // Vector2d
    } else if(type_compare(T, Vector2d)) {
        static MemberDefinition members_of_Vector2d[] = {
            {Type_int, "x", offset_of(&_Vector2d::x), false, 1},
            {Type_int, "y", offset_of(&_Vector2d::y), false, 1},
        };
        return(members_of_Vector2d);

    // Test
    } else if(type_compare(T, Test)) {
        static MemberDefinition members_of_Test[] = {
            {Type_int, "a", offset_of(&_Test::a), false, 1},
            {Type_int, "b", offset_of(&_Test::b), false, 1},
            {Type_float, "c", offset_of(&_Test::c), false, 1},
            {Type_Vector2d, "d", offset_of(&_Test::d), false, 1},
        };
        return(members_of_Test);
    }

    return(0); // Error.
}

// Convert a type into a members of pointer.
static MemberDefinition *get_members_of_str(char const *str) {
    // Recreated structs.
    struct _Struct {  _char *text;  _int length;  };
    struct _Vector2d {  _int x;  _int y;  };
    struct _Test {  _int a;  _int b;  _float c;  _Vector2d d;  };
    struct _Foo {  };
    // char
    if((strcmp(str, "char") == 0) || (strcmp(str, "char *") == 0) || (strcmp(str, "char **") == 0)) {
        static MemberDefinition members_of_char[] = {
            {Type_char, "", 0, false, 1}
        };
        return(members_of_char);

    // short
    } else if((strcmp(str, "short") == 0) || (strcmp(str, "short *") == 0) || (strcmp(str, "short **") == 0)) {
        static MemberDefinition members_of_short[] = {
            {Type_short, "", 0, false, 1}
        };
        return(members_of_short);

    // int
    } else if((strcmp(str, "int") == 0) || (strcmp(str, "int *") == 0) || (strcmp(str, "int **") == 0)) {
        static MemberDefinition members_of_int[] = {
            {Type_int, "", 0, false, 1}
        };
        return(members_of_int);

    // long
    } else if((strcmp(str, "long") == 0) || (strcmp(str, "long *") == 0) || (strcmp(str, "long **") == 0)) {
        static MemberDefinition members_of_long[] = {
            {Type_long, "", 0, false, 1}
        };
        return(members_of_long);

    // float
    } else if((strcmp(str, "float") == 0) || (strcmp(str, "float *") == 0) || (strcmp(str, "float **") == 0)) {
        static MemberDefinition members_of_float[] = {
            {Type_float, "", 0, false, 1}
        };
        return(members_of_float);

    // double
    } else if((strcmp(str, "double") == 0) || (strcmp(str, "double *") == 0) || (strcmp(str, "double **") == 0)) {
        static MemberDefinition members_of_double[] = {
            {Type_double, "", 0, false, 1}
        };
        return(members_of_double);

    // bool
    } else if((strcmp(str, "bool") == 0) || (strcmp(str, "bool *") == 0) || (strcmp(str, "bool **") == 0)) {
        static MemberDefinition members_of_bool[] = {
            {Type_bool, "", 0, false, 1}
        };
        return(members_of_bool);


    // Struct
    } else if((strcmp(str, "Struct") == 0) || (strcmp(str, "Struct *") == 0) || (strcmp(str, "Struct **") == 0)) {
        static MemberDefinition members_of_Struct[] = {
            {Type_char, "text", offset_of(&_Struct::text), true, 1},
            {Type_int, "length", offset_of(&_Struct::length), false, 1},
        };
        return(members_of_Struct);

    // Vector2d
    } else if((strcmp(str, "Vector2d") == 0) || (strcmp(str, "Vector2d *") == 0) || (strcmp(str, "Vector2d **") == 0)) {
        static MemberDefinition members_of_Vector2d[] = {
            {Type_int, "x", offset_of(&_Vector2d::x), false, 1},
            {Type_int, "y", offset_of(&_Vector2d::y), false, 1},
        };
        return(members_of_Vector2d);

    // Test
    } else if((strcmp(str, "Test") == 0) || (strcmp(str, "Test *") == 0) || (strcmp(str, "Test **") == 0)) {
        static MemberDefinition members_of_Test[] = {
            {Type_int, "a", offset_of(&_Test::a), false, 1},
            {Type_int, "b", offset_of(&_Test::b), false, 1},
            {Type_float, "c", offset_of(&_Test::c), false, 1},
            {Type_Vector2d, "d", offset_of(&_Test::d), false, 1},
        };
        return(members_of_Test);
    }

    return(0); // Error.
}

// Get the number of members for a type.
static int get_number_of_members_str(char const *str) {
    if(strcmp(str, "char") == 0) {return(1);}
    else if(strcmp(str, "short") == 0) {return(1);}
    else if(strcmp(str, "int") == 0) {return(1);}
    else if(strcmp(str, "long") == 0) {return(1);}
    else if(strcmp(str, "float") == 0) {return(1);}
    else if(strcmp(str, "double") == 0) {return(1);}
    else if(strcmp(str, "bool") == 0) {return(1);}
    else if(strcmp(str, "Struct") == 0) {return(2);} // Struct
    else if(strcmp(str, "Vector2d") == 0) {return(2);} // Vector2d
    else if(strcmp(str, "Test") == 0) {return(4);} // Test
    else if(strcmp(str, "Foo") == 0) {return(0);} // Foo

    return(-1); // Error.
}

#define weak_type_compare(A, B) TypeCompare_<pp::Type<A>::weak_type, pp::Type<B>::weak_type>::e;
#undef _std // :(
} // namespace pp

#endif // Header guard.


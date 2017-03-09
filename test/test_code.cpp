//
// Basic name/weak_name example
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

int main(int argc, char **argv) {
    int *i, j;

    std::cout << pp::TypeInfo<decltype(i)>::name << std::endl; // "int *"
    std::cout << pp::TypeInfo<decltype(j)>::name << std::endl; // "int"

    std::cout << pp::TypeInfo<decltype(i)>::weak_name << std::endl; // "int"
    std::cout << pp::TypeInfo<decltype(j)>::weak_name << std::endl; // "int"

    return(0);
}
*/

//
// Pointer/not pointer example
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

template<typename T>void do_something(T var) {
    if(pp::TypeInfo<T>::is_ptr) {
        std::cout << "This is a pointer" << std::endl;
    } else {
        std::cout << "This is not a pointer" << std::endl;
    }
}

int main(int argc, char **argv) {
    int *i, j;

    do_something(i); // "This is a pointer"
    do_something(j); // "This is not a pointer"

    return(0);
}
*/

//
// Pointer/not pointer, using C++17 constexpr if.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

template<typename T>void do_something(T var) {
    if constexpr(pp::TypeInfo<T>::is_ptr) {
        std::cout << "Var is a pointer. ";
        std::cout << "Text is " << var->text << std::endl;
    } else {
        std::cout << "Var is not a pointer. ";
        std::cout << "Text is " << var.text << std::endl;
    }
}

class String {
public:
    char *text;
    int length;
};

int main(int argc, char **argv) {
    String str, *str_ptr;

    str.text = "hello";
    str.length = strlen(str.text);

    str_ptr = new String;
    str_ptr->text = "world";
    str_ptr->length = strlen(str_ptr->text);

    do_something(str);     // "Var is a pointer. Text is hello"
    do_something(str_ptr); // "Var is not a pointer. Text is world"

    return(0);
}
*/
//
// Get number of classes inherited from
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class BaseOne {};
class BaseTwo {};
class BaseThree {};

class Test : public BaseOne, public BaseTwo, public BaseThree {};

int main(int argc, char **argv) {
    Test test;

    std::cout << pp::TypeInfo<Test>::name << " inherits from " <<
              pp::TypeInfo<Test>::base_count << " classes.";
    // “Test inherits from 3 classes.”

    return(0);
}
*/

//
// Get number of classes inherited from using template.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class BaseOne {};
class BaseTwo {};
class BaseThree {};

class Test : public BaseOne, public BaseTwo, public BaseThree {};

template<typename T>void print_base_class_count(T var) {
    std::cout << pp::TypeInfo<T>::name << " inherits from " <<
              pp::TypeInfo<T>::base_count << " classes" <<
              std::endl;
}

int main(int argc, char **argv) {
    Test test;
    BaseOne test2;

    print_base_class_count(test);  // “Test inherits from 3 classes.”
    print_base_class_count(test2); // “BaseOne inherits from 0 classes.”

    return(0);
}
*/

//
// Create a struct from another's base type, and output both their names.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class Base {};

class Test : public Base {};

int main(int argc, char **argv) {
    Test test;
    pp::TypeInfo<decltype(test)>::base test_base;

    // “Test”
    std::cout << pp::TypeInfo<decltype(test)>::name << std::endl;

    // “Base”
    std::cout << pp::TypeInfo<decltype(test_base)>::name << std::endl;

    return(0);
}
*/

//
// Recursively print out the type of a base classing using the sub class.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class Base {};
class Test : public Base {};

int main(int argc, char **argv) {
    Test test;

    // "Test"
    std::cout << pp::TypeInfo<decltype(test)>::name
              << std::endl;

    // "Base"
    std::cout << pp::TypeInfo<pp::TypeInfo<decltype(test)>::base>::name
              << std::endl;

    return(0);
}
*/

//
// Go up inheritance tree chain
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class BaseTwo {};
class BaseOne : public BaseTwo {};

class Test : public BaseOne {};

int main(int argc, char **argv) {
    // The inheritance hierarchy is:
    // BaseTwo -> BaseOne -> Test

    char const *str = pp::TypeInfo<pp::TypeInfo<pp::TypeInfo<Test>::base>::base>::name;
    // Prints "BaseTwo"
    std::cout << str;

    return(0);
}
*/

//
// C++17. Template which goes up any class heirarchy to print base type.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class BaseTwo {};
class BaseOne : public BaseTwo {};

class Test : public BaseOne {};

template<typename T>void chain() {
    if constexpr(pp::type_compare(pp::TypeInfo<T>::base, void)) {
        std::cout << "The most base classes type is " <<
                  pp::TypeInfo<T>::name << std::endl;
    } else {
        chain<pp::TypeInfo<T>::base>();
    }
}

int main(int argc, char **argv) {
    chain<Test>();    // Prints “BaseTwo”.
    chain<BaseOne>(); // Prints “BaseTwo”.

    return(0);
}
*/

//
// Static assert TypeInfo::base and a base class are the same.
//
/*
#include "pp_generated/test_code_generated.h"
#include <type_traits>

class Base {};
class Test : public Base {};

int main(int argc, char **argv) {
    static_assert(std::is_base_of<pp::TypeInfo<Test>::base, Base>::value,
                  "This assert will not get thrown, because Base is the "
                  "base class of Test");

    return(0);
}
*/

//
// Get the member at an of a struct.
//

#include "pp_generated/test_code_generated.h"

struct V2 { int x, y; };
struct Test {int *a; float f; V2 v;};

enum Letters : short {a, b, c};

template<typename T>
T adder(T v) {
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) {
    return first + adder(args...);
}

#define get_member_helper(var, Type, index) *pp::get_member(var, Type, index)

int main(int argc, char **argv) {
    adder(1, 2, 3, 4);

    Test test;
    test.a = new int; *test.a = 10;
    test.f = 3.14f;
    test.v = {10, 20};

    auto &v = get_member_helper(test, Test, 2);
    auto &b = get_member_helper(v, decltype(v), 1);

    ++b;

    float f = 0;
    float *p = &f;
    float **pp = &p;

    float ** &r = pp;

    char const *str1 = pp::TypeInfo<decltype(r)>::name;


    char const *str = pp::TypeInfo<decltype(b)>::name;

    return(0);
}

//
// Simple example showing pp::Types enum.
//
/*
#include "pp_generated/test_code_generated.h"

class Test {};

int main(int argc, char **argv) {
    pp::Type a = pp::Type_int;
    pp::Type b = pp::Type_Test;

    return(0);
}
*/

//
// Will not compile. How introspection is possible in other languages.
//
/*
#include "pp_generated/test_code_generated.h"

class Test {
public:
    int a;
    float f;
    short s;
    bool b;
};

int main(int argc, char **argv) {
    Test test = {10, 3.14f, 4, true};

    for(int i = 0; (i < pp::TypeInfo<decltype(test)>::member_count); ++i) {
        // Reference to the member at index i.
        auto member = pp::get_member_information(&test, i);

        // Print out the member’s type and the value it’s holding.
        std::cout << pp::TypeInfo<member>::name << " " <<
                  member << std::endl;
    }

    return(0);
}
*/

//
// Example showing iterating through a struct.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class Test {
public:
    int a;
    float f;
    short s;
    bool b;
};

int main(int argc, char **argv) {
    Test test = {10, 3.14f, 4, true};

    for(int i = 0; (i < pp::TypeInfo<decltype(test)>::member_count); ++i) {
        pp::MemberIter member_iter = pp::get_member_information(&test, i);

        switch(member_iter.type) {
            case pp::Type_int: {
                int member = *(int *)member_iter.ptr;
                std::cout << member << std::endl;
            } break;

            case pp::Type_float: {
                float member = *(float *)member_iter.ptr;
                std::cout << member << std::endl;
            } break;

            case pp::Type_short: {
                short member = *(short *)member_iter.ptr;
                std::cout << member << std::endl;
            } break;

            case pp::Type_bool: {
                bool member = *(bool *)member_iter.ptr;
                std::cout << member << std::endl;
            } break;
        }
    }

    return(0);
}
*/

//
// More advanced example of iterating through a struct.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class Vector2 {
public:
    int x, y;
};

class Test {
public:
    Vector2 v2;
    int normal_int;
    int *int_ptr;
    double double_arr[4];
};

int main(int argc, char **argv) {
    Test test;

    test.v2 = {10, 20};

    test.normal_int = 14;

    test.int_ptr = new int;
    *test.int_ptr = 15;

    test.double_arr[0] = 0.25;
    test.double_arr[1] = 0.50;
    test.double_arr[2] = 0.75;
    test.double_arr[3] = 1.00;

    for(int i = 0; (i < pp::TypeInfo<decltype(test)>::member_count); ++i) {
        pp::MemberIter member_iter = pp::get_member_information(&test, i);

        switch(member_iter.type) {
            case pp::Type_int: {
                if(member_iter.is_ptr) {
                    int member = **(int **)member_iter.ptr;
                    printf("%s = %d\n", member_iter.name, member);
                } else {
                    int member = *(int *)member_iter.ptr;
                    printf("%s = %d\n", member_iter.name, member);
                }
            } break;

            case pp::Type_Vector2: {
                Vector2 member = *(Vector2 *)member_iter.ptr;
                printf("x = %d y = %d\n", member.x, member.y);
            } break;

            case pp::Type_double: {
                double *member = (double *)member_iter.ptr;
                for(int j = 0; (j < member_iter.arr); ++j) {
                    printf("[%d] = %f\n", j, member[j]);
                }
            } break;
        }
    }

    return(0);
}
*/

//
// Example of going through a class and iterating on each member.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class Vector2d {
public:
    int x, y;

    void operator++() { ++x; ++y; }
};

class Test {
public:
    int a;
    int b;
    float c;
    Vector2d d;
};

int main(int argc, char **argv) {
    Test test;
    test.a = 1;
    test.b = 2;
    test.c = 3.5f;
    test.d = {4, 5};

    std::cout << "Before";
    pp::print(test);

    for(int i = 0; (i < pp::TypeInfo<decltype(test)>::member_count); ++i) {
        pp::MemberIter member_iter = pp::get_member_information(&test, i);

        switch(member_iter.type) {
            case pp::Type_int: {
                int &member = *(int *)member_iter.ptr;
                ++member;
            } break;

            case pp::Type_Vector2d: {
                Vector2d &member = *(Vector2d *)member_iter.ptr;
                ++member;
            } break;

            case pp::Type_float: {
                float &member = *(float *)member_iter.ptr;
                ++member;
            } break;
        }
    }

    std::cout << std::endl << "After";
    pp::print(test);

    return(0);
}
*/

//
// Compare weak_type of int and int *.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

int main(int argc, char **argv) {
    int i, *j;

    if(pp::type_compare(pp::TypeInfo<decltype(i)>::weak_type,
                        pp::TypeInfo<decltype(j)>::weak_type)) {
        std::cout << "i and j have the same base type!" << std::endl;
    }

    return(0);
}
*/

//
// Basic pp::print example.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class String {
public:
    char *text;
    int length;
};

int main(int argc, char **argv) {
    String str;
    str.text = "Hello World";
    str.length = strlen(str.text);

    pp::print(str);

    return(0);
}
*/

//
// Printing example with pointers, arrays, arrays of pointers, and structs.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

class Vector2 {
public:
    int x, y;
};

class Test {
public:
    int i;
    float f;
    Vector2 v2;

    int *i_ptr;
    float *f_ptr;
    Vector2 *v2_ptr;

    int i_arr[2];
    float f_arr[3];
    Vector2 v2_arr[4];

    int *i_arr_ptr[2];
    float *f_arr_ptr[3];
    Vector2 *v2_arr_ptr[4];
};

int main(int argc, char **argv) {
    Test test;

    test.i = 1;
    test.f = 2.5f;
    test.v2 = {3, 4};

    test.i_ptr = NULL; // Intentionally set to NULL.
    test.f_ptr = new float; *test.f_ptr = 5.25f;
    test.v2_ptr = new Vector2; *test.v2_ptr = {6, 7};

    for(int i = 0; (i < 2); ++i) test.i_arr[i] = i;
    for(int i = 0; (i < 3); ++i) test.f_arr[i] = (float)i;
    for(int i = 0; (i < 4); ++i) test.v2_arr[i] = {i, i * 2};

    for(int i = 0; (i < 2); ++i) {
        test.i_arr_ptr[i] = new int;
        *test.i_arr_ptr[i] = i;
    }

    for(int i = 0; (i < 3); ++i) {
        test.f_arr_ptr[i] = new float;
        *test.f_arr_ptr[i] = (float)i;
    }

    for(int i = 0; (i < 4); ++i) {
        test.v2_arr_ptr[i] = new Vector2;
        test.v2_arr_ptr[i]->x = i;
        test.v2_arr_ptr[i]->y = i * 2;
    }


    pp::print(test);

    return(0);
}
*/

//
// (Windows).Serialization example using widows Structured Exception Handling.
//
/*
#include “pp_generated/test_code_generated.h”
#include <windows.h>

class Test {
public:
    int *integer[32];
};

int main(int argc, char **argv) {
    Test test = {};

    __try { // Windows SEH equivalent of “try”.
        for(int i = 0; (i < 32); ++i) {
            // Skip 15 for this example, so it should be NULL.
            if(i == 15) continue;

            test.integer[i] = new int;
            *test.integer[i] = i;
        }

        for(int i = 0; (i < 32); ++i) {
            ++(*test.integer[i]);
        }

    } __except(1) { // Windows SEH equivalent of “catch”.
        size_t buffer_size = 1024;
        char *buffer = new char[buffer_size];

        pp::serialize(test, buffer, buffer_size);

        // Create a new file called “test_output.txt” and write
        // the serialized struct to it.
        FILE *file = fopen(“test_output.txt”, “w”);
        if(file) {
            fwrite(buffer, 1, buffer_size, file);
            fclose(file);
        }
    }


    return(0);
}
*/

//
// Get size from string.
//
/*
#include "pp_generated/test_code_generated.h"

class V3 {
public:
    int x;
    int y;
    int z;
};

int main(int argc, char **argv) {
    size_t a = sizeof(V3);
    size_t b = pp::get_size_from_str("V3");

    assert(a == b); // true

    return(0);
}
*/

//
// Get number of members from string.
//
/*
#include "pp_generated/test_code_generated.h"

class V3 {
public:
    int x;
    int y;
    int z;
};

int main(int argc, char **argv) {
    size_t a = 3;
    size_t b = pp::get_number_of_members_str("V3");
    size_t c = pp::TypeInfo<V3>::member_count;

    // All of these asserts will be true.
    assert(a == b);
    assert(b == c);
    assert(a == c);

    return(0);
}
*/

//
// TypeInfo for enums.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

enum Letters : short {
    a, b, c
};

int main(int argc, char **argv) {
    char const *str = pp::TypeInfo<Letters>::name;
    std::cout << str << std::endl; // Prints "Letters".

    size_t n = pp::TypeInfo<Letters>::member_count;
    std::cout << n << std::endl; // Prints "3".

    // For enums, base is reused in order to print
    // the stored type.
    char const *underlying_type =
    pp::TypeInfo<pp::TypeInfo<Letters>::base>:name;

    // Prints "short".
    std::cout << underlying_type << std::endl;

    return(0);
}
*/

//
// String to enum examples.
//
/*
#include "pp_generated/test_code_generated.h"
#include <string>

enum Numbers : int {
    zero,
    one,
    two,
};

int main(int argc, char **argv) {
    // Using string literal.
    Numbers get_zero = pp::string_to_enum<Numbers>("zero");
    assert(get_zero == 0);

    // Using std::string.
    std::string one_as_string = "one";
    Numbers get_one = pp::string_to_enum<Numbers>(one_as_string.c_str());
    assert(get_one == 1);

    // Using string concatonation.
    std::string two_part_a = "t";
    std::string two_part_b = "wo";
    std::string full_two = two_part_a + two_part_b;
    Numbers get_two = pp::string_to_enum<Numbers>(full_two.c_str());
    assert(get_two == 2);

    return(0);
}
*/

//
// Enum to string examples.
//
/*
#include "pp_generated/test_code_generated.h"
#include <iostream>

enum class Numbers : int {
    zero,
    one,
    two,
    three
};

int main(int argc, char **argv) {
    char const *zero_str = pp::enum_to_string<Numbers>(Numbers::zero);
    std::cout << zero_str << std::endl; // Prints "zero"

    Numbers one_cpy = Numbers::one;
    char const *one_str = pp::enum_to_string<Numbers>(one_cpy);
    std::cout << one_str << std::endl; // Prints "One"

    int as_integer = 1;
    ++as_integer;
    char const *two_str = pp::enum_to_string<Numbers>((Numbers)as_integer);
    std::cout << two_str << std::endl; // Prints "Two"

    return(0);
}
*/
/*===================================================================================================
  File:                    test_code.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

// File: test_code.cpp
#include "pp_generated/test_code_generated.h"

//
// struct test.
//

struct Test {
    int i, *j; // TODO(Jonny): Three things doesn't work... for some reason.
};

union V2 {
    int e[2];
    struct {
        int x; int y;
    };
};

struct A {
    int a;
};

struct B {
    double b;
};

#define NUMBER_FOUR 4
#define NUMBER_FIVE 5
struct Foo : public A, public B {
    char const *str;
    int *int_ptr;
    float *float_ptr;
    bool *bool_ptr;
    int int_array[NUMBER_FOUR];
    double *double_ptr_array[NUMBER_FIVE];
    int *int_ptr_array[6];
    V2 v2;
};

void test_struct(void) {
    Foo foo;
    memset(&foo, 0, sizeof(foo));

    foo.str = "Hello World";

    foo.int_ptr = NULL;

    foo.float_ptr = new float; *foo.float_ptr = 10.5f;

    foo.bool_ptr = new bool; *foo.bool_ptr = true;

    foo.int_array[0] = 10;
    foo.int_array[1] = 9;
    foo.int_array[2] = 8;
    foo.int_array[3] = 7;

    foo.double_ptr_array[0] = new double; *foo.double_ptr_array[0] = 1.1;
    foo.double_ptr_array[1] = new double; *foo.double_ptr_array[1] = 2.2;
    foo.double_ptr_array[2] = new double; *foo.double_ptr_array[2] = 3.3;
    foo.double_ptr_array[3] = NULL;
    foo.double_ptr_array[4] = new double; *foo.double_ptr_array[4] = 5.5;

    foo.int_ptr_array[0] = new int; *foo.int_ptr_array[0] = 3;
    foo.int_ptr_array[1] = new int; *foo.int_ptr_array[1] = 2;
    foo.int_ptr_array[2] = new int; *foo.int_ptr_array[2] = 1;
    foo.int_ptr_array[3] = new int; *foo.int_ptr_array[3] = 0;
    foo.int_ptr_array[4] = NULL;
    foo.int_ptr_array[5] = new int; *foo.int_ptr_array[5] = -2;

    foo.v2.x = 10;
    foo.v2.y = 20;

    // From struct A.
    foo.a = 1;

    // From struct B.
    foo.b = 3.1415f;

    pp::print(foo);

    int k = 0;
}

//
// enum test.
//
enum Letters {
    letter_a,
    letter_b,
    letter_c
};

void test_enum(void) {
    size_t num_members = pp::get_number_of_enum_elements(Letters);
    printf("\nNumber of members: %lu", num_members);

    {
        char const *a = pp::enum_to_string(Letters, letter_a);
        char const *b = pp::enum_to_string(Letters, letter_b);
        char const *c = pp::enum_to_string(Letters, letter_c);
        char const *d = pp::enum_to_string(Letters, 7); // Should be null, because it's out of range.

        printf("\na = %s\nb = %s\nc = %s\nd = %s\n", a, b, c, d);
    }

    {
        int a = pp::string_to_enum(Letters, "letter_a");
        int b = pp::string_to_enum(Letters, "letter_b");
        int c = pp::string_to_enum(Letters, "letter_c");

        // TODO(Jonny): No test to see if the string is _actually_ an enum or not. So should return 0 for now...
        int d = pp::string_to_enum(Letters, "letter_d");

        printf("\na = %d\nb = %d\nc = %d\nd = %d", a, b, c, d);
    }
}

//
// std::vector test.
//
struct V3 {
    int x;
    int y;
    int z;

    V3(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct VectorTest {
    std::vector<int> integer;
    std::vector<float> floating;
    //std::vector<V3> vector3;
};

void test_vector(void) {
    VectorTest vt;

    // TODO(Jonny): There's an issue with outputting the name of primitives for vectors. I think it's because
    //              primitives don't have any members, and the preprocessor's getting a little confused.
    for(int i = 0; (i < 5); ++i) {
        vt.integer.push_back(i);
    }

    for(float i = 0; (i < 4.0f); i += 0.5f) {
        vt.floating.push_back(i);
    }

    //vt.vector3.push_back({1, 2, 3});
    //vt.vector3.push_back({3, 2, 1});
    //vt.vector3.push_back({2, 3, 1});

    pp::print(vt);

}

int main(int /*argc*/, char ** /*argv*/) {
    //test_struct();
    //test_enum();
    test_vector();

    printf("\n");
    return(0);
}

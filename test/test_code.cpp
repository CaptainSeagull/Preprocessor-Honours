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
#include "test_code_generated.h"

//
// struct test.
//
struct thingy {
    int x;
    int y;
};

union V2 {
    int e[2];
    struct {
        int x; int y;
    };
};
struct Bar {
    short s;
    int i;
    float f;
    double d;
    V2 v2;
};

#define NUMBER_FIVE 5
#define NUMBER_FOUR 4
struct Foo : public Bar, public thingy {
    char const *str;
    int *int_ptr;
    float *float_ptr;
    bool *bool_ptr;
    double *double_ptr_array[NUMBER_FIVE];
    int int_array[NUMBER_FOUR];
    std::vector<int> vec_int;
};

struct Transform {
    V2 pos;
    V2 size;
};
void test_struct(void) {
    Foo foo;
    memset(&foo, 0, sizeof(foo));

    foo.str = "Hello World";
    foo.int_ptr = new int; *foo.int_ptr = 10;
    foo.float_ptr = new float; *foo.float_ptr = 10.5f;
    foo.bool_ptr = new bool; *foo.bool_ptr = true;
    foo.double_ptr_array[0] = new double; *foo.double_ptr_array[0] = 1.1;
    foo.double_ptr_array[1] = new double; *foo.double_ptr_array[1] = 2.2;
    foo.double_ptr_array[2] = new double; *foo.double_ptr_array[2] = 3.3;
    foo.double_ptr_array[3] = NULL;
    foo.double_ptr_array[4] = new double; *foo.double_ptr_array[4] = 5.5;

    foo.int_array[0] = 11;
    foo.int_array[1] = 22;
    foo.int_array[2] = 33;
    foo.int_array[3] = 44;

    foo.s = 10;

    foo.i = 3;
    foo.f = 3.14f;
    foo.d = 3.1415;
    foo.v2.x = 0;
    foo.v2.y = 1;
    foo.x = 101;

    foo.vec_int.push_back(1);
    foo.vec_int.push_back(2);
    foo.vec_int.push_back(3);

    pp::print(foo);
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

        printf("\na = %d\nb = %d\nc = %d\n", a, b, c);
    }
}

//
// std::vector test.
//
struct V3 {
    int x;
    int y;
    int z;
};

struct VectorTest {
    std::vector<int> integer;
    std::vector<float> floating;
    std::vector<V3> vector3;
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

    {
        V3 temp;

        temp.x = 1; temp.y = 2; temp.z = 3;
        vt.vector3.push_back(temp);
        temp.x = 3; temp.y = 2; temp.z = 1;
        vt.vector3.push_back(temp);
        temp.x = 10; temp.y = 11; temp.z = 12;
        vt.vector3.push_back(temp);
    }

    pp::print(vt);

}

int main(int /*argc*/, char ** /*argv*/) {
    ///test_struct();
    //test_enum();
    test_vector();

    printf("\n");
    return(0);
}

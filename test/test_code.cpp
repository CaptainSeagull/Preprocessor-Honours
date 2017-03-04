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
    //printf("\nNumber of members: %llu", num_members);

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
    std::vector<float> vec_floating;
    std::vector<int> vec_integer;
    std::vector<V3> vec_vector3;

    std::deque<int> deque_int;

    std::forward_list<int> fl_int;
    std::list<int> list_int;
};

void std_test(void) {
    VectorTest vt;

    for(int i = 0; (i < 5); ++i) {
        vt.vec_integer.push_back(i);
    }

    for(float i = 0; (i < 4.0f); i += 0.5f) {
        vt.vec_floating.push_back(i);
    }

    vt.vec_vector3.push_back({1, 2, 3});
    vt.vec_vector3.push_back({3, 2, 1});
    vt.vec_vector3.push_back({2, 3, 1});


    for(int i = 0; (i < 5); ++i) vt.deque_int.push_back(i);

    vt.fl_int = { 10, 9, 8, 7 };
    vt.list_int = { 10, 9, 8, 7 };

    pp::print(vt);

}

struct StringTest {
    float *ptr;
    char *text;
    int len;
    int some_array[5];
};


int main(int /*argc*/, char ** /*argv*/) {
    //test_struct();
    //test_enum();
    //std_test();


    //
    //
    //

    StringTest test;// = {"Hello", 5};
    test.text = "Hello";
    test.len = 5;
    for(int i = 0; (i < 5); ++i) test.some_array[i] = 5 - i;
    test.ptr = new float; *test.ptr = 3.14f;

    pp::print(test);


    pp::TypeInfo<Foo>::base temp = {};

    pp::TypeInfo<StringTest *> info = {};

    for(int i = 0; (i < pp::TypeInfo<StringTest>::member_count); ++i) {
        auto mi = pp::get_member_information(&test, i);

        switch(mi.type) {
            case pp::Type_int: {
                if(mi.arr) {
                    for(int j = 0; (j < mi.arr); ++j) {
                        int *integer = (int *)mi.ptr;

                        printf("%d\n", integer[j]);
                    }
                } else {
                    int integer = *(int *)mi.ptr;

                    printf("%d\n", integer);
                }
            } break;

            case pp::Type_float: {
                if(mi.is_ptr) {
                    float *real = *(float **)mi.ptr;

                    printf("%f\n", *real);
                }
            } break;

            case pp::Type_char: {
                char *str = *(char **)mi.ptr;

                printf("%s\n", str);
            } break;
        }
    }

    int i = 0;

    //
    //
    //




















#if 0
    {
        pp::MemberDefinition *mems = pp::get_members_of_<StringTest>();
        for(int i = 0; (i < pp::get_member_count<StringTest>()); ++i) {
            pp::MemberDefinition cur = mems[i];

            void *member_ptr = (size_t *)((char unsigned *)&test + cur.offset);
            switch(cur.type) {
                case pp::Type_int: {
                    int integer = *(int *)member_ptr;

                    int j = 0;
                } break;

                case pp::Type_char: {
                    char *txt = *(char **)member_ptr;

                    int j = 0;
                } break;
            }
        }
    }
#endif
    printf("\n");
    return(0);
}







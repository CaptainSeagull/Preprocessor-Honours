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

#include "test_code_generated.h"

//
// struct test.
//
struct thingy {
    int x;
    int y;
};

struct V2 {int x; int y;};
struct Bar {
    short s;
    int i;
    float f;
    double d;
    V2 v2;
};

struct A { float m; };
struct B { float n; };
struct C { float o; };

struct Foo : public Bar, public thingy, public A, public B, public C {
    char *str;
    int *ip;
    float *fp;
    bool *b;
    double *p_array[5];
};

struct X : public Foo {
    int i;
};

struct Y: public X {

};

struct Transform {V2 pos; V2 size;};
void test_struct(void)
{
    // TODO(Jonny): If structs aren't initialzied to zero, then pointers often to point to invalid memory
    //              which causes a crash. Could I somehow use this, parhaps with exception handles, to test if a
    //              struct has been initialized??
    Foo foo;
    memset(&foo, 0, sizeof(foo));

    foo.str = "Hello World"; // TODO(Jonny): Why does this fail?
    foo.ip = new int; *foo.ip = 10;
    foo.fp = new float; *foo.fp = 10.5f;
    foo.b = new bool; *foo.b = true;
    foo.p_array[0] = new double; *foo.p_array[0] = 1.1;
    foo.p_array[1] = new double; *foo.p_array[1] = 2.2;
    foo.p_array[2] = new double; *foo.p_array[2] = 3.3;
    foo.p_array[3] = new double; *foo.p_array[3] = 4.4;
    // Leave foo.p_array blank.
    foo.s = 10;

    V2 v1 = {};

    foo.i = 3;
    foo.f = 3.14f;
    foo.d = 3.1415;
    foo.v2.x = 0;
    foo.v2.y = 1;
    foo.x = 101;

    pp::print(foo);

    char *buf = new char[256 * 256];
    pp::print(foo, buf, 256 * 256);
    delete buf;


    for(int i = 0; (i < pp::get_base_type_count(Foo)); ++i) {
        char const *str = pp::get_base_type_as_string(Foo, i);

        int j = 0;
    }

    bool a = pp::fuzzy_type_compare(X, Foo);
    bool b = pp::fuzzy_type_compare(Foo, X);
    bool c = pp::fuzzy_type_compare(A, B);

    {
        char const *a = pp::type_to_string(Foo);
        char const *b = pp::type_to_string(Foo *);
        char const *c = pp::weak_type_to_string(Foo);
        char const *d = pp::weak_type_to_string(Foo *);

        bool one = pp::type_compare(Foo, Foo *);
        bool two = pp::weak_type_compare(Foo, Foo *);

        int i = 0;
    }

}

//
// enum test.
//

enum Letters {
    letter_a,
    letter_b,
    letter_c
};

void test_enum(void)
{
    size_t num_members = pp::get_number_of_enum_elements(Letters);
    printf("\nNumber of members: %llu", num_members);

    {
        char const *a = pp::enum_to_string(Letters, letter_a);
        char const *b = pp::enum_to_string(Letters, letter_b);
        char const *c = pp::enum_to_string(Letters, letter_c);
        char const *d = pp::enum_to_string(Letters, 7);

        printf("a = %s\nb = %s\nc = %s\nd = %s\n", a, b, c, d);
    }

    {
        int a = pp::string_to_enum(Letters, "letter_a");
        int b = pp::string_to_enum(Letters, "letter_b");
        int c = pp::string_to_enum(Letters, "letter_c");

        printf("a = %d\nb = %d\nc = %d\n", a, b, c);
    }
}

int main(int /*argc*/, char ** /*argv*/)
{
    printf("\n");

    test_struct();
    test_enum();

    bool a = pp::type_compare(int, int);
    bool b = pp::type_compare(int, float);

    char const *str = pp::type_to_string(Bar **);

    printf("\n");

    return(0);
}

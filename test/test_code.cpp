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


    size_t pp::serialize(TYPE variable, char *buffer, size_t buffer_size);







    #include "test_code_generated.h" // Generate code.
    #include <stdlib.h> // malloc
    #include <iostream> // std::cout

    struct V2 {
        int x;
        int y;
    };
    int main(int argc, char **argv)
    {
        char buf[1024];
        V2 v;
        v.x = 1;
        v.y = 2;
        pp::print(v, buf, 1024);

        return(0);
    }
    



#if 0
    struct foo {
        int i;
    };



    // File: test_code.cpp

    #include "test_code_generated.h" // Generate code.
    #include <stdlib.h> // malloc
    #include <iostream> // std::cout

    enum Errors {
        no_error,

        out_of_memory,
        no_parameters,
    };
    int main(int argc, char **argv)
    {
        Errors e = no_error;

        if(argc <= 1) {
            e = no_parameters;
        } else {
            int *p = (int *)malloc(sizeof(int));
            if(!p) {
                e = out_of_memory;
            }
        }

        if(e != no_error) {
            char const *error_str = pp::enum_to_string(Errors, e);
            std::cout << "There was an error. " << error_str;
        }

        return(0);
    }
#endif

    
    // File: test_code.cpp
#if 0
    #include "test_code_generated.h" // Generate code.
    #include <stdlib.h> // malloc
    #include <iostream> // std::cout

    struct BaseOne {
        int a;
        int b;
        char *str;
    };
    struct BaseTwo {
        double c;
        double d;
        double *double_ptr;
    };
    
    struct SubClass : public BaseOne, public BaseTwo {
        float *float_ptr;
        double *pointer_array[5];
    };
    
    int main(int argc, char **argv)
    {
        SubClass s;
        memset(&s, 0, sizeof(SubClass));

        // BaseOne
        s.a = 1;
        s.b = 2;
        s.str = "Hello World";

        // BaseTwo
        s.c = 3.3;
        s.d = 4.4;
        s.double_ptr = new double;
        *s.double_ptr = 5.5;
    
        // SubClass
        s.float_ptr = NULL; // Leave blank
        
        s.pointer_array[0] = new double;
        *s.pointer_array[0] = 1.1;
        
        s.pointer_array[1] = new double;
        *s.pointer_array[1] = 2.2;
        
        s.pointer_array[2] = NULL; // Leave blank.
        
        s.pointer_array[3] = new double;
        *s.pointer_array[3] = 4.4;
        
        s.pointer_array[4] = new double;
        *s.pointer_array[4] = 5.5;

        pp::print(s);

        return(0);
    }
#endif
#if 0
#if 0
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
    
        print(foo);
    
        char *buf = new char[256 * 256];
        print(foo, buf, 256 * 256);
        delete buf;
        #endif
    }












    // File: test_code.cpp

    #include "test_code_generated.h" // Generate code.
    #include <stdlib.h> // malloc
    #include <iostream> // std::cout

    enum Errors {
        no_error,

        out_of_memory,
        no_parameters,
    };
    int main(int argc, char **argv)
    {
        Errors e = no_error;

        if(argv <= 1) {
            e = no_parameters;
        } else {
            int *p = (int *)malloc(sizeof(int));
            if(!p) {
                e = out_of_memory;
            }
        }

        if(e != no_error) {
            char const *error_str = pp::enum_to_string(Errors, e);
            std::cout << error_str;
        }
    }












    enum Numbers {
        zero,
        one,
        two,
        three,
    };
    int main(int argc, char **argv)
    {
        char const *str = pp::enum_to_string(Numbers, one);
        std::cout << str; // "one"

        return(0);
    }




    char const *pp::enum_to_string(EnumType, EnumType index);


    






    EnumType::element string_to_enum(Enumtype type, char const *str);










    enum Letters {
        a,
        b,
        c,
    };
    int main(int argc, char **argv)
    {
        int n = pp::get_number_of_enum_elements(Letters);
        std::cout << n; // 3


        return(0);
    }







    size_t pp::get_number_of_enum_elements(EnumType type);


    enum Numbers {
        zero,
        one,
        two,
        three,
    };
    int main(int argc, char **argv)
    {
        Numbers n = pp::string_to_enum("two");
        std::cout << n; // 2

        return(0);
    }









    char const *pp::type_to_string(TYPE t);


    template<typename T> void print_with_type(T t)
    {
        char const *str pp::type_to_string(T);
        std::cout << str << ' ' << t;
    }

    struct V2 {
        int x;
        iny y;
    };
    int main(int argc, char **argv)
    {
        char const *str = pp::type_to_string(V2);
        coud << str; // V2

        return(0);
    }





    template<typename T>
    void foo(T a)
    {
        if(pp::type_compare(decltype(a), int)) {
            do_integer_stuff(a);
        } else if(pp::type_compare(decltype(a), float)) {
            do_float_stuff(a);
        }
    }


    int i;
    if(pp::type_compare(decltype(i) int))



    struct Animal {
        int x;
        int y;
    };
    struct Cat  {
        bool meow;
    };
    int main(int argc, char **argv)
    {
        bool a = pp::type_compare(int, int);      // true
        bool a = pp::type_compare(int, float);    // false
        bool a = pp::type_compare(int, short);    // false
        bool a = pp::type_compare(float, float);  // true
        bool a = pp::type_compare(float, double); // false
        bool a = pp::type_compare(int, Cat);      // false
        bool a = pp::type_compare(Cat, Cat);      // true
        bool a = pp::type_compare(Cat, Animal);   // false
    
        Cat c;
        bool a = pp::type_compare(Cat, decltype(c)); // true
    
        return(0);
    }


using namespace pp;

struct Pigeon {
    int i;
    int j;
};

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

    print(foo);

    char *buf = new char[256 * 256];
    print(foo, buf, 256 * 256);
    delete buf;
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
    size_t num_members = get_number_of_enum_elements(Letters);
    printf("\nNumber of members: %llu", num_members);

    {
        char const *a = enum_to_string(Letters, letter_a);
        char const *b = enum_to_string(Letters, letter_b);
        char const *c = enum_to_string(Letters, letter_c);
        char const *d = enum_to_string(Letters, 7);

        printf("a = %s\nb = %s\nc = %s\nd = %s\n", a, b, c, d);
    }

    {
        int a = string_to_enum(Letters, "letter_a");
        int b = string_to_enum(Letters, "letter_b");
        int c = string_to_enum(Letters, "letter_c");

        printf("a = %d\nb = %d\nc = %d\n", a, b, c);
    }
}

int main(int /*argc*/, char ** /*argv*/)
{
    printf("\n");

    test_struct();
    test_enum();

    bool a = type_compare(int, int);
    bool b = type_compare(int, float);

    char const *str = type_to_string(Bar **);

    printf("\n");

    return(0);
}
#endif

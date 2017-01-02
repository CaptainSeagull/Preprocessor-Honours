#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

#include "static_generated.h"

// Forward declared structs (these must be declared outside the namespace...)
struct TEST;
struct thingy;
struct V2;
struct Bar;
struct A;
struct B;
struct C;
struct Foo;
struct X;
struct Y;
struct Transform;

namespace pp { // PreProcessor

// Enum with field for every type detected.
enum MetaType {
    MetaType_char,
    MetaType_short,
    MetaType_int,
    MetaType_long,
    MetaType_float,
    MetaType_double,
    MetaType_bool,
    MetaType_TEST,
    MetaType_thingy,
    MetaType_V2,
    MetaType_Bar,
    MetaType_A,
    MetaType_B,
    MetaType_C,
    MetaType_Foo,
    MetaType_X,
    MetaType_Y,
    MetaType_Transform,
};

// Recreated structs (Clang in std=C++98 complains if these are local).
struct _TEST {  _int i[10];  };
struct _thingy {  _int x;  _int y;  };
struct _V2 {  _int x;  _int y;  };
struct _Bar {  _short s;  _int i;  _float f;  _double d;  _V2 v2;  };
struct _A {  _float m;  };
struct _B {  _float n;  };
struct _C {  _float o;  };
struct _Foo : public _Bar, public _thingy, public _A, public _B, public _C {  _char *str;  _int *ip;  _float *fp;  _bool *b;  _double *p_array[10];  };
struct _X : public _Foo {  _int i;  };
struct _Y : public _X {  };
struct _Transform {  _V2 pos;  _V2 size;  };

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // TEST
    if(type_compare(T, TEST)) {
        static MemberDefinition members_of_TEST[] = {
            {MetaType_int, "i", offset_of(&_TEST::i), false, 10},
        };
        return(members_of_TEST);

    // thingy
    } else if(type_compare(T, thingy)) {
        static MemberDefinition members_of_thingy[] = {
            {MetaType_int, "x", offset_of(&_thingy::x), false, 1},
            {MetaType_int, "y", offset_of(&_thingy::y), false, 1},
        };
        return(members_of_thingy);

    // V2
    } else if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            {MetaType_int, "x", offset_of(&_V2::x), false, 1},
            {MetaType_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // Bar
    } else if(type_compare(T, Bar)) {
        static MemberDefinition members_of_Bar[] = {
            {MetaType_short, "s", offset_of(&_Bar::s), false, 1},
            {MetaType_int, "i", offset_of(&_Bar::i), false, 1},
            {MetaType_float, "f", offset_of(&_Bar::f), false, 1},
            {MetaType_double, "d", offset_of(&_Bar::d), false, 1},
            {MetaType_V2, "v2", offset_of(&_Bar::v2), false, 1},
        };
        return(members_of_Bar);

    // A
    } else if(type_compare(T, A)) {
        static MemberDefinition members_of_A[] = {
            {MetaType_float, "m", offset_of(&_A::m), false, 1},
        };
        return(members_of_A);

    // B
    } else if(type_compare(T, B)) {
        static MemberDefinition members_of_B[] = {
            {MetaType_float, "n", offset_of(&_B::n), false, 1},
        };
        return(members_of_B);

    // C
    } else if(type_compare(T, C)) {
        static MemberDefinition members_of_C[] = {
            {MetaType_float, "o", offset_of(&_C::o), false, 1},
        };
        return(members_of_C);

    // Foo
    } else if(type_compare(T, Foo)) {
        static MemberDefinition members_of_Foo[] = {
            {MetaType_char, "str", offset_of(&_Foo::str), true, 1},
            {MetaType_int, "ip", offset_of(&_Foo::ip), true, 1},
            {MetaType_float, "fp", offset_of(&_Foo::fp), true, 1},
            {MetaType_bool, "b", offset_of(&_Foo::b), true, 1},
            {MetaType_double, "p_array", offset_of(&_Foo::p_array), true, 10},
            // Members inherited from Bar.
            {MetaType_short, "s", (size_t)&((_Foo *)0)->s, false, 1},
            {MetaType_int, "i", (size_t)&((_Foo *)0)->i, false, 1},
            {MetaType_float, "f", (size_t)&((_Foo *)0)->f, false, 1},
            {MetaType_double, "d", (size_t)&((_Foo *)0)->d, false, 1},
            {MetaType_V2, "v2", (size_t)&((_Foo *)0)->v2, false, 1},
            // Members inherited from thingy.
            {MetaType_int, "x", (size_t)&((_Foo *)0)->x, false, 1},
            {MetaType_int, "y", (size_t)&((_Foo *)0)->y, false, 1},
            // Members inherited from A.
            {MetaType_float, "m", (size_t)&((_Foo *)0)->m, false, 1},
            // Members inherited from B.
            {MetaType_float, "n", (size_t)&((_Foo *)0)->n, false, 1},
            // Members inherited from C.
            {MetaType_float, "o", (size_t)&((_Foo *)0)->o, false, 1},
        };
        return(members_of_Foo);

    // X
    } else if(type_compare(T, X)) {
        static MemberDefinition members_of_X[] = {
            {MetaType_int, "i", offset_of(&_X::i), false, 1},
            // Members inherited from Foo.
            {MetaType_char, "str", (size_t)&((_X *)0)->str, true, 1},
            {MetaType_int, "ip", (size_t)&((_X *)0)->ip, true, 1},
            {MetaType_float, "fp", (size_t)&((_X *)0)->fp, true, 1},
            {MetaType_bool, "b", (size_t)&((_X *)0)->b, true, 1},
            {MetaType_double, "p_array", (size_t)&((_X *)0)->p_array, true, 10},
        };
        return(members_of_X);

    // Y
    } else if(type_compare(T, Y)) {
        static MemberDefinition members_of_Y[] = {
            // Members inherited from X.
            {MetaType_int, "i", (size_t)&((_Y *)0)->i, false, 1},
        };
        return(members_of_Y);

    // Transform
    } else if(type_compare(T, Transform)) {
        static MemberDefinition members_of_Transform[] = {
            {MetaType_V2, "pos", offset_of(&_Transform::pos), false, 1},
            {MetaType_V2, "size", offset_of(&_Transform::size), false, 1},
        };
        return(members_of_Transform);
    }

    return(0); // Error.
}

// Get the number of members for a type.
template<typename T> static int get_number_of_members_(void) {
    if(type_compare(T, TEST)) { return(1); } // TEST
    else if(type_compare(T, thingy)) { return(2); } // thingy
    else if(type_compare(T, V2)) { return(2); } // V2
    else if(type_compare(T, Bar)) { return(5); } // Bar
    else if(type_compare(T, A)) { return(1); } // A
    else if(type_compare(T, B)) { return(1); } // B
    else if(type_compare(T, C)) { return(1); } // C
    else if(type_compare(T, Foo)) { return(15); } // Foo
    else if(type_compare(T, X)) { return(6); } // X
    else if(type_compare(T, Y)) { return(1); } // Y
    else if(type_compare(T, Transform)) { return(2); } // Transform

    return(-1); // Error.
}

// Convert a type to a string.
template<typename T> static char const *type_to_string_(void) {
    // Primitives.
    if(type_compare(T, char)) { return("char"); }
    else if(type_compare(T, char *)) { return("char *"); }
    else if(type_compare(T, char **)) { return("char **"); }
    else if(type_compare(T, short)) { return("short"); }
    else if(type_compare(T, short *)) { return("short *"); }
    else if(type_compare(T, short **)) { return("short **"); }
    else if(type_compare(T, int)) { return("int"); }
    else if(type_compare(T, int *)) { return("int *"); }
    else if(type_compare(T, int **)) { return("int **"); }
    else if(type_compare(T, long)) { return("long"); }
    else if(type_compare(T, long *)) { return("long *"); }
    else if(type_compare(T, long **)) { return("long **"); }
    else if(type_compare(T, float)) { return("float"); }
    else if(type_compare(T, float *)) { return("float *"); }
    else if(type_compare(T, float **)) { return("float **"); }
    else if(type_compare(T, double)) { return("double"); }
    else if(type_compare(T, double *)) { return("double *"); }
    else if(type_compare(T, double **)) { return("double **"); }
    else if(type_compare(T, bool)) { return("bool"); }
    else if(type_compare(T, bool *)) { return("bool *"); }
    else if(type_compare(T, bool **)) { return("bool **"); }

    // Struct types.
    else if(type_compare(T, TEST)) { return("TEST"); }
    else if(type_compare(T, TEST *)) { return("TEST *"); }
    else if(type_compare(T, TEST **)) { return("TEST **"); }
    else if(type_compare(T, thingy)) { return("thingy"); }
    else if(type_compare(T, thingy *)) { return("thingy *"); }
    else if(type_compare(T, thingy **)) { return("thingy **"); }
    else if(type_compare(T, V2)) { return("V2"); }
    else if(type_compare(T, V2 *)) { return("V2 *"); }
    else if(type_compare(T, V2 **)) { return("V2 **"); }
    else if(type_compare(T, Bar)) { return("Bar"); }
    else if(type_compare(T, Bar *)) { return("Bar *"); }
    else if(type_compare(T, Bar **)) { return("Bar **"); }
    else if(type_compare(T, A)) { return("A"); }
    else if(type_compare(T, A *)) { return("A *"); }
    else if(type_compare(T, A **)) { return("A **"); }
    else if(type_compare(T, B)) { return("B"); }
    else if(type_compare(T, B *)) { return("B *"); }
    else if(type_compare(T, B **)) { return("B **"); }
    else if(type_compare(T, C)) { return("C"); }
    else if(type_compare(T, C *)) { return("C *"); }
    else if(type_compare(T, C **)) { return("C **"); }
    else if(type_compare(T, Foo)) { return("Foo"); }
    else if(type_compare(T, Foo *)) { return("Foo *"); }
    else if(type_compare(T, Foo **)) { return("Foo **"); }
    else if(type_compare(T, X)) { return("X"); }
    else if(type_compare(T, X *)) { return("X *"); }
    else if(type_compare(T, X **)) { return("X **"); }
    else if(type_compare(T, Y)) { return("Y"); }
    else if(type_compare(T, Y *)) { return("Y *"); }
    else if(type_compare(T, Y **)) { return("Y **"); }
    else if(type_compare(T, Transform)) { return("Transform"); }
    else if(type_compare(T, Transform *)) { return("Transform *"); }
    else if(type_compare(T, Transform **)) { return("Transform **"); }

    else { return(0); } // Unknown Type.
}

// Convert a type to a string.
template<typename T> static char const *weak_type_to_string_(void) {
    // Primitives.
    if(type_compare(T, char)) { return("char"); }
    else if(type_compare(T, char *)) { return("char"); }
    else if(type_compare(T, char **)) { return("char"); }
    else if(type_compare(T, short)) { return("short"); }
    else if(type_compare(T, short *)) { return("short"); }
    else if(type_compare(T, short **)) { return("short"); }
    else if(type_compare(T, int)) { return("int"); }
    else if(type_compare(T, int *)) { return("int"); }
    else if(type_compare(T, int **)) { return("int"); }
    else if(type_compare(T, long)) { return("long"); }
    else if(type_compare(T, long *)) { return("long"); }
    else if(type_compare(T, long **)) { return("long"); }
    else if(type_compare(T, float)) { return("float"); }
    else if(type_compare(T, float *)) { return("float"); }
    else if(type_compare(T, float **)) { return("float"); }
    else if(type_compare(T, double)) { return("double"); }
    else if(type_compare(T, double *)) { return("double"); }
    else if(type_compare(T, double **)) { return("double"); }
    else if(type_compare(T, bool)) { return("bool"); }
    else if(type_compare(T, bool *)) { return("bool"); }
    else if(type_compare(T, bool **)) { return("bool"); }

    // Struct types.
    else if(type_compare(T, TEST)) { return("TEST"); }
    else if(type_compare(T, TEST *)) { return("TEST"); }
    else if(type_compare(T, TEST **)) { return("TEST"); }
    else if(type_compare(T, thingy)) { return("thingy"); }
    else if(type_compare(T, thingy *)) { return("thingy"); }
    else if(type_compare(T, thingy **)) { return("thingy"); }
    else if(type_compare(T, V2)) { return("V2"); }
    else if(type_compare(T, V2 *)) { return("V2"); }
    else if(type_compare(T, V2 **)) { return("V2"); }
    else if(type_compare(T, Bar)) { return("Bar"); }
    else if(type_compare(T, Bar *)) { return("Bar"); }
    else if(type_compare(T, Bar **)) { return("Bar"); }
    else if(type_compare(T, A)) { return("A"); }
    else if(type_compare(T, A *)) { return("A"); }
    else if(type_compare(T, A **)) { return("A"); }
    else if(type_compare(T, B)) { return("B"); }
    else if(type_compare(T, B *)) { return("B"); }
    else if(type_compare(T, B **)) { return("B"); }
    else if(type_compare(T, C)) { return("C"); }
    else if(type_compare(T, C *)) { return("C"); }
    else if(type_compare(T, C **)) { return("C"); }
    else if(type_compare(T, Foo)) { return("Foo"); }
    else if(type_compare(T, Foo *)) { return("Foo"); }
    else if(type_compare(T, Foo **)) { return("Foo"); }
    else if(type_compare(T, X)) { return("X"); }
    else if(type_compare(T, X *)) { return("X"); }
    else if(type_compare(T, X **)) { return("X"); }
    else if(type_compare(T, Y)) { return("Y"); }
    else if(type_compare(T, Y *)) { return("Y"); }
    else if(type_compare(T, Y **)) { return("Y"); }
    else if(type_compare(T, Transform)) { return("Transform"); }
    else if(type_compare(T, Transform *)) { return("Transform"); }
    else if(type_compare(T, Transform **)) { return("Transform"); }

    else { return(0); } // Unknown Type.
}

// Get the number of base types.
template<typename T> static int get_base_type_count_(void) {
    if(type_compare(T, Foo))    { return(5); }
    else if(type_compare(T, X)) { return(1); }
    else if(type_compare(T, Y)) { return(1); }

    return(0); // Not found.
}

// Get the base type.
template<typename T> static char const *get_base_type_as_string_(int index/*= 0*/) {
    if(type_compare(T, Foo)) {
        if(index == 0)      { return("Bar"); }
        else if(index == 1) { return("thingy"); }
        else if(index == 2) { return("A"); }
        else if(index == 3) { return("B"); }
        else if(index == 4) { return("C"); }
    } else if(type_compare(T, X)) {
        if(index == 0)      { return("Foo"); }
    } else if(type_compare(T, Y)) {
        if(index == 0)      { return("X"); }
    }

    return(0); // Not found.
}

//
// Enum meta data.
//

// Meta Data for Letters.
static int number_of_elements_in_enum_Letters = 3;
static char const *enum_to_string_Letters(int v) {
    switch(v) {
        case 0: { return("letter_a"); } break;
        case 1: { return("letter_b"); } break;
        case 2: { return("letter_c"); } break;
    }

    return(0); // v is out of bounds.
}
static int string_to_enum_Letters(char const *str) {
    if(str) {
        if(strcmp(str, "letter_a") == 0) { return(0); }
        else if(strcmp(str, "letter_b") == 0) { return(1); }
        else if(strcmp(str, "letter_c") == 0) { return(2); }
    }

    return(0);  // str didn't match.
}

} // namespace pp

#endif // Header guard.


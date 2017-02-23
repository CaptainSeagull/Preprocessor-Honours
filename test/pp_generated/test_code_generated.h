#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

// Forward declared structs (these must be declared outside the namespace...)
struct Test;
union V2;
struct A;
struct B;
struct Foo;
struct V3;
struct VectorTest;

#include "static_generated.h"

namespace pp { // PreProcessor
#define _std std // TODO(Jonny): This is really stupid...
// Enum with field for every type detected.
enum MetaType {
    MetaType_char,
    MetaType_short,
    MetaType_int,
    MetaType_long,
    MetaType_float,
    MetaType_double,
    MetaType_bool,
    MetaType_Test,
    MetaType_V2,
    MetaType_A,
    MetaType_B,
    MetaType_Foo,
    MetaType_V3,
    MetaType_VectorTest,
    MetaType_std_vector_float,
    MetaType_std_vector_int,
    MetaType_std_vector_V3,
};

static bool is_meta_type_container(int type) {
    if(type == MetaType_char) {return(false);} // false
    else if(type == MetaType_short) {return(false);} // false
    else if(type == MetaType_int) {return(false);} // false
    else if(type == MetaType_long) {return(false);} // false
    else if(type == MetaType_float) {return(false);} // false
    else if(type == MetaType_double) {return(false);} // false
    else if(type == MetaType_bool) {return(false);} // false
    else if(type == MetaType_Test) {return(false);} // false
    else if(type == MetaType_V2) {return(false);} // false
    else if(type == MetaType_A) {return(false);} // false
    else if(type == MetaType_B) {return(false);} // false
    else if(type == MetaType_Foo) {return(false);} // false
    else if(type == MetaType_V3) {return(false);} // false
    else if(type == MetaType_VectorTest) {return(false);} // false
    else if(type == MetaType_std_vector_float) {return(true);} // true
    else if(type == MetaType_std_vector_int) {return(true);} // true
    else if(type == MetaType_std_vector_V3) {return(true);} // true

    // Should not be reached.
    assert(0);
    return(0);
}
static char const * meta_type_to_name(/*MetaType*/int mt, bool is_ptr) {
    if(mt == MetaType_Test) {
        if(is_ptr) {return("Test *");}
        else       {return("Test");  }
    } else if(mt == MetaType_V2) {
        if(is_ptr) {return("V2 *");}
        else       {return("V2");  }
    } else if(mt == MetaType_A) {
        if(is_ptr) {return("A *");}
        else       {return("A");  }
    } else if(mt == MetaType_B) {
        if(is_ptr) {return("B *");}
        else       {return("B");  }
    } else if(mt == MetaType_Foo) {
        if(is_ptr) {return("Foo *");}
        else       {return("Foo");  }
    } else if(mt == MetaType_V3) {
        if(is_ptr) {return("V3 *");}
        else       {return("V3");  }
    } else if(mt == MetaType_VectorTest) {
        if(is_ptr) {return("VectorTest *");}
        else       {return("VectorTest");  }
    }
    assert(0); 
    return(0); // Not found
}
static size_t serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written);template<typename T, typename U> static size_t
serialize_container(void *member_ptr, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    T container = *(T *)member_ptr;
    for(auto &iter : container) {
        bytes_written = serialize_struct_((void *)&iter, name, type_to_string(U), indent, buffer, buf_size, bytes_written);
    }

    return(bytes_written);
}


// Function to serialize a struct to a char array buffer.
static size_t
serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    assert((buffer) && (buf_size > 0)); // Check params.

    if(!indent) {memset(buffer + bytes_written, 0, buf_size - bytes_written);} // If this is the first time through, zero the buffer.

    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); assert(members_of_Something); // Get the members_of pointer. 
    if(members_of_Something) {
        // Setup the indent buffer.
        char indent_buf[256] = {};
        for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}

        // Write the name and the type.
        if(name) {bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, type_as_str, name);}
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
                case MetaType_double: { // double.
                    bytes_written = serialize_primitive_((double *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_float: { // float.
                    bytes_written = serialize_primitive_((float *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_int: { // int.
                    bytes_written = serialize_primitive_((int *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_long: { // long.
                    bytes_written = serialize_primitive_((long *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_short: { // short.
                    bytes_written = serialize_primitive_((short *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_bool: { // bool.
                    bytes_written = serialize_primitive_((bool *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                // char (special case).
                case MetaType_char: {
                    if(member_ptr) {
                        if(member->is_ptr) {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, (char *)(*(size_t *)member_ptr));
                        } else {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)((size_t *)member_ptr));
                        }
                    } else {
                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                    }
                } break; // case MetaType_char

                default: {
                    if(is_meta_type_container(member->type)) {
                        if(member->type == MetaType_std_vector_float) {bytes_written = serialize_container<std::vector<float>, float>(member_ptr, name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == MetaType_std_vector_int) {bytes_written = serialize_container<std::vector<int>, int>(member_ptr, name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == MetaType_std_vector_V3) {bytes_written = serialize_container<std::vector<V3>, V3>(member_ptr, name, indent, buffer, buf_size, bytes_written);}

                    } else {
                        char const *name = meta_type_to_name(member->type, member->is_ptr != 0);
                        bytes_written = serialize_struct_(member_ptr, member->name, name, indent, buffer, buf_size - bytes_written, bytes_written);
                    }
                } break; // default 
            }
        }
    }

    return(bytes_written);
}
// Recreated structs (Clang in std=C++98 complains if these are local).
struct _Test {  _int i;  _int *j;  };
union _V2 {  _int e[2];  struct { _int x;  _int y;  }; };
struct _A {  _int a;  };
struct _B {  _double b;  };
struct _Foo : public _A, public _B {  _char *str;  _int *int_ptr;  _float *float_ptr;  _bool *bool_ptr;  _int int_array[4];  _double *double_ptr_array[5];  _int *int_ptr_array[6];  _V2 v2;  };
struct _V3 {  _int x;  _int y;  _int z;  };
struct _VectorTest {  _std::vector<float> floating;  _std::vector<int> integer;  _std::vector<V3> vector3;  };

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // Test
    if(type_compare(T, Test)) {
        static MemberDefinition members_of_Test[] = {
            {MetaType_int, "i", offset_of(&_Test::i), false, 1},
            {MetaType_int, "j", offset_of(&_Test::j), true, 1},
        };
        return(members_of_Test);

    // V2
    } else if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            {MetaType_int, "e", offset_of(&_V2::e), false, 2},
            {MetaType_int, "x", offset_of(&_V2::x), false, 1},
            {MetaType_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // A
    } else if(type_compare(T, A)) {
        static MemberDefinition members_of_A[] = {
            {MetaType_int, "a", offset_of(&_A::a), false, 1},
        };
        return(members_of_A);

    // B
    } else if(type_compare(T, B)) {
        static MemberDefinition members_of_B[] = {
            {MetaType_double, "b", offset_of(&_B::b), false, 1},
        };
        return(members_of_B);

    // Foo
    } else if(type_compare(T, Foo)) {
        static MemberDefinition members_of_Foo[] = {
            {MetaType_char, "str", offset_of(&_Foo::str), true, 1},
            {MetaType_int, "int_ptr", offset_of(&_Foo::int_ptr), true, 1},
            {MetaType_float, "float_ptr", offset_of(&_Foo::float_ptr), true, 1},
            {MetaType_bool, "bool_ptr", offset_of(&_Foo::bool_ptr), true, 1},
            {MetaType_int, "int_array", offset_of(&_Foo::int_array), false, 4},
            {MetaType_double, "double_ptr_array", offset_of(&_Foo::double_ptr_array), true, 5},
            {MetaType_int, "int_ptr_array", offset_of(&_Foo::int_ptr_array), true, 6},
            {MetaType_V2, "v2", offset_of(&_Foo::v2), false, 1},
            // Members inherited from A.
            {MetaType_int, "a", (size_t)&((_Foo *)0)->a, false, 1},
            // Members inherited from B.
            {MetaType_double, "b", (size_t)&((_Foo *)0)->b, false, 1},
        };
        return(members_of_Foo);

    // V3
    } else if(type_compare(T, V3)) {
        static MemberDefinition members_of_V3[] = {
            {MetaType_int, "x", offset_of(&_V3::x), false, 1},
            {MetaType_int, "y", offset_of(&_V3::y), false, 1},
            {MetaType_int, "z", offset_of(&_V3::z), false, 1},
        };
        return(members_of_V3);

    // VectorTest
    } else if(type_compare(T, VectorTest)) {
        static MemberDefinition members_of_VectorTest[] = {
            {MetaType_std_vector_float, "floating", offset_of(&_VectorTest::floating), false, 1},
            {MetaType_std_vector_int, "integer", offset_of(&_VectorTest::integer), false, 1},
            {MetaType_std_vector_V3, "vector3", offset_of(&_VectorTest::vector3), false, 1},
        };
        return(members_of_VectorTest);
    }

    return(0); // Error.
}

// Get the number of members for a type.
template<typename T> static int get_number_of_members_(void) {
    if(type_compare(T, Test)) { return(2); } // Test
    else if(type_compare(T, V2)) { return(3); } // V2
    else if(type_compare(T, A)) { return(1); } // A
    else if(type_compare(T, B)) { return(1); } // B
    else if(type_compare(T, Foo)) { return(10); } // Foo
    else if(type_compare(T, V3)) { return(3); } // V3
    else if(type_compare(T, VectorTest)) { return(3); } // VectorTest

    return(-1); // Error.
}

// Convert a type into a members of pointer.
static MemberDefinition *get_members_of_str(char const *str) {
    // char
    if((strcmp(str, "char") == 0) || (strcmp(str, "char *") == 0) || (strcmp(str, "char **") == 0)) {
        static MemberDefinition members_of_char[] = {
            {MetaType_char, "", 0, false, 1}
        };
        return(members_of_char);

    // short
    } else if((strcmp(str, "short") == 0) || (strcmp(str, "short *") == 0) || (strcmp(str, "short **") == 0)) {
        static MemberDefinition members_of_short[] = {
            {MetaType_short, "", 0, false, 1}
        };
        return(members_of_short);

    // int
    } else if((strcmp(str, "int") == 0) || (strcmp(str, "int *") == 0) || (strcmp(str, "int **") == 0)) {
        static MemberDefinition members_of_int[] = {
            {MetaType_int, "", 0, false, 1}
        };
        return(members_of_int);

    // long
    } else if((strcmp(str, "long") == 0) || (strcmp(str, "long *") == 0) || (strcmp(str, "long **") == 0)) {
        static MemberDefinition members_of_long[] = {
            {MetaType_long, "", 0, false, 1}
        };
        return(members_of_long);

    // float
    } else if((strcmp(str, "float") == 0) || (strcmp(str, "float *") == 0) || (strcmp(str, "float **") == 0)) {
        static MemberDefinition members_of_float[] = {
            {MetaType_float, "", 0, false, 1}
        };
        return(members_of_float);

    // double
    } else if((strcmp(str, "double") == 0) || (strcmp(str, "double *") == 0) || (strcmp(str, "double **") == 0)) {
        static MemberDefinition members_of_double[] = {
            {MetaType_double, "", 0, false, 1}
        };
        return(members_of_double);

    // bool
    } else if((strcmp(str, "bool") == 0) || (strcmp(str, "bool *") == 0) || (strcmp(str, "bool **") == 0)) {
        static MemberDefinition members_of_bool[] = {
            {MetaType_bool, "", 0, false, 1}
        };
        return(members_of_bool);


    // Test
    } else if((strcmp(str, "Test") == 0) || (strcmp(str, "Test *") == 0) || (strcmp(str, "Test **") == 0)) {
        static MemberDefinition members_of_Test[] = {
            {MetaType_int, "i", offset_of(&_Test::i), false, 1},
            {MetaType_int, "j", offset_of(&_Test::j), true, 1},
        };
        return(members_of_Test);

    // V2
    } else if((strcmp(str, "V2") == 0) || (strcmp(str, "V2 *") == 0) || (strcmp(str, "V2 **") == 0)) {
        static MemberDefinition members_of_V2[] = {
            {MetaType_int, "e", offset_of(&_V2::e), false, 2},
            {MetaType_int, "x", offset_of(&_V2::x), false, 1},
            {MetaType_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // A
    } else if((strcmp(str, "A") == 0) || (strcmp(str, "A *") == 0) || (strcmp(str, "A **") == 0)) {
        static MemberDefinition members_of_A[] = {
            {MetaType_int, "a", offset_of(&_A::a), false, 1},
        };
        return(members_of_A);

    // B
    } else if((strcmp(str, "B") == 0) || (strcmp(str, "B *") == 0) || (strcmp(str, "B **") == 0)) {
        static MemberDefinition members_of_B[] = {
            {MetaType_double, "b", offset_of(&_B::b), false, 1},
        };
        return(members_of_B);

    // Foo
    } else if((strcmp(str, "Foo") == 0) || (strcmp(str, "Foo *") == 0) || (strcmp(str, "Foo **") == 0)) {
        static MemberDefinition members_of_Foo[] = {
            {MetaType_char, "str", offset_of(&_Foo::str), true, 1},
            {MetaType_int, "int_ptr", offset_of(&_Foo::int_ptr), true, 1},
            {MetaType_float, "float_ptr", offset_of(&_Foo::float_ptr), true, 1},
            {MetaType_bool, "bool_ptr", offset_of(&_Foo::bool_ptr), true, 1},
            {MetaType_int, "int_array", offset_of(&_Foo::int_array), false, 4},
            {MetaType_double, "double_ptr_array", offset_of(&_Foo::double_ptr_array), true, 5},
            {MetaType_int, "int_ptr_array", offset_of(&_Foo::int_ptr_array), true, 6},
            {MetaType_V2, "v2", offset_of(&_Foo::v2), false, 1},
            // Members inherited from A.
            {MetaType_int, "a", (size_t)&((_Foo *)0)->a, false, 1},
            // Members inherited from B.
            {MetaType_double, "b", (size_t)&((_Foo *)0)->b, false, 1},
        };
        return(members_of_Foo);

    // V3
    } else if((strcmp(str, "V3") == 0) || (strcmp(str, "V3 *") == 0) || (strcmp(str, "V3 **") == 0)) {
        static MemberDefinition members_of_V3[] = {
            {MetaType_int, "x", offset_of(&_V3::x), false, 1},
            {MetaType_int, "y", offset_of(&_V3::y), false, 1},
            {MetaType_int, "z", offset_of(&_V3::z), false, 1},
        };
        return(members_of_V3);

    // VectorTest
    } else if((strcmp(str, "VectorTest") == 0) || (strcmp(str, "VectorTest *") == 0) || (strcmp(str, "VectorTest **") == 0)) {
        static MemberDefinition members_of_VectorTest[] = {
            {MetaType_std_vector_float, "floating", offset_of(&_VectorTest::floating), false, 1},
            {MetaType_std_vector_int, "integer", offset_of(&_VectorTest::integer), false, 1},
            {MetaType_std_vector_V3, "vector3", offset_of(&_VectorTest::vector3), false, 1},
        };
        return(members_of_VectorTest);
    }

    return(0); // Error.
}

// Get the number of members for a type.
static int get_number_of_members_str(char const *str) {
    if(strcmp(str, "char") == 0) { return(1); }
    else if(strcmp(str, "short") == 0) { return(1); }
    else if(strcmp(str, "int") == 0) { return(1); }
    else if(strcmp(str, "long") == 0) { return(1); }
    else if(strcmp(str, "float") == 0) { return(1); }
    else if(strcmp(str, "double") == 0) { return(1); }
    else if(strcmp(str, "bool") == 0) { return(1); }
    else if(strcmp(str, "Test") == 0) { return(2); } // Test
    else if(strcmp(str, "V2") == 0) { return(3); } // V2
    else if(strcmp(str, "A") == 0) { return(1); } // A
    else if(strcmp(str, "B") == 0) { return(1); } // B
    else if(strcmp(str, "Foo") == 0) { return(10); } // Foo
    else if(strcmp(str, "V3") == 0) { return(3); } // V3
    else if(strcmp(str, "VectorTest") == 0) { return(3); } // VectorTest

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
    else if(type_compare(T, Test)) { return("Test"); }
    else if(type_compare(T, Test *)) { return("Test *"); }
    else if(type_compare(T, Test **)) { return("Test **"); }
    else if(type_compare(T, V2)) { return("V2"); }
    else if(type_compare(T, V2 *)) { return("V2 *"); }
    else if(type_compare(T, V2 **)) { return("V2 **"); }
    else if(type_compare(T, A)) { return("A"); }
    else if(type_compare(T, A *)) { return("A *"); }
    else if(type_compare(T, A **)) { return("A **"); }
    else if(type_compare(T, B)) { return("B"); }
    else if(type_compare(T, B *)) { return("B *"); }
    else if(type_compare(T, B **)) { return("B **"); }
    else if(type_compare(T, Foo)) { return("Foo"); }
    else if(type_compare(T, Foo *)) { return("Foo *"); }
    else if(type_compare(T, Foo **)) { return("Foo **"); }
    else if(type_compare(T, V3)) { return("V3"); }
    else if(type_compare(T, V3 *)) { return("V3 *"); }
    else if(type_compare(T, V3 **)) { return("V3 **"); }
    else if(type_compare(T, VectorTest)) { return("VectorTest"); }
    else if(type_compare(T, VectorTest *)) { return("VectorTest *"); }
    else if(type_compare(T, VectorTest **)) { return("VectorTest **"); }

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
    else if(type_compare(T, Test)) { return("Test"); }
    else if(type_compare(T, Test *)) { return("Test"); }
    else if(type_compare(T, Test **)) { return("Test"); }
    else if(type_compare(T, V2)) { return("V2"); }
    else if(type_compare(T, V2 *)) { return("V2"); }
    else if(type_compare(T, V2 **)) { return("V2"); }
    else if(type_compare(T, A)) { return("A"); }
    else if(type_compare(T, A *)) { return("A"); }
    else if(type_compare(T, A **)) { return("A"); }
    else if(type_compare(T, B)) { return("B"); }
    else if(type_compare(T, B *)) { return("B"); }
    else if(type_compare(T, B **)) { return("B"); }
    else if(type_compare(T, Foo)) { return("Foo"); }
    else if(type_compare(T, Foo *)) { return("Foo"); }
    else if(type_compare(T, Foo **)) { return("Foo"); }
    else if(type_compare(T, V3)) { return("V3"); }
    else if(type_compare(T, V3 *)) { return("V3"); }
    else if(type_compare(T, V3 **)) { return("V3"); }
    else if(type_compare(T, VectorTest)) { return("VectorTest"); }
    else if(type_compare(T, VectorTest *)) { return("VectorTest"); }
    else if(type_compare(T, VectorTest **)) { return("VectorTest"); }

    else { return(0); } // Unknown Type.
}

// Get the number of base types.
template<typename T> static int get_base_type_count_(void) {
    if(type_compare(T, Foo))    { return(2); }

    return(0); // Not found.
}

// Get the base type.
template<typename T> static char const *get_base_type_as_string_(int index/*= 0*/) {
    if(type_compare(T, Foo)) {
        if(index == 0)      { return("A"); }
        else if(index == 1) { return("B"); }
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

#undef _std
} // namespace pp

#endif // Header guard.


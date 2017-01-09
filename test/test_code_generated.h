#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

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

#include "static_generated.h"

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

// Function to serialize a struct to a char array buffer.
static size_t
serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    assert((name) && (buffer) && (buf_size > 0)); // Check params.

    if(!indent) { memset(buffer + bytes_written, 0, buf_size - bytes_written); } // If this is the first time through, zero the buffer.

    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); assert(members_of_Something); // Get the members_of pointer. 
    if(members_of_Something) {
        // Setup the indent buffer.
        char indent_buf[256] = {};
        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }

        // Write the name and the type.
        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, type_as_str, name);
        indent += 4;

        // Add 4 to the indent.
        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }

        int num_members = get_number_of_members_str(type_as_str); assert(num_members != -1); // Get the number of members for the for loop.
        for(int i = 0; (i < num_members); ++i) {
            MemberDefinition *member = members_of_Something + i; // Get the member pointer with meta data.
            size_t *member_ptr = (size_t *)((char *)var + member->offset); // Get the actual pointer to the memory address.
            // TODO(Jonny): Go through and check all the pointers are correct on these.
            switch(member->type) {
                // double.
                case MetaType_double: {
                    if(member->arr_size > 1) {
                        for(int j = 0; (j < member->arr_size); ++j) {
                            bool is_null = (member->is_ptr) ? !(*(double **)(member_ptr + j)) : 0;
                            if(!is_null) {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(double *)member_ptr[j] : member_ptr[j]);
                            } else {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
                            }
                        }
                    } else {
                        double *double_value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;
                        if(double_value) {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, *double_value);
                        } else {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case MetaType_double

                // float.
                case MetaType_float: {
                    if(member->arr_size > 1) {
                        for(int j = 0; (j < member->arr_size); ++j) {
                            bool is_null = (member->is_ptr) ? !(*(float **)(member_ptr + j)) : 0;
                            if(!is_null) {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(float *)member_ptr[j] : member_ptr[j]);
                            } else {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
                            }
                        }
                    } else {
                        float *float_value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;
                        if(float_value) {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, *float_value);
                        } else {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case MetaType_float

                // int.
                case MetaType_int: {
                    if(member->arr_size > 1) {
                        for(int j = 0; (j < member->arr_size); ++j) {
                            bool is_null = (member->is_ptr) ? !(*(int **)(member_ptr + j)) : 0;
                            if(!is_null) {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(int *)member_ptr[j] : (int)member_ptr[j]);
                            } else {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
                            }
                        }
                    } else {
                        int *int_value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;
                        if(int_value) {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, *int_value);
                        } else {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case MetaType_int

                // long.
                case MetaType_long: {
                    if(member->arr_size > 1) {
                        for(int j = 0; (j < member->arr_size); ++j) {
                            bool is_null = (member->is_ptr) ? !(*(long **)(member_ptr + j)) : 0;
                            if(!is_null) {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %ld", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(long *)member_ptr[j] : (long)member_ptr[j]);
                            } else {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
                            }
                        }
                    } else {
                        long *long_value = (member->is_ptr) ? *(long **)member_ptr : (long *)member_ptr;
                        if(long_value) {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s = %ld", indent_buf, (member->is_ptr) ? "*" : "", member->name, *long_value);
                        } else {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case MetaType_long

                // short.
                case MetaType_short: {
                    if(member->arr_size > 1) {
                        for(int j = 0; (j < member->arr_size); ++j) {
                            bool is_null = (member->is_ptr) ? !(*(short **)(member_ptr + j)) : 0;
                            if(!is_null) {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(short *)member_ptr[j] : (short)member_ptr[j]);
                            } else {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
                            }
                        }
                    } else {
                        short *short_value = (member->is_ptr) ? *(short **)member_ptr : (short *)member_ptr;
                        if(short_value) {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, *short_value);
                        } else {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case MetaType_short

                // bool.
                case MetaType_bool: {
                    bool *bool_value = 0;
                    if(member->arr_size > 1) {
                        for(int j = 0; (j < member->arr_size); ++j) {
                            bool is_null = (member->is_ptr) ? !(*(bool **)(member_ptr + j)) : 0;
                            if(is_null) {
                                size_t value_to_print = (member->is_ptr) ? **(bool **)(member_ptr + j) : member_ptr[j];
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s[%d] = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (value_to_print) ? "true" : "false");
                            } else {
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
                            }
                        }
                    } else {
                        bool_value = (member->is_ptr) ? *(bool **)member_ptr : (bool *)member_ptr;
                        if(bool_value) {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, (bool_value) ? "true" : "false");
                        } else {
                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case MetaType_bool

                // char.
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

                // If the type wasn't a primtive, do a switchon the type again, but search for structs.
                // Then that should recursively call this function again.
                default: {
                    switch(member->type) {
                        case MetaType_TEST: {
                            // TEST
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "TEST *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "TEST", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_TEST

                        case MetaType_thingy: {
                            // thingy
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "thingy *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "thingy", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_thingy

                        case MetaType_V2: {
                            // V2
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "V2 *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "V2", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_V2

                        case MetaType_Bar: {
                            // Bar
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Bar *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Bar", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_Bar

                        case MetaType_A: {
                            // A
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "A *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "A", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_A

                        case MetaType_B: {
                            // B
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "B *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "B", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_B

                        case MetaType_C: {
                            // C
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "C *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "C", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_C

                        case MetaType_Foo: {
                            // Foo
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Foo *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Foo", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_Foo

                        case MetaType_X: {
                            // X
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "X *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "X", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_X

                        case MetaType_Y: {
                            // Y
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Y *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Y", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_Y

                        case MetaType_Transform: {
                            // Transform
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Transform *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "Transform", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_Transform

                    } // switch(member->type)
                } break; // default 
            }
        }
    }

    return(bytes_written);
}
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

// Convert a type into a members of pointer.
static MemberDefinition *get_members_of_str(char const *str) {
    // TEST
    if((strcmp(str, "TEST") == 0) || (strcmp(str, "TEST *") == 0) || (strcmp(str, "TEST **") == 0)) {
        static MemberDefinition members_of_TEST[] = {
            {MetaType_int, "i", offset_of(&_TEST::i), false, 10},
        };
        return(members_of_TEST);

    // thingy
    } if((strcmp(str, "thingy") == 0) || (strcmp(str, "thingy *") == 0) || (strcmp(str, "thingy **") == 0)) {
        static MemberDefinition members_of_thingy[] = {
            {MetaType_int, "x", offset_of(&_thingy::x), false, 1},
            {MetaType_int, "y", offset_of(&_thingy::y), false, 1},
        };
        return(members_of_thingy);

    // V2
    } if((strcmp(str, "V2") == 0) || (strcmp(str, "V2 *") == 0) || (strcmp(str, "V2 **") == 0)) {
        static MemberDefinition members_of_V2[] = {
            {MetaType_int, "x", offset_of(&_V2::x), false, 1},
            {MetaType_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // Bar
    } if((strcmp(str, "Bar") == 0) || (strcmp(str, "Bar *") == 0) || (strcmp(str, "Bar **") == 0)) {
        static MemberDefinition members_of_Bar[] = {
            {MetaType_short, "s", offset_of(&_Bar::s), false, 1},
            {MetaType_int, "i", offset_of(&_Bar::i), false, 1},
            {MetaType_float, "f", offset_of(&_Bar::f), false, 1},
            {MetaType_double, "d", offset_of(&_Bar::d), false, 1},
            {MetaType_V2, "v2", offset_of(&_Bar::v2), false, 1},
        };
        return(members_of_Bar);

    // A
    } if((strcmp(str, "A") == 0) || (strcmp(str, "A *") == 0) || (strcmp(str, "A **") == 0)) {
        static MemberDefinition members_of_A[] = {
            {MetaType_float, "m", offset_of(&_A::m), false, 1},
        };
        return(members_of_A);

    // B
    } if((strcmp(str, "B") == 0) || (strcmp(str, "B *") == 0) || (strcmp(str, "B **") == 0)) {
        static MemberDefinition members_of_B[] = {
            {MetaType_float, "n", offset_of(&_B::n), false, 1},
        };
        return(members_of_B);

    // C
    } if((strcmp(str, "C") == 0) || (strcmp(str, "C *") == 0) || (strcmp(str, "C **") == 0)) {
        static MemberDefinition members_of_C[] = {
            {MetaType_float, "o", offset_of(&_C::o), false, 1},
        };
        return(members_of_C);

    // Foo
    } if((strcmp(str, "Foo") == 0) || (strcmp(str, "Foo *") == 0) || (strcmp(str, "Foo **") == 0)) {
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
    } if((strcmp(str, "X") == 0) || (strcmp(str, "X *") == 0) || (strcmp(str, "X **") == 0)) {
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
    } if((strcmp(str, "Y") == 0) || (strcmp(str, "Y *") == 0) || (strcmp(str, "Y **") == 0)) {
        static MemberDefinition members_of_Y[] = {
            // Members inherited from X.
            {MetaType_int, "i", (size_t)&((_Y *)0)->i, false, 1},
        };
        return(members_of_Y);

    // Transform
    } if((strcmp(str, "Transform") == 0) || (strcmp(str, "Transform *") == 0) || (strcmp(str, "Transform **") == 0)) {
        static MemberDefinition members_of_Transform[] = {
            {MetaType_V2, "pos", offset_of(&_Transform::pos), false, 1},
            {MetaType_V2, "size", offset_of(&_Transform::size), false, 1},
        };
        return(members_of_Transform);
    }

    return(0); // Error.
}

// Get the number of members for a type.
static int get_number_of_members_str(char const *str) {
    if(strcmp(str, "TEST") == 0) { return(1); } // TEST
    else if(strcmp(str, "thingy") == 0) { return(2); } // thingy
    else if(strcmp(str, "V2") == 0) { return(2); } // V2
    else if(strcmp(str, "Bar") == 0) { return(5); } // Bar
    else if(strcmp(str, "A") == 0) { return(1); } // A
    else if(strcmp(str, "B") == 0) { return(1); } // B
    else if(strcmp(str, "C") == 0) { return(1); } // C
    else if(strcmp(str, "Foo") == 0) { return(15); } // Foo
    else if(strcmp(str, "X") == 0) { return(6); } // X
    else if(strcmp(str, "Y") == 0) { return(1); } // Y
    else if(strcmp(str, "Transform") == 0) { return(2); } // Transform

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


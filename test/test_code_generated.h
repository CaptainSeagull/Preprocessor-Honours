#if !defined(GENERATED_H) // TODO(Jonny): Add the actual filename in here?

#include "static_generated.h"

namespace pp { // PreProcessor

// Enum with field for every type detected.
enum MetaType {
    meta_type_char,
    meta_type_short,
    meta_type_int,
    meta_type_long,
    meta_type_float,
    meta_type_double,
    meta_type_bool,
    meta_type_Pigeon,
    meta_type_thingy,
    meta_type_V2,
    meta_type_Bar,
    meta_type_A,
    meta_type_B,
    meta_type_C,
    meta_type_Foo,
    meta_type_Transform,
};

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void)
{
    // Recreated structs.
    struct _Pigeon {  _int age;  _char *name;  };
    struct _thingy {  _int x;  _int y;  };
    struct _V2 {  _int x;  _int y;  };
    struct _Bar {  _short s;  _int i;  _float f;  _double d;  _V2 v2;  };
    struct _A {  _float m;  };
    struct _B {  _float n;  };
    struct _C {  _float o;  };
    struct _Foo : public _Bar, public _thingy, public _A, public _B, public _C {  _char *str;  _int *ip;  _float *fp;  _bool *b;  _double *p_array[5];  };
    struct _Transform {  _V2 pos;  _V2 size;  };
 
    // Pigeon
    if(type_compare(T, Pigeon)) {
        static MemberDefinition members_of_Pigeon[] = {
            // Members.
            {meta_type_int, "age", (size_t)&((_Pigeon *)0)->age, false, 1},
            {meta_type_char, "name", (size_t)&((_Pigeon *)0)->name, true, 1},
        };
        return(members_of_Pigeon);

    // thingy
    } else if(type_compare(T, thingy)) {
        static MemberDefinition members_of_thingy[] = {
            // Members.
            {meta_type_int, "x", (size_t)&((_thingy *)0)->x, false, 1},
            {meta_type_int, "y", (size_t)&((_thingy *)0)->y, false, 1},
        };
        return(members_of_thingy);

    // V2
    } else if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            // Members.
            {meta_type_int, "x", (size_t)&((_V2 *)0)->x, false, 1},
            {meta_type_int, "y", (size_t)&((_V2 *)0)->y, false, 1},
        };
        return(members_of_V2);

    // Bar
    } else if(type_compare(T, Bar)) {
        static MemberDefinition members_of_Bar[] = {
            // Members.
            {meta_type_short, "s", (size_t)&((_Bar *)0)->s, false, 1},
            {meta_type_int, "i", (size_t)&((_Bar *)0)->i, false, 1},
            {meta_type_float, "f", (size_t)&((_Bar *)0)->f, false, 1},
            {meta_type_double, "d", (size_t)&((_Bar *)0)->d, false, 1},
            {meta_type_V2, "v2", (size_t)&((_Bar *)0)->v2, false, 1},
        };
        return(members_of_Bar);

    // A
    } else if(type_compare(T, A)) {
        static MemberDefinition members_of_A[] = {
            // Members.
            {meta_type_float, "m", (size_t)&((_A *)0)->m, false, 1},
        };
        return(members_of_A);

    // B
    } else if(type_compare(T, B)) {
        static MemberDefinition members_of_B[] = {
            // Members.
            {meta_type_float, "n", (size_t)&((_B *)0)->n, false, 1},
        };
        return(members_of_B);

    // C
    } else if(type_compare(T, C)) {
        static MemberDefinition members_of_C[] = {
            // Members.
            {meta_type_float, "o", (size_t)&((_C *)0)->o, false, 1},
        };
        return(members_of_C);

    // Foo
    } else if(type_compare(T, Foo)) {
        static MemberDefinition members_of_Foo[] = {
            // Members.
            {meta_type_char, "str", (size_t)&((_Foo *)0)->str, true, 1},
            {meta_type_int, "ip", (size_t)&((_Foo *)0)->ip, true, 1},
            {meta_type_float, "fp", (size_t)&((_Foo *)0)->fp, true, 1},
            {meta_type_bool, "b", (size_t)&((_Foo *)0)->b, true, 1},
            {meta_type_double, "p_array", (size_t)&((_Foo *)0)->p_array, true, 5},
            // Members inherited from Bar.
            {meta_type_short, "s", (size_t)&((_Foo *)0)->s, false, 1},
            {meta_type_int, "i", (size_t)&((_Foo *)0)->i, false, 1},
            {meta_type_float, "f", (size_t)&((_Foo *)0)->f, false, 1},
            {meta_type_double, "d", (size_t)&((_Foo *)0)->d, false, 1},
            {meta_type_V2, "v2", (size_t)&((_Foo *)0)->v2, false, 1},
            // Members inherited from thingy.
            {meta_type_int, "x", (size_t)&((_Foo *)0)->x, false, 1},
            {meta_type_int, "y", (size_t)&((_Foo *)0)->y, false, 1},
            // Members inherited from A.
            {meta_type_float, "m", (size_t)&((_Foo *)0)->m, false, 1},
            // Members inherited from B.
            {meta_type_float, "n", (size_t)&((_Foo *)0)->n, false, 1},
            // Members inherited from C.
            {meta_type_float, "o", (size_t)&((_Foo *)0)->o, false, 1},
        };
        return(members_of_Foo);

    // Transform
    } else if(type_compare(T, Transform)) {
        static MemberDefinition members_of_Transform[] = {
            // Members.
            {meta_type_V2, "pos", (size_t)&((_Transform *)0)->pos, false, 1},
            {meta_type_V2, "size", (size_t)&((_Transform *)0)->size, false, 1},
        };
        return(members_of_Transform);

    } else { assert(0); return(0); } // Error.
}

// Convert a type into a members_of *.
template<typename T> static int get_number_of_members_(void)
{
    if(type_compare(T, Pigeon)) { return(2); } // Pigeon
    else if(type_compare(T, thingy)) { return(2); } // thingy
    else if(type_compare(T, V2)) { return(2); } // V2
    else if(type_compare(T, Bar)) { return(5); } // Bar
    else if(type_compare(T, A)) { return(1); } // A
    else if(type_compare(T, B)) { return(1); } // B
    else if(type_compare(T, C)) { return(1); } // C
    else if(type_compare(T, Foo)) { return(15); } // Foo
    else if(type_compare(T, Transform)) { return(2); } // Transform

    else { assert(0); return(-1); } // Error.
}
// Function to serialize a struct to a char array buffer.
template <typename T>static size_t
serialize_struct_(T var, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written)
{
    assert((name) && (buffer) && (buf_size > 0)); // Check params.

    if(!indent) { memset(buffer + bytes_written, 0, buf_size - bytes_written); } // If this is the first time through, zero the buffer.

    MemberDefinition *members_of_Something = get_members_of_<T>(); assert(members_of_Something); // Get the members_of pointer. 
    if(members_of_Something) {
        // Setup the indent buffer.
        char indent_buf[256] = {};
        for(int indent_buf_index = 0; (indent_buf_index < indent); ++indent_buf_index) { indent_buf[indent_buf_index] = ' '; }

        // Write the name and the type.
        bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, type_to_string(T), name);
        indent += 4;

        // Add 4 to the indent.
        for(int indent_index = 0; (indent_index < indent); ++indent_index) { indent_buf[indent_index] = ' '; }

        int num_members = get_number_of_members_<T>(); assert(num_members != -1); // Get the number of members for the for loop.
        for(int member_index = 0; (member_index < num_members); ++member_index) {
            MemberDefinition *member = members_of_Something + member_index; // Get the member pointer with meta data.
            size_t *member_ptr = (size_t *)((char *)&var + member->offset); // Get the actual pointer to the memory address.
            // TODO(Jonny): Go through and check all the pointers are correct on these.
            switch(member->type) {
                // double.
                case meta_type_double: {
                    if(member->arr_size > 1) {
                        for(int member_index = 0; (member_index < member->arr_size); ++member_index) {
                            bool is_null = (member->is_ptr) ? !(*(double **)(member_ptr + member_index)) : 0;
                            if(!is_null) {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index, (member->is_ptr) ? *(double *)member_ptr[member_index] : member_ptr[member_index]);
                            } else {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index);
                            }
                        }
                    } else {
                        double *double_value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;
                        if(double_value) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, *double_value);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case meta_type_double

                // float.
                case meta_type_float: {
                    if(member->arr_size > 1) {
                        for(int member_index = 0; (member_index < member->arr_size); ++member_index) {
                            bool is_null = (member->is_ptr) ? !(*(float **)(member_ptr + member_index)) : 0;
                            if(!is_null) {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index, (member->is_ptr) ? *(float *)member_ptr[member_index] : member_ptr[member_index]);
                            } else {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index);
                            }
                        }
                    } else {
                        float *float_value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;
                        if(float_value) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, *float_value);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case meta_type_float

                // int.
                case meta_type_int: {
                    if(member->arr_size > 1) {
                        for(member_index = 0; (member_index < member->arr_size); ++member_index) {
                            bool is_null = (member->is_ptr) ? !(*(int **)(member_ptr + member_index)) : 0;
                            if(!is_null) {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index, (member->is_ptr) ? *(int *)member_ptr[member_index] : (int)member_ptr[member_index]);
                            } else {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index);
                            }
                        }
                    } else {
                        int *int_value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;
                        if(int_value) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, *int_value);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case meta_type_int

                // long.
                case meta_type_long: {
                    if(member->arr_size > 1) {
                        for(int member_index = 0; (member_index < member->arr_size); ++member_index) {
                            bool is_null = (member->is_ptr) ? !(*(long **)(member_ptr + member_index)) : 0;
                            if(!is_null) {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %ld", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index, (member->is_ptr) ? *(long *)member_ptr[member_index] : (long)member_ptr[member_index]);
                            } else {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index);
                            }
                        }
                    } else {
                        long *long_value = (member->is_ptr) ? *(long **)member_ptr : (long *)member_ptr;
                        if(long_value) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s = %ld", indent_buf, (member->is_ptr) ? "*" : "", member->name, *long_value);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case meta_type_long

                // short.
                case meta_type_short: {
                    if(member->arr_size > 1) {
                        for(int member_index = 0; (member_index < member->arr_size); ++member_index) {
                            bool is_null = (member->is_ptr) ? !(*(short **)(member_ptr + member_index)) : 0;
                            if(!is_null) {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index, (member->is_ptr) ? *(short *)member_ptr[member_index] : (short)member_ptr[member_index]);
                            } else {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index);
                            }
                        }
                    } else {
                        short *short_value = (member->is_ptr) ? *(short **)member_ptr : (short *)member_ptr;
                        if(short_value) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, *short_value);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case meta_type_short

                // bool.
                case meta_type_bool: {
                    bool *bool_value = 0;
                    if(member->arr_size > 1) {
                        for(int member_index = 0; (member_index < member->arr_size); ++member_index) {
                            bool is_null = (member->is_ptr) ? !(*(bool **)(member_ptr + member_index)) : 0;
                            if(is_null) {
                                size_t value_to_print = (member->is_ptr) ? **(bool **)(member_ptr + member_index) : member_ptr[member_index];
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s[%d] = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index, (value_to_print) ? "true" : "false");
                            } else {
                                bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, member_index);
                            }
                        }
                    } else {
                        bool_value = (member->is_ptr) ? *(bool **)member_ptr : (bool *)member_ptr;
                        if(bool_value) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, (bool_value) ? "true" : "false");
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool *%s = (null)", indent_buf, member->name);
                        }
                    }
                } break; // case meta_type_bool

                // char.
                case meta_type_char: {
                    if(member_ptr) {
                        if(member->is_ptr) {
                            bytes_written += my_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, (char *)(*(size_t *)member_ptr));
                        } else {
                            bytes_written += my_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)((size_t *)member_ptr));
                        }
                    } else {
                        bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                    }
                } break; // case meta_type_char

                // If the type wasn't a primtive, do a switchon the type again, but search for structs.
                // Then that should recursively call this function again.
                default: {
                    switch(member->type) {
                        case meta_type_Pigeon: {
                            // Pigeon
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<Pigeon *>(*(Pigeon **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<Pigeon>(*(Pigeon *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_Pigeon

                        case meta_type_thingy: {
                            // thingy
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<thingy *>(*(thingy **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<thingy>(*(thingy *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_thingy

                        case meta_type_V2: {
                            // V2
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<V2 *>(*(V2 **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<V2>(*(V2 *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_V2

                        case meta_type_Bar: {
                            // Bar
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<Bar *>(*(Bar **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<Bar>(*(Bar *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_Bar

                        case meta_type_A: {
                            // A
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<A *>(*(A **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<A>(*(A *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_A

                        case meta_type_B: {
                            // B
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<B *>(*(B **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<B>(*(B *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_B

                        case meta_type_C: {
                            // C
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<C *>(*(C **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<C>(*(C *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_C

                        case meta_type_Foo: {
                            // Foo
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<Foo *>(*(Foo **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<Foo>(*(Foo *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_Foo

                        case meta_type_Transform: {
                            // Transform
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<Transform *>(*(Transform **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<Transform>(*(Transform *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_Transform

                    } // switch(member->type)
                } break; // default 
            }
        }
    }

    return(bytes_written);
}

// Convert a type to a string.
template<typename T> static char const *type_to_string_(void)
{
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
    else if(type_compare(T, Pigeon)) { return("Pigeon"); }
    else if(type_compare(T, Pigeon *)) { return("Pigeon *"); }
    else if(type_compare(T, Pigeon **)) { return("Pigeon **"); }
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
    else if(type_compare(T, Transform)) { return("Transform"); }
    else if(type_compare(T, Transform *)) { return("Transform *"); }
    else if(type_compare(T, Transform **)) { return("Transform **"); }

    else { return(0); } // Unknown Type.
}

//
// Enum meta data.
//

// Meta Data for Letters.
static size_t number_of_elements_in_enum_Letters = 3;
static char const *enum_to_string_Letters(int v)
{
    switch(v) {
        case 0: { return("letter_a"); } break;
        case 1: { return("letter_b"); } break;
        case 2: { return("letter_c"); } break;

        default: { return(0); } break; // v is out of bounds.
    }
}
static int string_to_enum_Letters(char const *str)
{
    int res = 0;
    if(str) {
        if(strcmp(str, "letter_a") == 0) { return(0); }
        else if(strcmp(str, "letter_b") == 0) { return(1); }
        else if(strcmp(str, "letter_c") == 0) { return(2); }
        else { assert(0); } // str didn't match. TODO(Jonny): Throw an error here?
    }

    return(res);
}

} // namespace pp

#define GENERATED_H
#endif // !defined(GENERATED_H)

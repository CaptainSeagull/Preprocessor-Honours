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
    meta_type_V2,
};

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void)
{
    // Recreated structs.
    struct _V2 {  _int x;  _int y;  };
 
    // V2
    if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            // Members.
            {meta_type_int, "x", offsetof(_V2, x), false, 1},
            {meta_type_int, "y", offsetof(_V2, y), false, 1},
        };
        return(members_of_V2);

    } else { assert(0); return(0); } // Error.
}

// Convert a type into a members_of *.
template<typename T> static int get_number_of_members_(void)
{
    if(type_compare(T, V2)) { return(2); } // V2

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
                        case meta_type_V2: {
                            // V2
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<V2 *>(*(V2 **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<V2>(*(V2 *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_V2

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
    else if(type_compare(T, V2)) { return("V2"); }
    else if(type_compare(T, V2 *)) { return("V2 *"); }
    else if(type_compare(T, V2 **)) { return("V2 **"); }

    else { return(0); } // Unknown Type.
}

} // namespace pp

#define GENERATED_H
#endif // !defined(GENERATED_H)

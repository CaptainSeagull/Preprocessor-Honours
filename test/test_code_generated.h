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
    meta_type_BaseTypeOne,
    meta_type_BaseTypeTwo,
    meta_type_BaseTypeThree,
    meta_type_Sub,
};

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // Recreated structs.
    struct _BaseTypeOne {  };
    struct _BaseTypeTwo {  };
    struct _BaseTypeThree {  };
    struct _Sub : public _BaseTypeOne, public _BaseTypeTwo, public _BaseTypeThree {  };
 
    // BaseTypeOne
    if(type_compare(T, BaseTypeOne)) {
        static MemberDefinition members_of_BaseTypeOne[] = {
            // Members.
        };
        return(members_of_BaseTypeOne);

    // BaseTypeTwo
    } else if(type_compare(T, BaseTypeTwo)) {
        static MemberDefinition members_of_BaseTypeTwo[] = {
            // Members.
        };
        return(members_of_BaseTypeTwo);

    // BaseTypeThree
    } else if(type_compare(T, BaseTypeThree)) {
        static MemberDefinition members_of_BaseTypeThree[] = {
            // Members.
        };
        return(members_of_BaseTypeThree);

    // Sub
    } else if(type_compare(T, Sub)) {
        static MemberDefinition members_of_Sub[] = {
            // Members.
            // Members inherited from BaseTypeOne.
            // Members inherited from BaseTypeTwo.
            // Members inherited from BaseTypeThree.
        };
        return(members_of_Sub);

    } else { assert(0); return(0); } // Error.
}

// Get the number of members for a type.
template<typename T> static int get_number_of_members_(void) {
    if(type_compare(T, BaseTypeOne)) { return(0); } // BaseTypeOne
    else if(type_compare(T, BaseTypeTwo)) { return(0); } // BaseTypeTwo
    else if(type_compare(T, BaseTypeThree)) { return(0); } // BaseTypeThree
    else if(type_compare(T, Sub)) { return(0); } // Sub

    else { assert(0); return(-1); } // Error.
}
// Function to serialize a struct to a char array buffer.
template <typename T>static size_t
serialize_struct_(T var, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    assert((name) && (buffer) && (buf_size > 0)); // Check params.

    if(!indent) { memset(buffer + bytes_written, 0, buf_size - bytes_written); } // If this is the first time through, zero the buffer.

    MemberDefinition *members_of_Something = get_members_of_<T>(); assert(members_of_Something); // Get the members_of pointer. 
    if(members_of_Something) {
        // Setup the indent buffer.
        char indent_buf[256] = {};
        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }

        // Write the name and the type.
        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, type_to_string(T), name);
        indent += 4;

        // Add 4 to the indent.
        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }

        int num_members = get_number_of_members_<T>(); assert(num_members != -1); // Get the number of members for the for loop.
        for(int i = 0; (i < num_members); ++i) {
            MemberDefinition *member = members_of_Something + i; // Get the member pointer with meta data.
            size_t *member_ptr = (size_t *)((char *)&var + member->offset); // Get the actual pointer to the memory address.
            // TODO(Jonny): Go through and check all the pointers are correct on these.
            switch(member->type) {
                // double.
                case meta_type_double: {
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
                } break; // case meta_type_double

                // float.
                case meta_type_float: {
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
                } break; // case meta_type_float

                // int.
                case meta_type_int: {
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
                } break; // case meta_type_int

                // long.
                case meta_type_long: {
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
                } break; // case meta_type_long

                // short.
                case meta_type_short: {
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
                } break; // case meta_type_short

                // bool.
                case meta_type_bool: {
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
                } break; // case meta_type_bool

                // char.
                case meta_type_char: {
                    if(member_ptr) {
                        if(member->is_ptr) {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, (char *)(*(size_t *)member_ptr));
                        } else {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)((size_t *)member_ptr));
                        }
                    } else {
                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                    }
                } break; // case meta_type_char

                // If the type wasn't a primtive, do a switchon the type again, but search for structs.
                // Then that should recursively call this function again.
                default: {
                    switch(member->type) {
                        case meta_type_BaseTypeOne: {
                            // BaseTypeOne
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<BaseTypeOne *>(*(BaseTypeOne **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<BaseTypeOne>(*(BaseTypeOne *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_BaseTypeOne

                        case meta_type_BaseTypeTwo: {
                            // BaseTypeTwo
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<BaseTypeTwo *>(*(BaseTypeTwo **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<BaseTypeTwo>(*(BaseTypeTwo *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_BaseTypeTwo

                        case meta_type_BaseTypeThree: {
                            // BaseTypeThree
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<BaseTypeThree *>(*(BaseTypeThree **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<BaseTypeThree>(*(BaseTypeThree *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_BaseTypeThree

                        case meta_type_Sub: {
                            // Sub
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_<Sub *>(*(Sub **)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_<Sub>(*(Sub *)member_ptr, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case meta_type_Sub

                    } // switch(member->type)
                } break; // default 
            }
        }
    }

    return(bytes_written);
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
    else if(type_compare(T, BaseTypeOne)) { return("BaseTypeOne"); }
    else if(type_compare(T, BaseTypeOne *)) { return("BaseTypeOne *"); }
    else if(type_compare(T, BaseTypeOne **)) { return("BaseTypeOne **"); }
    else if(type_compare(T, BaseTypeTwo)) { return("BaseTypeTwo"); }
    else if(type_compare(T, BaseTypeTwo *)) { return("BaseTypeTwo *"); }
    else if(type_compare(T, BaseTypeTwo **)) { return("BaseTypeTwo **"); }
    else if(type_compare(T, BaseTypeThree)) { return("BaseTypeThree"); }
    else if(type_compare(T, BaseTypeThree *)) { return("BaseTypeThree *"); }
    else if(type_compare(T, BaseTypeThree **)) { return("BaseTypeThree **"); }
    else if(type_compare(T, Sub)) { return("Sub"); }
    else if(type_compare(T, Sub *)) { return("Sub *"); }
    else if(type_compare(T, Sub **)) { return("Sub **"); }

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
    else if(type_compare(T, BaseTypeOne)) { return("BaseTypeOne"); }
    else if(type_compare(T, BaseTypeOne *)) { return("BaseTypeOne"); }
    else if(type_compare(T, BaseTypeOne **)) { return("BaseTypeOne"); }
    else if(type_compare(T, BaseTypeTwo)) { return("BaseTypeTwo"); }
    else if(type_compare(T, BaseTypeTwo *)) { return("BaseTypeTwo"); }
    else if(type_compare(T, BaseTypeTwo **)) { return("BaseTypeTwo"); }
    else if(type_compare(T, BaseTypeThree)) { return("BaseTypeThree"); }
    else if(type_compare(T, BaseTypeThree *)) { return("BaseTypeThree"); }
    else if(type_compare(T, BaseTypeThree **)) { return("BaseTypeThree"); }
    else if(type_compare(T, Sub)) { return("Sub"); }
    else if(type_compare(T, Sub *)) { return("Sub"); }
    else if(type_compare(T, Sub **)) { return("Sub"); }

    else { return(0); } // Unknown Type.
}

// Get the number of base types.
template<typename T> static int get_base_type_count_(void) {
    if(type_compare(T, Sub))    { return(3); }

    return(0); // Not found.
}

// Get the base type.
template<typename T> static char const *get_base_type_as_string_(int index = 0) {
    if(type_compare(T, Sub)) {
        if(index == 0)      { return("BaseTypeOne"); }
        else if(index == 1) { return("BaseTypeTwo"); }
        else if(index == 2) { return("BaseTypeThree"); }
    }

    return(0); // Not found.
}

} // namespace pp

#define GENERATED_H
#endif // !defined(GENERATED_H)


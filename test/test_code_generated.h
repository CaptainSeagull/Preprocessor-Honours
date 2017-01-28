#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

// Forward declared structs (these must be declared outside the namespace...)
struct SomeStruct;

#include "static_generated.h"

namespace pp { // PreProcessor
#define _std std
// Enum with field for every type detected.
enum MetaType {
    MetaType_char,
    MetaType_short,
    MetaType_int,
    MetaType_long,
    MetaType_float,
    MetaType_double,
    MetaType_bool,
    MetaType_SomeStruct,
    MetaType_std_vector_int,
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
                                double v = (member->is_ptr) ? *(double *)member_ptr[j] : *(double *)member_ptr + j;
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, v);
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
                                float v = (member->is_ptr) ? *(float *)member_ptr[j] : *(float *)member_ptr + j;
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, v);
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
                                int v = (member->is_ptr) ? *(int *)member_ptr[j] : *(int *)member_ptr + j;
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, v);
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
                                long v = (member->is_ptr) ? *(long *)member_ptr[j] : *(long *)member_ptr + j;
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %ld", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, v);
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
                                short v = (short)((member->is_ptr) ? (*(short *)member_ptr[j]) : (*(short *)member_ptr + j));
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, v);
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
                                size_t v = (member->is_ptr) ? **(bool **)(member_ptr + j) : *(bool *)member_ptr + j;
                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s[%d] = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (v) ? "true" : "false");
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
                        case MetaType_SomeStruct: {
                            // SomeStruct
                            if(member->is_ptr) {
                                bytes_written = serialize_struct_(member_ptr, member->name, "SomeStruct *", indent, buffer, buf_size - bytes_written, bytes_written);
                            } else {
                                bytes_written = serialize_struct_(member_ptr, member->name, "SomeStruct", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break; // case MetaType_SomeStruct

                        case MetaType_std_vector_int: {
                            std::vector<int> temp = *(std::vector<int> *)member_ptr;
                            size_t size = temp.size();
                            for(size_t i = 0; (i < size); ++i) {
                                bytes_written = serialize_struct_((void *)&temp[i], member->name, "int", indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        } break;

                    } // switch(member->type)
                } break; // default 
            }
        }
    }

    return(bytes_written);
}
// Recreated structs (Clang in std=C++98 complains if these are local).
struct _SomeStruct {  _std::vector<int> v;  };

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // SomeStruct
    if(type_compare(T, SomeStruct)) {
        static MemberDefinition members_of_SomeStruct[] = {
            {MetaType_std_vector_int, "v", offset_of(&_SomeStruct::v), false, 1},
        };
        return(members_of_SomeStruct);
    }

    return(0); // Error.
}

// Get the number of members for a type.
template<typename T> static int get_number_of_members_(void) {
    if(type_compare(T, SomeStruct)) { return(1); } // SomeStruct

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


    // SomeStruct
    } else if((strcmp(str, "SomeStruct") == 0) || (strcmp(str, "SomeStruct *") == 0) || (strcmp(str, "SomeStruct **") == 0)) {
        static MemberDefinition members_of_SomeStruct[] = {
            {MetaType_std_vector_int, "v", offset_of(&_SomeStruct::v), false, 1},
        };
        return(members_of_SomeStruct);
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
    else if(strcmp(str, "SomeStruct") == 0) { return(1); } // SomeStruct

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
    else if(type_compare(T, SomeStruct)) { return("SomeStruct"); }
    else if(type_compare(T, SomeStruct *)) { return("SomeStruct *"); }
    else if(type_compare(T, SomeStruct **)) { return("SomeStruct **"); }

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
    else if(type_compare(T, SomeStruct)) { return("SomeStruct"); }
    else if(type_compare(T, SomeStruct *)) { return("SomeStruct"); }
    else if(type_compare(T, SomeStruct **)) { return("SomeStruct"); }

    else { return(0); } // Unknown Type.
}

// Get the number of base types.
template<typename T> static int get_base_type_count_(void) {

    return(0); // Not found.
}

// Get the base type.
template<typename T> static char const *get_base_type_as_string_(int index/*= 0*/) {

    return(0); // Not found.
}

#undef _std
} // namespace pp

#endif // Header guard.


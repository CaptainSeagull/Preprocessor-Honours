/*===================================================================================================
  File:                    write_file.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include "write_file.h"
#include "lexer.h"
#include "stb_sprintf.h"

struct OutputBuffer {
    Char *buffer;
    Int index;
    Int size;
};

internal Void write_to_output_buffer(OutputBuffer *ob, Char *format, ...) {
    va_list args;
    va_start(args, format);
    ob->index += stbsp_vsnprintf(ob->buffer + ob->index, ob->size - ob->index, format, args);
    va_end(args);
}

internal Char *primitive_types[] = {"char", "short", "int", "long", "float", "double", "bool"};
#define get_num_of_primitive_types() array_count(primitive_types)

internal Int set_primitive_type(String *array) {
    Int res = array_count(primitive_types);

    for(Int i = 0; (i < res); ++i) {
        String *index = array + i;

        index->e = primitive_types[i];
        index->len = string_length(primitive_types[i]);
    }

    return(res);
}

internal Void write_serialize_struct_implementation(Char *def_struct_code, OutputBuffer *ob) {
    Char *top =
        "// Function to serialize a struct to a char array buffer.\n"
        "static size_t\nserialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {\n"
        "    assert((name) && (buffer) && (buf_size > 0)); // Check params.\n"
        "\n"
        "    if(!indent) { memset(buffer + bytes_written, 0, buf_size - bytes_written); } // If this is the first time through, zero the buffer.\n"
        "\n"
        "    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); assert(members_of_Something); // Get the members_of pointer. \n"
        "    if(members_of_Something) {\n"
        "        // Setup the indent buffer.\n"
        "        char indent_buf[256] = {};\n"
        "        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }\n"
        "\n"
        "        // Write the name and the type.\n"
        "        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%s%%s %%s\", indent_buf, type_as_str, name);\n"
        "        indent += 4;\n"
        "\n"
        "        // Add 4 to the indent.\n"
        "        for(int i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }\n"
        "\n"
        "        int num_members = get_number_of_members_str(type_as_str); assert(num_members != -1); // Get the number of members for the for loop.\n"
        "        for(int i = 0; (i < num_members); ++i) {\n"
        "            MemberDefinition *member = members_of_Something + i; // Get the member pointer with meta data.\n"
        "            size_t *member_ptr = (size_t *)((char *)var + member->offset); // Get the actual pointer to the memory address.\n"
        "            // TODO(Jonny): Go through and check all the pointers are correct on these.\n"
        "            switch(member->type) {\n"
        "                // double.\n"
        "                case MetaType_double: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(double **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                double v = (member->is_ptr) ? *(double *)member_ptr[j] : *((double *)member_ptr + j);\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        double *double_value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;\n"
        "                        if(double_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble %%s%%s = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *double_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sdouble *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_double\n"
        "\n"
        "                // float.\n"
        "                case MetaType_float: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(float **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                float v = (member->is_ptr) ? *(float *)member_ptr[j] : *((float *)member_ptr + j);\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat %%s%%s[%%d] = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        float *float_value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;\n"
        "                        if(float_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat %%s%%s = %%f\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *float_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sfloat *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_float\n"
        "\n"
        "                // int.\n"
        "                case MetaType_int: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(int **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                int v = (member->is_ptr) ? *(int *)member_ptr[j] : *((int *)member_ptr + j);\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        int *int_value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;\n"
        "                        if(int_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *int_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_int\n"
        "\n"
        "                // long.\n"
        "                case MetaType_long: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(long **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                long v = (member->is_ptr) ? *(long *)member_ptr[j] : *((long *)member_ptr + j);\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%ld\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        long *long_value = (member->is_ptr) ? *(long **)member_ptr : (long *)member_ptr;\n"
        "                        if(long_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s = %%ld\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *long_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_long\n"
        "\n"
        "                // short.\n"
        "                case MetaType_short: {\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(short **)(member_ptr + j)) : 0;\n"
        "                            if(!is_null) {\n"
        "                                short v = (short)((member->is_ptr) ? (*(short *)member_ptr[j]) : (*(short *)member_ptr + j));\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, v);\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        short *short_value = (member->is_ptr) ? *(short **)member_ptr : (short *)member_ptr;\n"
        "                        if(short_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint %%s%%s = %%d\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, *short_value);\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sint *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_short\n"
        "\n"
        "                // bool.\n"
        "                case MetaType_bool: {\n"
        "                    bool *bool_value = 0;\n"
        "                    if(member->arr_size > 1) {\n"
        "                        for(int j = 0; (j < member->arr_size); ++j) {\n"
        "                            bool is_null = (member->is_ptr) ? !(*(bool **)(member_ptr + j)) : 0;\n"
        "                            if(is_null) {\n"
        "                                size_t v = (member->is_ptr) ? **(bool **)(member_ptr + j) : *((bool *)member_ptr + j);\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool %%s%%s[%%d] = %%s\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j, (v) ? \"true\" : \"false\");\n"
        "                            } else {\n"
        "                                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool %%s%%s[%%d] = (null)\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, j);\n"
        "                            }\n"
        "                        }\n"
        "                    } else {\n"
        "                        bool_value = (member->is_ptr) ? *(bool **)member_ptr : (bool *)member_ptr;\n"
        "                        if(bool_value) {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool %%s%%s = %%s\", indent_buf, (member->is_ptr) ? \"*\" : \"\", member->name, (bool_value) ? \"true\" : \"false\");\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%sbool *%%s = (null)\", indent_buf, member->name);\n"
        "                        }\n"
        "                    }\n"
        "                } break; // case MetaType_bool\n"
        "\n"
        "                // char.\n"
        "                case MetaType_char: {\n"
        "                    if(member_ptr) {\n"
        "                        if(member->is_ptr) {\n"
        "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar *%%s = \\\"%%s\\\"\", indent_buf, member->name, (char *)(*(size_t *)member_ptr));\n"
        "                        } else {\n"
        "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar %%s = %%c\", indent_buf, member->name, *(char *)((size_t *)member_ptr));\n"
        "                        }\n"
        "                    } else {\n"
        "                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar *%%s = (null)\", indent_buf, member->name);\n"
        "                    }\n"
        "                } break; // case MetaType_char\n"
        "\n"
        "                // If the type wasn't a primtive, do a switchon the type again, but search for structs.\n"
        "                // Then that should recursively call this function again.\n"
        "                default: {\n";
    Char *bottom = "\n"
                   "                } break; // default \n"
                   "            }\n"
                   "        }\n"
                   "    }\n"
                   "\n"
                   "    return(bytes_written);\n"
                   "}\n";

    write_to_output_buffer(ob, top);
    write_to_output_buffer(ob, def_struct_code);
    write_to_output_buffer(ob, bottom);
}

internal Bool is_meta_type_already_in_array(String *array, Int len, String test) {
    Bool res = false;

    for(Int i = 0; (i < len); ++i) {
        if(string_compare(array[i], test)) {
            res = true;
            break; // for
        }
    }

    return(res);
}

internal StructData *find_struct(String str, StructData *structs, Int struct_count) {
    StructData *res = 0;

    if(str.len) {
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = structs + i;

            if(string_compare(str, sd->name)) {
                res = sd;
                break; // for
            }
        }
    }

    if(!res) {
        push_error(ErrorType_could_not_find_struct);
    }

    return(res);
}

enum StdTypes {
    StdTypes_not,
    StdTypes_vector,

    StdTypes_cnt,
};

struct StdResult {
    StdTypes type;
    String stored_type;
};

internal StdResult get_std_information(String str) {
    StdResult res = {};

    Char *std_vector_str = "std::vector";
    if(string_contains(str, std_vector_str)) {
        res.type = StdTypes_vector;

        Int len = string_length(std_vector_str);
        res.stored_type.len=  str.len - len - 2;
        res.stored_type.e = str.e + len + 1;
    }

    return(res);
}

internal void forward_declare_structs(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    // Forward declare structs.
    write_to_output_buffer(ob,
                           "// Forward declared structs (these must be declared outside the namespace...)\n");
    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        if(sd->struct_type == StructType_struct)     {
            write_to_output_buffer(ob, "struct %.*s;\n", sd->name.len, sd->name.e);
        } else if(sd->struct_type == StructType_class) {
            write_to_output_buffer(ob, "class %.*s;\n", sd->name.len, sd->name.e);
        } else if(sd->struct_type == StructType_union) {
            write_to_output_buffer(ob, "union %.*s;\n", sd->name.len, sd->name.e);
        } else {
            assert(0);
        }
    }
}

internal void write_meta_type_enum(OutputBuffer *ob, String *types, Int type_count, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob, "\n// Enum with field for every type detected.\n");
    write_to_output_buffer(ob, "enum MetaType {\n");
    for(Int i = 0; (i < type_count); ++i) {
        String *type = types + i;

        StdResult std_res = get_std_information(*type);
        switch(std_res.type) {
            case StdTypes_not: {
                write_to_output_buffer(ob, "    MetaType_%.*s,\n", type->len, type->e);
            } break;

            case StdTypes_vector: {
                write_to_output_buffer(ob, "    MetaType_std_vector_%.*s,\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            default: {
                assert(0);
            } break;
        }
    }

    write_to_output_buffer(ob, "};");
}

File write_data(Char *fname, StructData *struct_data, Int struct_count, EnumData *enum_data, Int enum_count) {
    File res = {};

    OutputBuffer ob = {};
    ob.size = 256 * 256;
    ob.buffer = alloc(Char, ob.size);
    if(ob.buffer) {
        Char *name_buf = cast(Char *)push_scratch_memory();
        Int len_wo_extension = string_length(fname) - 4; // TODO(Jonny): Do properly.
        for(Int i = 0; (i < len_wo_extension); ++i) {
            name_buf[i] = to_caps(fname[i]);
        }

        write_to_output_buffer(&ob,
                               "#if !defined(%s_GENERATED_H)\n"
                               "#define %s_GENERATED_H\n"
                               "\n",
                               name_buf, name_buf);

        clear_scratch_memory();

        forward_declare_structs(&ob, struct_data, struct_count);

        write_to_output_buffer(&ob,
                               "\n"
                               "#include \"static_generated.h\"\n"
                               "\n"
                               "namespace pp { // PreProcessor\n"
                               "#define _std std");

        //
        // MetaTypes enum.
        //
        // Get the absolute max number of meta types. This will be significantly bigger than the
        // actual number of unique types...

        Int max_type_count = get_num_of_primitive_types();
        for(Int i = 0; (i < struct_count); ++i) {
            max_type_count += struct_data[i].member_count + 1;
        }

        String *types = alloc(String, max_type_count);

        Int type_count = set_primitive_type(types);

        // Fill out the enum meta type enum.
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(!is_meta_type_already_in_array(types, type_count, sd->name)) {
                types[type_count++] = sd->name;
            }

            for(Int j = 0; (j < sd->member_count); ++j) {
                Variable *md = sd->members + j;

                if(!is_meta_type_already_in_array(types, type_count, md->type)) {
                    types[type_count++] = md->type;
                }
            }
        }

        assert(type_count <= max_type_count);

        write_meta_type_enum(&ob, types, type_count, struct_data, struct_count);

        //
        // Struct Meta Data
        //

        // Recursive part for calling on members of structs.
        write_to_output_buffer(&ob, "\n\n");

        Int def_struct_code_size = 10000;
        Char *def_struct_code_mem = alloc(Char, def_struct_code_size);
        if(def_struct_code_mem) {
            Int index = 0;

            Bool any_stds = false;
            for(Int i = 0; (i < type_count); ++i) {
                String *type = types + i;

                StdResult std_res = get_std_information(*type);
                switch(std_res.type) {
                    case StdTypes_vector: {
                        any_stds = true;
                    } break;
                }

                if(any_stds) {
                    break; // for
                }
            }


            if((struct_count) || (any_stds)) {
                Char *switch_start = "                    switch(member->type) {\n";
                string_copy(def_struct_code_mem + index, switch_start);
                index += string_length(switch_start);

                // Add structs.
                for(Int i = 0; (i < struct_count); ++i) {
                    StructData *sd = struct_data + i;

                    // TODO(Jonny): This could support unions better...
                    index +=
                        stbsp_snprintf(def_struct_code_mem + index, def_struct_code_size - index,
                                       "                        case MetaType_%.*s: {\n"
                                       "                            // %.*s\n"
                                       "                            if(member->is_ptr) {\n"
                                       "                                bytes_written = serialize_struct_(member_ptr, member->name, \"%.*s *\", indent, buffer, buf_size - bytes_written, bytes_written);\n"
                                       "                            } else {\n"
                                       "                                bytes_written = serialize_struct_(member_ptr, member->name, \"%.*s\", indent, buffer, buf_size - bytes_written, bytes_written);\n"
                                       "                            }\n"
                                       "                        } break; // case MetaType_%.*s\n"
                                       "\n",
                                       sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e, sd->name.len, sd->name.e);
                }

                // Add std things.
                for(Int i = 0; (i < type_count); ++i) {
                    String *type = types + i;

                    StdResult std_res = get_std_information(*type);

                    switch(std_res.type) {
                        case StdTypes_vector: {
                            index += stbsp_snprintf(def_struct_code_mem + index, def_struct_code_size - index,
                                                    "                        case MetaType_std_vector_%.*s: {\n"
                                                    "                            std::vector<%.*s> temp = *(std::vector<%.*s> *)member_ptr;\n"
                                                    "                            size_t size = temp.size();\n"
                                                    "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%sstd::vector<%.*s> %s\", indent_buf, member->name);\n"
                                                    "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%sSize = %s\", indent_buf, (int)size);\n"
                                                    "                            for(size_t i = 0; (i < size); ++i) {\n"
                                                    "                                bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%s[%s]\", indent_buf, (int)i);\n"
                                                    "                                bytes_written = serialize_struct_((void *)&temp[i], member->name, \"%.*s\", indent, buffer, buf_size - bytes_written, bytes_written);\n"
                                                    "                            }\n"
                                                    "                        } break;\n"
                                                    "\n",
                                                    std_res.stored_type.len, std_res.stored_type.e,
                                                    std_res.stored_type.len, std_res.stored_type.e,
                                                    std_res.stored_type.len, std_res.stored_type.e,
                                                    "%%s",
                                                    std_res.stored_type.len, std_res.stored_type.e,
                                                    "%%s",
                                                    "%%s",
                                                    "%%d",
                                                    "%%s",
                                                    "%%d",
                                                    std_res.stored_type.len, std_res.stored_type.e);
                        } break;
                    }
                }

                Char *switch_end = "                    } // switch(member->type)";
                string_copy(def_struct_code_mem + index, switch_end);
                index += string_length(switch_end);

                assert(index < def_struct_code_size);
            } else {
                index += stbsp_snprintf(def_struct_code_mem + index, def_struct_code_size - index,
                                        "                    // NOTE: No types found.");
            }

            write_serialize_struct_implementation(def_struct_code_mem, &ob);

            free(def_struct_code_mem);
        }

        // Recreated structs.
        write_to_output_buffer(&ob, "// Recreated structs (Clang in std=C++98 complains if these are local).\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            write_to_output_buffer(&ob, "%s _%.*s", (sd->struct_type != StructType_union) ? "struct" : "union",
                                   sd->name.len, sd->name.e);
            if(sd->inherited) {
                write_to_output_buffer(&ob, " :");

                for(Int j = 0; (j < sd->inherited_count); ++j) {
                    String *inherited = sd->inherited + j;

                    if(j) {
                        write_to_output_buffer(&ob, ",");
                    }

                    write_to_output_buffer(&ob, " public _%.*s", inherited->len, inherited->e);
                }
            }
            write_to_output_buffer(&ob, " { ");

            Bool is_inside_anonymous_struct = false;
            for(Int j = 0; (j < sd->member_count); ++j) {
                Variable *md = sd->members + j;


                if(md->is_inside_anonymous_struct != is_inside_anonymous_struct) {
                    is_inside_anonymous_struct = !is_inside_anonymous_struct;

                    if(is_inside_anonymous_struct) {
                        write_to_output_buffer(&ob, " struct {");
                    } else                           {
                        write_to_output_buffer(&ob, "};");
                    }
                }

                Char *arr = "";
                Char arr_buffer[256] = {};
                if(md->array_count > 1) {
                    stbsp_snprintf(arr_buffer, 256, "[%u]", md->array_count);
                    arr = arr_buffer;
                }

                write_to_output_buffer(&ob, " _%.*s %s%.*s%s; ",
                                       md->type.len, md->type.e,
                                       (md->is_ptr) ? "*" : "",
                                       md->name.len, md->name.e,
                                       (md->array_count > 1) ? arr_buffer : arr);

            }

            if(is_inside_anonymous_struct) {
                write_to_output_buffer(&ob, " };");
            }
            write_to_output_buffer(&ob, " };\n");
        }

        // Get Members of.
        write_to_output_buffer(&ob,
                               "\n"
                               "// Convert a type into a members of pointer.\n"
                               "template<typename T> static MemberDefinition *get_members_of_(void) {\n");

        if(struct_count) {
            for(Int i = 0; (i < struct_count); ++i) {
                StructData *sd = struct_data + i;

                if(!i) {
                    write_to_output_buffer(&ob,
                                           "    // %.*s\n"
                                           "    if(type_compare(T, %.*s)) {\n",
                                           sd->name.len, sd->name.e,
                                           sd->name.len, sd->name.e);
                } else {
                    write_to_output_buffer(&ob,
                                           "\n"
                                           "    // %.*s\n"
                                           "    } else if(type_compare(T, %.*s)) {\n",
                                           sd->name.len, sd->name.e,
                                           sd->name.len, sd->name.e);
                }

                write_to_output_buffer(&ob, "        static MemberDefinition members_of_%.*s[] = {\n", sd->name.len, sd->name.e);
                for(Int j = 0; (j < sd->member_count); ++j) {
                    Variable *md = sd->members + j;

                    StdResult std_res = get_std_information(md->type);
                    switch(std_res.type) {
                        case StdTypes_not: {
                            write_to_output_buffer(&ob, "            {MetaType_%.*s", md->type.len, md->type.e);
                        } break;

                        case StdTypes_vector: {
                            write_to_output_buffer(&ob, "            {MetaType_std_vector_%.*s", std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        default: {
                            assert(0);
                        } break;
                    }

                    write_to_output_buffer(&ob, ", \"%.*s\", offset_of(&_%.*s::%.*s), %s, %d},\n",
                                           md->name.len, md->name.e,
                                           sd->name.len, sd->name.e,
                                           md->name.len, md->name.e,
                                           (md->is_ptr) ? "true" : "false",
                                           md->array_count);
                }

                if(sd->inherited) {
                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);

                        write_to_output_buffer(&ob, "            // Members inherited from %.*s.\n",
                                               base_class->name.len, base_class->name.e);
                        for(Int k = 0; (k < base_class->member_count); ++k) {
                            Variable *base_class_var = base_class->members + k;

                            StdResult std_res = get_std_information(base_class_var->type);
                            switch(std_res.type) {
                                case StdTypes_not: {
                                    write_to_output_buffer(&ob,
                                                           "            {MetaType_%.*s",
                                                           base_class_var->type.len, base_class_var->type.e);
                                } break;

                                case StdTypes_vector: {
                                    write_to_output_buffer(&ob,
                                                           "            {MetaType_std_vector_%.*s",
                                                           std_res.stored_type.len, std_res.stored_type.e);
                                } break;

                                default: {
                                    assert(0);
                                } break;
                            }

                            write_to_output_buffer(&ob, ", \"%.*s\", (size_t)&((_%.*s *)0)->%.*s, %s, %d},\n",
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   sd->name.len, sd->name.e,
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   (base_class_var->is_ptr) ? "true" : "false",
                                                   base_class_var->array_count);
                        }
                    }
                }

                write_to_output_buffer(&ob,
                                       "        };\n"
                                       "        return(members_of_%.*s);\n",
                                       sd->name.len, sd->name.e);
            }

            write_to_output_buffer(&ob, "    }\n");
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Error.\n"
                               "}\n");

        // Get number of members.
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the number of members for a type.\n"
                               "template<typename T> static int get_number_of_members_(void) {\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            Int member_count = sd->member_count;

            // Add inherited struct members onto the member count.
            for(Int j = 0; (j < sd->inherited_count); ++j) {
                StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);


                member_count += base_class->member_count;
            }

            if(i == 0) {
                write_to_output_buffer(&ob,
                                       "    if(type_compare(T, %.*s)) { return(%d); } // %.*s\n",
                                       sd->name.len, sd->name.e, member_count, sd->name.len, sd->name.e);
            } else {
                write_to_output_buffer(&ob,
                                       "    else if(type_compare(T, %.*s)) { return(%d); } // %.*s\n",
                                       sd->name.len, sd->name.e, member_count, sd->name.len, sd->name.e);
            }
        }

        write_to_output_buffer(&ob,
                               "\n    return(-1); // Error.\n"
                               "}\n");

        clear_scratch_memory();


        //
        // Get Members of str.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Convert a type into a members of pointer.\n"
                               "static MemberDefinition *get_members_of_str(char const *str) {\n");

        String prim[array_count(primitive_types)] = {};
        set_primitive_type(prim);

        for(Int i = 0, cnt = array_count(prim); (i < cnt); ++i) {
            String *s = prim + i;

            if(!i) {
                write_to_output_buffer(&ob,
                                       "    // %.*s\n"
                                       "    if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e);
            } else {
                write_to_output_buffer(&ob,
                                       "    // %.*s\n"
                                       "    } else if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e,
                                       s->len, s->e);
            }

            Int len = 0;
            Char *output_string = 0;

            StdResult std_res = get_std_information(*s);
            switch(std_res.type) {
                case StdTypes_not: {
                    output_string = s->e;
                    len = s->len;
                } break;

                case StdTypes_vector: {
                    output_string = std_res.stored_type.e;
                    len = std_res.stored_type.len;
                } break;

                default: {
                    assert(0);
                } break;
            }

            write_to_output_buffer(&ob,
                                   "        static MemberDefinition members_of_%.*s[] = {\n"
                                   "            {MetaType_%.*s, \"\", 0, false, 1}\n"
                                   "        };\n"
                                   "        return(members_of_%.*s);\n"
                                   "\n",
                                   len, output_string,
                                   len, output_string,
                                   len, output_string,
                                   len, output_string);

        }
        //if((strcmp(str, "SomeStruct") == 0) || (strcmp(str, "SomeStruct *") == 0) || (strcmp(str, "SomeStruct **") == 0)) {


        if(struct_count) {
            for(Int i = 0; (i < struct_count); ++i) {
                StructData *sd = struct_data + i;

                write_to_output_buffer(&ob,
                                       "\n"
                                       "    // %.*s\n"
                                       "    } else if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e);

                write_to_output_buffer(&ob, "        static MemberDefinition members_of_%.*s[] = {\n", sd->name.len, sd->name.e);
                for(Int j = 0; (j < sd->member_count); ++j) {
                    Variable *md = sd->members + j;

                    StdResult std_res = get_std_information(md->type);
                    switch(std_res.type) {
                        case StdTypes_not: {
                            write_to_output_buffer(&ob, "            {MetaType_%.*s",
                                                   md->type.len, md->type.e);
                        } break;

                        case StdTypes_vector: {
                            write_to_output_buffer(&ob, "            {MetaType_std_vector_%.*s",
                                                   std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        default: {
                            assert(0);
                        } break;
                    }

                    write_to_output_buffer(&ob, ", \"%.*s\", offset_of(&_%.*s::%.*s), %s, %d},\n",
                                           md->name.len, md->name.e,
                                           sd->name.len, sd->name.e,
                                           md->name.len, md->name.e,
                                           (md->is_ptr) ? "true" : "false",
                                           md->array_count);
                }

                if(sd->inherited) {
                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);

                        write_to_output_buffer(&ob, "            // Members inherited from %.*s.\n",
                                               base_class->name.len, base_class->name.e);
                        for(Int k = 0; (k < base_class->member_count); ++k) {
                            Variable *base_class_var = base_class->members + k;

                            StdResult std_res = get_std_information(base_class_var->type);
                            switch(std_res.type) {
                                case StdTypes_not: {
                                    write_to_output_buffer(&ob, "            {MetaType_%.*s",
                                                           base_class_var->type.len, base_class_var->type.e);
                                } break;

                                case StdTypes_vector: {
                                    write_to_output_buffer(&ob, "            {MetaType_std_vector_%.*s",
                                                           std_res.stored_type.len, std_res.stored_type.e);
                                } break;
                            }


                            write_to_output_buffer(&ob, ", \"%.*s\", (size_t)&((_%.*s *)0)->%.*s, %s, %d},\n",
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   sd->name.len, sd->name.e,
                                                   base_class_var->name.len, base_class_var->name.e,
                                                   (base_class_var->is_ptr) ? "true" : "false",
                                                   base_class_var->array_count);
                        }
                    }
                }

                write_to_output_buffer(&ob,
                                       "        };\n"
                                       "        return(members_of_%.*s);\n",
                                       sd->name.len, sd->name.e);
            }

        }
        write_to_output_buffer(&ob, "    }\n");

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Error.\n"
                               "}\n");

        //
        // Get number of members from string.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the number of members for a type.\n"
                               "static int get_number_of_members_str(char const *str) {\n");

        for(Int i = 0, cnt = array_count(prim); (i < cnt); ++i) {
            String *p = prim + i;

            if(!i) {
                write_to_output_buffer(&ob,
                                       "    if(strcmp(str, \"%.*s\") == 0) { return(1); }\n",
                                       p->len, p->e);
            } else {
                write_to_output_buffer(&ob,
                                       "    else if(strcmp(str, \"%.*s\") == 0) { return(1); }\n",
                                       p->len, p->e);
            }
        }


        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            Int member_count = sd->member_count;

            // Add inherited struct members onto the member count.
            for(Int j = 0; (j < sd->inherited_count); ++j) {
                StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);

                member_count += base_class->member_count;
            }

            write_to_output_buffer(&ob,
                                   "    else if(strcmp(str, \"%.*s\") == 0) { return(%d); } // %.*s\n",
                                   sd->name.len, sd->name.e, member_count, sd->name.len, sd->name.e);
        }

        write_to_output_buffer(&ob,
                               "\n    return(-1); // Error.\n"
                               "}\n");

        // type_to_string.
        write_to_output_buffer(&ob,
                               "\n// Convert a type to a string.\n"
                               "template<typename T> static char const *type_to_string_(void) {\n"
                               "    // Primitives.\n");
        for(Int i = 0; (i < get_num_of_primitive_types()); ++i) {
            Char *primitive = primitive_types[i];

            if(!i) {
                write_to_output_buffer(&ob, "    if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s *\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s **\"); }\n", primitive, primitive);
            } else {
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s *\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s **\"); }\n", primitive, primitive);
            }
        }

        write_to_output_buffer(&ob, "\n    // Struct types.\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s *)) { return(\"%.*s *\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s **)) { return(\"%.*s **\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);
        }
        write_to_output_buffer(&ob, "\n    else { return(0); } // Unknown Type.\n}\n");

        // type_to_string ignore.
        write_to_output_buffer(&ob,
                               "\n// Convert a type to a string.\n"
                               "template<typename T> static char const *weak_type_to_string_(void) {\n"
                               "    // Primitives.\n");
        for(Int i = 0; (i < get_num_of_primitive_types()); ++i) {
            Char *primitive = primitive_types[i];

            if(!i) {
                write_to_output_buffer(&ob, "    if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s\"); }\n", primitive, primitive);
            } else {
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s *)) { return(\"%s\"); }\n", primitive, primitive);
                write_to_output_buffer(&ob, "    else if(type_compare(T, %s **)) { return(\"%s\"); }\n", primitive, primitive);
            }
        }

        write_to_output_buffer(&ob, "\n    // Struct types.\n");
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s *)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);

            write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s **)) { return(\"%.*s\"); }\n",
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e);
        }
        write_to_output_buffer(&ob, "\n    else { return(0); } // Unknown Type.\n}\n");

        //
        // Get base type count.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the number of base types.\n"
                               "template<typename T> static int get_base_type_count_(void) {\n");

        for(Int i = 0, written_count = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(sd->inherited_count) {
                if(!written_count) {
                    write_to_output_buffer(&ob, "    if(type_compare(T, %.*s))    { return(%d); }\n",
                                           sd->name.len, sd->name.e, sd->inherited_count);
                } else {
                    write_to_output_buffer(&ob, "    else if(type_compare(T, %.*s)) { return(%d); }\n",
                                           sd->name.len, sd->name.e, sd->inherited_count);
                }

                ++written_count;
            }
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Not found.\n"
                               "}\n");

        //
        // Get base type as string.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "// Get the base type.\n"
                               "template<typename T> static char const *get_base_type_as_string_(int index/*= 0*/) {\n");

        if(struct_count) {
            Bool actually_written_anything = false;
            for(Int i = 0, written_count = 0; (i < struct_count); ++i) {
                StructData *sd = struct_data + i;

                if(sd->inherited_count) {
                    actually_written_anything = true;
                    // TODO(Jonny): Make the index return the inherited index.
                    if(!written_count) {
                        write_to_output_buffer(&ob,
                                               "    if(type_compare(T, %.*s)) {\n",
                                               sd->name.len, sd->name.e);
                    } else {
                        write_to_output_buffer(&ob,
                                               "    } else if(type_compare(T, %.*s)) {\n",
                                               sd->name.len, sd->name.e);
                    }

                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        if(!j) {
                            write_to_output_buffer(&ob,
                                                   "        if(index == %d)      { return(\"%.*s\"); }\n",
                                                   j,
                                                   sd->inherited[j].len, sd->inherited[j].e);
                        } else {
                            write_to_output_buffer(&ob,
                                                   "        else if(index == %d) { return(\"%.*s\"); }\n",
                                                   j,
                                                   sd->inherited[j].len, sd->inherited[j].e);
                        }

                    }

                    ++written_count;
                }
            }

            if(actually_written_anything) {
                write_to_output_buffer(&ob,
                                       "    }\n");
            }
        }

        write_to_output_buffer(&ob,
                               "\n"
                               "    return(0); // Not found.\n"
                               "}\n");
        //
        // Enum Meta data.
        //

        // TODO(Jonny): Can I make the enum meta data templates as well, similar to the structs?
        if(enum_count) {
            write_to_output_buffer(&ob,
                                   "\n"
                                   "//\n"
                                   "// Enum meta data.\n"
                                   "//\n");

            Int half_scratch_memory_size = cast(Int)(cast(Float)scratch_memory_size * 0.5f);
            for(Int i = 0; (i < enum_count); ++i) {
                EnumData *ed = enum_data + i;
                write_to_output_buffer(&ob, "\n// Meta Data for %.*s.\n", ed->name.len, ed->name.e);

                Char type[32];
                if(ed->type.len) {
                    for(int j = 0; (j < ed->type.len); ++j) {
                        type[j] = ed->type.e[j];
                    }
                    type[ed->type.len] = 0;
                } else {
                    type[0] = 'i'; type[1] = 'n'; type[2] = 't'; type[3] = 0;
                }

                // Enum size.
                {
                    Char *buf = cast(Char *)push_scratch_memory();

                    int bytes_written = stbsp_snprintf(buf, scratch_memory_size,
                                                       "static %s number_of_elements_in_enum_%.*s = %d;",
                                                       type,
                                                       ed->name.len, ed->name.e,
                                                       ed->no_of_values);
                    assert(bytes_written < scratch_memory_size);

                    write_to_output_buffer(&ob, buf);

                    clear_scratch_memory();
                }

                // enum_to_string.
                {
                    Char *buf1 = cast(Char *)push_scratch_memory(half_scratch_memory_size);
                    Char *buf2 = cast(Char *)push_scratch_memory(half_scratch_memory_size);

                    Int index = 0;
                    for(int j = 0; (j < ed->no_of_values); ++j) {
                        index += stbsp_snprintf(buf1 + index, half_scratch_memory_size - index,
                                                "        case %d: { return(\"%.*s\"); } break;\n",
                                                ed->values[j].value,
                                                ed->values[j].name.len, ed->values[j].name.e);
                    }

                    Int bytes_written = stbsp_snprintf(buf2, half_scratch_memory_size,
                                                       "\nstatic char const *enum_to_string_%.*s(%s v) {\n"
                                                       "    switch(v) {\n"
                                                       "%s"
                                                       "    }\n"
                                                       "\n"
                                                       "    return(0); // v is out of bounds.\n"
                                                       "}\n",
                                                       ed->name.len, ed->name.e,
                                                       type,
                                                       buf1);
                    assert(bytes_written < half_scratch_memory_size);

                    write_to_output_buffer(&ob, buf2);

                    clear_scratch_memory();
                }

                // string_to_enum.
                {
                    Char *buf1 = cast(Char *)push_scratch_memory(half_scratch_memory_size);
                    Char *buf2 = cast(Char *)push_scratch_memory(half_scratch_memory_size);

                    Int index = 0;
                    index += stbsp_snprintf(buf1 + index, half_scratch_memory_size - index,
                                            "        if(strcmp(str, \"%.*s\") == 0) { return(%d); }\n",
                                            ed->values[0].name.len, ed->values[0].name.e,
                                            ed->values[0].value);
                    for(int j = 1; (j < ed->no_of_values); ++j) {
                        index += stbsp_snprintf(buf1 + index, half_scratch_memory_size - index,
                                                "        else if(strcmp(str, \"%.*s\") == 0) { return(%d); }\n",
                                                ed->values[j].name.len, ed->values[j].name.e,
                                                ed->values[j].value);
                    }
                    assert(index < half_scratch_memory_size);

                    Int bytes_written = stbsp_snprintf(buf2, half_scratch_memory_size,
                                                       "static %s string_to_enum_%.*s(char const *str) {\n"
                                                       "    if(str) {\n"
                                                       "%s"
                                                       "    }\n"
                                                       "\n"
                                                       "    return(0);  // str didn't match.\n" // TODO(Jonny): Throw an error here?
                                                       "}\n",
                                                       type,
                                                       ed->name.len, ed->name.e, buf1);
                    assert(bytes_written < half_scratch_memory_size);


                    write_to_output_buffer(&ob, buf2);

                    clear_scratch_memory();
                }
            }
        }

        //
        // # Guard macro.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "#undef _std\n"
                               "} // namespace pp\n"
                               "\n"
                               "#endif // Header guard.\n"
                               "\n");

        res.size = ob.index;
        res.data = ob.buffer;

        free(types);
    }

    return(res);
}

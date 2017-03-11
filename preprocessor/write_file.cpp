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

enum StdTypes {
    StdTypes_not,
    StdTypes_vector,
    StdTypes_deque,
    StdTypes_forward_list,
    StdTypes_list,

    StdTypes_cnt,
};

struct StdResult {
    StdTypes type;
    String stored_type;
};

internal StdResult get_std_information(String str) {
    StdResult res = {};

    Char *std_vector_str = "std::vector";
    Char *std_deque_str = "std::deque";
    Char *std_forward_list_str = "std::forward_list";
    Char *std_list_str = "std::list";

    if(string_contains(str, std_vector_str)) { // std::vector
        res.type = StdTypes_vector;

        Int len = string_length(std_vector_str);
        res.stored_type.len = str.len - len - 2;
        res.stored_type.e = str.e + len + 1;
    } else if(string_contains(str, std_deque_str)) { // std::array
        res.type = StdTypes_deque;

        Int len = string_length(std_deque_str);
        res.stored_type.len = str.len - len - 2;
        res.stored_type.e = str.e + len + 1;
    } else if(string_contains(str, std_forward_list_str)) { // std::forward_list
        res.type = StdTypes_forward_list;

        Int len = string_length(std_forward_list_str);
        res.stored_type.len = str.len - len - 2;
        res.stored_type.e = str.e + len + 1;
    } else if(string_contains(str, std_list_str)) { // std::list
        res.type = StdTypes_list;

        Int len = string_length(std_list_str);
        res.stored_type.len = str.len - len - 2;
        res.stored_type.e = str.e + len + 1;
    }

    return(res);
}

#define empty_line(ob) write_to_output_buffer(ob, "\n")
internal Void write_to_output_buffer(OutputBuffer *ob, Char *format, ...) {
    va_list args;
    va_start(args, format);
    ob->index += stbsp_vsnprintf(ob->buffer + ob->index, ob->size - ob->index, format, args);
    assert(ob->index < ob->size);
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

    return(res);
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

internal Int get_actual_type_count(String *types, StructData *struct_data, Int struct_count) {
    Int res = set_primitive_type(types);

    // Fill out the enum meta type enum.
    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        if(!is_meta_type_already_in_array(types, res, sd->name)) {
            types[res++] = sd->name;
        }

        for(Int j = 0; (j < sd->member_count); ++j) {
            Variable *md = sd->members + j;

            if(!is_meta_type_already_in_array(types, res, md->type)) {
                types[res++] = md->type;
            }
        }
    }

    return(res);
}

internal Bool is_primitive(String str) {
    Bool res = false;

    String prim_arr[get_num_of_primitive_types()];
    set_primitive_type(prim_arr);

    if(string_compare(str, create_string("void"))) {
        res = true;
    } else {
        res = is_in_string_array(str, prim_arr, get_num_of_primitive_types());
    }

    return(res);
}

enum TypeStructType {
    primitive, struct_class, an_enum
};

// TODO(Jonny): Remove tuple stuff.
internal Void write_type_struct(OutputBuffer *ob, String name, Int member_count, Char *pointer_stuff,
                                TypeStructType type, Bool is_ref, String base = create_string(""), Int inherited_count = 0) {
    Char const *ref = (is_ref) ? "&" : "";

    write_to_output_buffer(ob,
                           "template<> struct TypeInfo<%.*s%s%s> {\n"
                           "    using type      = %.*s%s%s;\n"
                           "    using weak_type = %.*s;\n"
                           "    using base      = %.*s;\n"
                           "\n"
                           "    static constexpr char const * const name      = \"%.*s%s%s\";\n"
                           "    static constexpr char const * const weak_name = \"%.*s\";\n"
                           "\n"
                           "    static constexpr size_t member_count = %d;\n"
                           "    static constexpr size_t base_count   = %d;\n"
                           "\n"
                           "    static constexpr bool is_ptr = %s;\n"
                           "    static constexpr bool is_ref = %s;\n"
                           "\n"
                           "    static constexpr bool is_primitive = %s;\n"
                           "    static constexpr bool is_class     = %s;\n"
                           "    static constexpr bool is_enum      = %s;\n"
                           "};\n"
                           "\n",
                           name.len, name.e, pointer_stuff, ref,
                           name.len, name.e, pointer_stuff, ref,
                           name.len, name.e,
                           (base.len) ? base.len : 4, (base.len) ? base.e : "void",
                           name.len, name.e, pointer_stuff, ref,
                           name.len, name.e,
                           member_count,
                           inherited_count,
                           (string_length(pointer_stuff)) ? "true" : "false",
                           (is_ref) ? "true" : "false",
                           (type == primitive) ? "true" : "false",
                           (type == struct_class) ? "true" : "false", // TODO(Jonny): Should I set this to true for enum classes?
                           (type == an_enum) ? "true" : "false");

    clear_scratch_memory();
}

internal Void write_type_struct_all(OutputBuffer *ob, String name, Int member_count, StructData *structs, Int struct_count) {
    write_to_output_buffer(ob, "\n// struct %.*s\n", name.len, name.e);

    String base = {};
    StructData *struct_data = find_struct(name, structs, struct_count);
    if(struct_data) {
        if(struct_data->inherited_count) {
            base = struct_data->inherited[0];
        }
    }

    if(!base.len) {
        base = create_string("void");
    }

    TypeStructType type = (is_primitive(name)) ? primitive : struct_class;
    Int inherited_count = (struct_data) ? struct_data->inherited_count : 0;

    if(!string_compare(name, create_string("void"))) {
        write_type_struct(ob, name, member_count, "", type, false, base, inherited_count);
    }


    write_type_struct(ob, name, member_count, " *",  type, false, base, inherited_count);
    write_type_struct(ob, name, member_count, " **", type, false, base, inherited_count);

    if(!string_compare(name, create_string("void"))) {
        write_type_struct(ob, name, member_count, "", type, true, base, inherited_count);
    }


    write_type_struct(ob, name, member_count, " *",  type, true, base, inherited_count);
    write_type_struct(ob, name, member_count, " **", type, true, base, inherited_count);

}

// TODO(Jonny): Maybe I could split this out into a serialize primitve and serialize struct code. For serialize primitive, it could be mostly templated,
//              with just a utility thing to get the printf modifier (%s for string, %d for ints). And I think most of the code for serializing structs
//              could be generalized through templates too. Maybe I could even add a third method, serialize container, as well?
internal Void write_serialize_struct_implementation(OutputBuffer *ob, String *types, Int type_count) {
    Char *temp = cast(Char *)push_scratch_memory();
    Int temp_cnt = 0;

    Int written_count = 0;

    for(Int i = 0; (i < type_count); ++i) {
        String *type = types + i;

        StdResult std_res = get_std_information(*type);
        switch(std_res.type) {
            case StdTypes_vector: {
                if(written_count) {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        else ");
                } else {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        ");
                }

                temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "if(member->type == Type_std_vector_%.*s) {bytes_written = serialize_container<std::vector<%.*s>, %.*s>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}\n",
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e);

                ++written_count;
            } break;

            case StdTypes_deque: {
                if(written_count) {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        else ");
                } else {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        ");
                }

                temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "if(member->type == Type_std_deque_%.*s) {bytes_written = serialize_container<std::deque<%.*s>, %.*s>(member_ptr, name, indent, buffer, buf_size, bytes_written);}\n",
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e);

                ++written_count;
            } break;

            case StdTypes_forward_list: {
                if(written_count) {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        else ");
                } else {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        ");
                }

                temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "if(member->type == Type_std_forward_list_%.*s) {bytes_written = serialize_container<std::forward_list<%.*s>, %.*s>(member_ptr, name, indent, buffer, buf_size, bytes_written);}\n",
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e);

                ++written_count;
            } break;

            case StdTypes_list: {
                if(written_count) {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        else ");
                } else {
                    temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "                        ");
                }

                temp_cnt += stbsp_snprintf(temp + temp_cnt, scratch_memory_size - temp_cnt, "if(member->type == Type_std_list_%.*s) {bytes_written = serialize_container<std::list<%.*s>, %.*s>(member_ptr, name, indent, buffer, buf_size, bytes_written);}\n",
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e,
                                           std_res.stored_type.len, std_res.stored_type.e);

                ++written_count;
            } break;
        }
    }

    // TODO(Jonny): Allow "name" to be null in serialize_struct.
    write_to_output_buffer(ob,
                           "// Function to serialize a struct to a char array buffer.\n"
                           "static size_t\nserialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {\n"
                           "    assert((buffer) && (buf_size > 0)); // Check params.\n"
                           "\n"
                           "    if(!bytes_written) {memset(buffer, 0, buf_size);} // If this is the first time through, zero the buffer.\n"
                           "\n"
                           "    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); assert(members_of_Something); // Get the members_of pointer. \n"
                           "    if(members_of_Something) {\n"
                           "        // Setup the indent buffer.\n"
                           "        char indent_buf[256] = {};\n"
                           "        for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}\n"
                           "\n"
                           "        // Write the name and the type.\n"
                           "        if((name) && (strlen(name) > 0)) {\n"
                           "            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%s%%s %%s\", indent_buf, type_as_str, name);\n"
                           "        }\n"
                           "        indent += 4;\n"
                           "\n"
                           "        // Add 4 to the indent.\n"
                           "        for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}\n"
                           "\n"
                           "        int num_members = get_number_of_members_str(type_as_str); assert(num_members != -1); // Get the number of members for the for loop.\n"
                           "        for(int i = 0; (i < num_members); ++i) {\n"
                           "            MemberDefinition *member = members_of_Something + i; // Get the member pointer with meta data.\n"
                           "            size_t *member_ptr = (size_t *)((char *)var + member->offset); // Get the actual pointer to the memory address.\n"
                           "            switch(member->type) {\n"
                           "                // This is a little verbose so I can get the right template overload for serialize_primitive. I should just\n"
                           "                // make it a macro though.\n"
                           "                case Type_double: { // double.\n"
                           "                    bytes_written = serialize_primitive_((double *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);\n"
                           "                } break;\n"
                           "\n"
                           "                case Type_float: { // float.\n"
                           "                    bytes_written = serialize_primitive_((float *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);\n"
                           "                } break;\n"
                           "\n"
                           "                case Type_int: { // int.\n"
                           "                    bytes_written = serialize_primitive_((int *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);\n"
                           "                } break;\n"
                           "\n"
                           "                case Type_long: { // long.\n"
                           "                    bytes_written = serialize_primitive_((long *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);\n"
                           "                } break;\n"
                           "\n"
                           "                case Type_short: { // short.\n"
                           "                    bytes_written = serialize_primitive_((short *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);\n"
                           "                } break;\n"
                           "\n"
                           "                case Type_bool: { // bool.\n"
                           "                    bytes_written = serialize_primitive_((bool *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);\n"
                           "                } break;\n"
                           "\n"
                           "                // char (special case).\n"
                           "                case Type_char: {\n"
                           "                    if(member_ptr) {\n"
                           "                        if(member->is_ptr) {\n"
                           "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar *%%s = \\\"%%s\\\"\", indent_buf, member->name, (char *)(*(size_t *)member_ptr));\n"
                           "                        } else {\n"
                           "                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar %%s = %%c\", indent_buf, member->name, *(char *)((size_t *)member_ptr));\n"
                           "                        }\n"
                           "                    } else {\n"
                           "                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, \"\\n%%schar *%%s = (null)\", indent_buf, member->name);\n"
                           "                    }\n"
                           "                } break; // case Type_char\n"
                           "\n"
                           "                default: {\n"
                           "                    if(is_meta_type_container(member->type)) {\n"
                           "%s\n" // serialize container stuff.
                           "                    } else {\n"
                           "                        char const *struct_name = meta_type_to_name(member->type, member->is_ptr != 0);\n"
                           "                        if(!member->arr_size) {\n"
                           "                            bytes_written = serialize_struct_(member_ptr, member->name, struct_name, indent, buffer, buf_size - bytes_written, bytes_written);\n"
                           "                        } else {\n"
                           "                            for(int j = 0; (j < member->arr_size); ++j) {\n"
                           "                                size_t size_of_struct = get_size_from_str(struct_name);\n"
                           "\n"
                           "                                char unsigned *ptr;\n"
                           "                                if(member->is_ptr) {\n"
                           "                                    ptr = *(char unsigned **)((char unsigned *)member_ptr + (j * sizeof(size_t)));\n"
                           "                                } else {\n"
                           "                                    ptr = ((char unsigned *)member_ptr + (j * size_of_struct));\n"
                           "                                }\n"
                           "\n"
                           "                                bytes_written = serialize_struct_(ptr, member->name, struct_name, indent, buffer, buf_size - bytes_written, bytes_written);\n"
                           "                            }\n"
                           "                        }\n"
                           "                    }\n"
                           "                } break; // default \n"
                           "            }\n"
                           "        }\n"
                           "    }\n"
                           "\n"
                           "    return(bytes_written);\n"
                           "}\n",
                           temp);

    clear_scratch_memory();
}

internal Void forward_declare_structs(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        if(sd->struct_type == StructType_struct)     { write_to_output_buffer(ob, "struct %.*s;\n", sd->name.len, sd->name.e); }
        else if(sd->struct_type == StructType_class) { write_to_output_buffer(ob, "class %.*s;\n", sd->name.len, sd->name.e);  }
        else if(sd->struct_type == StructType_union) { write_to_output_buffer(ob, "union %.*s;\n", sd->name.len, sd->name.e);  }
        else                                         { assert(0);                                                              }
    }
}

internal Void forward_declare_enums(OutputBuffer *ob, EnumData *enum_data, Int enum_count) {
    for(Int i = 0; (i < enum_count); ++i) {
        EnumData *ed = enum_data + i;

        if(ed->type.len) {
            write_to_output_buffer(ob,
                                   "enum %s%.*s : %.*s;\n",
                                   (ed->is_struct) ? "class " : "",
                                   ed->name.len, ed->name.e,
                                   ed->type.len, ed->type.e);

        }
    }
}

internal Void write_meta_type_enum(OutputBuffer *ob, String *types, Int type_count, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob, "\n// Enum with field for every type detected.\n");
    write_to_output_buffer(ob, "namespace pp { enum Type {\n");
    for(Int i = 0; (i < type_count); ++i) {
        String *type = types + i;

        StdResult std_res = get_std_information(*type);
        switch(std_res.type) {
            case StdTypes_not: {
                write_to_output_buffer(ob, "    Type_%.*s,\n", type->len, type->e);
            } break;

            case StdTypes_vector: {
                write_to_output_buffer(ob, "    Type_std_vector_%.*s,\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            case StdTypes_deque: {
                write_to_output_buffer(ob, "    Type_std_deque_%.*s,\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            case StdTypes_forward_list: {
                write_to_output_buffer(ob, "    Type_std_forward_list_%.*s,\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            case StdTypes_list: {
                write_to_output_buffer(ob, "    Type_std_list_%.*s,\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            default: {
                assert(0);
            } break;
        }
    }

    write_to_output_buffer(ob, "}; }\n");
}

internal Void write_meta_type_to_name(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob,
                           "static char const * meta_type_to_name(Type mt, bool is_ptr) {\n");
    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        if(!i) {
            write_to_output_buffer(ob,
                                   "    if(mt == Type_%.*s) {\n"
                                   "        if(is_ptr) {return(\"%.*s *\");}\n"
                                   "        else       {return(\"%.*s\");  }\n"
                                   "    }",
                                   sd->name.len, sd->name.e,
                                   sd->name.len, sd->name.e,
                                   sd->name.len, sd->name.e);
        } else {
            write_to_output_buffer(ob,
                                   " else if(mt == Type_%.*s) {\n"
                                   "        if(is_ptr) {return(\"%.*s *\");}\n"
                                   "        else       {return(\"%.*s\");  }\n"
                                   "    }",
                                   sd->name.len, sd->name.e,
                                   sd->name.len, sd->name.e,
                                   sd->name.len, sd->name.e);
        }
    }

    write_to_output_buffer(ob,
                           "\n"
                           "\n"
                           "    assert(0); \n"
                           "    return(0); // Not found\n"
                           "}\n");
}

internal void write_is_container(OutputBuffer *ob, String *types, Int type_count) {
    write_to_output_buffer(ob, "static bool is_meta_type_container(int type) {\n");

    for(Int i = 0; (i < type_count); ++i) {
        String *type = types + i;

        if(!i) write_to_output_buffer(ob, "    ");
        else   write_to_output_buffer(ob, "    else ");

        StdResult std_res = get_std_information(*type);
        switch(std_res.type) {
            case StdTypes_not: {
                write_to_output_buffer(ob, "if(type == Type_%.*s) {return(false);} // false\n", type->len, type->e);
            } break;

            case StdTypes_vector: {
                write_to_output_buffer(ob, "if(type == Type_std_vector_%.*s) {return(true);} // true\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            case StdTypes_deque: {
                write_to_output_buffer(ob, "if(type == Type_std_deque_%.*s) {return(true);} // true\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            case StdTypes_forward_list: {
                write_to_output_buffer(ob, "if(type == Type_std_forward_list_%.*s) {return(true);} // true\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            case StdTypes_list: {
                write_to_output_buffer(ob, "if(type == Type_std_list_%.*s) {return(true);} // true\n", std_res.stored_type.len, std_res.stored_type.e);
            } break;

            default: assert(0); break;
        }
    }

    write_to_output_buffer(ob,
                           "\n"
                           "    // Should not be reached.\n"
                           "    assert(0);\n"
                           "    return(0);\n"
                           "}\n");
}

internal Void write_out_recreated_struct(OutputBuffer *ob, StructData struct_data) {
    write_to_output_buffer(ob, "    %s _%.*s", (struct_data.struct_type != StructType_union) ? "struct" : "union",
                           struct_data.name.len, struct_data.name.e);
    if(struct_data.inherited) {
        write_to_output_buffer(ob, " :");

        for(Int j = 0; (j < struct_data.inherited_count); ++j) {
            String *inherited = struct_data.inherited + j;

            if(j > 0) write_to_output_buffer(ob, ",");

            write_to_output_buffer(ob, " public _%.*s", inherited->len, inherited->e);
        }
    }
    write_to_output_buffer(ob, " { ");

    Bool is_inside_anonymous_struct = false;
    for(Int j = 0; (j < struct_data.member_count); ++j) {
        Variable *md = struct_data.members + j;

        if(md->is_inside_anonymous_struct != is_inside_anonymous_struct) {
            is_inside_anonymous_struct = !is_inside_anonymous_struct;

            if(is_inside_anonymous_struct) {
                write_to_output_buffer(ob, " struct {");
            } else {
                write_to_output_buffer(ob, "};");
            }
        }

        Char *arr = "";
        Char arr_buffer[256] = {};
        if(md->array_count > 1) {
            stbsp_snprintf(arr_buffer, 256, "[%u]", md->array_count);
            arr = arr_buffer;
        }

        write_to_output_buffer(ob, " _%.*s %s%.*s%s; ",
                               md->type.len, md->type.e,
                               (md->is_ptr) ? "*" : "",
                               md->name.len, md->name.e,
                               (md->array_count > 1) ? arr_buffer : arr);

    }

    if(is_inside_anonymous_struct) write_to_output_buffer(ob, " };");

    write_to_output_buffer(ob, " };\n");
}

internal Void write_out_recreated_structs(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob, "    // Recreated structs.\n");
    for(Int i = 0; (i < struct_count); ++i) {
        write_out_recreated_struct(ob, struct_data[i]);
    }
}

internal Void write_out_get_access(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob,
                           "//\n"
                           "// Get access at index.\n"
                           "//\n"
                           "template<typename T, int index> constexpr Access get_access_at_index() { return(Access_unknown); }\n"
                           "\n");

    auto write_func = [](OutputBuffer *ob, StructData *sd, Int j, char *access, Char *modifier) {
        write_to_output_buffer(ob,
                               "template<> constexpr Access get_access_at_index<%.*s%s, %d>() { return(Access_%s); }\n",
                               sd->name.len, sd->name.e, modifier,
                               j,
                               access);
    };

    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        write_to_output_buffer(ob, "\n");

        for(Int j = 0; (j < sd->member_count); ++j) {
            Variable *md = sd->members + j;

            Char *access = 0;
            if(md->access == Access_public)         { access = "public"; }
            else if(md->access == Access_private)   { access = "private"; }
            else if(md->access == Access_protected) { access = "protected"; }
            else                                    { assert(0); /* Error, could not determine access. */ }

            write_func(ob, sd, j, access, "");
            write_func(ob, sd, j, access, " *");
            write_func(ob, sd, j, access, " **");
            write_func(ob, sd, j, access, " &");
            write_func(ob, sd, j, access, " *&");
            write_func(ob, sd, j, access, " **&");
        }
    }
}

// TODO(Jonny): This won't handle pointers or arrays.
internal Void write_out_get_at_index(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    auto write_get_member = [](OutputBuffer *ob, StructData *sd, Variable *md, Int j, Char *ref_info) {
        Char const *pointer_info = (md->is_ptr) ? " *" : "";

        write_to_output_buffer(ob,
                               "template<> struct GetMember<%.*s%s, %d> {\n"
                               "    static %.*s%s *get(%.*s *ptr) {\n"
                               "        _%.*s *cpy = (_%.*s *)ptr;\n"
                               "        %.*s%s * res = (%.*s%s *)&cpy->%.*s;\n"
                               "        return(res);\n"
                               "    };\n"
                               "};\n",
                               sd->name.len, sd->name.e, ref_info,
                               j,
                               md->type.len, md->type.e, pointer_info,
                               sd->name.len, sd->name.e,
                               sd->name.len, sd->name.e,
                               sd->name.len, sd->name.e,
                               md->type.len, md->type.e, pointer_info,
                               md->type.len, md->type.e, pointer_info,
                               md->name.len, md->name.e);
    };

    write_to_output_buffer(ob,
                           "// Get at index.\n"
                           "#define get_member(variable, index) GetMember<decltype(variable), index>::get(variable)\n"
                           "template<typename T, int index> struct GetMember { /* Can I have a static assert in here that will only get called if the function is generated?? */};\n");

    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;
        write_to_output_buffer(ob, "\n");

        for(Int j = 0; (j < sd->member_count); ++j) {
            Variable *md = sd->members + j;

            // Because get_member _requires_ a pointer, only generate code for the pointer version.
            write_get_member(ob, sd, md, j, " *");
            write_get_member(ob, sd, md, j, " *&");
        }
    }
}

internal Void write_out_get_name_at_index(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob,
                           "template<typename T>static char const * get_member_name(int index){return(0);}\n");
    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        write_to_output_buffer(ob,
                               "template<>char const * get_member_name<%.*s>(int index){\n"
                               "    switch(index) {\n",
                               sd->name.len, sd->name.e);

        for(Int j = 0; (j < sd->member_count); ++j) {
            Variable *md = sd->members + j;

            write_to_output_buffer(ob,
                                   "        case %d: { return(\"%.*s\"); } break;\n",
                                   j,
                                   md->name.len, md->name.e);
        }

        write_to_output_buffer(ob,
                               "    }\n"
                               "    return(0); // Not found.\n"
                               "}\n");
    }

}

internal Void write_sizeof_from_str(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob,
                           "static size_t get_size_from_str(char const *str) {\n");
    //write_out_recreated_structs(ob, struct_data, struct_count);
    write_to_output_buffer(ob, "\n");

    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        if(!i) write_to_output_buffer(ob, "    ");
        else   write_to_output_buffer(ob, "    else ");

        write_to_output_buffer(ob,
                               "if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {return(sizeof(_%.*s));}\n",
                               sd->name.len, sd->name.e,
                               sd->name.len, sd->name.e,
                               sd->name.len, sd->name.e,
                               sd->name.len, sd->name.e);
    }

    write_to_output_buffer(ob,
                           "\n"
                           "    return(0); // Not found.\n"
                           "}\n");
}

internal Void write_out_type_specification_struct(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    PtrSize size = 128;
    String *written_members = alloc(String, size);
    Int member_cnt = 0;

    write_to_output_buffer(ob,
                           "//\n"
                           "// Meta type specialization\n"
                           "//\n");

    write_type_struct_all(ob, create_string("void"), 0, struct_data, struct_count);

    String primatives[array_count(primitive_types)] = {};
    set_primitive_type(primatives);

    for(Int i = 0; (i < array_count(primatives)); ++i) {
        if(!is_in_string_array(primatives[i], written_members, member_cnt)) {
            if(member_cnt >= size) {
                size *= 2;
                void *ptr = realloc(written_members, sizeof(String) * size);
                if(ptr) {
                    written_members = cast(String *)ptr;
                }
            }

            written_members[member_cnt++] = primatives[i];

            write_type_struct_all(ob, primatives[i], 0, struct_data, struct_count);
        }
    }

    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        if(!is_in_string_array(sd->name, written_members, member_cnt)) {
            if(member_cnt >= size) {
                size *= 2;
                void *ptr = realloc(written_members, sizeof(String) * size);
                if(ptr) {
                    written_members = cast(String *)ptr;
                }
            }

            written_members[member_cnt++] = sd->name;

            write_type_struct_all(ob, sd->name, sd->member_count, struct_data, struct_count);

            for(Int j = 0; (j < sd->member_count); ++j) {
                Variable *md = sd->members + j;

                if(!is_in_string_array(md->type, written_members, member_cnt)) {
                    if(member_cnt >= size) {
                        size *= 2;
                        void *ptr = realloc(written_members, sizeof(String) * size);
                        if(ptr) {
                            written_members = cast(String *)ptr;
                        }
                    }

                    written_members[member_cnt++] = md->type;

                    Int number_of_members = 0;
                    StructData *members_struct_data = find_struct(md->type, struct_data, struct_count);
                    if(members_struct_data) {
                        number_of_members = members_struct_data->member_count;
                    }

                    write_type_struct_all(ob, md->type, number_of_members, struct_data, struct_count);
                }
            }
        }
    }

    free(written_members);
}

internal Void write_out_type_specification_enum(OutputBuffer *ob, EnumData *enum_data, Int enum_count) {
    for(Int i = 0; (i < enum_count); ++i) {
        EnumData *ed = enum_data + i;

        if(ed->type.len) {
            write_to_output_buffer(ob,
                                   "// enum %.*s\n",
                                   ed->name.len, ed->name.e);

            write_type_struct(ob, ed->name, ed->no_of_values, "", an_enum, false, ed->type);
            write_type_struct(ob, ed->name, ed->no_of_values, " *", an_enum, false, ed->type);
            write_type_struct(ob, ed->name, ed->no_of_values, " **", an_enum, false, ed->type);

            write_type_struct(ob, ed->name, ed->no_of_values, "", an_enum, true, ed->type);
            write_type_struct(ob, ed->name, ed->no_of_values, " *", an_enum, true, ed->type);
            write_type_struct(ob, ed->name, ed->no_of_values, " **", an_enum, true, ed->type);
        }
    }
}

internal Void write_get_members_of(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    // Get Members of.
    write_to_output_buffer(ob,
                           "\n"
                           "// Convert a type into a members of pointer.\n"
                           "template<typename T> static MemberDefinition *get_members_of_(void) {\n");

    if(struct_count) {
        //write_out_recreated_structs(ob, struct_data, struct_count);
        Bool actually_written_anything = false;

        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(sd->member_count) {
                actually_written_anything = true;
                if(!i) {
                    write_to_output_buffer(ob,
                                           "    // %.*s\n"
                                           "    if(type_compare(T, %.*s)) {\n",
                                           sd->name.len, sd->name.e,
                                           sd->name.len, sd->name.e);
                } else {
                    write_to_output_buffer(ob,
                                           "\n"
                                           "    // %.*s\n"
                                           "    } else if(type_compare(T, %.*s)) {\n",
                                           sd->name.len, sd->name.e,
                                           sd->name.len, sd->name.e);
                }

                write_to_output_buffer(ob, "        static MemberDefinition members_of_%.*s[] = {\n", sd->name.len, sd->name.e);
                for(Int j = 0; (j < sd->member_count); ++j) {
                    Variable *md = sd->members + j;

                    StdResult std_res = get_std_information(md->type);
                    switch(std_res.type) {
                        case StdTypes_not: {
                            write_to_output_buffer(ob, "            {Type_%.*s", md->type.len, md->type.e);
                        } break;

                        case StdTypes_vector: {
                            write_to_output_buffer(ob, "            {Type_std_vector_%.*s", std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        case StdTypes_deque: {
                            write_to_output_buffer(ob, "            {Type_std_deque_%.*s", std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        case StdTypes_forward_list: {
                            write_to_output_buffer(ob, "            {Type_std_forward_list_%.*s", std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        case StdTypes_list: {
                            write_to_output_buffer(ob, "            {Type_std_list_%.*s", std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        default: {
                            assert(0);
                        } break;
                    }

                    write_to_output_buffer(ob, ", \"%.*s\", offset_of(&_%.*s::%.*s), %s, %d},\n",
                                           md->name.len, md->name.e,
                                           sd->name.len, sd->name.e,
                                           md->name.len, md->name.e,
                                           (md->is_ptr) ? "true" : "false",
                                           md->array_count);
                }

                if(sd->inherited) {
                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);
                        if(base_class) {
                            write_to_output_buffer(ob, "            // Members inherited from %.*s.\n",
                                                   base_class->name.len, base_class->name.e);
                            for(Int k = 0; (k < base_class->member_count); ++k) {
                                Variable *base_class_var = base_class->members + k;

                                StdResult std_res = get_std_information(base_class_var->type);
                                switch(std_res.type) {
                                    case StdTypes_not: {
                                        write_to_output_buffer(ob,
                                                               "            {Type_%.*s",
                                                               base_class_var->type.len, base_class_var->type.e);
                                    } break;

                                    case StdTypes_vector: {
                                        write_to_output_buffer(ob,
                                                               "            {Type_std_vector_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;

                                    case StdTypes_deque: {
                                        write_to_output_buffer(ob,
                                                               "            {Type_std_deque_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;

                                    case StdTypes_forward_list: {
                                        write_to_output_buffer(ob,
                                                               "            {Type_std_forward_list_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;

                                    case StdTypes_list: {
                                        write_to_output_buffer(ob,
                                                               "            {Type_std_list_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;

                                    default: {
                                        assert(0);
                                    } break;
                                }

                                write_to_output_buffer(ob, ", \"%.*s\", (size_t)&((_%.*s *)0)->%.*s, %s, %d},\n",
                                                       base_class_var->name.len, base_class_var->name.e,
                                                       sd->name.len, sd->name.e,
                                                       base_class_var->name.len, base_class_var->name.e,
                                                       (base_class_var->is_ptr) ? "true" : "false",
                                                       base_class_var->array_count);
                            }
                        }
                    }
                }

                write_to_output_buffer(ob,
                                       "        };\n"
                                       "        return(members_of_%.*s);\n",
                                       sd->name.len, sd->name.e);
            }
        }

        if(actually_written_anything) {
            write_to_output_buffer(ob, "    }\n");
        }
    }

    write_to_output_buffer(ob,
                           "\n"
                           "    return(0); // Error.\n"
                           "}\n");

}

internal Void write_get_members_of_str(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob,
                           "\n"
                           "// Convert a type into a members of pointer.\n"
                           "static MemberDefinition *get_members_of_str(char const *str) {\n");

    //write_out_recreated_structs(ob, struct_data, struct_count);

    String prim[array_count(primitive_types)] = {};
    set_primitive_type(prim);

    for(Int i = 0, cnt = array_count(prim); (i < cnt); ++i) {
        String *s = prim + i;

        if(!i) {
            write_to_output_buffer(ob,
                                   "    // %.*s\n"
                                   "    if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                   s->len, s->e,
                                   s->len, s->e,
                                   s->len, s->e,
                                   s->len, s->e);
        } else {
            write_to_output_buffer(ob,
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

            // TODO(Jonny): Can I just use default for vector and array??
            case StdTypes_vector: {
                output_string = std_res.stored_type.e;
                len = std_res.stored_type.len;
            } break;

            case StdTypes_deque: {
                output_string = std_res.stored_type.e;
                len = std_res.stored_type.len;
            } break;

            case StdTypes_forward_list: {
                output_string = std_res.stored_type.e;
                len = std_res.stored_type.len;
            } break;

            case StdTypes_list: {
                output_string = std_res.stored_type.e;
                len = std_res.stored_type.len;
            } break;

            default: {
                assert(0);
            } break;
        }

        write_to_output_buffer(ob,
                               "        static MemberDefinition members_of_%.*s[] = {\n"
                               "            {Type_%.*s, \"\", 0, false, 1}\n"
                               "        };\n"
                               "        return(members_of_%.*s);\n"
                               "\n",
                               len, output_string,
                               len, output_string,
                               len, output_string,
                               len, output_string);

    }

    if(struct_count) {
        for(Int i = 0; (i < struct_count); ++i) {
            StructData *sd = struct_data + i;

            if(sd->member_count > 0) {
                write_to_output_buffer(ob,
                                       "\n"
                                       "    // %.*s\n"
                                       "    } else if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s\ *\") == 0) || (strcmp(str, \"%.*s\ **\") == 0)) {\n",
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e,
                                       sd->name.len, sd->name.e);

                write_to_output_buffer(ob, "        static MemberDefinition members_of_%.*s[] = {\n", sd->name.len, sd->name.e);
                for(Int j = 0; (j < sd->member_count); ++j) {
                    Variable *md = sd->members + j;

                    StdResult std_res = get_std_information(md->type);
                    switch(std_res.type) {
                        case StdTypes_not: {
                            write_to_output_buffer(ob, "            {Type_%.*s",
                                                   md->type.len, md->type.e);
                        } break;

                        case StdTypes_vector: {
                            write_to_output_buffer(ob, "            {Type_std_vector_%.*s",
                                                   std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        case StdTypes_deque: {
                            write_to_output_buffer(ob, "            {Type_std_deque_%.*s",
                                                   std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        case StdTypes_forward_list: {
                            write_to_output_buffer(ob, "            {Type_std_forward_list_%.*s",
                                                   std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        case StdTypes_list: {
                            write_to_output_buffer(ob, "            {Type_std_list_%.*s",
                                                   std_res.stored_type.len, std_res.stored_type.e);
                        } break;

                        default: {
                            assert(0);
                        } break;
                    }

                    write_to_output_buffer(ob, ", \"%.*s\", offset_of(&_%.*s::%.*s), %s, %d},\n",
                                           md->name.len, md->name.e,
                                           sd->name.len, sd->name.e,
                                           md->name.len, md->name.e,
                                           (md->is_ptr) ? "true" : "false",
                                           md->array_count);
                }

                if(sd->inherited) {
                    for(Int j = 0; (j < sd->inherited_count); ++j) {
                        StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);
                        if(base_class) {
                            write_to_output_buffer(ob, "            // Members inherited from %.*s.\n",
                                                   base_class->name.len, base_class->name.e);
                            for(Int k = 0; (k < base_class->member_count); ++k) {
                                Variable *base_class_var = base_class->members + k;

                                StdResult std_res = get_std_information(base_class_var->type);
                                switch(std_res.type) {
                                    case StdTypes_not: {
                                        write_to_output_buffer(ob, "            {Type_%.*s",
                                                               base_class_var->type.len, base_class_var->type.e);
                                    } break;

                                    case StdTypes_vector: {
                                        write_to_output_buffer(ob, "            {Type_std_vector_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;

                                    case StdTypes_deque: {
                                        write_to_output_buffer(ob, "            {Type_std_deque_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;

                                    case StdTypes_forward_list: {
                                        write_to_output_buffer(ob, "            {Type_std_forward_list_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;

                                    case StdTypes_list: {
                                        write_to_output_buffer(ob, "            {Type_std_list_%.*s",
                                                               std_res.stored_type.len, std_res.stored_type.e);
                                    } break;
                                }


                                write_to_output_buffer(ob, ", \"%.*s\", (size_t)&((_%.*s *)0)->%.*s, %s, %d},\n",
                                                       base_class_var->name.len, base_class_var->name.e,
                                                       sd->name.len, sd->name.e,
                                                       base_class_var->name.len, base_class_var->name.e,
                                                       (base_class_var->is_ptr) ? "true" : "false",
                                                       base_class_var->array_count);
                            }
                        }
                    }
                }

                write_to_output_buffer(ob,
                                       "        };\n"
                                       "        return(members_of_%.*s);\n",
                                       sd->name.len, sd->name.e);
            }
        }
    }
    write_to_output_buffer(ob, "    }\n");

    write_to_output_buffer(ob,
                           "\n"
                           "    return(0); // Error.\n"
                           "}\n");
}

internal Void write_get_number_of_members_str(OutputBuffer *ob, StructData *struct_data, Int struct_count) {
    write_to_output_buffer(ob,
                           "\n"
                           "// Get the number of members for a type.\n"
                           "static int get_number_of_members_str(char const *str) {\n");

    String prim[array_count(primitive_types)] = {};
    set_primitive_type(prim);

    for(Int i = 0, cnt = array_count(prim); (i < cnt); ++i) {
        String *p = prim + i;

        if(!i) {
            write_to_output_buffer(ob, "    ");
        } else {
            write_to_output_buffer(ob, "    else ");
        }

        write_to_output_buffer(ob,
                               "if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s *\") == 0) || (strcmp(str, \"%.*s **\") == 0)) {return(1);}\n",
                               p->len, p->e,
                               p->len, p->e,
                               p->len, p->e);
    }

    for(Int i = 0; (i < struct_count); ++i) {
        StructData *sd = struct_data + i;

        Int member_count = sd->member_count;

        // Add inherited struct members onto the member count.
        for(Int j = 0; (j < sd->inherited_count); ++j) {
            StructData *base_class = find_struct(sd->inherited[j], struct_data, struct_count);

            if(base_class) member_count += base_class->member_count;
        }

        write_to_output_buffer(ob,
                               "    else if((strcmp(str, \"%.*s\") == 0) || (strcmp(str, \"%.*s *\") == 0) || (strcmp(str, \"%.*s **\") == 0)) {return(%d);}\n",
                               sd->name.len, sd->name.e,
                               sd->name.len, sd->name.e,
                               sd->name.len, sd->name.e,
                               member_count);
    }

    write_to_output_buffer(ob,
                           "\n    return(-1); // Error.\n"
                           "}\n");
}

internal Void write_enum_to_string(OutputBuffer *ob, EnumData enum_data) {
    write_to_output_buffer(ob,
                           "template<>constexpr char const *enum_to_string<%.*s>(%.*s element) {\n"
                           "    %.*s index = (%.*s)element;\n"
                           "    switch(index) {\n",
                           enum_data.name.len, enum_data.name.e,
                           enum_data.name.len, enum_data.name.e,
                           enum_data.type.len, enum_data.type.e,
                           enum_data.type.len, enum_data.type.e);
    for(Int j = 0; (j < enum_data.no_of_values); ++j) {
        EnumValue *v = enum_data.values + j;

        write_to_output_buffer(ob,
                               "        case %d:  { return(\"%.*s\"); } break;\n",
                               v->value,
                               v->name.len, v->name.e);
    }

    write_to_output_buffer(ob,
                           "\n"
                           "        default: { return(0); } break;\n"
                           "    }\n"
                           "}\n");
}

internal void write_string_to_enum(OutputBuffer *ob, EnumData enum_data) {
    write_to_output_buffer(ob,
                           "template<>constexpr %.*s string_to_enum<%.*s>(char const *str) {\n"
                           "    %.*s res = {};\n"
                           "    bool equal = false;\n"
                           "    char const *cpy = 0;\n"
                           "    char const *cmp = 0;\n"
                           "\n",
                           enum_data.name.len, enum_data.name.e,
                           enum_data.name.len, enum_data.name.e,
                           enum_data.type.len, enum_data.type.e);
    for(Int j = 0; (j < enum_data.no_of_values); ++j) {
        EnumValue *v = enum_data.values + j;



        write_to_output_buffer(ob,
                               "    if(!equal) {\n"
                               "        equal = true;\n"
                               "        cpy = str;\n"
                               "        cmp = \"%.*s\";\n"
                               "        while((*cpy) && (*cmp)) {\n"
                               "            if(*cmp != *cpy) {\n"
                               "                equal = false;\n"
                               "                break; // while\n"
                               "            }\n"
                               "            ++cpy; ++cmp;\n"
                               "        }\n"
                               "        if(equal) { res = %d;}\n"
                               "    }"
                               "\n",
                               v->name.len, v->name.e,
                               v->value);
    }

    write_to_output_buffer(ob,
                           "\n"
                           "    return (%.*s)res;\n"
                           "}\n",
                           enum_data.name.len, enum_data.name.e);
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

        // Forward declare structs.
        write_to_output_buffer(&ob, "// Forward declared structs and enums (these must be declared outside the namespace...)\n");
        forward_declare_structs(&ob, struct_data, struct_count);
        forward_declare_enums(&ob, enum_data, enum_count);

        write_to_output_buffer(&ob,
                               "\n"
                               "#define _std std // TODO(Jonny): This is really stupid..."
                               "\n");

        //
        // Types enum.
        //

        // Get the absolute max number of meta types. This will be significantly bigger than the
        // actual number of unique types...
        Int max_type_count = get_num_of_primitive_types();
        for(Int i = 0; (i < struct_count); ++i) max_type_count += struct_data[i].member_count + 1;

        String *types = alloc(String, max_type_count);
        if(types) {
            Int type_count = get_actual_type_count(types, struct_data, struct_count);
            assert(type_count <= max_type_count);

            write_meta_type_enum(&ob, types, type_count, struct_data, struct_count);

            write_to_output_buffer(&ob, "\n");
            write_to_output_buffer(&ob,
                                   "#include \"static_generated.h\"\n"
                                   "namespace pp { // PreProcessor\n");
            write_to_output_buffer(&ob, "\n");

            write_out_recreated_structs(&ob, struct_data, struct_count);

            write_out_type_specification_struct(&ob, struct_data, struct_count);
            write_out_type_specification_enum(&ob, enum_data, enum_count);
            write_out_get_at_index(&ob, struct_data, struct_count);
            write_out_get_name_at_index(&ob, struct_data, struct_count);

            write_is_container(&ob, types, type_count);
            write_meta_type_to_name(&ob, struct_data, struct_count);
            write_sizeof_from_str(&ob, struct_data, struct_count);
            write_serialize_struct_implementation(&ob, types, type_count);
            write_out_get_access(&ob, struct_data, struct_count);


            free(types);
        }

        write_get_members_of(&ob, struct_data, struct_count);
        write_get_members_of_str(&ob, struct_data, struct_count);
        write_get_number_of_members_str(&ob, struct_data, struct_count);

        write_to_output_buffer(&ob,
                               "\n"
                               "//\n"
                               "// Enum Introspection data.\n"
                               "//\n"
                               "\n"
                               "// Stub functions.\n"
                               "template<typename T>static constexpr char const *enum_to_string(T element) { return(0); }\n"
                               "template<typename T>static constexpr T string_to_enum(char const *str) { return(0); }\n"
                               "\n");
        for(Int i = 0; (i < enum_count); ++i) {
            if(enum_data[i].type.len) {
                write_to_output_buffer(&ob,
                                       "// %.*s.\n",
                                       enum_data[i].name.len, enum_data[i].name.e);
                write_enum_to_string(&ob, enum_data[i]);
                write_string_to_enum(&ob, enum_data[i]);
            }
        }

        write_to_output_buffer(&ob, "\n");

        write_to_output_buffer(&ob,
                               "#define weak_type_compare(A, B) TypeCompare_<pp::Type<A>::weak_type, pp::Type<B>::weak_type>::e;");

        //
        // # Guard macro.
        //
        write_to_output_buffer(&ob,
                               "\n"
                               "#undef _std // :(\n"
                               "} // namespace pp\n"
                               "\n"
                               "#endif // Header guard.\n"
                               "\n");

        res.size = ob.index;
        res.data = ob.buffer;
    }

    return(res);
}

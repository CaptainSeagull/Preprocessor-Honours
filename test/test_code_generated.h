#if !defined(GENERATED_H) /* TODO(Jonny): Add the actual filename in here? */

#include "static_generated.h"

/* Enum with field for every type detected. */
typedef enum MetaType {
    meta_type_char,
    meta_type_short,
    meta_type_int,
    meta_type_long,
    meta_type_float,
    meta_type_double,
    meta_type_bool,
    meta_type_thingy,
    meta_type_V2,
    meta_type_Bar,
    meta_type_A,
    meta_type_B,
    meta_type_C,
    meta_type_Foo,
} MetaType;

/* Struct meta data. */

/* Struct typedefs. */
typedef struct _thingy _thingy;typedef struct _V2 _V2;typedef struct _Bar _Bar;typedef struct _A _A;typedef struct _B _B;typedef struct _C _C;typedef struct _Foo _Foo;
/* Recreated structs. */
struct _thingy {  _int x;  _int y;  };
struct _V2 {  _int x;  _int y;  };
struct _Bar {  _short s;  _int i;  _float f;  _double d;  _V2 v2;  };
struct _A {  _float dfksjl;  };
struct _B {  _float dfgkjn;  };
struct _C {  _float fdskl;  };
struct _Foo : public _Bar, public _thingy, public _A, public _B, public _C {  _char *str;  _int *ip;  _float *fp;  _bool *b;  _double *p_array[5];  };

/* Meta data for: thingy. */
static int num_members_for_thingy = 2;
static MemberDefinition members_of_thingy[] = {
    /* Members. */
    {meta_type_int, "x", (size_t)&((_thingy *)0)->x, 0, 1},
    {meta_type_int, "y", (size_t)&((_thingy *)0)->y, 0, 1},
};
#define thingyx int 
#define thingyy int 

/* Meta data for: V2. */
static int num_members_for_V2 = 2;
static MemberDefinition members_of_V2[] = {
    /* Members. */
    {meta_type_int, "x", (size_t)&((_V2 *)0)->x, 0, 1},
    {meta_type_int, "y", (size_t)&((_V2 *)0)->y, 0, 1},
};
#define V2x int 
#define V2y int 

/* Meta data for: Bar. */
static int num_members_for_Bar = 5;
static MemberDefinition members_of_Bar[] = {
    /* Members. */
    {meta_type_short, "s", (size_t)&((_Bar *)0)->s, 0, 1},
    {meta_type_int, "i", (size_t)&((_Bar *)0)->i, 0, 1},
    {meta_type_float, "f", (size_t)&((_Bar *)0)->f, 0, 1},
    {meta_type_double, "d", (size_t)&((_Bar *)0)->d, 0, 1},
    {meta_type_V2, "v2", (size_t)&((_Bar *)0)->v2, 0, 1},
};
#define Bars short 
#define Bari int 
#define Barf float 
#define Bard double 
#define Barv2 V2 

/* Meta data for: A. */
static int num_members_for_A = 1;
static MemberDefinition members_of_A[] = {
    /* Members. */
    {meta_type_float, "dfksjl", (size_t)&((_A *)0)->dfksjl, 0, 1},
};
#define Adfksjl float 

/* Meta data for: B. */
static int num_members_for_B = 1;
static MemberDefinition members_of_B[] = {
    /* Members. */
    {meta_type_float, "dfgkjn", (size_t)&((_B *)0)->dfgkjn, 0, 1},
};
#define Bdfgkjn float 

/* Meta data for: C. */
static int num_members_for_C = 1;
static MemberDefinition members_of_C[] = {
    /* Members. */
    {meta_type_float, "fdskl", (size_t)&((_C *)0)->fdskl, 0, 1},
};
#define Cfdskl float 

/* Meta data for: Foo. */
static int num_members_for_Foo = 15;
static MemberDefinition members_of_Foo[] = {
    /* Members. */
    {meta_type_char, "str", (size_t)&((_Foo *)0)->str, 1, 1},
    {meta_type_int, "ip", (size_t)&((_Foo *)0)->ip, 1, 1},
    {meta_type_float, "fp", (size_t)&((_Foo *)0)->fp, 1, 1},
    {meta_type_bool, "b", (size_t)&((_Foo *)0)->b, 1, 1},
    {meta_type_double, "p_array", (size_t)&((_Foo *)0)->p_array, 1, 5},

    /* Inherited Members for Bar */
    {meta_type_short, "s", (size_t)&((_Foo *)0)->s, 0, 1},
    {meta_type_int, "i", (size_t)&((_Foo *)0)->i, 0, 1},
    {meta_type_float, "f", (size_t)&((_Foo *)0)->f, 0, 1},
    {meta_type_double, "d", (size_t)&((_Foo *)0)->d, 0, 1},
    {meta_type_V2, "v2", (size_t)&((_Foo *)0)->v2, 0, 1},

    /* Inherited Members for thingy */
    {meta_type_int, "x", (size_t)&((_Foo *)0)->x, 0, 1},
    {meta_type_int, "y", (size_t)&((_Foo *)0)->y, 0, 1},

    /* Inherited Members for A */
    {meta_type_float, "dfksjl", (size_t)&((_Foo *)0)->dfksjl, 0, 1},

    /* Inherited Members for B */
    {meta_type_float, "dfgkjn", (size_t)&((_Foo *)0)->dfgkjn, 0, 1},

    /* Inherited Members for C */
    {meta_type_float, "fdskl", (size_t)&((_Foo *)0)->fdskl, 0, 1},
};
#define Foostr char *
#define Fooip int *
#define Foofp float *
#define Foob bool *
#define Foop_array double *


/* Convert a type into a members of pointer. */
template<typename T> static MemberDefinition *get_members_of_(void)
{
    if(type_compare(T, thingy)) { return(members_of_thingy); }
    else if(type_compare(T, V2)) { return(members_of_V2); }
    else if(type_compare(T, Bar)) { return(members_of_Bar); }
    else if(type_compare(T, A)) { return(members_of_A); }
    else if(type_compare(T, B)) { return(members_of_B); }
    else if(type_compare(T, C)) { return(members_of_C); }
    else if(type_compare(T, Foo)) { return(members_of_Foo); }

    else { assert(0); return(0); } /* Error */
}
/* Convert a type into a members of pointer. */
template<typename T> static size_t get_number_of_members_(void)
{
    if(type_compare(T, thingy)) { return(num_members_for_thingy); }
    else if(type_compare(T, V2)) { return(num_members_for_V2); }
    else if(type_compare(T, Bar)) { return(num_members_for_Bar); }
    else if(type_compare(T, A)) { return(num_members_for_A); }
    else if(type_compare(T, B)) { return(num_members_for_B); }
    else if(type_compare(T, C)) { return(num_members_for_C); }
    else if(type_compare(T, Foo)) { return(num_members_for_Foo); }

    else { assert(0); return(0); } /* Error */
}
/* Function to serialize a struct to a char array buffer. */
template <typename T>static size_t
serialize_struct_(void *var, MemberDefinition *members_of_Something, char const *name,
                  int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written)
{
    char indent_buf[256];
    int i = 0, j = 0;
    int/*bool*/ is_null = 0;
    MemberDefinition *member = 0;
    void *member_ptr = 0;
    size_t *value = 0;

    memset(indent_buf, 0, 256);

    assert((var) && (members_of_Something) && (num_members > 0) && (buffer) && (buf_size > 0));
    memset(buffer + bytes_written, 0, buf_size - bytes_written);
    for(i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }

    bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, type_to_string(T), name);
    indent += 4;

    for(i = 0; (i < indent); ++i) { indent_buf[i] = ' '; }

    for(i = 0; (i < num_members); ++i) {
         member = members_of_Something + i;

         member_ptr = (char *)var + member->offset;
         switch(member->type) {
            case meta_type_double: {
                if(member->arr_size > 1) {
                    value = (size_t *)member_ptr;
                    for(j = 0; (j < member->arr_size); ++j) {
                        is_null = (member->is_ptr) ? !(*(double **)(value + j)) : 0;
                        if(!is_null) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(double *)value[j] : value[j]);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sdouble %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
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
            } break;

            case meta_type_float: {
                if(member->arr_size > 1) {
                    value = (size_t *)member_ptr;
                    for(j = 0; (j < member->arr_size); ++j) {
                        is_null = (member->is_ptr) ? !(*(float **)(value + j)) : 0;
                        if(!is_null) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s[%d] = %f", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(float *)value[j] : value[j]);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sfloat %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
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
            } break;

            case meta_type_int: {
                if(member->arr_size > 1) {
                    value = (size_t *)member_ptr;
                    for(j = 0; (j < member->arr_size); ++j) {
                        is_null = (member->is_ptr) ? !(*(int **)(value + j)) : 0;
                        if(!is_null) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(int *)value[j] : (int)value[j]);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
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
            } break;

            case meta_type_long: {
                if(member->arr_size > 1) {
                    value = (size_t *)member_ptr;
                    for(j = 0; (j < member->arr_size); ++j) {
                        is_null = (member->is_ptr) ? !(*(long **)(value + j)) : 0;
                        if(!is_null) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %ld", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(long *)value[j] : (long)value[j]);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
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
            } break;

            case meta_type_short: {
                if(member->arr_size > 1) {
                    value = (size_t *)member_ptr;
                    for(j = 0; (j < member->arr_size); ++j) {
                        is_null = (member->is_ptr) ? !(*(short **)(value + j)) : 0;
                        if(!is_null) {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = %d", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (member->is_ptr) ? *(short *)value[j] : (short)value[j]);
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sint %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
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
            } break;

#if defined(__cplusplus)
            case meta_type_bool: {
                bool *bool_value = 0;
                if(member->arr_size > 1) {
                    value = (size_t *)member_ptr;
                    for(j = 0; (j < member->arr_size); ++j) {
                        is_null = (member->is_ptr) ? !(*(bool **)(value + j)) : 0;
                        if(is_null) {
                            size_t value_to_print = (member->is_ptr) ? **(bool **)(value + j) : value[j];
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s[%d] = %s", indent_buf, (member->is_ptr) ? "*" : "", member->name, j, (value_to_print) ? "true" : "false");
                        } else {
                            bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%sbool %s%s[%d] = (null)", indent_buf, (member->is_ptr) ? "*" : "", member->name, j);
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
            } break;
#endif /* #if defined(__cplusplus) */

            case meta_type_char: {
                value = (member->is_ptr) ? *(size_t **)member_ptr : (size_t *)member_ptr;
                if(value) {
                    if(member->is_ptr) {
                        bytes_written += my_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, (char *)value);
                    } else {
                        bytes_written += my_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)value);
                    }
                } else {
                    bytes_written += my_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                }
            } break;

            default: {
                switch(member->type) {
                    case meta_type_thingy: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_<thingy *>(*(char **)member_ptr, get_members_of_<thingy>(), member->name, indent, get_number_of_members_<thingy>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<thingy *>(**(char **)member_ptr, get_members_of_<thingy>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_<thingy>((char *)member_ptr, get_members_of_<thingy>(), member->name, indent, get_number_of_members_<thingy>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<thingy>(*(char *)member_ptr, get_members_of_<thingy>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_V2: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_<V2 *>(*(char **)member_ptr, get_members_of_<V2>(), member->name, indent, get_number_of_members_<V2>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<V2 *>(**(char **)member_ptr, get_members_of_<V2>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_<V2>((char *)member_ptr, get_members_of_<V2>(), member->name, indent, get_number_of_members_<V2>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<V2>(*(char *)member_ptr, get_members_of_<V2>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_Bar: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_<Bar *>(*(char **)member_ptr, get_members_of_<Bar>(), member->name, indent, get_number_of_members_<Bar>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<Bar *>(**(char **)member_ptr, get_members_of_<Bar>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_<Bar>((char *)member_ptr, get_members_of_<Bar>(), member->name, indent, get_number_of_members_<Bar>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<Bar>(*(char *)member_ptr, get_members_of_<Bar>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_A: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_<A *>(*(char **)member_ptr, get_members_of_<A>(), member->name, indent, get_number_of_members_<A>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<A *>(**(char **)member_ptr, get_members_of_<A>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_<A>((char *)member_ptr, get_members_of_<A>(), member->name, indent, get_number_of_members_<A>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<A>(*(char *)member_ptr, get_members_of_<A>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_B: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_<B *>(*(char **)member_ptr, get_members_of_<B>(), member->name, indent, get_number_of_members_<B>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<B *>(**(char **)member_ptr, get_members_of_<B>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_<B>((char *)member_ptr, get_members_of_<B>(), member->name, indent, get_number_of_members_<B>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<B>(*(char *)member_ptr, get_members_of_<B>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_C: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_<C *>(*(char **)member_ptr, get_members_of_<C>(), member->name, indent, get_number_of_members_<C>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<C *>(**(char **)member_ptr, get_members_of_<C>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_<C>((char *)member_ptr, get_members_of_<C>(), member->name, indent, get_number_of_members_<C>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<C>(*(char *)member_ptr, get_members_of_<C>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_Foo: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_<Foo *>(*(char **)member_ptr, get_members_of_<Foo>(), member->name, indent, get_number_of_members_<Foo>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<Foo *>(**(char **)member_ptr, get_members_of_<Foo>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_<Foo>((char *)member_ptr, get_members_of_<Foo>(), member->name, indent, get_number_of_members_<Foo>(), buffer, buf_size - bytes_written, bytes_written);
                            //bytes_written = serialize_struct_<Foo>(*(char *)member_ptr, get_members_of_<Foo>, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                }
            } break; /* default */
        }
    }

    return(bytes_written);
}

/* Convert a type to a string. */
template<typename T> static char const *type_to_string_(void)
 {
    /* Primitives. */
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

    /* Struct types. */
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

    else { return(0); } /* Unknown Type. */
}

/* Enum meta data. */

/* Meta Data for: Letters. */
static size_t number_of_elements_in_enum_Letters = 3;
static char const *enum_to_string_Letters(int v)
{
    switch(v) {
        case 0: { return("letter_a"); } break;
        case 1: { return("letter_b"); } break;
        case 2: { return("letter_c"); } break;

        default: { return(0); } break; /* v is out of bounds. */
    }
}

static int string_to_enum_Letters(char const *str)
{
    if(strcmp(str, "letter_a") == 0) { return(0); }
    else if(strcmp(str, "letter_b") == 0) { return(1); }
    else if(strcmp(str, "letter_c") == 0) { return(2); }
    else { return(0); } /* str didn't match. TODO(Jonny): Throw an error here? */
}

#define GENERATED_H
#endif /* !defined(GENERATED_H) */

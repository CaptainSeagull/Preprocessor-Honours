#if !defined(BREAKOUT_GENERATED_H)
#define BREAKOUT_GENERATED_H

// Forward declared structs (these must be declared outside the namespace...)
struct V2;
struct Transform;
struct Ball;
struct Paddle;
struct GameState;

#define _std std // TODO(Jonny): This is really stupid...

// Enum with field for every type detected.
namespace pp { enum Type {
    Type_char,
    Type_short,
    Type_int,
    Type_long,
    Type_float,
    Type_double,
    Type_bool,
    Type_V2,
    Type_Transform,
    Type_Ball,
    Type_Paddle,
    Type_GameState,
}; }

#include "static_generated.h"
namespace pp { // PreProcessor

//
// Meta type specialization
//

// char
template<> struct TypeInfo<char> {
    using type = char;
    using weak_type = char;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<char> operator=(TypeInfo<char> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<char>::name = "char";
char const * const TypeInfo<char>::weak_name = "char";

template<> struct TypeInfo<char *> {
    using type = char *;
    using weak_type = char;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<char *> operator=(TypeInfo<char *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<char *>::name = "char *";
char const * const TypeInfo<char *>::weak_name = "char";

template<> struct TypeInfo<char **> {
    using type = char **;
    using weak_type = char;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<char **> operator=(TypeInfo<char **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<char **>::name = "char **";
char const * const TypeInfo<char **>::weak_name = "char";


// short
template<> struct TypeInfo<short> {
    using type = short;
    using weak_type = short;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<short> operator=(TypeInfo<short> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<short>::name = "short";
char const * const TypeInfo<short>::weak_name = "short";

template<> struct TypeInfo<short *> {
    using type = short *;
    using weak_type = short;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<short *> operator=(TypeInfo<short *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<short *>::name = "short *";
char const * const TypeInfo<short *>::weak_name = "short";

template<> struct TypeInfo<short **> {
    using type = short **;
    using weak_type = short;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<short **> operator=(TypeInfo<short **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<short **>::name = "short **";
char const * const TypeInfo<short **>::weak_name = "short";


// int
template<> struct TypeInfo<int> {
    using type = int;
    using weak_type = int;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<int> operator=(TypeInfo<int> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<int>::name = "int";
char const * const TypeInfo<int>::weak_name = "int";

template<> struct TypeInfo<int *> {
    using type = int *;
    using weak_type = int;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<int *> operator=(TypeInfo<int *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<int *>::name = "int *";
char const * const TypeInfo<int *>::weak_name = "int";

template<> struct TypeInfo<int **> {
    using type = int **;
    using weak_type = int;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<int **> operator=(TypeInfo<int **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<int **>::name = "int **";
char const * const TypeInfo<int **>::weak_name = "int";


// long
template<> struct TypeInfo<long> {
    using type = long;
    using weak_type = long;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<long> operator=(TypeInfo<long> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<long>::name = "long";
char const * const TypeInfo<long>::weak_name = "long";

template<> struct TypeInfo<long *> {
    using type = long *;
    using weak_type = long;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<long *> operator=(TypeInfo<long *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<long *>::name = "long *";
char const * const TypeInfo<long *>::weak_name = "long";

template<> struct TypeInfo<long **> {
    using type = long **;
    using weak_type = long;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<long **> operator=(TypeInfo<long **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<long **>::name = "long **";
char const * const TypeInfo<long **>::weak_name = "long";


// float
template<> struct TypeInfo<float> {
    using type = float;
    using weak_type = float;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<float> operator=(TypeInfo<float> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<float>::name = "float";
char const * const TypeInfo<float>::weak_name = "float";

template<> struct TypeInfo<float *> {
    using type = float *;
    using weak_type = float;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<float *> operator=(TypeInfo<float *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<float *>::name = "float *";
char const * const TypeInfo<float *>::weak_name = "float";

template<> struct TypeInfo<float **> {
    using type = float **;
    using weak_type = float;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<float **> operator=(TypeInfo<float **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<float **>::name = "float **";
char const * const TypeInfo<float **>::weak_name = "float";


// double
template<> struct TypeInfo<double> {
    using type = double;
    using weak_type = double;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<double> operator=(TypeInfo<double> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<double>::name = "double";
char const * const TypeInfo<double>::weak_name = "double";

template<> struct TypeInfo<double *> {
    using type = double *;
    using weak_type = double;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<double *> operator=(TypeInfo<double *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<double *>::name = "double *";
char const * const TypeInfo<double *>::weak_name = "double";

template<> struct TypeInfo<double **> {
    using type = double **;
    using weak_type = double;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<double **> operator=(TypeInfo<double **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<double **>::name = "double **";
char const * const TypeInfo<double **>::weak_name = "double";


// bool
template<> struct TypeInfo<bool> {
    using type = bool;
    using weak_type = bool;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<bool> operator=(TypeInfo<bool> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<bool>::name = "bool";
char const * const TypeInfo<bool>::weak_name = "bool";

template<> struct TypeInfo<bool *> {
    using type = bool *;
    using weak_type = bool;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<bool *> operator=(TypeInfo<bool *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<bool *>::name = "bool *";
char const * const TypeInfo<bool *>::weak_name = "bool";

template<> struct TypeInfo<bool **> {
    using type = bool **;
    using weak_type = bool;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<bool **> operator=(TypeInfo<bool **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<bool **>::name = "bool **";
char const * const TypeInfo<bool **>::weak_name = "bool";


// V2
template<> struct TypeInfo<V2> {
    using type = V2;
    using weak_type = V2;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<V2> operator=(TypeInfo<V2> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<V2>::name = "V2";
char const * const TypeInfo<V2>::weak_name = "V2";

template<> struct TypeInfo<V2 *> {
    using type = V2 *;
    using weak_type = V2;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<V2 *> operator=(TypeInfo<V2 *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<V2 *>::name = "V2 *";
char const * const TypeInfo<V2 *>::weak_name = "V2";

template<> struct TypeInfo<V2 **> {
    using type = V2 **;
    using weak_type = V2;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<V2 **> operator=(TypeInfo<V2 **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<V2 **>::name = "V2 **";
char const * const TypeInfo<V2 **>::weak_name = "V2";


// Transform
template<> struct TypeInfo<Transform> {
    using type = Transform;
    using weak_type = Transform;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Transform> operator=(TypeInfo<Transform> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Transform>::name = "Transform";
char const * const TypeInfo<Transform>::weak_name = "Transform";

template<> struct TypeInfo<Transform *> {
    using type = Transform *;
    using weak_type = Transform;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Transform *> operator=(TypeInfo<Transform *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Transform *>::name = "Transform *";
char const * const TypeInfo<Transform *>::weak_name = "Transform";

template<> struct TypeInfo<Transform **> {
    using type = Transform **;
    using weak_type = Transform;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Transform **> operator=(TypeInfo<Transform **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Transform **>::name = "Transform **";
char const * const TypeInfo<Transform **>::weak_name = "Transform";


// Ball
template<> struct TypeInfo<Ball> {
    using type = Ball;
    using weak_type = Ball;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Ball> operator=(TypeInfo<Ball> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Ball>::name = "Ball";
char const * const TypeInfo<Ball>::weak_name = "Ball";

template<> struct TypeInfo<Ball *> {
    using type = Ball *;
    using weak_type = Ball;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Ball *> operator=(TypeInfo<Ball *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Ball *>::name = "Ball *";
char const * const TypeInfo<Ball *>::weak_name = "Ball";

template<> struct TypeInfo<Ball **> {
    using type = Ball **;
    using weak_type = Ball;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Ball **> operator=(TypeInfo<Ball **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Ball **>::name = "Ball **";
char const * const TypeInfo<Ball **>::weak_name = "Ball";


// Paddle
template<> struct TypeInfo<Paddle> {
    using type = Paddle;
    using weak_type = Paddle;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Paddle> operator=(TypeInfo<Paddle> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Paddle>::name = "Paddle";
char const * const TypeInfo<Paddle>::weak_name = "Paddle";

template<> struct TypeInfo<Paddle *> {
    using type = Paddle *;
    using weak_type = Paddle;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Paddle *> operator=(TypeInfo<Paddle *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Paddle *>::name = "Paddle *";
char const * const TypeInfo<Paddle *>::weak_name = "Paddle";

template<> struct TypeInfo<Paddle **> {
    using type = Paddle **;
    using weak_type = Paddle;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Paddle **> operator=(TypeInfo<Paddle **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<Paddle **>::name = "Paddle **";
char const * const TypeInfo<Paddle **>::weak_name = "Paddle";


// GameState
template<> struct TypeInfo<GameState> {
    using type = GameState;
    using weak_type = GameState;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<GameState> operator=(TypeInfo<GameState> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<GameState>::name = "GameState";
char const * const TypeInfo<GameState>::weak_name = "GameState";

template<> struct TypeInfo<GameState *> {
    using type = GameState *;
    using weak_type = GameState;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<GameState *> operator=(TypeInfo<GameState *> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<GameState *>::name = "GameState *";
char const * const TypeInfo<GameState *>::weak_name = "GameState";

template<> struct TypeInfo<GameState **> {
    using type = GameState **;
    using weak_type = GameState;
    using base = void;

    static char const * const name;
    static char const * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<GameState **> operator=(TypeInfo<GameState **> a) = delete; // To avoid warning 4512 in MSVC.
};

char const * const TypeInfo<GameState **>::name = "GameState **";
char const * const TypeInfo<GameState **>::weak_name = "GameState";

static bool is_meta_type_container(int type) {
    if(type == Type_char) {return(false);} // false
    else if(type == Type_short) {return(false);} // false
    else if(type == Type_int) {return(false);} // false
    else if(type == Type_long) {return(false);} // false
    else if(type == Type_float) {return(false);} // false
    else if(type == Type_double) {return(false);} // false
    else if(type == Type_bool) {return(false);} // false
    else if(type == Type_V2) {return(false);} // false
    else if(type == Type_Transform) {return(false);} // false
    else if(type == Type_Ball) {return(false);} // false
    else if(type == Type_Paddle) {return(false);} // false
    else if(type == Type_GameState) {return(false);} // false

    // Should not be reached.
    assert(0);
    return(0);
}
static char const * meta_type_to_name(Type mt, bool is_ptr) {
    if(mt == Type_V2) {
        if(is_ptr) {return("V2 *");}
        else       {return("V2");  }
    } else if(mt == Type_Transform) {
        if(is_ptr) {return("Transform *");}
        else       {return("Transform");  }
    } else if(mt == Type_Ball) {
        if(is_ptr) {return("Ball *");}
        else       {return("Ball");  }
    } else if(mt == Type_Paddle) {
        if(is_ptr) {return("Paddle *");}
        else       {return("Paddle");  }
    } else if(mt == Type_GameState) {
        if(is_ptr) {return("GameState *");}
        else       {return("GameState");  }
    }

    assert(0); 
    return(0); // Not found
}
// Function to serialize a struct to a char array buffer.
static size_t
serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    assert((buffer) && (buf_size > 0)); // Check params.

    if(!bytes_written) {memset(buffer, 0, buf_size);} // If this is the first time through, zero the buffer.

    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); assert(members_of_Something); // Get the members_of pointer. 
    if(members_of_Something) {
        // Setup the indent buffer.
        char indent_buf[256] = {};
        for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}

        // Write the name and the type.
        if((name) && (strlen(name) > 0)) {
            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, type_as_str, name);
        }
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
                case Type_double: { // double.
                    bytes_written = serialize_primitive_((double *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_float: { // float.
                    bytes_written = serialize_primitive_((float *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_int: { // int.
                    bytes_written = serialize_primitive_((int *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_long: { // long.
                    bytes_written = serialize_primitive_((long *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_short: { // short.
                    bytes_written = serialize_primitive_((short *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case Type_bool: { // bool.
                    bytes_written = serialize_primitive_((bool *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                // char (special case).
                case Type_char: {
                    if(member_ptr) {
                        if(member->is_ptr) {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, (char *)(*(size_t *)member_ptr));
                        } else {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)((size_t *)member_ptr));
                        }
                    } else {
                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                    }
                } break; // case Type_char

                default: {
                    if(is_meta_type_container(member->type)) {

                    } else {
                        char const *struct_name = meta_type_to_name(member->type, member->is_ptr != 0);
                        bytes_written = serialize_struct_(member_ptr, member->name, struct_name, indent, buffer, buf_size - bytes_written, bytes_written);
                    }
                } break; // default 
            }
        }
    }

    return(bytes_written);
}

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // Recreated structs.
    struct _V2 {  _float x;  _float y;  };
    struct _Transform {  _V2 pos;  _V2 size;  };
    struct _Ball {  _Transform trans;  _V2 speed;  };
    struct _Paddle {  _Transform trans;  };
    struct _GameState {  _Paddle paddle;  _Ball ball;  _int score;  };
    // V2
    if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            {Type_float, "x", offset_of(&_V2::x), false, 1},
            {Type_float, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // Transform
    } else if(type_compare(T, Transform)) {
        static MemberDefinition members_of_Transform[] = {
            {Type_V2, "pos", offset_of(&_Transform::pos), false, 1},
            {Type_V2, "size", offset_of(&_Transform::size), false, 1},
        };
        return(members_of_Transform);

    // Ball
    } else if(type_compare(T, Ball)) {
        static MemberDefinition members_of_Ball[] = {
            {Type_Transform, "trans", offset_of(&_Ball::trans), false, 1},
            {Type_V2, "speed", offset_of(&_Ball::speed), false, 1},
        };
        return(members_of_Ball);

    // Paddle
    } else if(type_compare(T, Paddle)) {
        static MemberDefinition members_of_Paddle[] = {
            {Type_Transform, "trans", offset_of(&_Paddle::trans), false, 1},
        };
        return(members_of_Paddle);

    // GameState
    } else if(type_compare(T, GameState)) {
        static MemberDefinition members_of_GameState[] = {
            {Type_Paddle, "paddle", offset_of(&_GameState::paddle), false, 1},
            {Type_Ball, "ball", offset_of(&_GameState::ball), false, 1},
            {Type_int, "score", offset_of(&_GameState::score), false, 1},
        };
        return(members_of_GameState);
    }

    return(0); // Error.
}

// Convert a type into a members of pointer.
static MemberDefinition *get_members_of_str(char const *str) {
    // Recreated structs.
    struct _V2 {  _float x;  _float y;  };
    struct _Transform {  _V2 pos;  _V2 size;  };
    struct _Ball {  _Transform trans;  _V2 speed;  };
    struct _Paddle {  _Transform trans;  };
    struct _GameState {  _Paddle paddle;  _Ball ball;  _int score;  };
    // char
    if((strcmp(str, "char") == 0) || (strcmp(str, "char *") == 0) || (strcmp(str, "char **") == 0)) {
        static MemberDefinition members_of_char[] = {
            {Type_char, "", 0, false, 1}
        };
        return(members_of_char);

    // short
    } else if((strcmp(str, "short") == 0) || (strcmp(str, "short *") == 0) || (strcmp(str, "short **") == 0)) {
        static MemberDefinition members_of_short[] = {
            {Type_short, "", 0, false, 1}
        };
        return(members_of_short);

    // int
    } else if((strcmp(str, "int") == 0) || (strcmp(str, "int *") == 0) || (strcmp(str, "int **") == 0)) {
        static MemberDefinition members_of_int[] = {
            {Type_int, "", 0, false, 1}
        };
        return(members_of_int);

    // long
    } else if((strcmp(str, "long") == 0) || (strcmp(str, "long *") == 0) || (strcmp(str, "long **") == 0)) {
        static MemberDefinition members_of_long[] = {
            {Type_long, "", 0, false, 1}
        };
        return(members_of_long);

    // float
    } else if((strcmp(str, "float") == 0) || (strcmp(str, "float *") == 0) || (strcmp(str, "float **") == 0)) {
        static MemberDefinition members_of_float[] = {
            {Type_float, "", 0, false, 1}
        };
        return(members_of_float);

    // double
    } else if((strcmp(str, "double") == 0) || (strcmp(str, "double *") == 0) || (strcmp(str, "double **") == 0)) {
        static MemberDefinition members_of_double[] = {
            {Type_double, "", 0, false, 1}
        };
        return(members_of_double);

    // bool
    } else if((strcmp(str, "bool") == 0) || (strcmp(str, "bool *") == 0) || (strcmp(str, "bool **") == 0)) {
        static MemberDefinition members_of_bool[] = {
            {Type_bool, "", 0, false, 1}
        };
        return(members_of_bool);


    // V2
    } else if((strcmp(str, "V2") == 0) || (strcmp(str, "V2 *") == 0) || (strcmp(str, "V2 **") == 0)) {
        static MemberDefinition members_of_V2[] = {
            {Type_float, "x", offset_of(&_V2::x), false, 1},
            {Type_float, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // Transform
    } else if((strcmp(str, "Transform") == 0) || (strcmp(str, "Transform *") == 0) || (strcmp(str, "Transform **") == 0)) {
        static MemberDefinition members_of_Transform[] = {
            {Type_V2, "pos", offset_of(&_Transform::pos), false, 1},
            {Type_V2, "size", offset_of(&_Transform::size), false, 1},
        };
        return(members_of_Transform);

    // Ball
    } else if((strcmp(str, "Ball") == 0) || (strcmp(str, "Ball *") == 0) || (strcmp(str, "Ball **") == 0)) {
        static MemberDefinition members_of_Ball[] = {
            {Type_Transform, "trans", offset_of(&_Ball::trans), false, 1},
            {Type_V2, "speed", offset_of(&_Ball::speed), false, 1},
        };
        return(members_of_Ball);

    // Paddle
    } else if((strcmp(str, "Paddle") == 0) || (strcmp(str, "Paddle *") == 0) || (strcmp(str, "Paddle **") == 0)) {
        static MemberDefinition members_of_Paddle[] = {
            {Type_Transform, "trans", offset_of(&_Paddle::trans), false, 1},
        };
        return(members_of_Paddle);

    // GameState
    } else if((strcmp(str, "GameState") == 0) || (strcmp(str, "GameState *") == 0) || (strcmp(str, "GameState **") == 0)) {
        static MemberDefinition members_of_GameState[] = {
            {Type_Paddle, "paddle", offset_of(&_GameState::paddle), false, 1},
            {Type_Ball, "ball", offset_of(&_GameState::ball), false, 1},
            {Type_int, "score", offset_of(&_GameState::score), false, 1},
        };
        return(members_of_GameState);
    }

    return(0); // Error.
}

// Get the number of members for a type.
static int get_number_of_members_str(char const *str) {
    if(strcmp(str, "char") == 0) {return(1);}
    else if(strcmp(str, "short") == 0) {return(1);}
    else if(strcmp(str, "int") == 0) {return(1);}
    else if(strcmp(str, "long") == 0) {return(1);}
    else if(strcmp(str, "float") == 0) {return(1);}
    else if(strcmp(str, "double") == 0) {return(1);}
    else if(strcmp(str, "bool") == 0) {return(1);}
    else if(strcmp(str, "V2") == 0) {return(2);} // V2
    else if(strcmp(str, "Transform") == 0) {return(2);} // Transform
    else if(strcmp(str, "Ball") == 0) {return(2);} // Ball
    else if(strcmp(str, "Paddle") == 0) {return(1);} // Paddle
    else if(strcmp(str, "GameState") == 0) {return(3);} // GameState

    return(-1); // Error.
}

#define weak_type_compare(A, B) TypeCompare_<pp::Type<A>::weak_type, pp::Type<B>::weak_type>::e;
#undef _std // :(
} // namespace pp

#endif // Header guard.


#if !defined(GENERATED_CPP)

#include "generated.h"
#include <string.h>
#include <assert.h>

/* Recreated structs. */
typedef struct base_class base_class;
struct base_class {
    int i;
};

typedef struct V2 V2;
struct V2 : public base_class {
    int x;
    int y;
};

typedef struct Transform Transform;
struct Transform {
    V2 pos;
    V2 size;
};

typedef struct Ball Ball;
struct Ball {
    char *name;
    V2 pos;
    int radius;
    int speed;
    int direction;
};

typedef struct Paddle Paddle;
struct Paddle {
    char *name;
    Transform trans;
    int score;
};

typedef struct GameState GameState;
struct GameState {
    Paddle right;
    Paddle left;
    Ball ball;
};


/* Struct meta data. */

/* Meta data for: base_class. */
MemberDefinition members_of_base_class[] = {
    {meta_type_int, "i", "", (size_t)&((base_class *)0)->i, 0, 1},
};
/* Meta data for: V2. */
MemberDefinition members_of_V2[] = {
    {meta_type_int, "x", "base_class", (size_t)&((V2 *)0)->x, 0, 1},
    {meta_type_int, "y", "base_class", (size_t)&((V2 *)0)->y, 0, 1},
};
/* Meta data for: Transform. */
MemberDefinition members_of_Transform[] = {
    {meta_type_V2, "pos", "", (size_t)&((Transform *)0)->pos, 0, 1},
    {meta_type_V2, "size", "", (size_t)&((Transform *)0)->size, 0, 1},
};
/* Meta data for: Ball. */
MemberDefinition members_of_Ball[] = {
    {meta_type_char, "name", "", (size_t)&((Ball *)0)->name, 1, 1},
    {meta_type_V2, "pos", "", (size_t)&((Ball *)0)->pos, 0, 1},
    {meta_type_int, "radius", "", (size_t)&((Ball *)0)->radius, 0, 1},
    {meta_type_int, "speed", "", (size_t)&((Ball *)0)->speed, 0, 1},
    {meta_type_int, "direction", "", (size_t)&((Ball *)0)->direction, 0, 1},
};
/* Meta data for: Paddle. */
MemberDefinition members_of_Paddle[] = {
    {meta_type_char, "name", "", (size_t)&((Paddle *)0)->name, 1, 1},
    {meta_type_Transform, "trans", "", (size_t)&((Paddle *)0)->trans, 0, 1},
    {meta_type_int, "score", "", (size_t)&((Paddle *)0)->score, 0, 1},
};
/* Meta data for: GameState. */
MemberDefinition members_of_GameState[] = {
    {meta_type_Paddle, "right", "", (size_t)&((GameState *)0)->right, 0, 1},
    {meta_type_Paddle, "left", "", (size_t)&((GameState *)0)->left, 0, 1},
    {meta_type_Ball, "ball", "", (size_t)&((GameState *)0)->ball, 0, 1},
};


/* Function to serialize a struct to a char array buffer. */
size_t
serialize_struct__(void *var, MemberDefinition members_of_Something[], char const *name, int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written)
{
    char indent_buf[256];
    unsigned indent_index = 0, member_index = 0, arr_index = 0;

    memset(indent_buf, 0, 256);


    assert((var) && (members_of_Something) && (num_members > 0) && (buffer) && (buf_size > 0));
    memset(buffer + bytes_written, 0, buf_size - bytes_written);
    for(indent_index = 0; (indent_index < indent); ++indent_index) {
        indent_buf[indent_index] = ' ';
    }

    bytes_written += sprintf((char *)buffer + bytes_written, "\n%s%s", indent_buf, name);
    indent += 4;

    for(indent_index = 0; (indent_index < indent); ++indent_index) {
        indent_buf[indent_index] = ' ';
    }

    for(member_index = 0; (member_index < num_members); ++member_index) {
        MemberDefinition *member = members_of_Something + member_index;

         void *member_ptr = (char *)var + member->offset;
         switch(member->type) {
            case meta_type_float: {
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    float *value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s[%d] = %f", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s = %f", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            case meta_type_short: case meta_type_int: case meta_type_long: {
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    int *value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s[%d] = %d", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sint %s = %d", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            case meta_type_char: {
                if(member->is_ptr) {
                    bytes_written += sprintf(buffer + bytes_written, "\n%schar * %s = \"%s\"", indent_buf, member->name, *(char **)member_ptr);
                } else {
                    bytes_written += sprintf(buffer + bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)member_ptr);
                }
            } break;

            case meta_type_double: {
                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {
                    double *value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;
                    if(member->arr_size > 1) {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s[%d] = %f", indent_buf, member->name, arr_index, value[arr_index]);
                    } else {
                        bytes_written += sprintf((char *)buffer + bytes_written, "\n%sfloat %s = %f", indent_buf, member->name, value[arr_index]);
                    }
                }
            } break;

            default: {
                switch(member->type) {
                    case meta_type_base_class: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, base_class, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, base_class, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_V2: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, V2, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, V2, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_Transform: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, Transform, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, Transform, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_Ball: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, Ball, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, Ball, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_Paddle: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, Paddle, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, Paddle, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                    case meta_type_GameState: {
                        if(member->is_ptr) {
                            bytes_written = serialize_struct_(**(char **)member_ptr, GameState, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            bytes_written = serialize_struct_(*(char *)member_ptr, GameState, member->name, indent, buffer, buf_size - bytes_written, bytes_written);
                        }
                    } break;

                }
            } break; /* default */
        }
    }

    return(bytes_written);
}

#define GENERATED_CPP
#endif /* #if !defined(GENERATED_CPP) */

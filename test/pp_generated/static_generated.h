// Preprocessor API.
//
// Reference.
//
// Structs
//     - Print a struct to the console.
//     bool pp::print(TYPE var, char *buffer = 0, size_t buf_size = 0);
//
//     - Serialize a struct for output.
//     size_t pp::serialize(TYPE var, char *buffer, size_t buf_size);
//
//     - Get the number of members of a struct/class.
//     int pp::get_num_of_members(TYPE type);
//
//     - Turn type t into a string literal.
//     char const * pp::type_to_string(TYPE t);
//
//     - Turn type t into a string literal. Ignores pointer status.
//     char const * pp::weak_type_to_string(TYPE t);
//
//     - Get the number of objects this struct inherits from
//     int pp::get_base_type_count(TYPE t);
//
//     - Get the class t inherits from, as a string.
//     char const * pp::get_base_type_as_string(TYPE t, int index = 0);
//
// Enums
//     - Convert an enum index to a string.
//     char const * pp::enum_to_string(EnumType, EnumType value);
//
//     - Convert a string to an enum index.
//     int pp::string_to_enum(EnumType, char const *str);
//
//     - Get the total number of elements for an enum.
//     size_t pp::get_number_of_enum_elements(EnumType);
//
// Misc.
//     - Tests whether two types are the same.
//     bool pp::type_compare(TYPE a, TYPE b);
//
//     - Tests whether two types are the same, or if one is a base class of another.
//     bool pp::fuzzy_type_compare(TYPE a, TYPE b);
//
//     - Tests whether two types are the same, ignoring pointer status.
//     bool pp::weak_type_compare(TYPE a, TYPE b);

//
// Code shared between generated files.
#if !defined(STATIC_GENERATED_H)

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
// TODO(Jonny): Only include these if their needed?
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <stack>

namespace pp { // PreProcessor

typedef char _char;
typedef short _short;
typedef int _int;
typedef long _long;
typedef float _float;
typedef double _double;
typedef bool _bool;

struct MemberDefinition {
    int/*MetaType*/ type;
    char const *name;
    size_t offset;
    int is_ptr;
    int arr_size;
};

struct Variable {
    char const *ret_type;
    char const *name;
};

#define get_num_of_members(type) get_number_of_members_<type>()

template<typename T> static char const *type_to_string_(void);
#define type_to_string(Type) type_to_string_<Type>()
#define weak_type_to_string(Type) weak_type_to_string_<Type>()

#define serialize_type(var, Type, buf, size) serialize_struct_(&var, #var, pp::type_to_string(Type), 0, buf, size, 0)
#define serialize(var, buf, size) serialize_type(var, decltype(var), buf, size)

static MemberDefinition *get_members_of_str(char const *str);
static int get_number_of_members_str(char const *str);

static size_t serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written);
#define print_type(var, Type, ...) print_<Type>(&var, #var, ##__VA_ARGS__)
#define print(var, ...) print_type(var, decltype(var), ##__VA_ARGS__)
template<typename T>static bool print_(T *var, char const *name, char *buf = 0, size_t size = 0) {
    bool res = false, custom_buf = false;

    if(!buf) {
        size = 256 * 256;
        buf = (char *)malloc(size);
        custom_buf = true;
    }

    if(buf) {
        memset(buf, 0, size);
        size_t bytes_written = serialize_struct_(var, name, type_to_string(T), 0, buf, size, 0);
        if(bytes_written < size) {
            printf("%s", buf);
            res = true;
        }

        if(custom_buf) { free(buf); }
    }

    return(res);
}

#define enum_to_string(Type, v) enum_to_string_##Type((int)v)

#define string_to_enum(Type, str) string_to_enum_##Type(str)

#define get_number_of_enum_elements(Type) number_of_elements_in_enum_##Type

template<class T, class U>struct TypeCompare_{ enum {e = 0}; };
template<class T>struct TypeCompare_<T, T>{ enum {e = 1}; };
#define type_compare(a, b) TypeCompare_<a, b>::e

template<typename T> static int get_base_type_count_(void);
#define get_base_type_count(Type) get_base_type_count_<Type>()

template<typename T> static char const *get_base_type_as_string_(int index = 0);
#define get_base_type_as_string(Type)       get_base_type_as_string_<Type>()
#define get_base_type_as_string_index(Type, i) get_base_type_as_string_<Type>(i)

#define fuzzy_type_compare(A, B) fuzzy_type_compare_<A, B>()
template<typename T, typename U> bool fuzzy_type_compare_(void) {
    char const *a_str = type_to_string(T);
    char const *b_str = type_to_string(U);
    if((a_str) && (b_str)) {
        if(strcmp(a_str, b_str) == 0) {
            return(true);
        } else {
            int base_count = get_base_type_count(T);
            for(int i = 0; (i < base_count); ++i) {
                char const *str = get_base_type_as_string_<T>(i);
                if(strcmp(b_str, str)) { return(true); }
            }
            
            for(int i = 0; (i < base_count); ++i) {
                char const *str = get_base_type_as_string_<U>(i);
                if(strcmp(a_str, str)) { return(true); }
            }
        }
    }

    return(false);
}

template<typename T> static char const *weak_type_to_string_(void);
#define weak_type_compare(A, B) weak_type_compare_<A, B>()
template<typename T, typename U> bool weak_type_compare_(void) {
    char const *a_str = weak_type_to_string(T);
    char const *b_str = weak_type_to_string(U);
    if((a_str) && (b_str)) {
        if(strcmp(a_str, b_str) == 0) { return(true); }
    }

    return(false);
}
#if defined(_MSC_VER)
    #define pp_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)
#else
    #define pp_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)
#endif

template<typename T>static size_t
serialize_primitive_(T *member_ptr, bool is_ptr, int arr_size, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    char const *type_as_string = type_to_string(T);
    char indent_buf[256] = {};
    for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}

    if(arr_size > 1) {
        for(int j = 0; (j < arr_size); ++j) {
            size_t *member_ptr_as_size_t = (size_t *)member_ptr; // For arrays of pointers.
            bool is_null = (is_ptr) ? member_ptr_as_size_t[j] == 0 : false;
            if(!is_null) {
                T v;
                if(is_ptr) {
                    v = *(T *)member_ptr_as_size_t[j];
                } else {
                    v = member_ptr[j];
                }

#define print_prim_arr(m, type) bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s " #type " %s[%d] = " m "", indent_buf, (is_ptr) ? "*" : "", name, j, (type)v)
                if(type_compare(T, double))     print_prim_arr("%f",  double);
                else if(type_compare(T, float)) print_prim_arr("%f",  float);
                else if(type_compare(T, int))   print_prim_arr("%d",  int);
                else if(type_compare(T, long))  print_prim_arr("%ld", long);
                else if(type_compare(T, short)) print_prim_arr("%d",  short);
                else if(type_compare(T, bool))  print_prim_arr("%d",  int); // This is int to avoid warning C4800 on MSVC. Bool values get serialized as int (1 or 0) anyway.
#undef print_prim_arr
            } else {
                bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s %s[%d] = (null)", indent_buf, (is_ptr) ? "*" : "", type_as_string, name, j);
            }
        }
    } else {
        T *v = (is_ptr) ? *(T **)member_ptr : (T *)member_ptr;
        if(v) {
#define print_prim(m, type) bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s%s " #type " %s = " m "", indent_buf, (is_ptr) ? "*" : "", name, (type)*v)
            if(type_compare(T, double))     print_prim("%f",  double);
            else if(type_compare(T, float)) print_prim("%f",  float);
            else if(type_compare(T, int))   print_prim("%d",  int);
            else if(type_compare(T, long))  print_prim("%ld", long);
            else if(type_compare(T, short)) print_prim("%d",  short);
            else if(type_compare(T, bool))  print_prim("%d",  int);// This is int to avoid warning C4800 on MSVC. Bool values get serialized as int (1 or 0) anyway.
#undef print_prim
        } else {
            bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%s %s *%s = (null)", indent_buf, type_as_string, name);
        }
    }

    return(bytes_written);

}
static size_t serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written);template<typename T, typename U> static size_t
serialize_container(void *member_ptr, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    T &container = *(T *)member_ptr;
    for(auto &iter : container) {
        bytes_written = serialize_struct_((void *)&iter, name, type_to_string(U), indent, buffer, buf_size, bytes_written);
    }

    return(bytes_written);
}

template<typename T, typename U> static /*constexpr*/ size_t offset_of(U T::*member) { return (char *)&((T *)0->*member) - (char *)0; }

} // namespace pp

#define STATIC_GENERATED
#endif // !defined(STATIC_GENERATED_H)

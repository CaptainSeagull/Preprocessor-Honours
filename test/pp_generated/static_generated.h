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

namespace pp { // PreProcessor

typedef void _void;
typedef char _char;
typedef short _short;
typedef int _int;
typedef long _long;
typedef float _float;
typedef double _double;
typedef bool _bool;

#define PP_COMPILER_MSVC 0
#define PP_COMPILER_CLANG 0
#define PP_COMPILER_GCC 0

#define PP_ENVIRONMENT64 0
#define PP_ENVIRONMENT32 0

#define PP_OS_WIN32 0
#define PP_OS_LINUX 0

#if defined(__clang__)
    #undef PP_COMPILER_CLANG
    #define PP_COMPILER_CLANG 1
#elif defined(_MSC_VER)
    #undef PP_COMPILER_MSVC
    #define PP_COMPILER_MSVC 1
#elif (defined(__GNUC__) || defined(__GNUG__)) // This has to be after __clang__, because Clang also defines this.
    #undef PP_COMPILER_GCC
    #define PP_COMPILER_GCC 1
#endif

#if defined(__linux__)
    #undef PP_OS_LINUX
    #define PP_OS_LINUX 1
#elif defined(_WIN32)
    #undef PP_OS_WIN32
    #define PP_OS_WIN32 1
#endif

#if PP_OS_LINUX
    #if (__x86_64__ || __ppc64__)
        #undef PP_ENVIRONMENT64
        #define PP_ENVIRONMENT64 1
    #else
        #undef PP_ENVIRONMENT32
        #define PP_ENVIRONMENT32 1
    #endif
#elif OS_WIN32
    #if defined(_WIN64)
        #undef PP_ENVIRONMENT64
        #define PP_ENVIRONMENT64 1
    #else
        #undef PP_ENVIRONMENT32
        #define PP_ENVIRONMENT32 1
    #endif
#endif

// TODO(Jonny): Add Type in here?
template<typename T> struct TypeInfo {
    using type      = void;
    using weak_type = void;
    using base      = void;

    static constexpr char const * const name      = 0;
    static constexpr char const * const weak_name = 0;

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr bool const is_ptr = 0;
    static constexpr bool const is_ref = 0;


    static constexpr bool const is_primitive = 0;
    static constexpr bool const is_class     = 0;
    static constexpr bool const is_enum      = 0;
};

struct MemberDefinition {
    Type type;
    char const *name;
    size_t offset;
    int is_ptr;
    int arr_size;
};


struct Variable {
    char const *ret_type;
    char const *name;
};

struct MemberIter {
    Type type;
    char *name;
    void *ptr;
    bool is_ptr;
    int arr;
};

template<typename T> static MemberDefinition *get_members_of_();

template<typename T>MemberIter get_member_information(T *var, size_t i) {
    pp::MemberDefinition *mems = pp::get_members_of_<T>();

    pp::MemberDefinition cur = mems[i];

    size_t *member_ptr = (size_t *)((char unsigned *)var + cur.offset);
    MemberIter res;
    res.name = (char *)cur.name;
    res.type = cur.type;
    res.ptr = member_ptr;
    res.is_ptr = cur.is_ptr != 0;
    res.arr = (cur.arr_size > 1) ? cur.arr_size : 0;

    return(res);
}

#define serialize_type(var, T, buf, size) serialize_struct_(&var, #var, pp::TypeInfo<T>::name, 0, buf, size, 0)
#define serialize(var, buf, size) serialize_type(var, decltype(var), buf, size)

static MemberDefinition *get_members_of_str(char const *str);
static int get_number_of_members_str(char const *str);

static size_t serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer,
                                size_t buf_size, size_t bytes_written);
#define print_type(var, Type, ...) print_<Type>(&var, #var, ##__VA_ARGS__)
#define print(var, ...) print_type(var, decltype(var), ##__VA_ARGS__)
template<typename T>static void print_(T *var, char const *name, char *buf = 0, size_t size = 0) {
    bool custom_buf = false;

    if(!buf) {
        size = 256 * 256;
        buf = (char *)malloc(size);
        custom_buf = true;
    }

    if(buf) {
        memset(buf, 0, size);
        size_t bytes_written = serialize_struct_(var, name, TypeInfo<T>::name, 0, buf, size, 0);
        if(bytes_written < size) {
            printf("%s", buf);
        }

        if(custom_buf) {
            free(buf);
        }
    }
}

template<class T, class U>struct TypeCompare_{ static const bool e = false; };
template<class T>struct TypeCompare_<T, T>{ static const bool e = true; };
#define type_compare(a, b) TypeCompare_<a, b>::e

template<typename T> static int get_base_type_count_(void);
#define get_base_type_count(Type) get_base_type_count_<Type>()

template<typename T> static char const *get_base_type_as_string_(int index = 0);
#define get_base_type_as_string(Type)       get_base_type_as_string_<Type>()
#define get_base_type_as_string_index(Type, i) get_base_type_as_string_<Type>(i)

#define fuzzy_type_compare(A, B) fuzzy_type_compare_<A, B>()
template<typename T, typename U> bool fuzzy_type_compare_(void) {
    char const *a_str = TypeInfo<T>::name;
    char const *b_str = TypeInfo<U>::name;
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

enum Access {
    Access_unknown,
    Access_public,
    Access_private,
    Access_protected,

    Access_count,
};

#if defined(_MSC_VER)
    #define pp_sprintf(buf, size, format, ...) sprintf_s(buf, size, format, ##__VA_ARGS__)
#else
    #define pp_sprintf(buf, size, format, ...) sprintf(buf, format, ##__VA_ARGS__)
#endif

template<typename T>static size_t
serialize_primitive_(T *member_ptr, bool is_ptr, int arr_size, char const *name, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    char const *type_as_string = TypeInfo<T>::name;
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
    char indent_buf[256] = {};
    for(int i = 0; (i < indent); ++i) {indent_buf[i] = ' ';}

    bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%s%s %s", indent_buf, TypeInfo<T>::name, name);
    T &container = *(T *)member_ptr;
    for(auto &iter : container) {
        bytes_written = serialize_struct_((void *)&iter, "", TypeInfo<U>::name, indent, buffer, buf_size, bytes_written);
    }

    return(bytes_written);
}

template<typename T, typename U> static size_t offset_of(U T::*member) {
    return((char *)&((T *)0->*member) - (char *)0);
}

} // namespace pp

#define STATIC_GENERATED
#endif // !defined(STATIC_GENERATED_H)


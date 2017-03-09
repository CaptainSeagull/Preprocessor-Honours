#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

// Forward declared structs and enums (these must be declared outside the namespace...)
struct V2;
struct Test;
enum Letters : short;

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
    Type_Test,
}; }

#include "static_generated.h"
namespace pp { // PreProcessor

    // Recreated structs.
    struct _V2 {  _int x;  _int y;  };
    struct _Test {  _int *a;  _float f;  _V2 v;  };
//
// Meta type specialization
//

// struct void
template<> struct TypeInfo<void *> {
    using type = void *;
    using weak_type = void;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "void *";
    static constexpr char * const weak_name = "void";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<void **> {
    using type = void **;
    using weak_type = void;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "void **";
    static constexpr char * const weak_name = "void";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<void *&> {
    using type = void *&;
    using weak_type = void;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "void *&";
    static constexpr char * const weak_name = "void";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<void **&> {
    using type = void **&;
    using weak_type = void;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "void **&";
    static constexpr char * const weak_name = "void";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct char
template<> struct TypeInfo<char> {
    using type = char;
    using weak_type = char;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "char";
    static constexpr char * const weak_name = "char";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<char *> {
    using type = char *;
    using weak_type = char;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "char *";
    static constexpr char * const weak_name = "char";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<char **> {
    using type = char **;
    using weak_type = char;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "char **";
    static constexpr char * const weak_name = "char";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<char&> {
    using type = char&;
    using weak_type = char;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "char&";
    static constexpr char * const weak_name = "char";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<char *&> {
    using type = char *&;
    using weak_type = char;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "char *&";
    static constexpr char * const weak_name = "char";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<char **&> {
    using type = char **&;
    using weak_type = char;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "char **&";
    static constexpr char * const weak_name = "char";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct short
template<> struct TypeInfo<short> {
    using type = short;
    using weak_type = short;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "short";
    static constexpr char * const weak_name = "short";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<short *> {
    using type = short *;
    using weak_type = short;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "short *";
    static constexpr char * const weak_name = "short";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<short **> {
    using type = short **;
    using weak_type = short;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "short **";
    static constexpr char * const weak_name = "short";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<short&> {
    using type = short&;
    using weak_type = short;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "short&";
    static constexpr char * const weak_name = "short";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<short *&> {
    using type = short *&;
    using weak_type = short;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "short *&";
    static constexpr char * const weak_name = "short";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<short **&> {
    using type = short **&;
    using weak_type = short;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "short **&";
    static constexpr char * const weak_name = "short";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct int
template<> struct TypeInfo<int> {
    using type = int;
    using weak_type = int;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "int";
    static constexpr char * const weak_name = "int";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<int *> {
    using type = int *;
    using weak_type = int;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "int *";
    static constexpr char * const weak_name = "int";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<int **> {
    using type = int **;
    using weak_type = int;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "int **";
    static constexpr char * const weak_name = "int";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<int&> {
    using type = int&;
    using weak_type = int;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "int&";
    static constexpr char * const weak_name = "int";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<int *&> {
    using type = int *&;
    using weak_type = int;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "int *&";
    static constexpr char * const weak_name = "int";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<int **&> {
    using type = int **&;
    using weak_type = int;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "int **&";
    static constexpr char * const weak_name = "int";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct long
template<> struct TypeInfo<long> {
    using type = long;
    using weak_type = long;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "long";
    static constexpr char * const weak_name = "long";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<long *> {
    using type = long *;
    using weak_type = long;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "long *";
    static constexpr char * const weak_name = "long";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<long **> {
    using type = long **;
    using weak_type = long;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "long **";
    static constexpr char * const weak_name = "long";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<long&> {
    using type = long&;
    using weak_type = long;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "long&";
    static constexpr char * const weak_name = "long";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<long *&> {
    using type = long *&;
    using weak_type = long;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "long *&";
    static constexpr char * const weak_name = "long";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<long **&> {
    using type = long **&;
    using weak_type = long;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "long **&";
    static constexpr char * const weak_name = "long";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct float
template<> struct TypeInfo<float> {
    using type = float;
    using weak_type = float;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "float";
    static constexpr char * const weak_name = "float";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<float *> {
    using type = float *;
    using weak_type = float;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "float *";
    static constexpr char * const weak_name = "float";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<float **> {
    using type = float **;
    using weak_type = float;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "float **";
    static constexpr char * const weak_name = "float";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<float&> {
    using type = float&;
    using weak_type = float;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "float&";
    static constexpr char * const weak_name = "float";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<float *&> {
    using type = float *&;
    using weak_type = float;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "float *&";
    static constexpr char * const weak_name = "float";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<float **&> {
    using type = float **&;
    using weak_type = float;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "float **&";
    static constexpr char * const weak_name = "float";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct double
template<> struct TypeInfo<double> {
    using type = double;
    using weak_type = double;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "double";
    static constexpr char * const weak_name = "double";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<double *> {
    using type = double *;
    using weak_type = double;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "double *";
    static constexpr char * const weak_name = "double";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<double **> {
    using type = double **;
    using weak_type = double;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "double **";
    static constexpr char * const weak_name = "double";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<double&> {
    using type = double&;
    using weak_type = double;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "double&";
    static constexpr char * const weak_name = "double";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<double *&> {
    using type = double *&;
    using weak_type = double;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "double *&";
    static constexpr char * const weak_name = "double";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<double **&> {
    using type = double **&;
    using weak_type = double;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "double **&";
    static constexpr char * const weak_name = "double";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct bool
template<> struct TypeInfo<bool> {
    using type = bool;
    using weak_type = bool;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "bool";
    static constexpr char * const weak_name = "bool";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<bool *> {
    using type = bool *;
    using weak_type = bool;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "bool *";
    static constexpr char * const weak_name = "bool";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<bool **> {
    using type = bool **;
    using weak_type = bool;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "bool **";
    static constexpr char * const weak_name = "bool";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<bool&> {
    using type = bool&;
    using weak_type = bool;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "bool&";
    static constexpr char * const weak_name = "bool";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<bool *&> {
    using type = bool *&;
    using weak_type = bool;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "bool *&";
    static constexpr char * const weak_name = "bool";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<bool **&> {
    using type = bool **&;
    using weak_type = bool;
    using base = void;
    using members = std::tuple<void>;

    static constexpr char * const name = "bool **&";
    static constexpr char * const weak_name = "bool";

    static constexpr size_t member_count = 0;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = true;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = false;
};


// struct V2
template<> struct TypeInfo<V2> {
    using type = V2;
    using weak_type = V2;
    using base = void;
    using members = std::tuple<int, int>;

    static constexpr char * const name = "V2";
    static constexpr char * const weak_name = "V2";

    static constexpr size_t member_count = 2;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<V2 *> {
    using type = V2 *;
    using weak_type = V2;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "V2 *";
    static constexpr char * const weak_name = "V2";

    static constexpr size_t member_count = 2;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<V2 **> {
    using type = V2 **;
    using weak_type = V2;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "V2 **";
    static constexpr char * const weak_name = "V2";

    static constexpr size_t member_count = 2;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<V2&> {
    using type = V2&;
    using weak_type = V2;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "V2&";
    static constexpr char * const weak_name = "V2";

    static constexpr size_t member_count = 2;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<V2 *&> {
    using type = V2 *&;
    using weak_type = V2;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "V2 *&";
    static constexpr char * const weak_name = "V2";

    static constexpr size_t member_count = 2;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<V2 **&> {
    using type = V2 **&;
    using weak_type = V2;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "V2 **&";
    static constexpr char * const weak_name = "V2";

    static constexpr size_t member_count = 2;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};


// struct Test
template<> struct TypeInfo<Test> {
    using type = Test;
    using weak_type = Test;
    using base = void;
    using members = std::tuple<int *, float, V2>;

    static constexpr char * const name = "Test";
    static constexpr char * const weak_name = "Test";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<Test *> {
    using type = Test *;
    using weak_type = Test;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "Test *";
    static constexpr char * const weak_name = "Test";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<Test **> {
    using type = Test **;
    using weak_type = Test;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "Test **";
    static constexpr char * const weak_name = "Test";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<Test&> {
    using type = Test&;
    using weak_type = Test;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "Test&";
    static constexpr char * const weak_name = "Test";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<Test *&> {
    using type = Test *&;
    using weak_type = Test;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "Test *&";
    static constexpr char * const weak_name = "Test";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

template<> struct TypeInfo<Test **&> {
    using type = Test **&;
    using weak_type = Test;
    using base = void;
    using members = std::tuple<>;

    static constexpr char * const name = "Test **&";
    static constexpr char * const weak_name = "Test";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = true;
    static constexpr bool is_enum = false;
};

// enum Letters
template<> struct TypeInfo<Letters> {
    using type = Letters;
    using weak_type = Letters;
    using base = short;
    using members = std::tuple<void>;

    static constexpr char * const name = "Letters";
    static constexpr char * const weak_name = "Letters";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = true;
};

template<> struct TypeInfo<Letters *> {
    using type = Letters *;
    using weak_type = Letters;
    using base = short;
    using members = std::tuple<void>;

    static constexpr char * const name = "Letters *";
    static constexpr char * const weak_name = "Letters";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = true;
};

template<> struct TypeInfo<Letters **> {
    using type = Letters **;
    using weak_type = Letters;
    using base = short;
    using members = std::tuple<void>;

    static constexpr char * const name = "Letters **";
    static constexpr char * const weak_name = "Letters";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = false;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = true;
};

template<> struct TypeInfo<Letters&> {
    using type = Letters&;
    using weak_type = Letters;
    using base = short;
    using members = std::tuple<void>;

    static constexpr char * const name = "Letters&";
    static constexpr char * const weak_name = "Letters";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = false;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = true;
};

template<> struct TypeInfo<Letters *&> {
    using type = Letters *&;
    using weak_type = Letters;
    using base = short;
    using members = std::tuple<void>;

    static constexpr char * const name = "Letters *&";
    static constexpr char * const weak_name = "Letters";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = true;
};

template<> struct TypeInfo<Letters **&> {
    using type = Letters **&;
    using weak_type = Letters;
    using base = short;
    using members = std::tuple<void>;

    static constexpr char * const name = "Letters **&";
    static constexpr char * const weak_name = "Letters";

    static constexpr size_t member_count = 3;

    static constexpr bool is_ptr = true;
    static constexpr bool is_ref = true;
    static constexpr size_t base_count = 0;
    static constexpr bool is_primitive = false;
    static constexpr bool is_class = false;
    static constexpr bool is_enum = true;
};

// Get at index.
#define get_member(variable, Type, index) GetMember<Type, index>::get(&variable);
template<typename T, int index> struct GetMember {};

template<> struct GetMember<V2, 0> {
    static int *get(V2 *ptr) {
        _V2 *cpy = (_V2 *)ptr;
        int * res = (int *)&cpy->x;
        return(res);
    };
};
template<> struct GetMember<V2 &, 0> {
    static int *get(V2 *ptr) {
        _V2 *cpy = (_V2 *)ptr;
        int * res = (int *)&cpy->x;
        return(res);
    };
};
template<> struct GetMember<V2, 1> {
    static int *get(V2 *ptr) {
        _V2 *cpy = (_V2 *)ptr;
        int * res = (int *)&cpy->y;
        return(res);
    };
};
template<> struct GetMember<V2 &, 1> {
    static int *get(V2 *ptr) {
        _V2 *cpy = (_V2 *)ptr;
        int * res = (int *)&cpy->y;
        return(res);
    };
};

template<> struct GetMember<Test, 0> {
    static int * *get(Test *ptr) {
        _Test *cpy = (_Test *)ptr;
        int * * res = (int * *)&cpy->a;
        return(res);
    };
};
template<> struct GetMember<Test &, 0> {
    static int * *get(Test *ptr) {
        _Test *cpy = (_Test *)ptr;
        int * * res = (int * *)&cpy->a;
        return(res);
    };
};
template<> struct GetMember<Test, 1> {
    static float *get(Test *ptr) {
        _Test *cpy = (_Test *)ptr;
        float * res = (float *)&cpy->f;
        return(res);
    };
};
template<> struct GetMember<Test &, 1> {
    static float *get(Test *ptr) {
        _Test *cpy = (_Test *)ptr;
        float * res = (float *)&cpy->f;
        return(res);
    };
};
template<> struct GetMember<Test, 2> {
    static V2 *get(Test *ptr) {
        _Test *cpy = (_Test *)ptr;
        V2 * res = (V2 *)&cpy->v;
        return(res);
    };
};
template<> struct GetMember<Test &, 2> {
    static V2 *get(Test *ptr) {
        _Test *cpy = (_Test *)ptr;
        V2 * res = (V2 *)&cpy->v;
        return(res);
    };
};
static bool is_meta_type_container(int type) {
    if(type == Type_char) {return(false);} // false
    else if(type == Type_short) {return(false);} // false
    else if(type == Type_int) {return(false);} // false
    else if(type == Type_long) {return(false);} // false
    else if(type == Type_float) {return(false);} // false
    else if(type == Type_double) {return(false);} // false
    else if(type == Type_bool) {return(false);} // false
    else if(type == Type_V2) {return(false);} // false
    else if(type == Type_Test) {return(false);} // false

    // Should not be reached.
    assert(0);
    return(0);
}
static char const * meta_type_to_name(Type mt, bool is_ptr) {
    if(mt == Type_V2) {
        if(is_ptr) {return("V2 *");}
        else       {return("V2");  }
    } else if(mt == Type_Test) {
        if(is_ptr) {return("Test *");}
        else       {return("Test");  }
    }

    assert(0); 
    return(0); // Not found
}
static size_t get_size_from_str(char const *str) {

    if((strcmp(str, "V2") == 0) || (strcmp(str, "V2 *") == 0) || (strcmp(str, "V2 **") == 0)) {return(sizeof(_V2));}
    else if((strcmp(str, "Test") == 0) || (strcmp(str, "Test *") == 0) || (strcmp(str, "Test **") == 0)) {return(sizeof(_Test));}

    return(0); // Not found.
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
                        if(!member->arr_size) {
                            bytes_written = serialize_struct_(member_ptr, member->name, struct_name, indent, buffer, buf_size - bytes_written, bytes_written);
                        } else {
                            for(int j = 0; (j < member->arr_size); ++j) {
                                size_t size_of_struct = get_size_from_str(struct_name);

                                char unsigned *ptr;
                                if(member->is_ptr) {
                                    ptr = *(char unsigned **)((char unsigned *)member_ptr + (j * sizeof(size_t)));
                                } else {
                                    ptr = ((char unsigned *)member_ptr + (j * size_of_struct));
                                }

                                bytes_written = serialize_struct_(ptr, member->name, struct_name, indent, buffer, buf_size - bytes_written, bytes_written);
                            }
                        }
                    }
                } break; // default 
            }
        }
    }

    return(bytes_written);
}

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // V2
    if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            {Type_int, "x", offset_of(&_V2::x), false, 1},
            {Type_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // Test
    } else if(type_compare(T, Test)) {
        static MemberDefinition members_of_Test[] = {
            {Type_int, "a", offset_of(&_Test::a), true, 1},
            {Type_float, "f", offset_of(&_Test::f), false, 1},
            {Type_V2, "v", offset_of(&_Test::v), false, 1},
        };
        return(members_of_Test);
    }

    return(0); // Error.
}

// Convert a type into a members of pointer.
static MemberDefinition *get_members_of_str(char const *str) {
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
            {Type_int, "x", offset_of(&_V2::x), false, 1},
            {Type_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // Test
    } else if((strcmp(str, "Test") == 0) || (strcmp(str, "Test *") == 0) || (strcmp(str, "Test **") == 0)) {
        static MemberDefinition members_of_Test[] = {
            {Type_int, "a", offset_of(&_Test::a), true, 1},
            {Type_float, "f", offset_of(&_Test::f), false, 1},
            {Type_V2, "v", offset_of(&_Test::v), false, 1},
        };
        return(members_of_Test);
    }

    return(0); // Error.
}

// Get the number of members for a type.
static int get_number_of_members_str(char const *str) {
    if((strcmp(str, "char") == 0) || (strcmp(str, "char *") == 0) || (strcmp(str, "char **") == 0)) {return(1);}
    else if((strcmp(str, "short") == 0) || (strcmp(str, "short *") == 0) || (strcmp(str, "short **") == 0)) {return(1);}
    else if((strcmp(str, "int") == 0) || (strcmp(str, "int *") == 0) || (strcmp(str, "int **") == 0)) {return(1);}
    else if((strcmp(str, "long") == 0) || (strcmp(str, "long *") == 0) || (strcmp(str, "long **") == 0)) {return(1);}
    else if((strcmp(str, "float") == 0) || (strcmp(str, "float *") == 0) || (strcmp(str, "float **") == 0)) {return(1);}
    else if((strcmp(str, "double") == 0) || (strcmp(str, "double *") == 0) || (strcmp(str, "double **") == 0)) {return(1);}
    else if((strcmp(str, "bool") == 0) || (strcmp(str, "bool *") == 0) || (strcmp(str, "bool **") == 0)) {return(1);}
    else if((strcmp(str, "V2") == 0) || (strcmp(str, "V2 *") == 0) || (strcmp(str, "V2 **") == 0)) {return(2);}
    else if((strcmp(str, "Test") == 0) || (strcmp(str, "Test *") == 0) || (strcmp(str, "Test **") == 0)) {return(3);}

    return(-1); // Error.
}

//
// Enum Introspection data.
//

// Stub functions.
template<typename T>static char const *enum_to_string(T element) { return(0); }
template<typename T>static T string_to_enum(char const *str) { return(0); }

// Letters.
template<>char const *enum_to_string<Letters>(Letters element) {
    short index = (short)element;
    switch(index) {
        case 0:  { return("a"); } break;
        case 1:  { return("b"); } break;
        case 2:  { return("c"); } break;

        default: { return(0); } break;
    }
}
template<>Letters string_to_enum<Letters>(char const *str) {
    short res = {};
    if(strcmp(str, "a") == 0) { res = 0; }
    if(strcmp(str, "b") == 0) { res = 1; }
    if(strcmp(str, "c") == 0) { res = 2; }

    return (Letters)res;
}

#define weak_type_compare(A, B) TypeCompare_<pp::Type<A>::weak_type, pp::Type<B>::weak_type>::e;
#undef _std // :(
} // namespace pp

#endif // Header guard.


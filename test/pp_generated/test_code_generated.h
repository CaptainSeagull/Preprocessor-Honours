#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

// Forward declared structs (these must be declared outside the namespace...)
struct Test;
union V2;
struct A;
struct B;
struct Foo;
struct V3;
struct VectorTest;
struct StringTest;

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
    Type_Test,
    Type_V2,
    Type_A,
    Type_B,
    Type_Foo,
    Type_V3,
    Type_VectorTest,
    Type_std_vector_float,
    Type_std_vector_int,
    Type_std_vector_V3,
    Type_std_deque_int,
    Type_std_forward_list_int,
    Type_std_list_int,
    Type_StringTest,
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

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<char> operator=(TypeInfo<char> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<char>::name = "char";
char * const TypeInfo<char>::weak_name = "char";

template<> struct TypeInfo<char *> {
    using type = char *;
    using weak_type = char;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<char *> operator=(TypeInfo<char *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<char *>::name = "char *";
char * const TypeInfo<char *>::weak_name = "char";

template<> struct TypeInfo<char **> {
    using type = char **;
    using weak_type = char;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<char **> operator=(TypeInfo<char **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<char **>::name = "char **";
char * const TypeInfo<char **>::weak_name = "char";


// short
template<> struct TypeInfo<short> {
    using type = short;
    using weak_type = short;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<short> operator=(TypeInfo<short> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<short>::name = "short";
char * const TypeInfo<short>::weak_name = "short";

template<> struct TypeInfo<short *> {
    using type = short *;
    using weak_type = short;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<short *> operator=(TypeInfo<short *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<short *>::name = "short *";
char * const TypeInfo<short *>::weak_name = "short";

template<> struct TypeInfo<short **> {
    using type = short **;
    using weak_type = short;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<short **> operator=(TypeInfo<short **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<short **>::name = "short **";
char * const TypeInfo<short **>::weak_name = "short";


// int
template<> struct TypeInfo<int> {
    using type = int;
    using weak_type = int;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<int> operator=(TypeInfo<int> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<int>::name = "int";
char * const TypeInfo<int>::weak_name = "int";

template<> struct TypeInfo<int *> {
    using type = int *;
    using weak_type = int;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<int *> operator=(TypeInfo<int *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<int *>::name = "int *";
char * const TypeInfo<int *>::weak_name = "int";

template<> struct TypeInfo<int **> {
    using type = int **;
    using weak_type = int;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<int **> operator=(TypeInfo<int **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<int **>::name = "int **";
char * const TypeInfo<int **>::weak_name = "int";


// long
template<> struct TypeInfo<long> {
    using type = long;
    using weak_type = long;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<long> operator=(TypeInfo<long> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<long>::name = "long";
char * const TypeInfo<long>::weak_name = "long";

template<> struct TypeInfo<long *> {
    using type = long *;
    using weak_type = long;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<long *> operator=(TypeInfo<long *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<long *>::name = "long *";
char * const TypeInfo<long *>::weak_name = "long";

template<> struct TypeInfo<long **> {
    using type = long **;
    using weak_type = long;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<long **> operator=(TypeInfo<long **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<long **>::name = "long **";
char * const TypeInfo<long **>::weak_name = "long";


// float
template<> struct TypeInfo<float> {
    using type = float;
    using weak_type = float;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<float> operator=(TypeInfo<float> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<float>::name = "float";
char * const TypeInfo<float>::weak_name = "float";

template<> struct TypeInfo<float *> {
    using type = float *;
    using weak_type = float;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<float *> operator=(TypeInfo<float *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<float *>::name = "float *";
char * const TypeInfo<float *>::weak_name = "float";

template<> struct TypeInfo<float **> {
    using type = float **;
    using weak_type = float;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<float **> operator=(TypeInfo<float **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<float **>::name = "float **";
char * const TypeInfo<float **>::weak_name = "float";


// double
template<> struct TypeInfo<double> {
    using type = double;
    using weak_type = double;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<double> operator=(TypeInfo<double> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<double>::name = "double";
char * const TypeInfo<double>::weak_name = "double";

template<> struct TypeInfo<double *> {
    using type = double *;
    using weak_type = double;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<double *> operator=(TypeInfo<double *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<double *>::name = "double *";
char * const TypeInfo<double *>::weak_name = "double";

template<> struct TypeInfo<double **> {
    using type = double **;
    using weak_type = double;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<double **> operator=(TypeInfo<double **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<double **>::name = "double **";
char * const TypeInfo<double **>::weak_name = "double";


// bool
template<> struct TypeInfo<bool> {
    using type = bool;
    using weak_type = bool;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<bool> operator=(TypeInfo<bool> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<bool>::name = "bool";
char * const TypeInfo<bool>::weak_name = "bool";

template<> struct TypeInfo<bool *> {
    using type = bool *;
    using weak_type = bool;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<bool *> operator=(TypeInfo<bool *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<bool *>::name = "bool *";
char * const TypeInfo<bool *>::weak_name = "bool";

template<> struct TypeInfo<bool **> {
    using type = bool **;
    using weak_type = bool;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<bool **> operator=(TypeInfo<bool **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<bool **>::name = "bool **";
char * const TypeInfo<bool **>::weak_name = "bool";


// Test
template<> struct TypeInfo<Test> {
    using type = Test;
    using weak_type = Test;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<Test> operator=(TypeInfo<Test> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<Test>::name = "Test";
char * const TypeInfo<Test>::weak_name = "Test";

template<> struct TypeInfo<Test *> {
    using type = Test *;
    using weak_type = Test;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Test *> operator=(TypeInfo<Test *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<Test *>::name = "Test *";
char * const TypeInfo<Test *>::weak_name = "Test";

template<> struct TypeInfo<Test **> {
    using type = Test **;
    using weak_type = Test;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 2;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<Test **> operator=(TypeInfo<Test **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<Test **>::name = "Test **";
char * const TypeInfo<Test **>::weak_name = "Test";


// V2
template<> struct TypeInfo<V2> {
    using type = V2;
    using weak_type = V2;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<V2> operator=(TypeInfo<V2> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<V2>::name = "V2";
char * const TypeInfo<V2>::weak_name = "V2";

template<> struct TypeInfo<V2 *> {
    using type = V2 *;
    using weak_type = V2;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<V2 *> operator=(TypeInfo<V2 *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<V2 *>::name = "V2 *";
char * const TypeInfo<V2 *>::weak_name = "V2";

template<> struct TypeInfo<V2 **> {
    using type = V2 **;
    using weak_type = V2;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<V2 **> operator=(TypeInfo<V2 **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<V2 **>::name = "V2 **";
char * const TypeInfo<V2 **>::weak_name = "V2";


// A
template<> struct TypeInfo<A> {
    using type = A;
    using weak_type = A;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<A> operator=(TypeInfo<A> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<A>::name = "A";
char * const TypeInfo<A>::weak_name = "A";

template<> struct TypeInfo<A *> {
    using type = A *;
    using weak_type = A;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<A *> operator=(TypeInfo<A *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<A *>::name = "A *";
char * const TypeInfo<A *>::weak_name = "A";

template<> struct TypeInfo<A **> {
    using type = A **;
    using weak_type = A;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<A **> operator=(TypeInfo<A **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<A **>::name = "A **";
char * const TypeInfo<A **>::weak_name = "A";


// B
template<> struct TypeInfo<B> {
    using type = B;
    using weak_type = B;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<B> operator=(TypeInfo<B> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<B>::name = "B";
char * const TypeInfo<B>::weak_name = "B";

template<> struct TypeInfo<B *> {
    using type = B *;
    using weak_type = B;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<B *> operator=(TypeInfo<B *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<B *>::name = "B *";
char * const TypeInfo<B *>::weak_name = "B";

template<> struct TypeInfo<B **> {
    using type = B **;
    using weak_type = B;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 1;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<B **> operator=(TypeInfo<B **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<B **>::name = "B **";
char * const TypeInfo<B **>::weak_name = "B";


// Foo
template<> struct TypeInfo<Foo> {
    using type = Foo;
    using weak_type = Foo;
    using base = A;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 8;

    static bool const is_ptr = false;
    static size_t const base_count = 2;

    TypeInfo<Foo> operator=(TypeInfo<Foo> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<Foo>::name = "Foo";
char * const TypeInfo<Foo>::weak_name = "Foo";

template<> struct TypeInfo<Foo *> {
    using type = Foo *;
    using weak_type = Foo;
    using base = A;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 8;

    static bool const is_ptr = true;
    static size_t const base_count = 2;

    TypeInfo<Foo *> operator=(TypeInfo<Foo *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<Foo *>::name = "Foo *";
char * const TypeInfo<Foo *>::weak_name = "Foo";

template<> struct TypeInfo<Foo **> {
    using type = Foo **;
    using weak_type = Foo;
    using base = A;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 8;

    static bool const is_ptr = true;
    static size_t const base_count = 2;

    TypeInfo<Foo **> operator=(TypeInfo<Foo **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<Foo **>::name = "Foo **";
char * const TypeInfo<Foo **>::weak_name = "Foo";


// V3
template<> struct TypeInfo<V3> {
    using type = V3;
    using weak_type = V3;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<V3> operator=(TypeInfo<V3> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<V3>::name = "V3";
char * const TypeInfo<V3>::weak_name = "V3";

template<> struct TypeInfo<V3 *> {
    using type = V3 *;
    using weak_type = V3;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<V3 *> operator=(TypeInfo<V3 *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<V3 *>::name = "V3 *";
char * const TypeInfo<V3 *>::weak_name = "V3";

template<> struct TypeInfo<V3 **> {
    using type = V3 **;
    using weak_type = V3;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 3;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<V3 **> operator=(TypeInfo<V3 **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<V3 **>::name = "V3 **";
char * const TypeInfo<V3 **>::weak_name = "V3";


// VectorTest
template<> struct TypeInfo<VectorTest> {
    using type = VectorTest;
    using weak_type = VectorTest;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 6;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<VectorTest> operator=(TypeInfo<VectorTest> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<VectorTest>::name = "VectorTest";
char * const TypeInfo<VectorTest>::weak_name = "VectorTest";

template<> struct TypeInfo<VectorTest *> {
    using type = VectorTest *;
    using weak_type = VectorTest;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 6;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<VectorTest *> operator=(TypeInfo<VectorTest *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<VectorTest *>::name = "VectorTest *";
char * const TypeInfo<VectorTest *>::weak_name = "VectorTest";

template<> struct TypeInfo<VectorTest **> {
    using type = VectorTest **;
    using weak_type = VectorTest;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 6;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<VectorTest **> operator=(TypeInfo<VectorTest **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<VectorTest **>::name = "VectorTest **";
char * const TypeInfo<VectorTest **>::weak_name = "VectorTest";


// std::vector<float>
template<> struct TypeInfo<std::vector<float>> {
    using type = std::vector<float>;
    using weak_type = std::vector<float>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<std::vector<float>> operator=(TypeInfo<std::vector<float>> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<float>>::name = "std::vector<float>";
char * const TypeInfo<std::vector<float>>::weak_name = "std::vector<float>";

template<> struct TypeInfo<std::vector<float> *> {
    using type = std::vector<float> *;
    using weak_type = std::vector<float>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::vector<float> *> operator=(TypeInfo<std::vector<float> *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<float> *>::name = "std::vector<float> *";
char * const TypeInfo<std::vector<float> *>::weak_name = "std::vector<float>";

template<> struct TypeInfo<std::vector<float> **> {
    using type = std::vector<float> **;
    using weak_type = std::vector<float>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::vector<float> **> operator=(TypeInfo<std::vector<float> **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<float> **>::name = "std::vector<float> **";
char * const TypeInfo<std::vector<float> **>::weak_name = "std::vector<float>";


// std::vector<int>
template<> struct TypeInfo<std::vector<int>> {
    using type = std::vector<int>;
    using weak_type = std::vector<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<std::vector<int>> operator=(TypeInfo<std::vector<int>> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<int>>::name = "std::vector<int>";
char * const TypeInfo<std::vector<int>>::weak_name = "std::vector<int>";

template<> struct TypeInfo<std::vector<int> *> {
    using type = std::vector<int> *;
    using weak_type = std::vector<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::vector<int> *> operator=(TypeInfo<std::vector<int> *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<int> *>::name = "std::vector<int> *";
char * const TypeInfo<std::vector<int> *>::weak_name = "std::vector<int>";

template<> struct TypeInfo<std::vector<int> **> {
    using type = std::vector<int> **;
    using weak_type = std::vector<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::vector<int> **> operator=(TypeInfo<std::vector<int> **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<int> **>::name = "std::vector<int> **";
char * const TypeInfo<std::vector<int> **>::weak_name = "std::vector<int>";


// std::vector<V3>
template<> struct TypeInfo<std::vector<V3>> {
    using type = std::vector<V3>;
    using weak_type = std::vector<V3>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<std::vector<V3>> operator=(TypeInfo<std::vector<V3>> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<V3>>::name = "std::vector<V3>";
char * const TypeInfo<std::vector<V3>>::weak_name = "std::vector<V3>";

template<> struct TypeInfo<std::vector<V3> *> {
    using type = std::vector<V3> *;
    using weak_type = std::vector<V3>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::vector<V3> *> operator=(TypeInfo<std::vector<V3> *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<V3> *>::name = "std::vector<V3> *";
char * const TypeInfo<std::vector<V3> *>::weak_name = "std::vector<V3>";

template<> struct TypeInfo<std::vector<V3> **> {
    using type = std::vector<V3> **;
    using weak_type = std::vector<V3>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::vector<V3> **> operator=(TypeInfo<std::vector<V3> **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::vector<V3> **>::name = "std::vector<V3> **";
char * const TypeInfo<std::vector<V3> **>::weak_name = "std::vector<V3>";


// std::deque<int>
template<> struct TypeInfo<std::deque<int>> {
    using type = std::deque<int>;
    using weak_type = std::deque<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<std::deque<int>> operator=(TypeInfo<std::deque<int>> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::deque<int>>::name = "std::deque<int>";
char * const TypeInfo<std::deque<int>>::weak_name = "std::deque<int>";

template<> struct TypeInfo<std::deque<int> *> {
    using type = std::deque<int> *;
    using weak_type = std::deque<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::deque<int> *> operator=(TypeInfo<std::deque<int> *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::deque<int> *>::name = "std::deque<int> *";
char * const TypeInfo<std::deque<int> *>::weak_name = "std::deque<int>";

template<> struct TypeInfo<std::deque<int> **> {
    using type = std::deque<int> **;
    using weak_type = std::deque<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::deque<int> **> operator=(TypeInfo<std::deque<int> **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::deque<int> **>::name = "std::deque<int> **";
char * const TypeInfo<std::deque<int> **>::weak_name = "std::deque<int>";


// std::forward_list<int>
template<> struct TypeInfo<std::forward_list<int>> {
    using type = std::forward_list<int>;
    using weak_type = std::forward_list<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<std::forward_list<int>> operator=(TypeInfo<std::forward_list<int>> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::forward_list<int>>::name = "std::forward_list<int>";
char * const TypeInfo<std::forward_list<int>>::weak_name = "std::forward_list<int>";

template<> struct TypeInfo<std::forward_list<int> *> {
    using type = std::forward_list<int> *;
    using weak_type = std::forward_list<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::forward_list<int> *> operator=(TypeInfo<std::forward_list<int> *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::forward_list<int> *>::name = "std::forward_list<int> *";
char * const TypeInfo<std::forward_list<int> *>::weak_name = "std::forward_list<int>";

template<> struct TypeInfo<std::forward_list<int> **> {
    using type = std::forward_list<int> **;
    using weak_type = std::forward_list<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::forward_list<int> **> operator=(TypeInfo<std::forward_list<int> **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::forward_list<int> **>::name = "std::forward_list<int> **";
char * const TypeInfo<std::forward_list<int> **>::weak_name = "std::forward_list<int>";


// std::list<int>
template<> struct TypeInfo<std::list<int>> {
    using type = std::list<int>;
    using weak_type = std::list<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<std::list<int>> operator=(TypeInfo<std::list<int>> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::list<int>>::name = "std::list<int>";
char * const TypeInfo<std::list<int>>::weak_name = "std::list<int>";

template<> struct TypeInfo<std::list<int> *> {
    using type = std::list<int> *;
    using weak_type = std::list<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::list<int> *> operator=(TypeInfo<std::list<int> *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::list<int> *>::name = "std::list<int> *";
char * const TypeInfo<std::list<int> *>::weak_name = "std::list<int>";

template<> struct TypeInfo<std::list<int> **> {
    using type = std::list<int> **;
    using weak_type = std::list<int>;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 0;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<std::list<int> **> operator=(TypeInfo<std::list<int> **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<std::list<int> **>::name = "std::list<int> **";
char * const TypeInfo<std::list<int> **>::weak_name = "std::list<int>";


// StringTest
template<> struct TypeInfo<StringTest> {
    using type = StringTest;
    using weak_type = StringTest;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 4;

    static bool const is_ptr = false;
    static size_t const base_count = 0;

    TypeInfo<StringTest> operator=(TypeInfo<StringTest> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<StringTest>::name = "StringTest";
char * const TypeInfo<StringTest>::weak_name = "StringTest";

template<> struct TypeInfo<StringTest *> {
    using type = StringTest *;
    using weak_type = StringTest;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 4;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<StringTest *> operator=(TypeInfo<StringTest *> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<StringTest *>::name = "StringTest *";
char * const TypeInfo<StringTest *>::weak_name = "StringTest";

template<> struct TypeInfo<StringTest **> {
    using type = StringTest **;
    using weak_type = StringTest;
    using base = void;

    static char * const name;
    static char * const weak_name;

    static size_t const member_count = 4;

    static bool const is_ptr = true;
    static size_t const base_count = 0;

    TypeInfo<StringTest **> operator=(TypeInfo<StringTest **> a) = delete; // To avoid warning 4512 in MSVC.
};

char * const TypeInfo<StringTest **>::name = "StringTest **";
char * const TypeInfo<StringTest **>::weak_name = "StringTest";

static bool is_meta_type_container(int type) {
    if(type == Type_char) {return(false);} // false
    else if(type == Type_short) {return(false);} // false
    else if(type == Type_int) {return(false);} // false
    else if(type == Type_long) {return(false);} // false
    else if(type == Type_float) {return(false);} // false
    else if(type == Type_double) {return(false);} // false
    else if(type == Type_bool) {return(false);} // false
    else if(type == Type_Test) {return(false);} // false
    else if(type == Type_V2) {return(false);} // false
    else if(type == Type_A) {return(false);} // false
    else if(type == Type_B) {return(false);} // false
    else if(type == Type_Foo) {return(false);} // false
    else if(type == Type_V3) {return(false);} // false
    else if(type == Type_VectorTest) {return(false);} // false
    else if(type == Type_std_vector_float) {return(true);} // true
    else if(type == Type_std_vector_int) {return(true);} // true
    else if(type == Type_std_vector_V3) {return(true);} // true
    else if(type == Type_std_deque_int) {return(true);} // true
    else if(type == Type_std_forward_list_int) {return(true);} // true
    else if(type == Type_std_list_int) {return(true);} // true
    else if(type == Type_StringTest) {return(false);} // false

    // Should not be reached.
    assert(0);
    return(0);
}
static char const * meta_type_to_name(Type mt, bool is_ptr) {
    if(mt == Type_Test) {
        if(is_ptr) {return("Test *");}
        else       {return("Test");  }
    } else if(mt == Type_V2) {
        if(is_ptr) {return("V2 *");}
        else       {return("V2");  }
    } else if(mt == Type_A) {
        if(is_ptr) {return("A *");}
        else       {return("A");  }
    } else if(mt == Type_B) {
        if(is_ptr) {return("B *");}
        else       {return("B");  }
    } else if(mt == Type_Foo) {
        if(is_ptr) {return("Foo *");}
        else       {return("Foo");  }
    } else if(mt == Type_V3) {
        if(is_ptr) {return("V3 *");}
        else       {return("V3");  }
    } else if(mt == Type_VectorTest) {
        if(is_ptr) {return("VectorTest *");}
        else       {return("VectorTest");  }
    } else if(mt == Type_StringTest) {
        if(is_ptr) {return("StringTest *");}
        else       {return("StringTest");  }
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
                        if(member->type == Type_std_vector_float) {bytes_written = serialize_container<std::vector<float>, float>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == Type_std_vector_int) {bytes_written = serialize_container<std::vector<int>, int>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == Type_std_vector_V3) {bytes_written = serialize_container<std::vector<V3>, V3>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == Type_std_deque_int) {bytes_written = serialize_container<std::deque<int>, int>(member_ptr, name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == Type_std_forward_list_int) {bytes_written = serialize_container<std::forward_list<int>, int>(member_ptr, name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == Type_std_list_int) {bytes_written = serialize_container<std::list<int>, int>(member_ptr, name, indent, buffer, buf_size, bytes_written);}

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
    struct _Test {  _int i;  _int *j;  };
    union _V2 {  _int e[2];  struct { _int x;  _int y;  }; };
    struct _A {  _int a;  };
    struct _B {  _double b;  };
    struct _Foo : public _A, public _B {  _char *str;  _int *int_ptr;  _float *float_ptr;  _bool *bool_ptr;  _int int_array[4];  _double *double_ptr_array[5];  _int *int_ptr_array[6];  _V2 v2;  };
    struct _V3 {  _int x;  _int y;  _int z;  };
    struct _VectorTest {  _std::vector<float> vec_floating;  _std::vector<int> vec_integer;  _std::vector<V3> vec_vector3;  _std::deque<int> deque_int;  _std::forward_list<int> fl_int;  _std::list<int> list_int;  };
    struct _StringTest {  _float *ptr;  _char *text;  _int len;  _int some_array[5];  };
    // Test
    if(type_compare(T, Test)) {
        static MemberDefinition members_of_Test[] = {
            {Type_int, "i", offset_of(&_Test::i), false, 1},
            {Type_int, "j", offset_of(&_Test::j), true, 1},
        };
        return(members_of_Test);

    // V2
    } else if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            {Type_int, "e", offset_of(&_V2::e), false, 2},
            {Type_int, "x", offset_of(&_V2::x), false, 1},
            {Type_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // A
    } else if(type_compare(T, A)) {
        static MemberDefinition members_of_A[] = {
            {Type_int, "a", offset_of(&_A::a), false, 1},
        };
        return(members_of_A);

    // B
    } else if(type_compare(T, B)) {
        static MemberDefinition members_of_B[] = {
            {Type_double, "b", offset_of(&_B::b), false, 1},
        };
        return(members_of_B);

    // Foo
    } else if(type_compare(T, Foo)) {
        static MemberDefinition members_of_Foo[] = {
            {Type_char, "str", offset_of(&_Foo::str), true, 1},
            {Type_int, "int_ptr", offset_of(&_Foo::int_ptr), true, 1},
            {Type_float, "float_ptr", offset_of(&_Foo::float_ptr), true, 1},
            {Type_bool, "bool_ptr", offset_of(&_Foo::bool_ptr), true, 1},
            {Type_int, "int_array", offset_of(&_Foo::int_array), false, 4},
            {Type_double, "double_ptr_array", offset_of(&_Foo::double_ptr_array), true, 5},
            {Type_int, "int_ptr_array", offset_of(&_Foo::int_ptr_array), true, 6},
            {Type_V2, "v2", offset_of(&_Foo::v2), false, 1},
            // Members inherited from A.
            {Type_int, "a", (size_t)&((_Foo *)0)->a, false, 1},
            // Members inherited from B.
            {Type_double, "b", (size_t)&((_Foo *)0)->b, false, 1},
        };
        return(members_of_Foo);

    // V3
    } else if(type_compare(T, V3)) {
        static MemberDefinition members_of_V3[] = {
            {Type_int, "x", offset_of(&_V3::x), false, 1},
            {Type_int, "y", offset_of(&_V3::y), false, 1},
            {Type_int, "z", offset_of(&_V3::z), false, 1},
        };
        return(members_of_V3);

    // VectorTest
    } else if(type_compare(T, VectorTest)) {
        static MemberDefinition members_of_VectorTest[] = {
            {Type_std_vector_float, "vec_floating", offset_of(&_VectorTest::vec_floating), false, 1},
            {Type_std_vector_int, "vec_integer", offset_of(&_VectorTest::vec_integer), false, 1},
            {Type_std_vector_V3, "vec_vector3", offset_of(&_VectorTest::vec_vector3), false, 1},
            {Type_std_deque_int, "deque_int", offset_of(&_VectorTest::deque_int), false, 1},
            {Type_std_forward_list_int, "fl_int", offset_of(&_VectorTest::fl_int), false, 1},
            {Type_std_list_int, "list_int", offset_of(&_VectorTest::list_int), false, 1},
        };
        return(members_of_VectorTest);

    // StringTest
    } else if(type_compare(T, StringTest)) {
        static MemberDefinition members_of_StringTest[] = {
            {Type_float, "ptr", offset_of(&_StringTest::ptr), true, 1},
            {Type_char, "text", offset_of(&_StringTest::text), true, 1},
            {Type_int, "len", offset_of(&_StringTest::len), false, 1},
            {Type_int, "some_array", offset_of(&_StringTest::some_array), false, 5},
        };
        return(members_of_StringTest);
    }

    return(0); // Error.
}

// Convert a type into a members of pointer.
static MemberDefinition *get_members_of_str(char const *str) {
    // Recreated structs.
    struct _Test {  _int i;  _int *j;  };
    union _V2 {  _int e[2];  struct { _int x;  _int y;  }; };
    struct _A {  _int a;  };
    struct _B {  _double b;  };
    struct _Foo : public _A, public _B {  _char *str;  _int *int_ptr;  _float *float_ptr;  _bool *bool_ptr;  _int int_array[4];  _double *double_ptr_array[5];  _int *int_ptr_array[6];  _V2 v2;  };
    struct _V3 {  _int x;  _int y;  _int z;  };
    struct _VectorTest {  _std::vector<float> vec_floating;  _std::vector<int> vec_integer;  _std::vector<V3> vec_vector3;  _std::deque<int> deque_int;  _std::forward_list<int> fl_int;  _std::list<int> list_int;  };
    struct _StringTest {  _float *ptr;  _char *text;  _int len;  _int some_array[5];  };
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


    // Test
    } else if((strcmp(str, "Test") == 0) || (strcmp(str, "Test *") == 0) || (strcmp(str, "Test **") == 0)) {
        static MemberDefinition members_of_Test[] = {
            {Type_int, "i", offset_of(&_Test::i), false, 1},
            {Type_int, "j", offset_of(&_Test::j), true, 1},
        };
        return(members_of_Test);

    // V2
    } else if((strcmp(str, "V2") == 0) || (strcmp(str, "V2 *") == 0) || (strcmp(str, "V2 **") == 0)) {
        static MemberDefinition members_of_V2[] = {
            {Type_int, "e", offset_of(&_V2::e), false, 2},
            {Type_int, "x", offset_of(&_V2::x), false, 1},
            {Type_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // A
    } else if((strcmp(str, "A") == 0) || (strcmp(str, "A *") == 0) || (strcmp(str, "A **") == 0)) {
        static MemberDefinition members_of_A[] = {
            {Type_int, "a", offset_of(&_A::a), false, 1},
        };
        return(members_of_A);

    // B
    } else if((strcmp(str, "B") == 0) || (strcmp(str, "B *") == 0) || (strcmp(str, "B **") == 0)) {
        static MemberDefinition members_of_B[] = {
            {Type_double, "b", offset_of(&_B::b), false, 1},
        };
        return(members_of_B);

    // Foo
    } else if((strcmp(str, "Foo") == 0) || (strcmp(str, "Foo *") == 0) || (strcmp(str, "Foo **") == 0)) {
        static MemberDefinition members_of_Foo[] = {
            {Type_char, "str", offset_of(&_Foo::str), true, 1},
            {Type_int, "int_ptr", offset_of(&_Foo::int_ptr), true, 1},
            {Type_float, "float_ptr", offset_of(&_Foo::float_ptr), true, 1},
            {Type_bool, "bool_ptr", offset_of(&_Foo::bool_ptr), true, 1},
            {Type_int, "int_array", offset_of(&_Foo::int_array), false, 4},
            {Type_double, "double_ptr_array", offset_of(&_Foo::double_ptr_array), true, 5},
            {Type_int, "int_ptr_array", offset_of(&_Foo::int_ptr_array), true, 6},
            {Type_V2, "v2", offset_of(&_Foo::v2), false, 1},
            // Members inherited from A.
            {Type_int, "a", (size_t)&((_Foo *)0)->a, false, 1},
            // Members inherited from B.
            {Type_double, "b", (size_t)&((_Foo *)0)->b, false, 1},
        };
        return(members_of_Foo);

    // V3
    } else if((strcmp(str, "V3") == 0) || (strcmp(str, "V3 *") == 0) || (strcmp(str, "V3 **") == 0)) {
        static MemberDefinition members_of_V3[] = {
            {Type_int, "x", offset_of(&_V3::x), false, 1},
            {Type_int, "y", offset_of(&_V3::y), false, 1},
            {Type_int, "z", offset_of(&_V3::z), false, 1},
        };
        return(members_of_V3);

    // VectorTest
    } else if((strcmp(str, "VectorTest") == 0) || (strcmp(str, "VectorTest *") == 0) || (strcmp(str, "VectorTest **") == 0)) {
        static MemberDefinition members_of_VectorTest[] = {
            {Type_std_vector_float, "vec_floating", offset_of(&_VectorTest::vec_floating), false, 1},
            {Type_std_vector_int, "vec_integer", offset_of(&_VectorTest::vec_integer), false, 1},
            {Type_std_vector_V3, "vec_vector3", offset_of(&_VectorTest::vec_vector3), false, 1},
            {Type_std_deque_int, "deque_int", offset_of(&_VectorTest::deque_int), false, 1},
            {Type_std_forward_list_int, "fl_int", offset_of(&_VectorTest::fl_int), false, 1},
            {Type_std_list_int, "list_int", offset_of(&_VectorTest::list_int), false, 1},
        };
        return(members_of_VectorTest);

    // StringTest
    } else if((strcmp(str, "StringTest") == 0) || (strcmp(str, "StringTest *") == 0) || (strcmp(str, "StringTest **") == 0)) {
        static MemberDefinition members_of_StringTest[] = {
            {Type_float, "ptr", offset_of(&_StringTest::ptr), true, 1},
            {Type_char, "text", offset_of(&_StringTest::text), true, 1},
            {Type_int, "len", offset_of(&_StringTest::len), false, 1},
            {Type_int, "some_array", offset_of(&_StringTest::some_array), false, 5},
        };
        return(members_of_StringTest);
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
    else if(strcmp(str, "Test") == 0) {return(2);} // Test
    else if(strcmp(str, "V2") == 0) {return(3);} // V2
    else if(strcmp(str, "A") == 0) {return(1);} // A
    else if(strcmp(str, "B") == 0) {return(1);} // B
    else if(strcmp(str, "Foo") == 0) {return(10);} // Foo
    else if(strcmp(str, "V3") == 0) {return(3);} // V3
    else if(strcmp(str, "VectorTest") == 0) {return(6);} // VectorTest
    else if(strcmp(str, "StringTest") == 0) {return(4);} // StringTest

    return(-1); // Error.
}

//
// Enum meta data.
//

// Meta Data for Letters.
static int const number_of_elements_in_enum_Letters = 3;
static char const *enum_to_string_Letters(int v) {
    switch(v) {
        case 0: {return("letter_a");} break;
        case 1: {return("letter_b");} break;
        case 2: {return("letter_c");} break;
    }

    return(0); // v is out of bounds.
}
static int string_to_enum_Letters(char const *str) {
    if(str) {
        if(strcmp(str, "letter_a") == 0) {return(0);}
        else if(strcmp(str, "letter_b") == 0) {return(1);}
        else if(strcmp(str, "letter_c") == 0) {return(2);}
    }

    return(0);  // str didn't match.
}

#define weak_type_compare(A, B) TypeCompare_<pp::Type<A>::weak_type, pp::Type<B>::weak_type>::e;
#undef _std // :(
} // namespace pp

#endif // Header guard.


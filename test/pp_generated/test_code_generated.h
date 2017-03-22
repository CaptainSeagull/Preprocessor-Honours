#if !defined(TEST_CODE_GENERATED_H)
#define TEST_CODE_GENERATED_H

// Forward declared structs, enums, and function (these must be declared outside the namespace...)
class Person;
class Student;

// This is nessessary due to the way the generated code is outputted. Is #undef'd at the bottom of this file.
#define _std std


// Enum with field for every type detected.
namespace pp { enum Type {
    Type_char,
    Type_short,
    Type_int,
    Type_long,
    Type_float,
    Type_double,
    Type_bool,
    Type_Person,
    Type_std_string_char,
    Type_Student,
}; }

#include "static_generated.h"
namespace pp { // PreProcessor

// Recreated Enums.
// Recreated structs.
struct _Person {  _std::string name;  _int age;  _std::string city;  _char gender;  };
struct _Student : public _Person {  _std::string major;  _std::string minor;  };
//
// Meta type specialization
//

// struct void
template<> class TypeInfo<void> {
public:
    using type      = void;
    using weak_type = void;
    using base      = void;

    static constexpr char const * const name      = "void";
    static constexpr char const * const weak_name = "void";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<void*> {
public:
    using type      = void*;
    using weak_type = void;
    using base      = void;

    static constexpr char const * const name      = "void*";
    static constexpr char const * const weak_name = "void";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<void**> {
public:
    using type      = void**;
    using weak_type = void;
    using base      = void;

    static constexpr char const * const name      = "void**";
    static constexpr char const * const weak_name = "void";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<void***> {
public:
    using type      = void***;
    using weak_type = void;
    using base      = void;

    static constexpr char const * const name      = "void***";
    static constexpr char const * const weak_name = "void";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct char
template<> class TypeInfo<char> {
public:
    using type      = char;
    using weak_type = char;
    using base      = void;

    static constexpr char const * const name      = "char";
    static constexpr char const * const weak_name = "char";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<char*> {
public:
    using type      = char*;
    using weak_type = char;
    using base      = void;

    static constexpr char const * const name      = "char*";
    static constexpr char const * const weak_name = "char";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<char*&> {
public:
    using type      = char*&;
    using weak_type = char;
    using base      = void;

    static constexpr char const * const name      = "char*&";
    static constexpr char const * const weak_name = "char";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<char**> {
public:
    using type      = char**;
    using weak_type = char;
    using base      = void;

    static constexpr char const * const name      = "char**";
    static constexpr char const * const weak_name = "char";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<char**&> {
public:
    using type      = char**&;
    using weak_type = char;
    using base      = void;

    static constexpr char const * const name      = "char**&";
    static constexpr char const * const weak_name = "char";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<char***> {
public:
    using type      = char***;
    using weak_type = char;
    using base      = void;

    static constexpr char const * const name      = "char***";
    static constexpr char const * const weak_name = "char";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<char***&> {
public:
    using type      = char***&;
    using weak_type = char;
    using base      = void;

    static constexpr char const * const name      = "char***&";
    static constexpr char const * const weak_name = "char";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct short
template<> class TypeInfo<short> {
public:
    using type      = short;
    using weak_type = short;
    using base      = void;

    static constexpr char const * const name      = "short";
    static constexpr char const * const weak_name = "short";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<short*> {
public:
    using type      = short*;
    using weak_type = short;
    using base      = void;

    static constexpr char const * const name      = "short*";
    static constexpr char const * const weak_name = "short";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<short*&> {
public:
    using type      = short*&;
    using weak_type = short;
    using base      = void;

    static constexpr char const * const name      = "short*&";
    static constexpr char const * const weak_name = "short";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<short**> {
public:
    using type      = short**;
    using weak_type = short;
    using base      = void;

    static constexpr char const * const name      = "short**";
    static constexpr char const * const weak_name = "short";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<short**&> {
public:
    using type      = short**&;
    using weak_type = short;
    using base      = void;

    static constexpr char const * const name      = "short**&";
    static constexpr char const * const weak_name = "short";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<short***> {
public:
    using type      = short***;
    using weak_type = short;
    using base      = void;

    static constexpr char const * const name      = "short***";
    static constexpr char const * const weak_name = "short";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<short***&> {
public:
    using type      = short***&;
    using weak_type = short;
    using base      = void;

    static constexpr char const * const name      = "short***&";
    static constexpr char const * const weak_name = "short";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct int
template<> class TypeInfo<int> {
public:
    using type      = int;
    using weak_type = int;
    using base      = void;

    static constexpr char const * const name      = "int";
    static constexpr char const * const weak_name = "int";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<int*> {
public:
    using type      = int*;
    using weak_type = int;
    using base      = void;

    static constexpr char const * const name      = "int*";
    static constexpr char const * const weak_name = "int";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<int*&> {
public:
    using type      = int*&;
    using weak_type = int;
    using base      = void;

    static constexpr char const * const name      = "int*&";
    static constexpr char const * const weak_name = "int";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<int**> {
public:
    using type      = int**;
    using weak_type = int;
    using base      = void;

    static constexpr char const * const name      = "int**";
    static constexpr char const * const weak_name = "int";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<int**&> {
public:
    using type      = int**&;
    using weak_type = int;
    using base      = void;

    static constexpr char const * const name      = "int**&";
    static constexpr char const * const weak_name = "int";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<int***> {
public:
    using type      = int***;
    using weak_type = int;
    using base      = void;

    static constexpr char const * const name      = "int***";
    static constexpr char const * const weak_name = "int";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<int***&> {
public:
    using type      = int***&;
    using weak_type = int;
    using base      = void;

    static constexpr char const * const name      = "int***&";
    static constexpr char const * const weak_name = "int";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct long
template<> class TypeInfo<long> {
public:
    using type      = long;
    using weak_type = long;
    using base      = void;

    static constexpr char const * const name      = "long";
    static constexpr char const * const weak_name = "long";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<long*> {
public:
    using type      = long*;
    using weak_type = long;
    using base      = void;

    static constexpr char const * const name      = "long*";
    static constexpr char const * const weak_name = "long";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<long*&> {
public:
    using type      = long*&;
    using weak_type = long;
    using base      = void;

    static constexpr char const * const name      = "long*&";
    static constexpr char const * const weak_name = "long";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<long**> {
public:
    using type      = long**;
    using weak_type = long;
    using base      = void;

    static constexpr char const * const name      = "long**";
    static constexpr char const * const weak_name = "long";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<long**&> {
public:
    using type      = long**&;
    using weak_type = long;
    using base      = void;

    static constexpr char const * const name      = "long**&";
    static constexpr char const * const weak_name = "long";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<long***> {
public:
    using type      = long***;
    using weak_type = long;
    using base      = void;

    static constexpr char const * const name      = "long***";
    static constexpr char const * const weak_name = "long";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<long***&> {
public:
    using type      = long***&;
    using weak_type = long;
    using base      = void;

    static constexpr char const * const name      = "long***&";
    static constexpr char const * const weak_name = "long";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct float
template<> class TypeInfo<float> {
public:
    using type      = float;
    using weak_type = float;
    using base      = void;

    static constexpr char const * const name      = "float";
    static constexpr char const * const weak_name = "float";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<float*> {
public:
    using type      = float*;
    using weak_type = float;
    using base      = void;

    static constexpr char const * const name      = "float*";
    static constexpr char const * const weak_name = "float";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<float*&> {
public:
    using type      = float*&;
    using weak_type = float;
    using base      = void;

    static constexpr char const * const name      = "float*&";
    static constexpr char const * const weak_name = "float";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<float**> {
public:
    using type      = float**;
    using weak_type = float;
    using base      = void;

    static constexpr char const * const name      = "float**";
    static constexpr char const * const weak_name = "float";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<float**&> {
public:
    using type      = float**&;
    using weak_type = float;
    using base      = void;

    static constexpr char const * const name      = "float**&";
    static constexpr char const * const weak_name = "float";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<float***> {
public:
    using type      = float***;
    using weak_type = float;
    using base      = void;

    static constexpr char const * const name      = "float***";
    static constexpr char const * const weak_name = "float";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<float***&> {
public:
    using type      = float***&;
    using weak_type = float;
    using base      = void;

    static constexpr char const * const name      = "float***&";
    static constexpr char const * const weak_name = "float";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct double
template<> class TypeInfo<double> {
public:
    using type      = double;
    using weak_type = double;
    using base      = void;

    static constexpr char const * const name      = "double";
    static constexpr char const * const weak_name = "double";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<double*> {
public:
    using type      = double*;
    using weak_type = double;
    using base      = void;

    static constexpr char const * const name      = "double*";
    static constexpr char const * const weak_name = "double";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<double*&> {
public:
    using type      = double*&;
    using weak_type = double;
    using base      = void;

    static constexpr char const * const name      = "double*&";
    static constexpr char const * const weak_name = "double";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<double**> {
public:
    using type      = double**;
    using weak_type = double;
    using base      = void;

    static constexpr char const * const name      = "double**";
    static constexpr char const * const weak_name = "double";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<double**&> {
public:
    using type      = double**&;
    using weak_type = double;
    using base      = void;

    static constexpr char const * const name      = "double**&";
    static constexpr char const * const weak_name = "double";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<double***> {
public:
    using type      = double***;
    using weak_type = double;
    using base      = void;

    static constexpr char const * const name      = "double***";
    static constexpr char const * const weak_name = "double";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<double***&> {
public:
    using type      = double***&;
    using weak_type = double;
    using base      = void;

    static constexpr char const * const name      = "double***&";
    static constexpr char const * const weak_name = "double";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct bool
template<> class TypeInfo<bool> {
public:
    using type      = bool;
    using weak_type = bool;
    using base      = void;

    static constexpr char const * const name      = "bool";
    static constexpr char const * const weak_name = "bool";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<bool*> {
public:
    using type      = bool*;
    using weak_type = bool;
    using base      = void;

    static constexpr char const * const name      = "bool*";
    static constexpr char const * const weak_name = "bool";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<bool*&> {
public:
    using type      = bool*&;
    using weak_type = bool;
    using base      = void;

    static constexpr char const * const name      = "bool*&";
    static constexpr char const * const weak_name = "bool";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<bool**> {
public:
    using type      = bool**;
    using weak_type = bool;
    using base      = void;

    static constexpr char const * const name      = "bool**";
    static constexpr char const * const weak_name = "bool";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<bool**&> {
public:
    using type      = bool**&;
    using weak_type = bool;
    using base      = void;

    static constexpr char const * const name      = "bool**&";
    static constexpr char const * const weak_name = "bool";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<bool***> {
public:
    using type      = bool***;
    using weak_type = bool;
    using base      = void;

    static constexpr char const * const name      = "bool***";
    static constexpr char const * const weak_name = "bool";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<bool***&> {
public:
    using type      = bool***&;
    using weak_type = bool;
    using base      = void;

    static constexpr char const * const name      = "bool***&";
    static constexpr char const * const weak_name = "bool";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = true;
    static constexpr bool const is_class     = false;
    static constexpr bool const is_enum      = false;
};


// struct Person
template<> class TypeInfo<Person> {
public:
    using type      = Person;
    using weak_type = Person;
    using base      = void;

    static constexpr char const * const name      = "Person";
    static constexpr char const * const weak_name = "Person";

    static constexpr size_t const member_count = 4;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Person*> {
public:
    using type      = Person*;
    using weak_type = Person;
    using base      = void;

    static constexpr char const * const name      = "Person*";
    static constexpr char const * const weak_name = "Person";

    static constexpr size_t const member_count = 4;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Person*&> {
public:
    using type      = Person*&;
    using weak_type = Person;
    using base      = void;

    static constexpr char const * const name      = "Person*&";
    static constexpr char const * const weak_name = "Person";

    static constexpr size_t const member_count = 4;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Person**> {
public:
    using type      = Person**;
    using weak_type = Person;
    using base      = void;

    static constexpr char const * const name      = "Person**";
    static constexpr char const * const weak_name = "Person";

    static constexpr size_t const member_count = 4;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Person**&> {
public:
    using type      = Person**&;
    using weak_type = Person;
    using base      = void;

    static constexpr char const * const name      = "Person**&";
    static constexpr char const * const weak_name = "Person";

    static constexpr size_t const member_count = 4;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Person***> {
public:
    using type      = Person***;
    using weak_type = Person;
    using base      = void;

    static constexpr char const * const name      = "Person***";
    static constexpr char const * const weak_name = "Person";

    static constexpr size_t const member_count = 4;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Person***&> {
public:
    using type      = Person***&;
    using weak_type = Person;
    using base      = void;

    static constexpr char const * const name      = "Person***&";
    static constexpr char const * const weak_name = "Person";

    static constexpr size_t const member_count = 4;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};


// struct std::string
template<> class TypeInfo<std::string> {
public:
    using type      = std::string;
    using weak_type = std::string;
    using base      = void;

    static constexpr char const * const name      = "std::string";
    static constexpr char const * const weak_name = "std::string";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<std::string*> {
public:
    using type      = std::string*;
    using weak_type = std::string;
    using base      = void;

    static constexpr char const * const name      = "std::string*";
    static constexpr char const * const weak_name = "std::string";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<std::string*&> {
public:
    using type      = std::string*&;
    using weak_type = std::string;
    using base      = void;

    static constexpr char const * const name      = "std::string*&";
    static constexpr char const * const weak_name = "std::string";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<std::string**> {
public:
    using type      = std::string**;
    using weak_type = std::string;
    using base      = void;

    static constexpr char const * const name      = "std::string**";
    static constexpr char const * const weak_name = "std::string";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<std::string**&> {
public:
    using type      = std::string**&;
    using weak_type = std::string;
    using base      = void;

    static constexpr char const * const name      = "std::string**&";
    static constexpr char const * const weak_name = "std::string";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<std::string***> {
public:
    using type      = std::string***;
    using weak_type = std::string;
    using base      = void;

    static constexpr char const * const name      = "std::string***";
    static constexpr char const * const weak_name = "std::string";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<std::string***&> {
public:
    using type      = std::string***&;
    using weak_type = std::string;
    using base      = void;

    static constexpr char const * const name      = "std::string***&";
    static constexpr char const * const weak_name = "std::string";

    static constexpr size_t const member_count = 0;
    static constexpr size_t const base_count   = 0;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};


// struct Student
template<> class TypeInfo<Student> {
public:
    using type      = Student;
    using weak_type = Student;
    using base      = Person;

    static constexpr char const * const name      = "Student";
    static constexpr char const * const weak_name = "Student";

    static constexpr size_t const member_count = 2;
    static constexpr size_t const base_count   = 1;

    static constexpr size_t const ptr    = 0;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Student*> {
public:
    using type      = Student*;
    using weak_type = Student;
    using base      = Person;

    static constexpr char const * const name      = "Student*";
    static constexpr char const * const weak_name = "Student";

    static constexpr size_t const member_count = 2;
    static constexpr size_t const base_count   = 1;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Student*&> {
public:
    using type      = Student*&;
    using weak_type = Student;
    using base      = Person;

    static constexpr char const * const name      = "Student*&";
    static constexpr char const * const weak_name = "Student";

    static constexpr size_t const member_count = 2;
    static constexpr size_t const base_count   = 1;

    static constexpr size_t const ptr    = 1;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Student**> {
public:
    using type      = Student**;
    using weak_type = Student;
    using base      = Person;

    static constexpr char const * const name      = "Student**";
    static constexpr char const * const weak_name = "Student";

    static constexpr size_t const member_count = 2;
    static constexpr size_t const base_count   = 1;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Student**&> {
public:
    using type      = Student**&;
    using weak_type = Student;
    using base      = Person;

    static constexpr char const * const name      = "Student**&";
    static constexpr char const * const weak_name = "Student";

    static constexpr size_t const member_count = 2;
    static constexpr size_t const base_count   = 1;

    static constexpr size_t const ptr    = 2;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Student***> {
public:
    using type      = Student***;
    using weak_type = Student;
    using base      = Person;

    static constexpr char const * const name      = "Student***";
    static constexpr char const * const weak_name = "Student";

    static constexpr size_t const member_count = 2;
    static constexpr size_t const base_count   = 1;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = false;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

template<> class TypeInfo<Student***&> {
public:
    using type      = Student***&;
    using weak_type = Student;
    using base      = Person;

    static constexpr char const * const name      = "Student***&";
    static constexpr char const * const weak_name = "Student";

    static constexpr size_t const member_count = 2;
    static constexpr size_t const base_count   = 1;

    static constexpr size_t const ptr    = 3;
    static constexpr bool   const is_ref = true;

    static constexpr bool const is_primitive = false;
    static constexpr bool const is_class     = true;
    static constexpr bool const is_enum      = false;
};

// Get at index.
#define get_member(variable, index) GetMember<decltype(variable), index>::get(variable)
template<typename T, int index> struct GetMember { };

template<> struct GetMember<Person *, 0> {
    static std::string *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        std::string * res = (std::string *)&cpy->name;
        return(res);
    };
};
template<> struct GetMember<Person *&, 0> {
    static std::string *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        std::string * res = (std::string *)&cpy->name;
        return(res);
    };
};
template<> struct GetMember<Person *, 1> {
    static int *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        int * res = (int *)&cpy->age;
        return(res);
    };
};
template<> struct GetMember<Person *&, 1> {
    static int *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        int * res = (int *)&cpy->age;
        return(res);
    };
};
template<> struct GetMember<Person *, 2> {
    static std::string *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        std::string * res = (std::string *)&cpy->city;
        return(res);
    };
};
template<> struct GetMember<Person *&, 2> {
    static std::string *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        std::string * res = (std::string *)&cpy->city;
        return(res);
    };
};
template<> struct GetMember<Person *, 3> {
    static char *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        char * res = (char *)&cpy->gender;
        return(res);
    };
};
template<> struct GetMember<Person *&, 3> {
    static char *get(Person *ptr) {
        _Person *cpy = (_Person *)ptr;
        char * res = (char *)&cpy->gender;
        return(res);
    };
};

template<> struct GetMember<Student *, 0> {
    static std::string *get(Student *ptr) {
        _Student *cpy = (_Student *)ptr;
        std::string * res = (std::string *)&cpy->major;
        return(res);
    };
};
template<> struct GetMember<Student *&, 0> {
    static std::string *get(Student *ptr) {
        _Student *cpy = (_Student *)ptr;
        std::string * res = (std::string *)&cpy->major;
        return(res);
    };
};
template<> struct GetMember<Student *, 1> {
    static std::string *get(Student *ptr) {
        _Student *cpy = (_Student *)ptr;
        std::string * res = (std::string *)&cpy->minor;
        return(res);
    };
};
template<> struct GetMember<Student *&, 1> {
    static std::string *get(Student *ptr) {
        _Student *cpy = (_Student *)ptr;
        std::string * res = (std::string *)&cpy->minor;
        return(res);
    };
};
template<typename T>static char const * get_member_name(int index){return(0);}
template<>char const * get_member_name<Person>(int index){
    switch(index) {
        case 0: { return("name"); } break;
        case 1: { return("age"); } break;
        case 2: { return("city"); } break;
        case 3: { return("gender"); } break;
    }
    return(0); // Not found.
}
template<>char const * get_member_name<Student>(int index){
    switch(index) {
        case 0: { return("major"); } break;
        case 1: { return("minor"); } break;
    }
    return(0); // Not found.
}
static bool is_meta_type_container(int type) {
    if(type == Type_char) {return(false);} // false
    else if(type == Type_short) {return(false);} // false
    else if(type == Type_int) {return(false);} // false
    else if(type == Type_long) {return(false);} // false
    else if(type == Type_float) {return(false);} // false
    else if(type == Type_double) {return(false);} // false
    else if(type == Type_bool) {return(false);} // false
    else if(type == Type_Person) {return(false);} // false
    else if(type == Type_std_string_char) {return(true);} // true
    else if(type == Type_Student) {return(false);} // false

    // Should not be reached.
    assert(0);
    return(0);
}
static char const * meta_type_to_name(Type mt, bool is_ptr) {
    if(mt == Type_Person) {
        if(is_ptr) {return("Person *");}
        else       {return("Person");  }
    } else if(mt == Type_Student) {
        if(is_ptr) {return("Student *");}
        else       {return("Student");  }
    }

    assert(0); 
    return(0); // Not found
}
static size_t get_size_from_str(char const *str) {

    if((strcmp(str, "Person") == 0) || (strcmp(str, "Person *") == 0) || (strcmp(str, "Person **") == 0)) {return(sizeof(_Person));}
    else if((strcmp(str, "Student") == 0) || (strcmp(str, "Student *") == 0) || (strcmp(str, "Student **") == 0)) {return(sizeof(_Student));}

    return(0); // Not found.
}
// Function to serialize a struct to a char array buffer.
static size_t
serialize_struct_(void *var, char const *name, char const *type_as_str, int indent, char *buffer, size_t buf_size, size_t bytes_written) {
    assert((buffer) && (buf_size > 0)); // Check params.

    if(!bytes_written) {memset(buffer, 0, buf_size);} // If this is the first time through, zero the buffer.

    MemberDefinition *members_of_Something = get_members_of_str(type_as_str); // Get the members_of pointer. 
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
                        if(member->type == Type_std_string_char) {bytes_written = serialize_container<std::string, char>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}

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
//
// Get access at index.
//
template<typename T, int index> constexpr Access get_access_at_index() { return(Access_unknown); }


template<> constexpr Access get_access_at_index<Person, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person &, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *&, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **&, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person &, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *&, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **&, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person, 2>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *, 2>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **, 2>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person &, 2>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *&, 2>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **&, 2>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person, 3>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *, 3>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **, 3>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person &, 3>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person *&, 3>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Person **&, 3>() { return(Access_public); }

template<> constexpr Access get_access_at_index<Student, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student *, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student **, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student &, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student *&, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student **&, 0>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student *, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student **, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student &, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student *&, 1>() { return(Access_public); }
template<> constexpr Access get_access_at_index<Student **&, 1>() { return(Access_public); }

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // Person
    if(type_compare(T, Person)) {
        static MemberDefinition members_of_Person[] = {
            {Type_std_string_char, "name", offset_of(&_Person::name), 0, 1},
            {Type_int, "age", offset_of(&_Person::age), 0, 1},
            {Type_std_string_char, "city", offset_of(&_Person::city), 0, 1},
            {Type_char, "gender", offset_of(&_Person::gender), 0, 1},
        };
        return(members_of_Person);

    // Student
    } else if(type_compare(T, Student)) {
        static MemberDefinition members_of_Student[] = {
            {Type_std_string_char, "major", offset_of(&_Student::major), 0, 1},
            {Type_std_string_char, "minor", offset_of(&_Student::minor), 0, 1},
            // Members inherited from Person.
            {Type_std_string_char, "name", (size_t)&((_Student *)0)->name, 0, 1},
            {Type_int, "age", (size_t)&((_Student *)0)->age, 0, 1},
            {Type_std_string_char, "city", (size_t)&((_Student *)0)->city, 0, 1},
            {Type_char, "gender", (size_t)&((_Student *)0)->gender, 0, 1},
        };
        return(members_of_Student);
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


    // Person
    } else if((strcmp(str, "Person") == 0) || (strcmp(str, "Person *") == 0) || (strcmp(str, "Person **") == 0)) {
        static MemberDefinition members_of_Person[] = {
            {Type_std_string_char, "name", offset_of(&_Person::name), 0, 1},
            {Type_int, "age", offset_of(&_Person::age), 0, 1},
            {Type_std_string_char, "city", offset_of(&_Person::city), 0, 1},
            {Type_char, "gender", offset_of(&_Person::gender), 0, 1},
        };
        return(members_of_Person);

    // Student
    } else if((strcmp(str, "Student") == 0) || (strcmp(str, "Student *") == 0) || (strcmp(str, "Student **") == 0)) {
        static MemberDefinition members_of_Student[] = {
            {Type_std_string_char, "major", offset_of(&_Student::major), 0, 1},
            {Type_std_string_char, "minor", offset_of(&_Student::minor), 0, 1},
            // Members inherited from Person.
            {Type_std_string_char, "name", (size_t)&((_Student *)0)->name, 0, 1},
            {Type_int, "age", (size_t)&((_Student *)0)->age, 0, 1},
            {Type_std_string_char, "city", (size_t)&((_Student *)0)->city, 0, 1},
            {Type_char, "gender", (size_t)&((_Student *)0)->gender, 0, 1},
        };
        return(members_of_Student);
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
    else if((strcmp(str, "Person") == 0) || (strcmp(str, "Person *") == 0) || (strcmp(str, "Person **") == 0)) {return(4);}
    else if((strcmp(str, "Student") == 0) || (strcmp(str, "Student *") == 0) || (strcmp(str, "Student **") == 0)) {return(6);}

    return(-1); // Error.
}

//
// Enum Introspection data.
//

// Stub functions.
template<typename T>static constexpr char const *enum_to_string(T element) { return(0); }
template<typename T>static constexpr T string_to_enum(char const *str) { return(0); }


#define weak_type_compare(A, B) TypeCompare_<pp::Type<A>::weak_type, pp::Type<B>::weak_type>::e;
#undef _std // :(
} // namespace pp

#endif // Header guard.


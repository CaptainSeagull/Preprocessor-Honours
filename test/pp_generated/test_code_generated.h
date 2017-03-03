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
struct IntTest;
struct StringTest;

#define _std std // TODO(Jonny): This is really stupid...

// Enum with field for every type detected.
namespace pp { enum MetaType {
    MetaType_char,
    MetaType_short,
    MetaType_int,
    MetaType_long,
    MetaType_float,
    MetaType_double,
    MetaType_bool,
    MetaType_Test,
    MetaType_V2,
    MetaType_A,
    MetaType_B,
    MetaType_Foo,
    MetaType_V3,
    MetaType_VectorTest,
    MetaType_std_vector_float,
    MetaType_std_vector_int,
    MetaType_std_vector_V3,
    MetaType_std_deque_int,
    MetaType_std_forward_list_int,
    MetaType_std_list_int,
    MetaType_IntTest,
    MetaType_StringTest,
}; }

#include "static_generated.h"
namespace pp { // PreProcessor

//
// Meta type specialization
//

// char
template<> struct TypeStruct<char> {
    using type = char;
    using weak_type = char;

    static constexpr char const * name = "char";
    static constexpr char const * weak_name = "char";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<char *> {
    using type = char *;
    using weak_type = char;

    static constexpr char const * name = "char *";
    static constexpr char const * weak_name = "char";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<char **> {
    using type = char **;
    using weak_type = char;

    static constexpr char const * name = "char **";
    static constexpr char const * weak_name = "char";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// short
template<> struct TypeStruct<short> {
    using type = short;
    using weak_type = short;

    static constexpr char const * name = "short";
    static constexpr char const * weak_name = "short";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<short *> {
    using type = short *;
    using weak_type = short;

    static constexpr char const * name = "short *";
    static constexpr char const * weak_name = "short";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<short **> {
    using type = short **;
    using weak_type = short;

    static constexpr char const * name = "short **";
    static constexpr char const * weak_name = "short";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// int
template<> struct TypeStruct<int> {
    using type = int;
    using weak_type = int;

    static constexpr char const * name = "int";
    static constexpr char const * weak_name = "int";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<int *> {
    using type = int *;
    using weak_type = int;

    static constexpr char const * name = "int *";
    static constexpr char const * weak_name = "int";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<int **> {
    using type = int **;
    using weak_type = int;

    static constexpr char const * name = "int **";
    static constexpr char const * weak_name = "int";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// long
template<> struct TypeStruct<long> {
    using type = long;
    using weak_type = long;

    static constexpr char const * name = "long";
    static constexpr char const * weak_name = "long";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<long *> {
    using type = long *;
    using weak_type = long;

    static constexpr char const * name = "long *";
    static constexpr char const * weak_name = "long";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<long **> {
    using type = long **;
    using weak_type = long;

    static constexpr char const * name = "long **";
    static constexpr char const * weak_name = "long";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// float
template<> struct TypeStruct<float> {
    using type = float;
    using weak_type = float;

    static constexpr char const * name = "float";
    static constexpr char const * weak_name = "float";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<float *> {
    using type = float *;
    using weak_type = float;

    static constexpr char const * name = "float *";
    static constexpr char const * weak_name = "float";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<float **> {
    using type = float **;
    using weak_type = float;

    static constexpr char const * name = "float **";
    static constexpr char const * weak_name = "float";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// double
template<> struct TypeStruct<double> {
    using type = double;
    using weak_type = double;

    static constexpr char const * name = "double";
    static constexpr char const * weak_name = "double";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<double *> {
    using type = double *;
    using weak_type = double;

    static constexpr char const * name = "double *";
    static constexpr char const * weak_name = "double";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<double **> {
    using type = double **;
    using weak_type = double;

    static constexpr char const * name = "double **";
    static constexpr char const * weak_name = "double";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// bool
template<> struct TypeStruct<bool> {
    using type = bool;
    using weak_type = bool;

    static constexpr char const * name = "bool";
    static constexpr char const * weak_name = "bool";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<bool *> {
    using type = bool *;
    using weak_type = bool;

    static constexpr char const * name = "bool *";
    static constexpr char const * weak_name = "bool";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<bool **> {
    using type = bool **;
    using weak_type = bool;

    static constexpr char const * name = "bool **";
    static constexpr char const * weak_name = "bool";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// Test
template<> struct TypeStruct<Test> {
    using type = Test;
    using weak_type = Test;

    static constexpr char const * name = "Test";
    static constexpr char const * weak_name = "Test";

    static size_t const member_count = 2;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<Test *> {
    using type = Test *;
    using weak_type = Test;

    static constexpr char const * name = "Test *";
    static constexpr char const * weak_name = "Test";

    static size_t const member_count = 2;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<Test **> {
    using type = Test **;
    using weak_type = Test;

    static constexpr char const * name = "Test **";
    static constexpr char const * weak_name = "Test";

    static size_t const member_count = 2;

    static bool const is_ptr = true;
};

// V2
template<> struct TypeStruct<V2> {
    using type = V2;
    using weak_type = V2;

    static constexpr char const * name = "V2";
    static constexpr char const * weak_name = "V2";

    static size_t const member_count = 3;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<V2 *> {
    using type = V2 *;
    using weak_type = V2;

    static constexpr char const * name = "V2 *";
    static constexpr char const * weak_name = "V2";

    static size_t const member_count = 3;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<V2 **> {
    using type = V2 **;
    using weak_type = V2;

    static constexpr char const * name = "V2 **";
    static constexpr char const * weak_name = "V2";

    static size_t const member_count = 3;

    static bool const is_ptr = true;
};

// A
template<> struct TypeStruct<A> {
    using type = A;
    using weak_type = A;

    static constexpr char const * name = "A";
    static constexpr char const * weak_name = "A";

    static size_t const member_count = 1;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<A *> {
    using type = A *;
    using weak_type = A;

    static constexpr char const * name = "A *";
    static constexpr char const * weak_name = "A";

    static size_t const member_count = 1;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<A **> {
    using type = A **;
    using weak_type = A;

    static constexpr char const * name = "A **";
    static constexpr char const * weak_name = "A";

    static size_t const member_count = 1;

    static bool const is_ptr = true;
};

// B
template<> struct TypeStruct<B> {
    using type = B;
    using weak_type = B;

    static constexpr char const * name = "B";
    static constexpr char const * weak_name = "B";

    static size_t const member_count = 1;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<B *> {
    using type = B *;
    using weak_type = B;

    static constexpr char const * name = "B *";
    static constexpr char const * weak_name = "B";

    static size_t const member_count = 1;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<B **> {
    using type = B **;
    using weak_type = B;

    static constexpr char const * name = "B **";
    static constexpr char const * weak_name = "B";

    static size_t const member_count = 1;

    static bool const is_ptr = true;
};

// Foo
template<> struct TypeStruct<Foo> {
    using type = Foo;
    using weak_type = Foo;

    static constexpr char const * name = "Foo";
    static constexpr char const * weak_name = "Foo";

    static size_t const member_count = 8;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<Foo *> {
    using type = Foo *;
    using weak_type = Foo;

    static constexpr char const * name = "Foo *";
    static constexpr char const * weak_name = "Foo";

    static size_t const member_count = 8;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<Foo **> {
    using type = Foo **;
    using weak_type = Foo;

    static constexpr char const * name = "Foo **";
    static constexpr char const * weak_name = "Foo";

    static size_t const member_count = 8;

    static bool const is_ptr = true;
};

// V3
template<> struct TypeStruct<V3> {
    using type = V3;
    using weak_type = V3;

    static constexpr char const * name = "V3";
    static constexpr char const * weak_name = "V3";

    static size_t const member_count = 3;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<V3 *> {
    using type = V3 *;
    using weak_type = V3;

    static constexpr char const * name = "V3 *";
    static constexpr char const * weak_name = "V3";

    static size_t const member_count = 3;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<V3 **> {
    using type = V3 **;
    using weak_type = V3;

    static constexpr char const * name = "V3 **";
    static constexpr char const * weak_name = "V3";

    static size_t const member_count = 3;

    static bool const is_ptr = true;
};

// VectorTest
template<> struct TypeStruct<VectorTest> {
    using type = VectorTest;
    using weak_type = VectorTest;

    static constexpr char const * name = "VectorTest";
    static constexpr char const * weak_name = "VectorTest";

    static size_t const member_count = 6;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<VectorTest *> {
    using type = VectorTest *;
    using weak_type = VectorTest;

    static constexpr char const * name = "VectorTest *";
    static constexpr char const * weak_name = "VectorTest";

    static size_t const member_count = 6;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<VectorTest **> {
    using type = VectorTest **;
    using weak_type = VectorTest;

    static constexpr char const * name = "VectorTest **";
    static constexpr char const * weak_name = "VectorTest";

    static size_t const member_count = 6;

    static bool const is_ptr = true;
};

// std::vector<float>
template<> struct TypeStruct<std::vector<float>> {
    using type = std::vector<float>;
    using weak_type = std::vector<float>;

    static constexpr char const * name = "std::vector<float>";
    static constexpr char const * weak_name = "std::vector<float>";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<std::vector<float> *> {
    using type = std::vector<float> *;
    using weak_type = std::vector<float>;

    static constexpr char const * name = "std::vector<float> *";
    static constexpr char const * weak_name = "std::vector<float>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<std::vector<float> **> {
    using type = std::vector<float> **;
    using weak_type = std::vector<float>;

    static constexpr char const * name = "std::vector<float> **";
    static constexpr char const * weak_name = "std::vector<float>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// std::vector<int>
template<> struct TypeStruct<std::vector<int>> {
    using type = std::vector<int>;
    using weak_type = std::vector<int>;

    static constexpr char const * name = "std::vector<int>";
    static constexpr char const * weak_name = "std::vector<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<std::vector<int> *> {
    using type = std::vector<int> *;
    using weak_type = std::vector<int>;

    static constexpr char const * name = "std::vector<int> *";
    static constexpr char const * weak_name = "std::vector<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<std::vector<int> **> {
    using type = std::vector<int> **;
    using weak_type = std::vector<int>;

    static constexpr char const * name = "std::vector<int> **";
    static constexpr char const * weak_name = "std::vector<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// std::vector<V3>
template<> struct TypeStruct<std::vector<V3>> {
    using type = std::vector<V3>;
    using weak_type = std::vector<V3>;

    static constexpr char const * name = "std::vector<V3>";
    static constexpr char const * weak_name = "std::vector<V3>";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<std::vector<V3> *> {
    using type = std::vector<V3> *;
    using weak_type = std::vector<V3>;

    static constexpr char const * name = "std::vector<V3> *";
    static constexpr char const * weak_name = "std::vector<V3>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<std::vector<V3> **> {
    using type = std::vector<V3> **;
    using weak_type = std::vector<V3>;

    static constexpr char const * name = "std::vector<V3> **";
    static constexpr char const * weak_name = "std::vector<V3>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// std::deque<int>
template<> struct TypeStruct<std::deque<int>> {
    using type = std::deque<int>;
    using weak_type = std::deque<int>;

    static constexpr char const * name = "std::deque<int>";
    static constexpr char const * weak_name = "std::deque<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<std::deque<int> *> {
    using type = std::deque<int> *;
    using weak_type = std::deque<int>;

    static constexpr char const * name = "std::deque<int> *";
    static constexpr char const * weak_name = "std::deque<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<std::deque<int> **> {
    using type = std::deque<int> **;
    using weak_type = std::deque<int>;

    static constexpr char const * name = "std::deque<int> **";
    static constexpr char const * weak_name = "std::deque<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// std::forward_list<int>
template<> struct TypeStruct<std::forward_list<int>> {
    using type = std::forward_list<int>;
    using weak_type = std::forward_list<int>;

    static constexpr char const * name = "std::forward_list<int>";
    static constexpr char const * weak_name = "std::forward_list<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<std::forward_list<int> *> {
    using type = std::forward_list<int> *;
    using weak_type = std::forward_list<int>;

    static constexpr char const * name = "std::forward_list<int> *";
    static constexpr char const * weak_name = "std::forward_list<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<std::forward_list<int> **> {
    using type = std::forward_list<int> **;
    using weak_type = std::forward_list<int>;

    static constexpr char const * name = "std::forward_list<int> **";
    static constexpr char const * weak_name = "std::forward_list<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// std::list<int>
template<> struct TypeStruct<std::list<int>> {
    using type = std::list<int>;
    using weak_type = std::list<int>;

    static constexpr char const * name = "std::list<int>";
    static constexpr char const * weak_name = "std::list<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<std::list<int> *> {
    using type = std::list<int> *;
    using weak_type = std::list<int>;

    static constexpr char const * name = "std::list<int> *";
    static constexpr char const * weak_name = "std::list<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<std::list<int> **> {
    using type = std::list<int> **;
    using weak_type = std::list<int>;

    static constexpr char const * name = "std::list<int> **";
    static constexpr char const * weak_name = "std::list<int>";

    static size_t const member_count = 0;

    static bool const is_ptr = true;
};

// IntTest
template<> struct TypeStruct<IntTest> {
    using type = IntTest;
    using weak_type = IntTest;

    static constexpr char const * name = "IntTest";
    static constexpr char const * weak_name = "IntTest";

    static size_t const member_count = 1;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<IntTest *> {
    using type = IntTest *;
    using weak_type = IntTest;

    static constexpr char const * name = "IntTest *";
    static constexpr char const * weak_name = "IntTest";

    static size_t const member_count = 1;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<IntTest **> {
    using type = IntTest **;
    using weak_type = IntTest;

    static constexpr char const * name = "IntTest **";
    static constexpr char const * weak_name = "IntTest";

    static size_t const member_count = 1;

    static bool const is_ptr = true;
};

// StringTest
template<> struct TypeStruct<StringTest> {
    using type = StringTest;
    using weak_type = StringTest;

    static constexpr char const * name = "StringTest";
    static constexpr char const * weak_name = "StringTest";

    static size_t const member_count = 2;

    static bool const is_ptr = false;
};
template<> struct TypeStruct<StringTest *> {
    using type = StringTest *;
    using weak_type = StringTest;

    static constexpr char const * name = "StringTest *";
    static constexpr char const * weak_name = "StringTest";

    static size_t const member_count = 2;

    static bool const is_ptr = true;
};
template<> struct TypeStruct<StringTest **> {
    using type = StringTest **;
    using weak_type = StringTest;

    static constexpr char const * name = "StringTest **";
    static constexpr char const * weak_name = "StringTest";

    static size_t const member_count = 2;

    static bool const is_ptr = true;
};
static bool is_meta_type_container(int type) {
    if(type == MetaType_char) {return(false);} // false
    else if(type == MetaType_short) {return(false);} // false
    else if(type == MetaType_int) {return(false);} // false
    else if(type == MetaType_long) {return(false);} // false
    else if(type == MetaType_float) {return(false);} // false
    else if(type == MetaType_double) {return(false);} // false
    else if(type == MetaType_bool) {return(false);} // false
    else if(type == MetaType_Test) {return(false);} // false
    else if(type == MetaType_V2) {return(false);} // false
    else if(type == MetaType_A) {return(false);} // false
    else if(type == MetaType_B) {return(false);} // false
    else if(type == MetaType_Foo) {return(false);} // false
    else if(type == MetaType_V3) {return(false);} // false
    else if(type == MetaType_VectorTest) {return(false);} // false
    else if(type == MetaType_std_vector_float) {return(true);} // true
    else if(type == MetaType_std_vector_int) {return(true);} // true
    else if(type == MetaType_std_vector_V3) {return(true);} // true
    else if(type == MetaType_std_deque_int) {return(true);} // true
    else if(type == MetaType_std_forward_list_int) {return(true);} // true
    else if(type == MetaType_std_list_int) {return(true);} // true
    else if(type == MetaType_IntTest) {return(false);} // false
    else if(type == MetaType_StringTest) {return(false);} // false

    // Should not be reached.
    assert(0);
    return(0);
}
static char const * meta_type_to_name(/*MetaType*/int mt, bool is_ptr) {
    if(mt == MetaType_Test) {
        if(is_ptr) {return("Test *");}
        else       {return("Test");  }
    } else if(mt == MetaType_V2) {
        if(is_ptr) {return("V2 *");}
        else       {return("V2");  }
    } else if(mt == MetaType_A) {
        if(is_ptr) {return("A *");}
        else       {return("A");  }
    } else if(mt == MetaType_B) {
        if(is_ptr) {return("B *");}
        else       {return("B");  }
    } else if(mt == MetaType_Foo) {
        if(is_ptr) {return("Foo *");}
        else       {return("Foo");  }
    } else if(mt == MetaType_V3) {
        if(is_ptr) {return("V3 *");}
        else       {return("V3");  }
    } else if(mt == MetaType_VectorTest) {
        if(is_ptr) {return("VectorTest *");}
        else       {return("VectorTest");  }
    } else if(mt == MetaType_IntTest) {
        if(is_ptr) {return("IntTest *");}
        else       {return("IntTest");  }
    } else if(mt == MetaType_StringTest) {
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
                case MetaType_double: { // double.
                    bytes_written = serialize_primitive_((double *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_float: { // float.
                    bytes_written = serialize_primitive_((float *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_int: { // int.
                    bytes_written = serialize_primitive_((int *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_long: { // long.
                    bytes_written = serialize_primitive_((long *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_short: { // short.
                    bytes_written = serialize_primitive_((short *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                case MetaType_bool: { // bool.
                    bytes_written = serialize_primitive_((bool *)member_ptr, (member->is_ptr != 0), member->arr_size, member->name, indent, buffer, buf_size, bytes_written);
                } break;

                // char (special case).
                case MetaType_char: {
                    if(member_ptr) {
                        if(member->is_ptr) {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = \"%s\"", indent_buf, member->name, (char *)(*(size_t *)member_ptr));
                        } else {
                            bytes_written += pp_sprintf(buffer + bytes_written, buf_size - bytes_written, "\n%schar %s = %c", indent_buf, member->name, *(char *)((size_t *)member_ptr));
                        }
                    } else {
                        bytes_written += pp_sprintf((char *)buffer + bytes_written, buf_size - bytes_written, "\n%schar *%s = (null)", indent_buf, member->name);
                    }
                } break; // case MetaType_char

                default: {
                    if(is_meta_type_container(member->type)) {
                        if(member->type == MetaType_std_vector_float) {bytes_written = serialize_container<std::vector<float>, float>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == MetaType_std_vector_int) {bytes_written = serialize_container<std::vector<int>, int>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == MetaType_std_vector_V3) {bytes_written = serialize_container<std::vector<V3>, V3>(member_ptr, member->name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == MetaType_std_deque_int) {bytes_written = serialize_container<std::deque<int>, int>(member_ptr, name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == MetaType_std_forward_list_int) {bytes_written = serialize_container<std::forward_list<int>, int>(member_ptr, name, indent, buffer, buf_size, bytes_written);}
                        else if(member->type == MetaType_std_list_int) {bytes_written = serialize_container<std::list<int>, int>(member_ptr, name, indent, buffer, buf_size, bytes_written);}

                    } else {
                        char const *name = meta_type_to_name(member->type, member->is_ptr != 0);
                        bytes_written = serialize_struct_(member_ptr, member->name, name, indent, buffer, buf_size - bytes_written, bytes_written);
                    }
                } break; // default 
            }
        }
    }

    return(bytes_written);
}
// Recreated structs (Clang in std=C++98 complains if these are local).
struct _Test {  _int i;  _int *j;  };
union _V2 {  _int e[2];  struct { _int x;  _int y;  }; };
struct _A {  _int a;  };
struct _B {  _double b;  };
struct _Foo : public _A, public _B {  _char *str;  _int *int_ptr;  _float *float_ptr;  _bool *bool_ptr;  _int int_array[4];  _double *double_ptr_array[5];  _int *int_ptr_array[6];  _V2 v2;  };
struct _V3 {  _int x;  _int y;  _int z;  };
struct _VectorTest {  _std::vector<float> vec_floating;  _std::vector<int> vec_integer;  _std::vector<V3> vec_vector3;  _std::deque<int> deque_int;  _std::forward_list<int> fl_int;  _std::list<int> list_int;  };
struct _IntTest {  _int i;  };
struct _StringTest {  _char *text;  _int len;  };

// Convert a type into a members of pointer.
template<typename T> static MemberDefinition *get_members_of_(void) {
    // Test
    if(type_compare(T, Test)) {
        static MemberDefinition members_of_Test[] = {
            {MetaType_int, "i", offset_of(&_Test::i), false, 1},
            {MetaType_int, "j", offset_of(&_Test::j), true, 1},
        };
        return(members_of_Test);

    // V2
    } else if(type_compare(T, V2)) {
        static MemberDefinition members_of_V2[] = {
            {MetaType_int, "e", offset_of(&_V2::e), false, 2},
            {MetaType_int, "x", offset_of(&_V2::x), false, 1},
            {MetaType_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // A
    } else if(type_compare(T, A)) {
        static MemberDefinition members_of_A[] = {
            {MetaType_int, "a", offset_of(&_A::a), false, 1},
        };
        return(members_of_A);

    // B
    } else if(type_compare(T, B)) {
        static MemberDefinition members_of_B[] = {
            {MetaType_double, "b", offset_of(&_B::b), false, 1},
        };
        return(members_of_B);

    // Foo
    } else if(type_compare(T, Foo)) {
        static MemberDefinition members_of_Foo[] = {
            {MetaType_char, "str", offset_of(&_Foo::str), true, 1},
            {MetaType_int, "int_ptr", offset_of(&_Foo::int_ptr), true, 1},
            {MetaType_float, "float_ptr", offset_of(&_Foo::float_ptr), true, 1},
            {MetaType_bool, "bool_ptr", offset_of(&_Foo::bool_ptr), true, 1},
            {MetaType_int, "int_array", offset_of(&_Foo::int_array), false, 4},
            {MetaType_double, "double_ptr_array", offset_of(&_Foo::double_ptr_array), true, 5},
            {MetaType_int, "int_ptr_array", offset_of(&_Foo::int_ptr_array), true, 6},
            {MetaType_V2, "v2", offset_of(&_Foo::v2), false, 1},
            // Members inherited from A.
            {MetaType_int, "a", (size_t)&((_Foo *)0)->a, false, 1},
            // Members inherited from B.
            {MetaType_double, "b", (size_t)&((_Foo *)0)->b, false, 1},
        };
        return(members_of_Foo);

    // V3
    } else if(type_compare(T, V3)) {
        static MemberDefinition members_of_V3[] = {
            {MetaType_int, "x", offset_of(&_V3::x), false, 1},
            {MetaType_int, "y", offset_of(&_V3::y), false, 1},
            {MetaType_int, "z", offset_of(&_V3::z), false, 1},
        };
        return(members_of_V3);

    // VectorTest
    } else if(type_compare(T, VectorTest)) {
        static MemberDefinition members_of_VectorTest[] = {
            {MetaType_std_vector_float, "vec_floating", offset_of(&_VectorTest::vec_floating), false, 1},
            {MetaType_std_vector_int, "vec_integer", offset_of(&_VectorTest::vec_integer), false, 1},
            {MetaType_std_vector_V3, "vec_vector3", offset_of(&_VectorTest::vec_vector3), false, 1},
            {MetaType_std_deque_int, "deque_int", offset_of(&_VectorTest::deque_int), false, 1},
            {MetaType_std_forward_list_int, "fl_int", offset_of(&_VectorTest::fl_int), false, 1},
            {MetaType_std_list_int, "list_int", offset_of(&_VectorTest::list_int), false, 1},
        };
        return(members_of_VectorTest);

    // IntTest
    } else if(type_compare(T, IntTest)) {
        static MemberDefinition members_of_IntTest[] = {
            {MetaType_int, "i", offset_of(&_IntTest::i), false, 1},
        };
        return(members_of_IntTest);

    // StringTest
    } else if(type_compare(T, StringTest)) {
        static MemberDefinition members_of_StringTest[] = {
            {MetaType_char, "text", offset_of(&_StringTest::text), true, 1},
            {MetaType_int, "len", offset_of(&_StringTest::len), false, 1},
        };
        return(members_of_StringTest);
    }

    return(0); // Error.
}

// Convert a type into a members of pointer.
static MemberDefinition *get_members_of_str(char const *str) {
    // char
    if((strcmp(str, "char") == 0) || (strcmp(str, "char *") == 0) || (strcmp(str, "char **") == 0)) {
        static MemberDefinition members_of_char[] = {
            {MetaType_char, "", 0, false, 1}
        };
        return(members_of_char);

    // short
    } else if((strcmp(str, "short") == 0) || (strcmp(str, "short *") == 0) || (strcmp(str, "short **") == 0)) {
        static MemberDefinition members_of_short[] = {
            {MetaType_short, "", 0, false, 1}
        };
        return(members_of_short);

    // int
    } else if((strcmp(str, "int") == 0) || (strcmp(str, "int *") == 0) || (strcmp(str, "int **") == 0)) {
        static MemberDefinition members_of_int[] = {
            {MetaType_int, "", 0, false, 1}
        };
        return(members_of_int);

    // long
    } else if((strcmp(str, "long") == 0) || (strcmp(str, "long *") == 0) || (strcmp(str, "long **") == 0)) {
        static MemberDefinition members_of_long[] = {
            {MetaType_long, "", 0, false, 1}
        };
        return(members_of_long);

    // float
    } else if((strcmp(str, "float") == 0) || (strcmp(str, "float *") == 0) || (strcmp(str, "float **") == 0)) {
        static MemberDefinition members_of_float[] = {
            {MetaType_float, "", 0, false, 1}
        };
        return(members_of_float);

    // double
    } else if((strcmp(str, "double") == 0) || (strcmp(str, "double *") == 0) || (strcmp(str, "double **") == 0)) {
        static MemberDefinition members_of_double[] = {
            {MetaType_double, "", 0, false, 1}
        };
        return(members_of_double);

    // bool
    } else if((strcmp(str, "bool") == 0) || (strcmp(str, "bool *") == 0) || (strcmp(str, "bool **") == 0)) {
        static MemberDefinition members_of_bool[] = {
            {MetaType_bool, "", 0, false, 1}
        };
        return(members_of_bool);


    // Test
    } else if((strcmp(str, "Test") == 0) || (strcmp(str, "Test *") == 0) || (strcmp(str, "Test **") == 0)) {
        static MemberDefinition members_of_Test[] = {
            {MetaType_int, "i", offset_of(&_Test::i), false, 1},
            {MetaType_int, "j", offset_of(&_Test::j), true, 1},
        };
        return(members_of_Test);

    // V2
    } else if((strcmp(str, "V2") == 0) || (strcmp(str, "V2 *") == 0) || (strcmp(str, "V2 **") == 0)) {
        static MemberDefinition members_of_V2[] = {
            {MetaType_int, "e", offset_of(&_V2::e), false, 2},
            {MetaType_int, "x", offset_of(&_V2::x), false, 1},
            {MetaType_int, "y", offset_of(&_V2::y), false, 1},
        };
        return(members_of_V2);

    // A
    } else if((strcmp(str, "A") == 0) || (strcmp(str, "A *") == 0) || (strcmp(str, "A **") == 0)) {
        static MemberDefinition members_of_A[] = {
            {MetaType_int, "a", offset_of(&_A::a), false, 1},
        };
        return(members_of_A);

    // B
    } else if((strcmp(str, "B") == 0) || (strcmp(str, "B *") == 0) || (strcmp(str, "B **") == 0)) {
        static MemberDefinition members_of_B[] = {
            {MetaType_double, "b", offset_of(&_B::b), false, 1},
        };
        return(members_of_B);

    // Foo
    } else if((strcmp(str, "Foo") == 0) || (strcmp(str, "Foo *") == 0) || (strcmp(str, "Foo **") == 0)) {
        static MemberDefinition members_of_Foo[] = {
            {MetaType_char, "str", offset_of(&_Foo::str), true, 1},
            {MetaType_int, "int_ptr", offset_of(&_Foo::int_ptr), true, 1},
            {MetaType_float, "float_ptr", offset_of(&_Foo::float_ptr), true, 1},
            {MetaType_bool, "bool_ptr", offset_of(&_Foo::bool_ptr), true, 1},
            {MetaType_int, "int_array", offset_of(&_Foo::int_array), false, 4},
            {MetaType_double, "double_ptr_array", offset_of(&_Foo::double_ptr_array), true, 5},
            {MetaType_int, "int_ptr_array", offset_of(&_Foo::int_ptr_array), true, 6},
            {MetaType_V2, "v2", offset_of(&_Foo::v2), false, 1},
            // Members inherited from A.
            {MetaType_int, "a", (size_t)&((_Foo *)0)->a, false, 1},
            // Members inherited from B.
            {MetaType_double, "b", (size_t)&((_Foo *)0)->b, false, 1},
        };
        return(members_of_Foo);

    // V3
    } else if((strcmp(str, "V3") == 0) || (strcmp(str, "V3 *") == 0) || (strcmp(str, "V3 **") == 0)) {
        static MemberDefinition members_of_V3[] = {
            {MetaType_int, "x", offset_of(&_V3::x), false, 1},
            {MetaType_int, "y", offset_of(&_V3::y), false, 1},
            {MetaType_int, "z", offset_of(&_V3::z), false, 1},
        };
        return(members_of_V3);

    // VectorTest
    } else if((strcmp(str, "VectorTest") == 0) || (strcmp(str, "VectorTest *") == 0) || (strcmp(str, "VectorTest **") == 0)) {
        static MemberDefinition members_of_VectorTest[] = {
            {MetaType_std_vector_float, "vec_floating", offset_of(&_VectorTest::vec_floating), false, 1},
            {MetaType_std_vector_int, "vec_integer", offset_of(&_VectorTest::vec_integer), false, 1},
            {MetaType_std_vector_V3, "vec_vector3", offset_of(&_VectorTest::vec_vector3), false, 1},
            {MetaType_std_deque_int, "deque_int", offset_of(&_VectorTest::deque_int), false, 1},
            {MetaType_std_forward_list_int, "fl_int", offset_of(&_VectorTest::fl_int), false, 1},
            {MetaType_std_list_int, "list_int", offset_of(&_VectorTest::list_int), false, 1},
        };
        return(members_of_VectorTest);

    // IntTest
    } else if((strcmp(str, "IntTest") == 0) || (strcmp(str, "IntTest *") == 0) || (strcmp(str, "IntTest **") == 0)) {
        static MemberDefinition members_of_IntTest[] = {
            {MetaType_int, "i", offset_of(&_IntTest::i), false, 1},
        };
        return(members_of_IntTest);

    // StringTest
    } else if((strcmp(str, "StringTest") == 0) || (strcmp(str, "StringTest *") == 0) || (strcmp(str, "StringTest **") == 0)) {
        static MemberDefinition members_of_StringTest[] = {
            {MetaType_char, "text", offset_of(&_StringTest::text), true, 1},
            {MetaType_int, "len", offset_of(&_StringTest::len), false, 1},
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
    else if(strcmp(str, "IntTest") == 0) {return(1);} // IntTest
    else if(strcmp(str, "StringTest") == 0) {return(2);} // StringTest

    return(-1); // Error.
}

// Convert a type to a string.
template<typename T> static char const *weak_type_to_string_(void) {
    // Primitives.
    if(type_compare(T, char)) {return("char");}
    else if(type_compare(T, char *)) {return("char");}
    else if(type_compare(T, char **)) {return("char");}
    else if(type_compare(T, char &)) {return("char");}
    else if(type_compare(T, short)) {return("short");}
    else if(type_compare(T, short *)) {return("short");}
    else if(type_compare(T, short **)) {return("short");}
    else if(type_compare(T, short &)) {return("short");}
    else if(type_compare(T, int)) {return("int");}
    else if(type_compare(T, int *)) {return("int");}
    else if(type_compare(T, int **)) {return("int");}
    else if(type_compare(T, int &)) {return("int");}
    else if(type_compare(T, long)) {return("long");}
    else if(type_compare(T, long *)) {return("long");}
    else if(type_compare(T, long **)) {return("long");}
    else if(type_compare(T, long &)) {return("long");}
    else if(type_compare(T, float)) {return("float");}
    else if(type_compare(T, float *)) {return("float");}
    else if(type_compare(T, float **)) {return("float");}
    else if(type_compare(T, float &)) {return("float");}
    else if(type_compare(T, double)) {return("double");}
    else if(type_compare(T, double *)) {return("double");}
    else if(type_compare(T, double **)) {return("double");}
    else if(type_compare(T, double &)) {return("double");}
    else if(type_compare(T, bool)) {return("bool");}
    else if(type_compare(T, bool *)) {return("bool");}
    else if(type_compare(T, bool **)) {return("bool");}
    else if(type_compare(T, bool &)) {return("bool");}

    // Struct types.
    else if(type_compare(T, Test)) {return("Test");}
    else if(type_compare(T, Test *)) {return("Test");}
    else if(type_compare(T, Test **)) {return("Test");}
    else if(type_compare(T, Test &)) {return("Test");}
    else if(type_compare(T, V2)) {return("V2");}
    else if(type_compare(T, V2 *)) {return("V2");}
    else if(type_compare(T, V2 **)) {return("V2");}
    else if(type_compare(T, V2 &)) {return("V2");}
    else if(type_compare(T, A)) {return("A");}
    else if(type_compare(T, A *)) {return("A");}
    else if(type_compare(T, A **)) {return("A");}
    else if(type_compare(T, A &)) {return("A");}
    else if(type_compare(T, B)) {return("B");}
    else if(type_compare(T, B *)) {return("B");}
    else if(type_compare(T, B **)) {return("B");}
    else if(type_compare(T, B &)) {return("B");}
    else if(type_compare(T, Foo)) {return("Foo");}
    else if(type_compare(T, Foo *)) {return("Foo");}
    else if(type_compare(T, Foo **)) {return("Foo");}
    else if(type_compare(T, Foo &)) {return("Foo");}
    else if(type_compare(T, V3)) {return("V3");}
    else if(type_compare(T, V3 *)) {return("V3");}
    else if(type_compare(T, V3 **)) {return("V3");}
    else if(type_compare(T, V3 &)) {return("V3");}
    else if(type_compare(T, VectorTest)) {return("VectorTest");}
    else if(type_compare(T, VectorTest *)) {return("VectorTest");}
    else if(type_compare(T, VectorTest **)) {return("VectorTest");}
    else if(type_compare(T, VectorTest &)) {return("VectorTest");}
    else if(type_compare(T, std::vector<float>)) {return("std::vector<float>");}
    else if(type_compare(T, std::vector<float> *)) {return("std::vector<float>");}
    else if(type_compare(T, std::vector<float> **)) {return("std::vector<float>");}
    else if(type_compare(T, std::vector<float> &)) {return("std::vector<float>");}
    else if(type_compare(T, std::vector<int>)) {return("std::vector<int>");}
    else if(type_compare(T, std::vector<int> *)) {return("std::vector<int>");}
    else if(type_compare(T, std::vector<int> **)) {return("std::vector<int>");}
    else if(type_compare(T, std::vector<int> &)) {return("std::vector<int>");}
    else if(type_compare(T, std::vector<V3>)) {return("std::vector<V3>");}
    else if(type_compare(T, std::vector<V3> *)) {return("std::vector<V3>");}
    else if(type_compare(T, std::vector<V3> **)) {return("std::vector<V3>");}
    else if(type_compare(T, std::vector<V3> &)) {return("std::vector<V3>");}
    else if(type_compare(T, std::deque<int>)) {return("std::deque<int>");}
    else if(type_compare(T, std::deque<int> *)) {return("std::deque<int>");}
    else if(type_compare(T, std::deque<int> **)) {return("std::deque<int>");}
    else if(type_compare(T, std::deque<int> &)) {return("std::deque<int>");}
    else if(type_compare(T, std::forward_list<int>)) {return("std::forward_list<int>");}
    else if(type_compare(T, std::forward_list<int> *)) {return("std::forward_list<int>");}
    else if(type_compare(T, std::forward_list<int> **)) {return("std::forward_list<int>");}
    else if(type_compare(T, std::forward_list<int> &)) {return("std::forward_list<int>");}
    else if(type_compare(T, std::list<int>)) {return("std::list<int>");}
    else if(type_compare(T, std::list<int> *)) {return("std::list<int>");}
    else if(type_compare(T, std::list<int> **)) {return("std::list<int>");}
    else if(type_compare(T, std::list<int> &)) {return("std::list<int>");}
    else if(type_compare(T, IntTest)) {return("IntTest");}
    else if(type_compare(T, IntTest *)) {return("IntTest");}
    else if(type_compare(T, IntTest **)) {return("IntTest");}
    else if(type_compare(T, IntTest &)) {return("IntTest");}
    else if(type_compare(T, StringTest)) {return("StringTest");}
    else if(type_compare(T, StringTest *)) {return("StringTest");}
    else if(type_compare(T, StringTest **)) {return("StringTest");}
    else if(type_compare(T, StringTest &)) {return("StringTest");}

    else {return(0);} // Unknown Type.
}

// Get the number of base types.
template<typename T> static int get_base_type_count_(void) {
    if(type_compare(T, Foo)) {return(2);}

    return(0); // Not found.
}

// Get the base type.
template<typename T> static char const *get_base_type_as_string_(int index/*= 0*/) {
    if(type_compare(T, Foo)) {
        switch(index) {
            case 0: {return("A");} break;
            case 1: {return("B");} break;

            default: {assert(0);} break;
        } // switch(index)
    }

    return(0); // Not found.
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

#define weak_type_compare(A, B) TypeCompare_<pp::TypeStruct<A>::weak_type, pp::TypeStruct<B>::weak_type>::e;
#undef _std // :(
} // namespace pp

#endif // Header guard.


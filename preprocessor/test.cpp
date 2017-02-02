/*===================================================================================================
  File:                    test.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include "google_test/gtest.h"
#include "lexer.h"
namespace {
#include "lexer.cpp"
}
#include "test.h"

//
// Test utils.
//
StructData parse_struct_test(Char *str, int ahead = 0) {
    Tokenizer tokenizer = {str};

    eat_token(&tokenizer);
    for(int i = 0; (i < ahead); ++i) {
        parse_struct(&tokenizer, StructType_struct);
        eat_token(&tokenizer);
        eat_token(&tokenizer);
    }

    return(parse_struct(&tokenizer, StructType_struct).sd);
}

enum StructCompareFailure {
    StructCompareFailure_success,

    StructCompareFailure_name,
    StructCompareFailure_member_count,
    StructCompareFailure_members,
    StructCompareFailure_inherited_count,
    StructCompareFailure_inherited,
    StructCompareFailure_func_data,
    StructCompareFailure_func_count,
};
Char *struct_compare_failure_to_string(StructCompareFailure scf) {
    Char *res = 0;
    if(scf == StructCompareFailure_success)           { res = "StructCompareFailure_success";      }
    else if(scf == StructCompareFailure_name)         { res = "StructCompareFailure_name";         }
    else if(scf == StructCompareFailure_member_count) { res = "StructCompareFailure_member_count"; }
    else if(scf == StructCompareFailure_members)      { res = "StructCompareFailure_members";      }
    else if(scf == StructCompareFailure_inherited)    { res = "StructCompareFailure_inherited";    }
    else if(scf == StructCompareFailure_func_data)    { res = "StructCompareFailure_func_data";    }
    else if(scf == StructCompareFailure_func_count)   { res = "StructCompareFailure_func_count";   }

    return(res);
};

StructCompareFailure compare_struct_data(StructData a, StructData b) {
    StructCompareFailure res = StructCompareFailure_success;

    if(!string_compare(a.name, b.name))                                         { res = StructCompareFailure_name;            }
    else if(a.member_count != b.member_count)                                   { res = StructCompareFailure_member_count;    }
    else if(!compare_variable_array(a.members, b.members, a.member_count))      { res = StructCompareFailure_members;         }
    else if(a.inherited_count != b.inherited_count)                             { res = StructCompareFailure_inherited_count; }
    else if(!string_compare_array(a.inherited, b.inherited, a.inherited_count)) { res = StructCompareFailure_inherited;       }

    return(res);
}

//
// Tests.
//
TEST(StructTest, basic_struct_test) {
    Char *basic_struct = "struct BasicStruct {\n"
                         "    int i;\n"
                         "    float *f;\n"
                         "    bool b[10];\n"
                         "    double *d[12];\n"
                         "};\n";

    StructData hardcoded = {};
    hardcoded.name = create_string("BasicStruct");
    hardcoded.member_count = 4;
    hardcoded.members = cast(Variable *)malloc(sizeof(Variable) * hardcoded.member_count);
    Int member_index = 0;
    hardcoded.members[member_index++] = create_variable("int", "i");
    hardcoded.members[member_index++] = create_variable("float", "f", true);
    hardcoded.members[member_index++] = create_variable("bool", "b", false, 10);
    hardcoded.members[member_index++] = create_variable("double", "d", true, 12);

    StructData generated = parse_struct_test(basic_struct);
    StructCompareFailure struct_compare_failure = compare_struct_data(hardcoded, generated);
    ASSERT_TRUE(struct_compare_failure == StructCompareFailure_success)
            << "Failed because struct_compare_failure == " << struct_compare_failure_to_string(struct_compare_failure);
}

TEST(StructTest, inhertiance_struct_test) {
    Char *inheritance_struct = "struct BaseOne { int a; };\n"
                               "struct BaseTwo { int b; };\n"
                               "struct Sub : public BaseOne, public BaseTwo { int c; };";

    StructData hardcoded = {};
    hardcoded.name = create_string("Sub");
    hardcoded.member_count = 1;
    hardcoded.members = cast(Variable *)malloc(sizeof(Variable));
    *hardcoded.members = create_variable("int", "c");
    hardcoded.inherited_count = 2;
    hardcoded.inherited = alloc(String, hardcoded.inherited_count);
    hardcoded.inherited[0] = create_string("BaseOne");
    hardcoded.inherited[1] = create_string("BaseTwo");

    StructData generated = parse_struct_test(inheritance_struct, 2);
    StructCompareFailure struct_compare_failure = compare_struct_data(hardcoded, generated);
    ASSERT_TRUE(struct_compare_failure == StructCompareFailure_success)
            << "Failed because struct_compare_failure == " << struct_compare_failure_to_string(struct_compare_failure);
}

TEST(StructTest, number_of_members_test) {
    Char *str = "struct A { int a; int b; int c; };";
    StructData gen = parse_struct_test(str);
    ASSERT_TRUE(gen.member_count == 3) << "Error: Number of members in struct not correct";
}

TEST(StructTest, struct_name) {
    Char *str = "struct my_name {};";
    StructData gen = parse_struct_test(str);
    ASSERT_TRUE(string_compare("my_name", gen.name.e, gen.name.len)) << "Error: Failed to properly generate struct name.";
}

EnumData parse_enum_test(Char *str) {
    Tokenizer tokenizer = {str};

    eat_token(&tokenizer);
    return(parse_enum(&tokenizer).ed);
}

TEST(EnumTest, enum_name_test) {
    Char *str = "enum MyName {};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(string_compare("MyName", gen.name.e, gen.name.len)) << "Error: Failed to properly generate enum name.";
}

TEST(EnumTest, enum_type_test) {
    Char *str = "enum Enum : short {};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(string_compare("short", gen.type.e, gen.type.len)) << "Error: Failed to properly handle enum type.";
}

TEST(EnumTest, enum_class_test) {
    Char *str = "enum class Enum {};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(gen.is_struct) << "Error: Failed to properly handle an enum class.";
}

TEST(EnumTest, enum_number_of_values_test) {
    Char *str = "enum Nums {one, two, three};";
    EnumData gen = parse_enum_test(str);
    ASSERT_TRUE(gen.no_of_values == 3) << "Error: Did not generate the correct number of values for an enum.";
}

Int run_tests(void) {
    Int res = 0;
    // Google test uses so much memory, it's difficult to run in x86.
    if(sizeof(PtrSize) == 8) {
        Char *flags[] = {"--gtest_break_on_failure", "--gtest_catch_exceptions=0"};
        Int number_of_flags = array_count(flags);

        testing::InitGoogleTest(&number_of_flags, flags);
        res = RUN_ALL_TESTS();
    }

    return(res);
}

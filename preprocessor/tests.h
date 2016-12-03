/*===================================================================================================
  File:                    tests.h
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#if !defined(TESTS_H)

#if INTERNAL

#if defined(internal)
    #undef internal
#endif
#if defined(global)
    #undef global
#endif

#include "google_test/gtest.h"

//
// Test Structs.
//
StructData
parse_struct_test(Char *str)
{
    Tokenizer tokenizer = {str};
    eat_token(&tokenizer);

    return(parse_struct(&tokenizer).sd);
}

enum StructCompareFailure {
    StructCompareFailure_success,

    StructCompareFailure_name,
    StructCompareFailure_member_count,
    StructCompareFailure_members,
    StructCompareFailure_inherited,
    StructCompareFailure_func_data,
    StructCompareFailure_func_count,
};
Char *
struct_compare_failure_to_string(StructCompareFailure scf)
{
    Char *res = 0;
    if(scf == StructCompareFailure_success)       { res = "StructCompareFailure_success";      }
    if(scf == StructCompareFailure_name)          { res = "StructCompareFailure_name";         }
    if(scf == StructCompareFailure_member_count)  { res = "StructCompareFailure_member_count"; }
    if(scf == StructCompareFailure_members)       { res = "StructCompareFailure_members";      }
    if(scf == StructCompareFailure_inherited)     { res = "StructCompareFailure_inherited";    }
    if(scf == StructCompareFailure_func_data)     { res = "StructCompareFailure_func_data";    }
    if(scf == StructCompareFailure_func_count)    { res = "StructCompareFailure_func_count";   }

    return(res);
};

StructCompareFailure
compare_struct_data(StructData a, StructData b)
{
    StructCompareFailure res = StructCompareFailure_success;

    if(0) {}
    else if(!string_compare(a.name, b.name))                               { res = StructCompareFailure_name;         }
    else if(a.member_count != b.member_count)                              { res = StructCompareFailure_member_count; }
    else if(!compare_variable_array(a.members, b.members, a.member_count)) { res = StructCompareFailure_members;      }
    else if(!string_compare(a.inherited, b.inherited))                     { res = StructCompareFailure_inherited;    }
    else if(a.func_count != b.func_count)                                  { res = StructCompareFailure_func_count;   }
    // TODO(Jonny): Do func_data.

    return(res);
}

TEST(StructTest, basic_struct_test)
{
    Char *basic_struct = "struct BasicStruct {\n"
                         "    int i;\n"
                         "    float *f;\n"
                         "    bool b[10];\n"
                         "};\n";
    StructData hardcoded_basic_struct = {};
    hardcoded_basic_struct.name = create_string("BasicStruct");
    hardcoded_basic_struct.member_count = 3;
    hardcoded_basic_struct.members = new Variable[hardcoded_basic_struct.member_count];

    Int member_index = 0;
    hardcoded_basic_struct.members[member_index++] = create_variable("int", "i");
    hardcoded_basic_struct.members[member_index++] = create_variable("float", "f", true);
    hardcoded_basic_struct.members[member_index++] = create_variable("bool", "b", false, 10);

    StructData generated_basic_struct = parse_struct_test(basic_struct);

    StructCompareFailure struct_compare_failure = compare_struct_data(hardcoded_basic_struct, generated_basic_struct);
    ASSERT_TRUE(struct_compare_failure == StructCompareFailure_success)
            << "Failed because struct_compare_failure == " << struct_compare_failure_to_string(struct_compare_failure);
}

#endif

Int
run_tests(void)
{
    Int res = 0;
#if INTERNAL
    // Google test uses so much memory, it's difficult to run in x86.
    if(sizeof(PtrSize) == 8) {
        Char *flags[] = {"--gtest_list_tests", "--gtest_repeat=1", "--gtest_break_on_failure"};
        Int number_of_flags = array_count(flags);

        testing::InitGoogleTest(&number_of_flags, flags);
        res = RUN_ALL_TESTS();
    }
#endif
    return(res);
}

#define TESTS_H
#endif

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

int add(int a, int b) { return(a + b); }

TEST(AddTest, Test)
{
    EXPECT_EQ(4, add(2, 2));
    EXPECT_EQ(8, add(7, 1));
    EXPECT_EQ(10, add(4, 6));
    EXPECT_EQ(3, add(2, 1));
}
#endif

Int
run_tests(void)
{
    Int res = 0;
#if INTERNAL
    Char *flags[] = {"--gtest_list_tests", "--gtest_repeat=1", /*"--gtest_break_on_failure"*/};
    Int number_of_flags = array_count(flags);

    testing::InitGoogleTest(&number_of_flags, flags);
    res = RUN_ALL_TESTS();
#endif
    return(res);
}

#define TESTS_H
#endif
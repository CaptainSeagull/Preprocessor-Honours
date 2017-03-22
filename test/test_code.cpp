#include "pp_generated/test_code_generated.h"
#include <iostream>

enum class Numbers : int {
    zero,
    one,
    two,
    three
};

int main(int argc, char **argv) {
    char const *zero_str = pp::enum_to_string<Numbers>(Numbers::zero);
    std::cout << zero_str << std::endl; // Prints "zero"

    Numbers one_cpy = Numbers::one;
    char const *one_str = pp::enum_to_string<Numbers>(one_cpy);
    std::cout << one_str << std::endl; // Prints "One"

    int as_integer = 1;
    ++as_integer;
    char const *two_str = pp::enum_to_string<Numbers>((Numbers)as_integer);
    std::cout << two_str << std::endl; // Prints "Two"

    return(0);
}

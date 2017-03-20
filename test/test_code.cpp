#include <iostream>
#include <typeinfo.h>

class Base {};
class Derived : public Base {};

int main(int argc, char **argv) {
    Derived *derived = new Derived;
    Base *base = derived;

    std::cout << typeid(base).name()     << std::endl; // "class Base *"
    std::cout << typeid(*base).name()    << std::endl; // "class Derived"
    std::cout << typeid(derived).name()  << std::endl; // "class Derived *"
    std::cout << typeid(*derived).name() << std::endl; // "class Derived"

    return(0);
}
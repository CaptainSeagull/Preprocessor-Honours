#include "pp_generated/test_code_generated.h"
#include <string.h>

class Shape {
public:
    int width;
    int height;
};

class Rectangle : public Shape {
public:
    std::string s;
};

int main(int argc, char **argv) {

    Rectangle r;
    r.width = 10;
    r.height = 10;
    r.s = "Hello World";

    pp::print(r);

    return(0);
}

// To build: g++ -std=c++14 example.cpp -o example

#include <iostream>
#include "curry.hpp"

int add_then_sub(int x, int y, int z) {
    return x + y - z;
}

// auto return type to save lots of typing
// this is also an example of eta reduction
auto step_one() {
    // first template parameter is the return type, the others are arguments' types
    return curry(add_then_sub)(5);
}

int main(int argc, char* argv[]) {
    std::cout << uncurry(step_one())(4, 3) << "\n";

    return 0;
}
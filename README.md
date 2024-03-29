This is a tiny header file that allows you to use all objects that would otherwise be usable with `std::function` in a curried manner, like in functional languages.


Dependencies
============

A sane compiler (with C++14 support). Tested on MinGW-w64 with g++ 4.9.1. Should work fine with clang, probably doesn't with MSVC.


Example
=======

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

Output:
    
    6


But why?
========

I was bored.


But we already have `std::bind`!
================================

I was bored.


License
=======

This is meant mostly for educational/"because-I-can" purposes, rather than being usable. The code is so short it's not unrealistic to write something similar by accident. However, if you for some reason think using this in actual, real-world code is a good idea, then you can do so under the terms of the Simplified BSD license, as provided in the `LICENSE` file.

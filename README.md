This is a tiny header file that allows you to use all objects that would otherwise be usable with `std::function` in a curried manner, like in functional languages.

Dependencies
============

A sane compiler (one with C++14 support).

Example
=======

    #include <iostream>
    #include "curry.hpp"

    int add_then_sub(int x, int y, int z) {
        return x + y - z;
    }

    int step_one() {
        // first template parameter is the return type, the others are arguments' types
        return Curried<int, int, int, int>(add_then_sub)(5);
    }

    int main(int argc, char* argv[]) {
        std::cout << step_one()(4)(3) << "\n";

        return 0;
    }

Output:
    
    6

But why?
========

I was bored.


License
=======

If you for some reason think using this in actual, real-world code is a good idea, then you can do so under the terms of the Simplified BSD license, as provided in the `LICENSE` file.
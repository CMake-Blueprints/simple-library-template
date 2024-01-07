#include <cassert>
#include <iostream>

#include "simplelib/simplelib.h"

using namespace simplelib;

int main() {
    assert(the_answer() == 42);
    std::cout << "All tests passed!\n";
    return 0;
}

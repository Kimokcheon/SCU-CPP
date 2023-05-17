// system and timing
#include <iostream>
#include <chrono>

// data structure imports
#include <deque>
#include <vector>
#include <iterator>
#include <utility> // pair

using std::cout;    using std::endl;

// myMin function from lecture

int main() {

    /*
     * explicit instantiation of template function (3, 4), (3.2, 3.1), (Frankie, Sathya)
     */


    /*
     * implicit (type-deduced) instantiation of template function (4, 5), (4, 3.2)
     */

    // string literals like the ones below are c-strings, with a "char *" data type.
    // char *'s are pointers, which means myMin is comparing the addresses of these two strings,
    // and not the letters themselves! this is a danger of type deduction.

    return 0;
}


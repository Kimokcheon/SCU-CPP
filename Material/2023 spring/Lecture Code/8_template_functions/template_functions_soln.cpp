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
template <typename T>
T myMin(T a, T b) {
    return a < b ? a : b;
}

// auto-return type + multiple types
template <typename T, typename U>
auto smarterMyMin(const T& a, const U& b) {
    return a < b ? a : b;
}

int main() {

    /*
     * explicit instantiation of template function
     */
    cout << myMin<std::string>("Frankie", "Sathya") << endl;
    cout << myMin<int>(3, 4) << endl;
    cout << myMin<double>(3.2, 3.1) << endl;


    /*
     * implicit (type-deduced) instantiation of template function
     */
    cout << myMin(4, 5) << endl;
    cout << smarterMyMin(4, 3.2) << endl;

    // string literals like the ones below are c-strings, with a "char *" data type.
    // char *'s are pointers, which means myMin is comparing the addresses of these two strings,
    // and not the letters themselves! this is a danger of type deduction.
    cout << myMin("Frankie", "Sathya") << endl;

    return 0;
}


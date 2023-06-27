#include <iostream>
#include <cstdio>

template<typename T>
void swap(T& a, T& b) {
    T c = a;
    a = b;
    b = c;
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << "before swap:";
    std::cout << "a=" << a << "," << "b=" << b << std::endl;
    swap(a, b);
    std::cout << "after  swap:";
    std::cout << "a=" << a << "," << "b=" << b << std::endl;
    return 0;
}
#include <iostream>
#include <cstdio>
#include <vector>

std::vector<int> vec;

int main() {
    for (int i = 0; i < 5; ++i) {
        int x;
        std::cin >> x;
        vec.push_back(x);
    }
    // 正向遍历
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // 反向遍历
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
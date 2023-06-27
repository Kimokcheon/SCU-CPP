#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

// 用于存储学生信息
struct Student {
    std::string name;
    double score;
};

std::vector<Student> stu;

int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::string name;
        double scr;
        std::cin >> name >> scr;
        stu.push_back({name, scr});
    }
    std::ofstream fout("stu.dat");
    for (auto y : stu) {
        fout << y.name << " "<< y.score << std::endl;
    }
    return 0;
}
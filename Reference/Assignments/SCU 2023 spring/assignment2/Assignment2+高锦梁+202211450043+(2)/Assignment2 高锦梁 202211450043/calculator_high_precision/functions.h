
#ifndef CALCULATOR_HIGH_PRECISION_FUNCTIONS_H
#define CALCULATOR_HIGH_PRECISION_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Functions {
public:
    int LmoreThanR(string a, string b);
    string add(string a, string b);
    string add_decimal(string a, string b);
    string multiply(char a, string b);
    string multiply_decimal(string a, string b);
    string minus(string a, string b);
    string minus_decimal(string a, string b);
};


#endif //CALCULATOR_HIGH_PRECISION_FUNCTIONS_H

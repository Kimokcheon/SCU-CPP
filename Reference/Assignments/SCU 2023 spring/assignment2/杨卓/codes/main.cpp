#include <iostream>
#include <cstring>
#include "expression.h"
using namespace std;
using EXP::Expression;
int main(){
    while (1) {
        string str;
        getline(cin, str);
        if (str == "exit") break;
        Expression expr;
        expr = str;
        expr.produce();
    }
    return 0;
}
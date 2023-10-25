

#ifndef CALCULATOR_FUNCTIONS_H
#define CALCULATOR_FUNCTIONS_H

#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

class functions {
    public:
        bool isOpChar(char a);
        bool isChar(char a);
        bool nameRight(char a);
        int priority(char op);
        double calculate(double a, double b, char op);
        double evaluate(string expr);
        void getExpressions(string a[], int &t);
        void preDeal(string a[], pair<string, string> value[], int &end);
        void isError(string a[], pair<string, string> value[], int &end);
};


#endif //CALCULATOR_FUNCTIONS_H

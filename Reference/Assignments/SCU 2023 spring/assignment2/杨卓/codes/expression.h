#pragma once
#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <map>

namespace EXP {

// accuracy
const double eps = 1e-6;

// Error message
const int NO_ERROR = 0;
const int ERROR_DIVIDE_BY_ZERO = 1;
const int ERROR_BRACKET = 1<<1;
const int ERROR_VARIABLE_NAME = 1<<2;
const int ERROR_CONST_VALUE = 1<<3;
const int ERROR_UNDEFINED_VARIABLE = 1<<4;

class Expression {
  private:
    std::string expr;
    int length;// length of expr
    static std::map<std::string,double> var_map;// variables
    std::stack<double> number_stack;
    std::stack<int> option_stack;
    int error_number;
    std::string getVariableName(const int &pos);// position of '='
    std::pair<double, int> getNumberFrom(const int &pos);
    void function_produce(const int &option);
    void value_calc();
    bool basic_option(const char &option);
    bool isLegalName(const std::string &var_name);
    void printErrorMessage();
    std::pair<std::string, int> getName(const int &pos);
    int judgeFunction(const std::string &fun_name);
    bool judgeConstValue(const std::string &var_name);
    std::pair<bool, double> calc();
  public:
    Expression();
    Expression(std::string);
    void produce();// main produce function
};

}
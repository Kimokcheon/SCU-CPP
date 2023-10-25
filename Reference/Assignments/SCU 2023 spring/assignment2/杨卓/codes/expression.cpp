#include "expression.h"
#include <cstring>
#include <iostream>
#include <cmath>
#include <iomanip>

namespace EXP {

std::map<std::string, double> Expression::var_map;

// private:

std::string Expression::getVariableName(const int &pos) {
    std::string name = expr.substr(0, pos);
    int len = name.length();
    int i = 0, j = len-1;
    while (i < len && name[i] == ' ') ++i;
    while (j >= 0 && name[j] == ' ') --j;
    return name.substr(i, j-i+1);
}

void Expression::function_produce(const int &option) {
    /*
        option = -1 refers to sqrt
        option = -2 refers to exp
        option = -3 refers to abs
        option = -4/-5/-6 refers to sin/cos/tan
        option = -7 refers to max
    */
    double x = number_stack.top();
    number_stack.pop();
    if (option == -1) number_stack.push(std::sqrt(x));
    else if (option == -2) number_stack.push(std::exp(x));
    else if (option == -3) number_stack.push(std::fabs(x));
    else if (option == -4) number_stack.push(std::sin(x));
    else if (option == -5) number_stack.push(std::cos(x));
    else if (option == -6) number_stack.push(std::tan(x));
    else if (option == -7) {
        double y = number_stack.top();
        number_stack.push(std::max(x, y));
    } else error_number |= ERROR_UNDEFINED_VARIABLE;
}

std::pair<double, int> Expression::getNumberFrom(const int &pos) {
    double res = 0, base = 0.1;
    int fn = length-1, fn0 = 0;
    for (int i = pos; i < length; ++i) {
        if (expr[i] >= '0' && expr[i] <= '9') res = res*10+expr[i]-'0';
        else {
            fn = i-1;
            break;
        }
    }
    if (fn+1 < length && expr[fn+1] == '.') {
        fn0 = fn+2;
        fn = length-1;
        for (int i = fn0; i < length; ++i) {
            if (expr[i] >= '0' && expr[i] <= '9') {
                res += base*(expr[i]-'0');
                base *= 0.1;
            } else {
                fn = i-1;
                break;
            }
        }
    }
    return std::make_pair(res, fn);
}

bool Expression::basic_option(const char &option) {
    if (option == '+' || option == '-' || option == '*' || option == '/') return true;
    else return false;
}

void Expression::value_calc() {
    double x1 = 0, x2 = 0;
    int op = option_stack.top();
    if (basic_option(op)) {
        x1 = number_stack.top();
        number_stack.pop();
        x2 = number_stack.top();
        number_stack.pop();
        if (op == '+') {
            number_stack.push(x1+x2);
        } else if (op == '-') {
            number_stack.push(x2-x1);
        } else if (op == '*') {
            number_stack.push(x2*x1);
        } else if (op == '/') {
            if (std::fabs(x1) < eps) {
                error_number |= ERROR_DIVIDE_BY_ZERO;
                number_stack.push(0);
            } else number_stack.push(x2/x1);
        }
    } else {
        function_produce(op);
    }
}

bool Expression::isLegalName(const std::string &var_name) {
    int len = var_name.length();
    int i = 0, j = len-1;
    while (i < len && var_name[i] == ' ') i++;
    while (j >= 0 && var_name[j] == ' ') j--;
    for (int k = i; k <= j; ++k) {
        if (!((var_name[k] >= 'A' && var_name[k] <= 'Z') || (var_name[k] >= 'a' && var_name[k] <= 'z') || var_name[k] == '_')) return 0;
    }
    return 1;
}

void Expression::printErrorMessage() {
    if (error_number == ERROR_DIVIDE_BY_ZERO) std::cerr << "#INFINITE" << std::endl;
    if (error_number & ERROR_BRACKET) std::cerr << "The bracket is not matching! (error message)" << std::endl;
    if (error_number & ERROR_VARIABLE_NAME) std::cerr << "The variable name is not valid! (error message)" << std::endl;
    if (error_number & ERROR_CONST_VALUE) std::cerr << "This is constant value. Cannot be changed! (error message)" << std::endl;
    if (error_number & ERROR_UNDEFINED_VARIABLE) std::cerr << "The variable does not exist! (error message)" << std::endl;
}

std::pair<std::string, int> Expression::getName(const int &pos) {
    int fn = length-1;
    for (int i = pos; i < length; ++i) {
        if ((expr[i] >= 'a' && expr[i] <= 'z') || (expr[i] >= 'A' && expr[i] <= 'Z') || expr[i] == '_') continue;
        else {
            fn = i-1;
            break;
        }
    }
    return std::make_pair(expr.substr(pos, fn-pos+1), fn);
}

int Expression::judgeFunction(const std::string &fun_name) {
    /*
        option = -1 refers to sqrt
        option = -2 refers to exp
        option = -3 refers to abs
        option = -4/-5/-6 refers to sin/cos/tan
        option = -7 refers to max
    */
    if (fun_name == "sqrt") return -1;
    if (fun_name == "exp") return -2;
    if (fun_name == "abs") return -3;
    if (fun_name == "sin") return -4;
    if (fun_name == "cos") return -5;
    if (fun_name == "tan") return -6;
    if (fun_name == "max") return -7;
    return 0;// variable name
}

bool Expression::judgeConstValue(const std::string &var_name) {
    // std::cout << var_name << " " << var_name.length() << std::endl;
    if (var_name == "PI" || var_name == "E") return true;
    return false; 
}

std::pair<bool, double> Expression::calc() {
    int fr = 0;
    while (fr < length && expr[fr] == ' ') ++fr;
    expr = expr.substr(fr, length-fr);
    if (expr[0] == '-') expr = "0"+expr;
    length = expr.length();
    for (int i = 0; i < length; ++i) {
        if (expr[i] == ',') continue;
        if (expr[i] >= '0' && expr[i] <= '9') {
            auto t = getNumberFrom(i);
            number_stack.push(t.first);
            i = t.second;
        } else if (expr[i] == '(') {
            option_stack.push('(');
        } else if (expr[i] == ')') {
            while (!option_stack.empty() && option_stack.top() != '(') {
                value_calc();
                option_stack.pop();
            }
            if (!option_stack.empty() && option_stack.top() == '(') option_stack.pop();
            else if (option_stack.empty()) error_number |= ERROR_BRACKET;
            if (!option_stack.empty() && option_stack.top() < 0) {
                value_calc();
                option_stack.pop();
            }
        } else if (basic_option(expr[i])) {
            if (expr[i] == '+') {
                while (!option_stack.empty() && option_stack.top() != '+'
                     && option_stack.top() != '-' && option_stack.top() !='(') {
                    value_calc();
                    option_stack.pop();
                }
                option_stack.push('+');
            } else if (expr[i] == '-') {
                while (!option_stack.empty() && option_stack.top() != '+'
                     && option_stack.top() != '-' && option_stack.top() !='(') {
                    value_calc();
                    option_stack.pop();
                }
                option_stack.push('-');
            } else if (expr[i] == '*' || expr[i] == '/') {
                option_stack.push(expr[i]);
            }
        } else if (expr[i] != ' ') {
            // function name & variable name
            auto t = getName(i);
            std::string name = t.first;
            i = t.second;
            int j = judgeFunction(name);
            if (j < 0) {
                // name is a function, id is j
                option_stack.push(j);
            } else {
                // name is a variable
                if (Expression::var_map.find(name) != Expression::var_map.end()) {
                    number_stack.push(Expression::var_map[name]);
                } else if (judgeConstValue(name)){
                    if (name == "PI") number_stack.push(std::acos(-1));
                    if (name == "E") number_stack.push(std::exp(1));
                } else {
                    error_number |= ERROR_UNDEFINED_VARIABLE;
                    break;
                }
            }
        }
        if (error_number != 0) break;
    }
    if (error_number != 0) return std::make_pair(true, 0);
    while (!option_stack.empty()) {
        if (option_stack.top() == '(') {
            error_number |= ERROR_BRACKET;
            break;
        }
        value_calc();
        option_stack.pop();
    }
    if (error_number != 0) return std::make_pair(true, 0);

    // without error
    return std::make_pair(false, number_stack.top());
}

// public:

Expression::Expression() {
    expr = "";
    length = 0;
    error_number = 0;
}

Expression::Expression(std::string S) {
    expr = S;
    length = expr.length();
    error_number = 0;
}

void Expression::produce() {
    bool isVar = 0;
    for (int i = 0; i < length; ++i) {
        if (expr[i] == '=') {
            std::string name = getVariableName(i);
            if (!isLegalName(name)) {
                error_number |= ERROR_VARIABLE_NAME;
                break;
            }
            if (judgeConstValue(name)) {
                error_number |= ERROR_CONST_VALUE;
                break;
            }
            expr = expr.substr(i+1, length-i-1);
            auto [error, value] = calc();
            if (error) break;
            Expression::var_map[name] = value;
            isVar = 1;
            break;
        }
    }
    if (error_number != NO_ERROR) {
        printErrorMessage();
        return;
    }
    if (!isVar) {
        auto [error, value] = calc();
        if (error) printErrorMessage();
        else std::cout << std::fixed << std::setprecision(6) << value << std::endl;
    }
}

}
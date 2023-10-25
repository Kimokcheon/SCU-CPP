#include <iostream>
#include "Calculation.h"
#include <string>
#include <cmath>
#include <any>
#include <algorithm>
#include <random>
using namespace std;
bool Calculation::isNumber(char c) {
    return c >= '0' && c <= '9';
}
//获取优先级前提是是运算符，所以不用判断
//操作符有两种一种是字符，一种是字符串

int Calculation::getPriority(std::any ch) {
    if(ch.type() == typeid(char))
    {
        if (std::any_cast<char>(ch) == '(' || std::any_cast<char>(ch) == ')')
            return 0;
        else if(std::any_cast<char>(ch) == '+' || std::any_cast<char>(ch) == '-')
            return 1;
        else if(std::any_cast<char>(ch) == '*' || std::any_cast<char>(ch) == '/')
            return 2;
        else
            return -1;
    }
    else if(ch.type() == typeid(string))
    {
        //不需要参数
        if (std::any_cast<string>(ch) == "random")
            return 3;
        //单目函数
        else if (std::any_cast<string>(ch) == (string )"sin" || std::any_cast<string>(ch) == (string )"cos" ||
            std::any_cast<string>(ch) == (string )"tan" || std::any_cast<string>(ch) == (string )"asin" ||
            std::any_cast<string>(ch) == (string )"acos" || std::any_cast<string>(ch) == (string )"atan"||
            std::any_cast<string>(ch) == (string )"abs" || std::any_cast<string>(ch) == (string )"sqr"||
            std::any_cast<string>(ch) == (string )"sqrt" ||std::any_cast<string>(ch) == (string )"lon" ||
            std::any_cast<string>(ch) == (string )"exp")
        return 4;
        //双目函数
        else if (std::any_cast<string>(ch) == "max" ||std::any_cast<string>(ch) == "log" || std::any_cast<string>(ch) == "pow")
            return 5;
        else
            return -1;
    }
    else
        return -1;
}

//运算符返回1，函数返回2，数字返回0，其他返回-1
int Calculation::isOperator(string ch,int n,int length) {
    if(ch[n] == '+' || ch[n] == '-' || ch[n] == '*' || ch[n] == '/' || ch[n] == '(' || ch[n] == ')')
        return 1;
    //函数名称里面不会有空格
    else if(n+2 <= length && ch[n] == 'a' && ch[n+1] == 'b' && ch[n+2] == 's' || //abs
            n+2 <= length && ch[n] == 's' && ch[n+1] == 'i' && ch[n+2] == 'n' || //sin
            n+2 <= length && ch[n] == 'c' && ch[n+1] == 'o' && ch[n+2] == 's' || //cos
            n+2 <= length && ch[n] == 't' && ch[n+1] == 'a' && ch[n+2] == 'n' || //tan
            n+2 <= length && ch[n] == 'l' && ch[n+1] == 'o' && ch[n+2] == 'g' || //log
//            n+2 <= length && ch[n] == 's' && ch[n+1] == 'q' && ch[n+2] == 'r' || //sqr    //sqr和sqrt有冲突,所以不用
            n+2 <= length && ch[n] == 'p' && ch[n+1] == 'o' && ch[n+2] == 'w' || //pow
            n+2 <= length && ch[n] == 'm' && ch[n+1] == 'a' && ch[n+2] == 'x' || //max
//            n+2 <= length && ch[n] == 'l' && ch[n+1] == 'n' && ch[n+2] == 'n' ||//lon
            n+2 <= length && ch[n] == 'e' && ch[n+1] == 'x' && ch[n+2] == 'p' )//exp
        return 2;
    else if(n+3 <= length && ch[n] == 'a' && ch[n+1] == 's' && ch[n+2] == 'i' && ch[n+3] == 'n' || //asin
            n+3 <= length && ch[n] == 'a' && ch[n+1] == 'c' && ch[n+2] == 'o' && ch[n+3] == 's' || //acos
            n+3 <= length && ch[n] == 'a' && ch[n+1] == 't' && ch[n+2] == 'a' && ch[n+3] == 'n' || //atan
            n+3 <= length && ch[n] == 's' && ch[n+1] == 'q' && ch[n+2] == 'r' && ch[n+3] == 't' ) //sqrt
        return 3;
    else if(n+5 <= length && ch[n] == 'r' && ch[n+1] == 'a' && ch[n+2] == 'n' && ch[n+3] == 'd' && ch[n+4] == 'o' && ch[n+5] == 'm')//random
        return 5;
    else if(ch[n] >= '0' && ch[n] <= '9')
        return 0;
    else
        return -1;
}
void Calculation::get_expression() {
    std::cout << "Please enter the expression to be calculated:\n";
    std::getline(std::cin, expression);
    //删除expression里面的空格
    expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    //在(和-之间加上0
    int length = (int)expression.length();
    for (int i = 0; i < length; i++) {
        if (expression[i] == '(' && expression[i + 1] == '-') {
            expression.insert(i + 1, "0");
            length++;
        }
    }
    for (int i = 0; i < length; i++) {
        if (expression[i] == 'P' && expression[i + 1] == 'I') {
            expression.erase(i,2);
            expression.insert(i, "3.1415926535");
            length = (int)expression.length();
        }
    }

//    cout << expression << endl;
}
void Calculation::expression_to_infix() {
    int length;
    length = (int)expression.length();
    for (int i = 0; i < length; i++) {
        if (isNumber(expression[i])) {
            double temp = (double)stoi(&expression[i]);
            while (isNumber(expression[i]) && i < length) {
                i++;
            } if(expression[i] == '.' && i < length){
                i++;
                int j = 1;
                while (isNumber(expression[i])) {
                    temp += (expression[i] - '0') * pow(10, -j);
                    j++;
                    i++;
                }
            }
            i--;
            if(temp-(int)temp == 0)
                infix_expression.emplace_back((int)temp);
            else
                infix_expression.emplace_back(temp);
        } else if(expression[i] ==  ','){
            continue;
        } else if (isOperator(expression, i, length) == 1) {
            infix_expression.emplace_back(expression[i]);
        } else if (isOperator(expression, i, length) == 2) {
            infix_expression.emplace_back(expression.substr(i, 3));
            i += 2;
        } else if (isOperator(expression, i, length) == 3) {
            infix_expression.emplace_back(expression.substr(i, 4));
            i += 3;
        } else if (isOperator(expression, i, length) == 5) {
            infix_expression.emplace_back(expression.substr(i, 6));
            i += 5;
        } else if (isOperator(expression, i, length) == -1) {
            std::cout << "Error: Invalid expression!\n";
            exit(0);
        }
    }
    //输出中缀表达式
//    for (auto & i : infix_expression){
//        if (i.type() == typeid(int)){
//            std::cout << std::any_cast<int>(i);
//        }
//        else if (i.type() == typeid(double)){
//            std::cout << std::any_cast<double>(i);
//        }
//        else if (i.type() == typeid(std::string)){
//            std::cout << std::any_cast<string>(i);
//        }
//        else if (i.type() == typeid(char)){
//            std::cout << std::any_cast<char>(i);
//        }
//    }
//    cout << endl;
}
int Calculation::infix_to_postfix() {
    for (auto & i : infix_expression){
        //如果是数字
        if (i.type() == typeid(int)){
            postfix_expression.push_back(i);
        } else if (i.type() == typeid(double)){
            postfix_expression.push_back(i);
        }
        //如果是运算符
        else {
            //'('
            if(i.type() == typeid(char) && std::any_cast<char>(i) == '(')
            {
                operator_stack.emplace(std::any_cast<char>(i));
            }
            //')'
            else if(i.type() == typeid(char) && std::any_cast<char>(i) == ')')
            {
                while(!operator_stack.empty() && (operator_stack.top().type() == typeid(char) && any_cast<char>(operator_stack.top()) != '(' || operator_stack.top().type() == typeid(std::string))){
                    postfix_expression.emplace_back(operator_stack.top());
                    operator_stack.pop();
                }
                if( operator_stack.top().type() == typeid(char) && any_cast<char>(operator_stack.top()) == '('){
                    operator_stack.pop();
                }
                else if(operator_stack.empty())
                {
                    return 1;
                }
            }
            //+ — * /
            else{
                //栈为空，或者栈里面的运算符优先级小于当前运算符0
                if(i.type() == typeid(char) && (operator_stack.empty() || getPriority(operator_stack.top()) < getPriority(std::any_cast<char>(i)))){
                    operator_stack.emplace(std::any_cast<char>(i));

                }
                else if(i.type() == typeid(std::string) && (operator_stack.empty() || getPriority(operator_stack.top()) < getPriority(std::any_cast<std::string>(i)))){
                    operator_stack.emplace(std::any_cast<std::string>(i));
                }

                else{
                    if(i.type() == typeid(char))
                    {
                        while (!operator_stack.empty() &&
                               getPriority(operator_stack.top()) >= getPriority(std::any_cast<char>(i))) {
                            postfix_expression.emplace_back(operator_stack.top());
                            operator_stack.pop();
                        }
                        operator_stack.emplace(std::any_cast<char>(i));
                    }
                    else if(i.type() == typeid(std::string))
                    {
                        while (!operator_stack.empty() && getPriority(operator_stack.top()) >= getPriority(std::any_cast<std::string>(i))) {
                            postfix_expression.emplace_back(operator_stack.top());
                            operator_stack.pop();
                        }
                        operator_stack.emplace(std::any_cast<std::string>(i));
                    }
                }
            }
        }
    }
    while(!operator_stack.empty()){
        postfix_expression.emplace_back(operator_stack.top());
        operator_stack.pop();
    }
//    //输出后缀表达式
//    for (auto & i : postfix_expression){
//        if (i.type() == typeid(int)){
//            std::cout << std::any_cast<int>(i);
//        }
//        else if (i.type() == typeid(double)){
//            std::cout << std::any_cast<double>(i);
//        }
//        else if (i.type() == typeid(std::string)){
//            std::cout << std::any_cast<string>(i);
//        }
//        else if (i.type() == typeid(char)){
//            std::cout << std::any_cast<char>(i);
//        }
//    }
//    cout << endl;
    return 0;
}
void Calculation::calculate() {
    number_stack.push(0);
    for (auto & i : postfix_expression){
        if (i.type() == typeid(int)){
            number_stack.push(std::any_cast<int>(i));
        }
        else if (i.type() == typeid(double)){
            number_stack.push(std::any_cast<double>(i));
        }
        else
        {
            if(getPriority(i) == 1 || getPriority(i) == 2)
            {
                double num1 = number_stack.top();
                number_stack.pop();
                double num2 = number_stack.top();
                number_stack.pop();
                switch (std::any_cast<char>(i)){
                    case '+':
                        number_stack.push(num2 + num1);
                        break;
                    case '-':
                        number_stack.push(num2 - num1);
                        break;
                    case '*':
                        number_stack.push(num2 * num1);
                        break;
                    case '/':
                        number_stack.push(num2 / num1);
                        break;
                }
            } else if(getPriority(i) == 4){
                double num1 = number_stack.top();
                number_stack.pop();
                if(std::any_cast<std::string>(i) == "sin"){
                    number_stack.push(sin(num1));
                } else if(std::any_cast<std::string>(i) == "cos"){
                    number_stack.push(cos(num1));
                } else if(std::any_cast<std::string>(i) == "tan"){
                    number_stack.push(tan(num1));
                } else if(std::any_cast<std::string>(i) == "asin"){
                    number_stack.push(asin(num1));
                } else if(std::any_cast<std::string>(i) == "acos"){
                    number_stack.push(acos(num1));
                } else if(std::any_cast<std::string>(i) == "atan"){
                    number_stack.push(atan(num1));
                } else if(std::any_cast<std::string>(i) == "abs"){
                    number_stack.push(abs(num1));
                } else if(std::any_cast<std::string>(i) == "sqr"){
                    number_stack.push(pow(num1, 2));
                } else if(std::any_cast<std::string>(i) == "sqrt"){
                    number_stack.push(sqrt(num1));
                } else if(std::any_cast<std::string>(i) == "exp"){
                    number_stack.push(exp(num1));
                    cout << exp(num1) << endl;
                }
            } else if(getPriority(i) == 5){
                double num1 = number_stack.top();
                number_stack.pop();
                double num2 = number_stack.top();
                number_stack.pop();
                if(std::any_cast<std::string>(i) == "pow"){
                    number_stack.push(pow(num2, num1));
                } else if (std::any_cast<std::string>(i) == "log"){
                    number_stack.push(log(num1) / log(num2));
                } else if (std::any_cast<std::string>(i) == "max"){
                    number_stack.push(max(num2, num1));
                }
            } else if(getPriority(i) == 3){
                if(std::any_cast<std::string>(i) == "random"){
                    std::random_device rd;  // 随机数种子
                    std::mt19937 gen(rd()); // 随机数生成器
                    std::uniform_int_distribution<> dis(10, 99);
                    number_stack.push(dis(gen));
                }
            }
        }
    }
    std::cout <<  "The result is: " << number_stack.top() << std::endl;
}
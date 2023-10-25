#ifndef CALCULATORS_CALCULATION_H
#define CALCULATORS_CALCULATION_H
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <any>

class Calculation {
    private:
        std::vector<std::any> postfix_expression;
        std::vector<std::any> infix_expression;
        std::stack<std::any> operator_stack;
        //std::stack<double> number_stack ({(double)0});
        std::stack<double> number_stack;
        static bool isNumber(char c);
        static int isOperator(std::string ch,int n,int length);
        static int getPriority(std::any ch);

    public:
        std::string expression;
        void get_expression();
        void expression_to_infix();
        int  infix_to_postfix();
        void calculate();

};


#endif //CALCULATORS_CALCULATION_H

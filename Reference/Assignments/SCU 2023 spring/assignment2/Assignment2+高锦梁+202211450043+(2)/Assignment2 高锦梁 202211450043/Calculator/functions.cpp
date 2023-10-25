//
// Created by GAO on 2023/3/27.
//

#include "functions.h"

map<int , string> m{
        {1, "sin"},
        {2, "cos"},
        {3, "tan"},
        {4, "asin"},
        {5, "acos"},
        {6, "atan"},
        {7, "sqrt"},
        {8, "exp"},
        {9, "abs"},
        {10, "log"},
        {11, "min"},
        {12, "max"},
        {13, "random"}
};

map<int , string>keywords{
        {1, "PI"},
        {2, "E"},
        {3, "asm"},
        {4, "auto"},
        {5, "bool"},
        {6, "break"},
        {7, "case"},
        {8, "catch"},
        {9, "char"},
        {10, "class"},
        {11, "const"},
        {12, "const_cast"},
        {13, "continue"},
        {14, "default"},
        {15, "delete"},
        {16, "do"},
        {17, "double"},
        {18, "dynamic_cast"},
        {19, "else"},
        {20, "enum"},
        {21, "explicit"},
        {22, "export"},
        {23, "extern"},
        {24, "false"},
        {25, "float"},
        {26, "for"},
        {27, "friend"},
        {28, "goto"},
        {29, "if"},
        {30, "inline"},
        {31, "int"},
        {32, "long"},
        {33, "mutable"},
        {34, "namespace"},
        {35, "new"},
        {36, "operator"},
        {37, "private"},
        {38, "protected"},
        {39, "public"},
        {40, "register"},
        {41, "reinterpret_cast"},
        {42, "return"},
        {43, "short"},
        {44, "signed"},
        {45, "sizeof"},
        {46, "static"},
        {47, "static_cast"},
        {48, "struct"},
        {49, "switch"},
        {50, "template"},
        {51, "this"},
        {52, "throw"},
        {53, "true"},
        {54, "try"},
        {55, "typedef"},
        {56, "typeid"},
        {57, "typename"},
        {58, "union"},
        {59, "unsigned"},
        {60, "using"},
        {61, "virtual"},
        {62, "void"},
        {63, "volatile"},
        {64, "wchar_t"},
        {65, "while"},
};

bool functions::nameRight(char a){
    if((a <= 'z' && a >= 'a') || (a <= 'Z' && a >= 'A') || (a <= '9' && a >= '0') || a == '_') return 1;
    else return 0;
}

bool functions::isOpChar(char a){
    if(a == '+' || a == '-' || a == '*' || a == '/' || a == '^' || isdigit(a) || (a <= 'f' && a >= 'a')) return 1;
    return 0;
}

bool functions::isChar(char a){
    if(a == '+' || a == '-' || a == '*' || a == '/' || a == '^' || a == '(' || a == ')' || a == ' ') return 1;
    return 0;
}

int functions::priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

double functions::calculate(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) {
            cout << "#INFINITE" << endl;
            exit(0);
        }
        return a / b;
    }
    if (op == '^') return pow(a, b);
    if (op == 'a') return sin(a);
    if (op == 'b') return cos(a);
    if (op == 'c') return tan(a);
    if (op == 'd') return asin(a);
    if (op == 'e') return acos(a);
    if (op == 'f') return atan(a);
    if (op == 'g') return sqrt(a);
    if (op == 'h') return exp(a);
    if (op == 'i') return abs(a);
    if (op == 'j') return log(a);
    if (op == 'k') return min(a, b);
    if (op == 'l') return max(a, b);
    if (op == 'm') return rand() % (int)a;
    return 0;
}

void functions::getExpressions(string a[], int& t){
    for(int i = 0; i < 10; i++){
        getline(cin, a[i]);
        int stop = 0;
        for(int j = 0; j < a[i].length(); j++){
            if(a[i][j] == '=') {
                stop = 1;
            }
        }
        t = i;
        if(stop == 0) break;
    }
}

void functions::preDeal(string a[], pair<string, string> value[], int &end) {
    for(int i = 0; i < end; i++){
        for(int j = 0; j < a[i].length(); j++){
            if(a[i][j] == ' ') continue;
            if(a[i][j] == '=') {
                for(int k = j + 1; k < a[i].length(); k++){
                    value[i].second += a[i][k];
                }
                break;
            }
            value[i].first += a[i][j];
        }
    }
    for(int i = 0; i < 12; i++){
        if(isdigit(value[i].first[0]) && value[i].first.length() != 0){
            cout << "The variable name is not valid!(error message)" << endl;
            exit(0);
        }
        for(int j = 0; j < value[i].first.length(); j++){
            if(nameRight(value[i].first[j]) == 0 && value[i].first.length() != 0){
                cout << "The variable name is not valid!(error message)" << endl;
                exit(0);
            }
        }
        for(int j = 1; j <= keywords.size() && i < 10; j++){
            if(value[i].first == keywords[j]){
                cout << "The variable name is not valid!(error message)" << endl;
                exit(0);
            }
        }
    }
    for(int i = 0; i < a[end].length(); i++) {
        for (int j = 0; j < 12; j++) {
            bool judge1 = 0;
            if(a[end][i] == value[j].first[0]){
                if(i == 0){
                    if(value[j].first.length() == a[end].length()){
                        judge1 = 1;
                    } else if(functions::isChar(a[end][i + value[j].first.length()]) && value[j].first.length() < a[end].length()){
                        judge1 = 1;
                    }
                }
                else{
                    if(functions::isChar(a[end][i - 1])){
                        if(value[j].first.length() + i == a[end].length()){
                            judge1 = 1;
                        } else if(functions::isChar(a[end][i + value[j].first.length()]) && value[j].first.length() + i < a[end].length()){
                            judge1 = 1;
                        }
                    }
                }
            }
            if (judge1){
                int judge = 0;
                for (int k = 0; k < value[j].first.length(); k++) {
                    if (a[end][i + k] != value[j].first[k]) {
                        judge = 1;
                        break;
                    }
                }
                if (judge == 0) {
                    a[end].replace(i, value[j].first.length(), value[j].second);
                }
            }
        }
    }
    for(int i = 0; i < a[end].length(); i++){
        if(a[end][i] == '-'){
            a[end].replace(i, 1, "(0-1)*");
            i+=5;
        }
    }
}

void functions::isError(string a[], pair<string, string> value[], int &end){
    int cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < a[end].length(); i++){
        if(a[end][i] == '(') cnt1++;
        if(a[end][i] == ')') cnt2++;
        if(a[end][i] == '('){
            if(a[end][i + 1] == ')'){
                cout << "#ERROR" << endl;
                exit(0);
            }
        }
    }
    if(cnt1 != cnt2){
        cout << "The bracket is not matching!(error message)" << endl;
        exit(0);
    }
    for(int i = 0; i < a[end].length(); i++){
        if(isalpha(a[end][i])){
            string str;
            while(isalpha(a[end][i])){
                str += a[end][i];
                i++;
            }
            for(int j = 0; j < 12; j++){
                if(str == value[j].first){
                    break;
                }
                if(j == 11){
                    cout << "The variable does not exist!(error message)" << endl;
                    exit(0);
                }
            }
            for(int j = 1; j <= m.size(); j++){
                if(str == m[j]){
                    break;
                }
                if(j == m.size()){
                    cout << "The variable does not exist!(error message)" << endl;
                    exit(0);
                }
            }
        }
    }
}

double functions::evaluate(string expr) {
    stack<double> numStack;
    stack<char> opStack;
    int n = expr.length();
    for (int i = 0; i < n; i++) {
        if (isdigit(expr[i])) {
            double num = 0;
            bool judge = 0;
            int book;
            while (i < n && isdigit(expr[i])) {
                if(judge){
                    num += (expr[i] - '0') * pow(10, book - i);
                }
                else{
                    num = num * 10 + (expr[i] - '0');
                }
                if(expr[i + 1] == '.'){
                    judge = 1;
                    book = i + 1;
                    i++;
                }
                i++;
            }
            i--;
            numStack.push(num);
        } else if (expr[i] == '(') {
            opStack.push(expr[i]);
        } else if (expr[i] == ')') {
            while (opStack.top() != '(') {
                char op = opStack.top();
                opStack.pop();
                double b = numStack.top();
                numStack.pop();
                double a = numStack.top();
                numStack.pop();
                numStack.push(calculate(a, b, op));
            }
            opStack.pop();
            if(!opStack.empty() && (opStack.top() == 'k' || opStack.top() == 'l')){
                char op = opStack.top();
                opStack.pop();
                double b = numStack.top();
                numStack.pop();
                double a = numStack.top();
                numStack.pop();
                numStack.push(calculate(a, b, op));
            }
            if (!opStack.empty() && (opStack.top() >= 'a' && opStack.top() <= 'j') || opStack.top() == 'm') {
                char op = opStack.top();
                opStack.pop();
                double a = numStack.top();
                numStack.pop();
                numStack.push(calculate(a, 0, op));
            }
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            while (!opStack.empty() && opStack.top() != '(' && priority(opStack.top()) >= priority(expr[i])) {
                char op = opStack.top();
                opStack.pop();
                double b = numStack.top();
                numStack.pop();
                double a = numStack.top();
                numStack.pop();
                numStack.push(calculate(a, b, op));
            }
            opStack.push(expr[i]);
        } else if (expr[i] == 's' || expr[i] == 'c' || expr[i] == 't' || expr[i] == 'a' || expr[i] == 'e' || expr[i] == 'l' || expr[i] == 'm' || expr[i] == 'r') {
            string func;
            bool judge1 = 0;
            bool judge2 = 1;
            while (i < n && isalpha(expr[i])) {
                judge1 = 1;
                func += expr[i];
                i++;
            }
            if(judge1){
                for(int j = 1; j <= 13; j++){
                    judge2 = 0;
                    if(func == m[j]){
                        judge2 = 1;
                        opStack.push('a' + j - 1);
                        break;
                    }
                }
            }
            if(judge2 == 0){
                cout << "The variable does not exist!(error message)" << endl;
                exit(0);
            }
            i--;
        }
        else if(expr[i] == 'k' || expr[i] == 'l'){
            opStack.push(expr[i]);
        }
    }
    while (!opStack.empty()) {
        char op = opStack.top();
        opStack.pop();
        double b = numStack.top();
        numStack.pop();
        double a = numStack.top();
        numStack.pop();
        numStack.push(calculate(a, b, op));
    }
    return numStack.top();
}


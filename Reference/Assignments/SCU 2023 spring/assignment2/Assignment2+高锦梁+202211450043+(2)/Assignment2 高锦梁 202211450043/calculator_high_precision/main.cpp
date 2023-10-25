#include "functions.h"

Functions f;

int main() {
    while(1){
        string a, b;
        char op;
        cin >> a >> op >> b;
        if(op == '+') {
            cout << f.add_decimal(a, b) << endl;
        } else if(op == '-') {
            cout << f.minus_decimal(a, b) << endl;
        } else if(op == '*') {
            cout << f.multiply_decimal(a, b) << endl;
        }
        char u;
        if((u = getchar()) == EOF){
            break;
        } else {
            ungetc(u, stdin);
        }
    }
    return 0;
}




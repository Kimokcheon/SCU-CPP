#include <iostream>
#include "Calculation.h"
#include <algorithm>
using namespace std;
int main() {
    while (true) {

        Calculation calculation;

        calculation.get_expression();

        calculation.expression_to_infix();

        calculation.infix_to_postfix();

        calculation.calculate();
    }


    return 0;
}

#include "functions.h"

functions f;
string a[10];

int main() {
    while(1) {
        int end = 0;
        f.getExpressions(a, end);
        pair<string, string> value[12];
        value[10].first = "PI";
        value[10].second = "3.141592653589793";
        value[11].first = "E";
        value[11].second = "2.718281828459045";
        f.preDeal(a, value, end);
        f.isError(a, value, end);
        double output = f.evaluate(a[end]);
        cout << fixed << setprecision(8) << output << endl;
        char u;
        if((u = getchar()) != EOF){
            ungetc(u, stdin);
        } else {
            break;
        }
    }
}

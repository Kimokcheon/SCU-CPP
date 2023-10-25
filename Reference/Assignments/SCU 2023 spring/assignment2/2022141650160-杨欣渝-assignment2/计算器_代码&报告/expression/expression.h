#include <bits/stdc++.h>
using namespace std;
namespace EXPRESSION {
const double eps=1e-6;
const int NO_ERROR=0,ERROR_DIVIDE_BY_ZERO=1,ERROR_BRACKET=2,ERROR_VARIABLE_NAME=4,ERROR_CONST_VALUE=8,ERROR_UNDEFINED_VARIABLE=16;
class Expression {
  public:
    Expression();
    Expression(string);
    void CULTI();
    int L;
  private:
    stack<int> O_S;
    stack<double> N_S;
    static map<string,double> V_M;
    int ER_info;
    string expr;
    string get_V_N(const int &pos);
    pair<double,int> get_N_F(const int &pos);
    void PRO_func(const int &option);
    void V_C();
    bool B_O(const char &option);
    bool CHK_N(const std::string &var_name);
    void Error_print();
    pair<string,int> NAME_get(const int &pos);
    int JUDGE_func(const string &fun_name);
    bool JUDGE_C_V(const string &var_name);
    pair<bool,double> calc();
};

}
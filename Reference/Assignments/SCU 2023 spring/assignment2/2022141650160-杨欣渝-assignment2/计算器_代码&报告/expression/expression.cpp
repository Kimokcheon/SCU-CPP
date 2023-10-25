#include "expression.h"
#include <bits/stdc++.h>
using namespace std;
namespace EXPRESSION {
map<string,double> Expression::V_M;
bool Expression::B_O(const char &option){ return (bool)(option =='+'||option=='-'||option=='*'||option=='/'); }
pair<double,int> Expression::get_N_F(const int &pos){
    double res=0,base=0.1; int fn=L-1,fn0=0;
    for(int i=pos;i<L;i++){
        if(expr[i]>='0'&&expr[i]<='9') res=res*10+expr[i]-'0';
        else{ fn=i-1; break; }
    }
    if(fn+1<L&&expr[fn+1]=='.'){
        fn0=fn+2,fn=L-1;
        for (int i=fn0;i<L;++i){
            if(expr[i]>='0'&&expr[i]<='9') res+=base*(expr[i]-'0'), base*= 0.1;
            else{ fn=i-1; break; }
        }
    }
    return make_pair(res,fn);
}
void Expression::PRO_func(const int &option){
    double x=N_S.top();
    N_S.pop();
    if(option==-1) N_S.push(sqrt(x)); else if(option==-2) N_S.push(exp(x)); else if(option==-3) N_S.push(fabs(x));
    else if(option==-4) N_S.push(sin(x)); else if(option==-5) N_S.push(cos(x)); else if(option==-6) N_S.push(tan(x));
    else ER_info|=ERROR_UNDEFINED_VARIABLE;
}
void Expression::V_C(){
    double x1=0,x2=0;
    int op=O_S.top();
    if(B_O(op)){
        x1=N_S.top(), N_S.pop(), x2=N_S.top(), N_S.pop();
        if(op=='+') N_S.push(x1+x2);
        else if(op=='-') N_S.push(x2-x1);
        else if(op=='*') N_S.push(x2*x1);
        else if(op=='/'){
            if(fabs(x1)<eps) ER_info|=ERROR_DIVIDE_BY_ZERO, N_S.push(0);
            else N_S.push(x2/x1);
        }
    }
    else PRO_func(op);
}
bool Expression::CHK_N(const string &var_name){
    int len=var_name.length();
    int i=0, j=len-1;
    while(i<len&&var_name[i]==' ') i++;
    while(j>=0&&var_name[j]==' ') j--;
    for (int k=i; k <= j; ++k){
        if(!((var_name[k]>='A'&&var_name[k] <= 'Z')||(var_name[k]>='a'&&var_name[k] <= 'z')||var_name[k]=='_')) return 0;
    }
    return 1;
}
pair<string, int> Expression::NAME_get(const int &pos){
    int fn=L-1;
    for (int i=pos; i<L; ++i){
        if((expr[i]>='a'&&expr[i] <= 'z')||(expr[i]>='A'&&expr[i] <= 'Z')||expr[i]=='_') continue;
        else { fn=i-1;  break; }
    }
    return make_pair(expr.substr(pos, fn-pos+1), fn);
}
void Expression::Error_print(){
    if(ER_info==ERROR_DIVIDE_BY_ZERO) cerr << "#INFINITE" << endl; if(ER_info&ERROR_BRACKET) cerr << "The bracket is not matching!" << endl;
    if(ER_info&ERROR_VARIABLE_NAME) cerr << "The variable name is not valid!" << endl; if(ER_info&ERROR_CONST_VALUE) cerr << "This is constant value. Cannot be changed!" << endl;
    if(ER_info&ERROR_UNDEFINED_VARIABLE) cerr << "The variable does not exist!" << endl;
}
int Expression::JUDGE_func(const string &fun_name){
    if(fun_name=="sqrt") return -1; if(fun_name=="exp") return -1; if(fun_name=="abs") return -3;
    if(fun_name=="sin") return -4; if(fun_name=="cos") return -5; if(fun_name=="tan") return -6;
    return 0;
}
bool Expression::JUDGE_C_V(const string &var_name){ return (bool)(var_name=="PI"||var_name=="E"); }
pair<bool, double> Expression::calc(){
    int fr=0;
    while(fr<L&&expr[fr]==' ') ++fr;
    expr=expr.substr(fr, L-fr);
    if(expr[0]=='-') expr="0"+expr;
    L=expr.length();
    for (int i=0; i<L; ++i){
        if(expr[i]>='0'&&expr[i] <= '9'){ auto t=get_N_F(i); N_S.push(t.first); i=t.second; } 
        else if(expr[i]=='(')  O_S.push('(');
        else if(expr[i]==')'){
            while(!O_S.empty()&&O_S.top()!='(') V_C(), O_S.pop(); 
            if(!O_S.empty()&&O_S.top()=='(') O_S.pop();
            else if(O_S.empty()) ER_info|=ERROR_BRACKET;
            if(!O_S.empty()&&O_S.top()<0) V_C(), O_S.pop();
        } 
        else if(B_O(expr[i])){
            if(expr[i]=='+'){ while(!O_S.empty()&&O_S.top()!='+'&&O_S.top()!='-'&&O_S.top() !='(') V_C(), O_S.pop(); O_S.push('+'); } 
            else if(expr[i]=='-'){ while(!O_S.empty()&&O_S.top()!='+'&&O_S.top()!='-'&&O_S.top() !='(')  V_C(), O_S.pop(); O_S.push('-'); } 
            else if(expr[i]=='*'||expr[i]=='/') O_S.push(expr[i]);
        } else if(expr[i]!=' '){
            auto t=NAME_get(i); string name=t.first; i=t.second;
            int j=JUDGE_func(name);
            if(j<0) O_S.push(j);
            else {
                if(Expression::V_M.find(name)!=Expression::V_M.end()) N_S.push(Expression::V_M[name]);
                else if(JUDGE_C_V(name)){
                    if(name=="PI") N_S.push(acos(-1));
                    if(name=="E") N_S.push(exp(1));
                } 
                else { ER_info|=ERROR_UNDEFINED_VARIABLE; break; }
            }
        }
        if(ER_info!=0) break;
    }
    if(ER_info!=0) return make_pair(true, 0);
    while(!O_S.empty()){ if(O_S.top()=='('){ ER_info|=ERROR_BRACKET; break; }  V_C(), O_S.pop(); }
    if(ER_info!=0) return make_pair(true, 0);
    return make_pair(false, N_S.top());
}
Expression::Expression(){ expr="", L=0, ER_info=0; }
Expression::Expression(string S){ expr=S, L=expr.length(), ER_info=0; }
string Expression::get_V_N(const int &pos){
    string name=expr.substr(0, pos);
    int len=name.length();
    int i=0, j=len-1;
    while(i<len&&name[i]==' ') ++i;
    while(j>=0&&name[j]==' ') --j;
    return name.substr(i, j-i+1);
}
void Expression::CULTI(){
    bool isVar=0;
    for(int i=0;i<L;++i) if(expr[i]=='='){
            string name=get_V_N(i); if(!CHK_N(name)){ ER_info|=ERROR_VARIABLE_NAME; break;  }
            if(JUDGE_C_V(name)){ ER_info|=ERROR_CONST_VALUE; break; }
            expr=expr.substr(i+1, L-i-1);
            auto [error, value]=calc();
            if(error) break; Expression::V_M[name]=value; isVar=1;
            break;
        }
    if(ER_info!=NO_ERROR){ Error_print(); return; }
    if(!isVar){ auto [error, value]=calc(); if(error) Error_print(); else cout << fixed << setprecision(6) << value << endl; }
}

}
//(2.34+5.67)*3.5/2-1.23+4.56/2*(8.9-3.4)

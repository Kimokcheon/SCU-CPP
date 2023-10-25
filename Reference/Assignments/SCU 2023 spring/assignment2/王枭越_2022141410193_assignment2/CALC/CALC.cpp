#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <map>
#include <utility>
#include <cmath>
#include <random>
using namespace std;

stack<char> opt;
queue<string> out;
stack<double> num;
map<string,string> f;

bool isok;
int op;

bool isille(string x){
    for(int i=0;i<x.size();i++){
        if(!isalpha(x[i])){
            return false;
        }
    }
    return true;
}

void Postfix_Expression(string x){
    isok=1;op=0;
    //预处理
    string _x,t;
    for(int i=0;i<x.size();i++){
        if(!isalpha(x[i])){
            _x+=x[i];
        }else{
            t+=x[i];
            if(!isalpha(x[i+1]))
                if(t=="sqrt")
                _x+=t,op=1,t="";
                else if(t=="exp")
                _x+=t,op=2,t="";
                else if(t=="abs")
                _x+=t,op=3,t="";
                else if(t=="max")
                _x+=t,op=4,t="";
                else if(t=="random")
                _x+=t,op=5,t="";
                else if(t=="sin")
                _x+=t,op=6,t="";
                else if(f.find(t)!=f.end()){
                    _x+=f[t];t="";
                }else{
                    isok=0;
                    cout<<"The Variable does not exist!(error message)"<<endl;
                    t="";
                    return;
                }
        }
    }

    x=_x;
    
    while(!opt.empty())opt.pop();
    while(!out.empty())out.pop();
    string tmp;
    for(int i=0;i<x.size();i++){
        if(x[i]=='('){
            opt.push(x[i]);
        }else if(x[i]==')'){
            if(opt.empty()){
                isok=0;
                cout<<"The bracket is not matching!(error message)"<<endl;
                return;
            }
            char t=opt.top();
            while(t!='('){
                opt.pop();
                string _t;
                _t+=t;
                out.push(_t);
                if(opt.empty()){
                    isok=0;
                    cout<<"The bracket is not matching!(error message)"<<endl;
                    return;
                }
                t=opt.top();
            }
            if(t=='('){
                opt.pop();
            }
        }else if(x[i]=='+'||(x[i]=='-'&&i!=0&&isdigit(x[i-1]))||x[i]=='*'||x[i]=='/'||x[i]=='^'){
            if(x[i]=='+'||(x[i]=='-'&&isdigit(x[i-1]))){
                while(!opt.empty()){
                    char t=opt.top();
                    if(t=='(')break;
                    string _t;
                    _t+=t;
                    out.push(_t);
                    opt.pop();
                }
                opt.push(x[i]);
            }else if(x[i]=='*'||x[i]=='/'){
                while(!opt.empty()){
                    char t=opt.top();
                    if(t=='+'||t=='-'||opt.empty()||t=='(')break;
                    string _t;
                    _t+=t;
                    out.push(_t);
                    opt.pop();
                }
                opt.push(x[i]);
            }else if(x[i]=='^'){
                opt.push('^');
            }
        }else if(isdigit(x[i])||x[i]=='.'||x[i]=='-'){
            tmp+=x[i];
            if(!(isdigit(x[i+1])||x[i+1]=='.')){
                out.push(tmp);
                tmp="";
            }
        }
    }
    while(!opt.empty()){
        char t=opt.top();
        if(t=='('){
            cout<<"The bracket is not matching!(error message)"<<endl;
            isok=0;
            break;
        }
        string _t;
        _t+=t;
        out.push(_t);
        opt.pop();
    }
}

double calc(){
    while(!num.empty())num.pop();
    while(!out.empty()){
        string tmp=out.front();
        out.pop();
        if(isdigit(tmp[0])||(tmp[0]=='-'&&tmp.size()>1)){
            double t=stod(tmp);
            num.push(t);
        }else{
            double t1=num.top();
            num.pop();
            double t2=num.top();
            num.pop();
            if(tmp=="+"){
                num.push(t1+t2);
            }else if(tmp=="-"){
                num.push(t2-t1);
            }else if(tmp=="*"){
                num.push(t1*t2);
            }else if(tmp=="/"){
                num.push(t2/t1);
            }else if(tmp=="^"){
                num.push(pow(t2,t1));
            }
        }
    }
    if(op==0)
    return num.top();
    else if(op==1)
    return sqrt(num.top());
    else if(op==2)
    return exp(num.top());
    else if(op==3)
    return abs(num.top());
    else if(op==4){
        double t1=num.top();
        num.pop();
        double t2=num.top();
        num.pop();
        return max(t1,t2);
    }else if(op==5){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 100);
        int random_number = dis(gen);
        return random_number;
    }else if(op==6){
        return sin(num.top());
    }else{
        return num.top();
    }
}

pair<bool,pair<string,string>> val(string x){
    int pos=x.find('=');
    if(pos==-1)return make_pair(false,make_pair("","-1"));
    return make_pair(true,make_pair(x.substr(0,pos),x.substr(pos+1)));
}



int main(){

    f["PI"]=to_string(acos(-1));
    f["E"]=to_string(exp(1));

    string x;
    while(getline(cin,x)){
        if(!val(x).first){
            Postfix_Expression(x);
            if(isok)
            cout<<calc()<<endl;
        }else{
            if(val(x).second.first=="PI"||val(x).second.first=="E"){
                cout<<"This is constant value!(error message)"<<endl;
            }else if(isille(val(x).second.first))
            f[val(x).second.first]=val(x).second.second;
            else
            cout<<"The variable name is not valid!(error message)"<<endl;
        }
    }
    return 0;
}
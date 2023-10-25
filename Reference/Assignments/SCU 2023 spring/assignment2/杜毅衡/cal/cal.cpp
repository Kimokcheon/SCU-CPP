#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include "cal.h"
using namespace std;
map<string,double>vis,val;
void init(){
    vis["PI"]=-1;
    val["PI"]=3.14159265;
    vis["E"]=-1;
    val["E"]=2.718281828;

    return ;
}
int priority(char c){
	int k;
	switch (c){
	    case '*':k = 3; break;
	    case '/':k = 3; break;
	    case '+':k = 2; break;
	    case '-':k = 2; break;
	    case '(':k = 1; break;
	    case ')':k = 1; break;
	    default:k = 0; break;
	}
	return k;
}
//Get the value of the expression 
pair<int,double> get_value(string op){ 
    if(op[0]=='-') op='0'+op;
    op=op+'?';
    int len=op.length();
    
    //error2
    int sum=0;
    for(int i=0;i<len;++i){
        if(op[i]=='(') ++sum;
        if(op[i]==')') --sum;
        if(sum<0) return make_pair(2,0);
    }
    if(sum!=0) return make_pair(2,0);

    
    double sck_num[1100];   //the stack of num
    char sck_sgn[1100];      //the stack of sign
    int cnt_num=0,cnt_sgn=0;
    sck_num[++cnt_num]=0;
    sck_num[0]=0;
    for(int i=0 ; i < len ; ++i){
        //expression stack 
        if(priority(op[i])||op[i]=='?'){
            if(op[i]=='('||priority(op[i])>priority(sck_sgn[cnt_sgn])){
                sck_sgn[++cnt_sgn]=op[i];
                if(op[i]=='('&&op[i+1]=='-') sck_num[++cnt_num]=0;
            }
            else{
                while(  cnt_sgn && \
                        (op[i]=='?'||\
                        (op[i]==')' && sck_sgn[cnt_sgn]!='(' ) ||\
                        (op[i]!=')' && priority(op[i])<=priority(sck_sgn[cnt_sgn]) ) ) ){
                    double s1=0,s2=0,ss=0;
                    s2=sck_num[cnt_num--];
                    s1=sck_num[cnt_num--];
                    if(sck_sgn[cnt_sgn]=='*'){
                        ss=s1*s2;
                    }
                    if(sck_sgn[cnt_sgn]=='/'){
                        if(abs(s2)<eps) return make_pair(1,0);
                        ss=s1/s2;
                    }
                    if(sck_sgn[cnt_sgn]=='+'){
                        ss=s1+s2;
                    }
                    if(sck_sgn[cnt_sgn]=='-'){
                        ss=s1-s2;
                    }
                    sck_num[++cnt_num]=ss;
                    cnt_sgn--;
                }
                if( op[i]==')'&&sck_sgn[cnt_sgn]=='(') cnt_sgn--;
                if( op[i]!=')' )
                    sck_sgn[++cnt_sgn]=op[i];
            }

        }
        else{
            //num stack
            if(isdigit(op[i])){
                double res=0,flag=1;
                while( isdigit(op[i]) && op[i]!='?'){
                    res=res*10+op[i]-'0';
                    ++i;
                } 
                if(i!=len&&op[i]=='.'){
                    ++i;
                    while( isdigit(op[i]) && op[i]!='?' ){
                        flag*=0.1;
                        res+=flag*(op[i]-'0');
                        ++i;
                    }
                }
                --i;

                sck_num[++cnt_num]=res;
            }
            // variable
            else{
                string Name;
                while( !priority(op[i]) && op[i]!='?'){
                    if(op[i]=='_') return make_pair(3,0);
                    Name+=op[i];
                    ++i;
                }
                --i;
                
                //function
                if(Name=="sqrt"||Name=="exp"||Name=="abs"||Name=="sin"){
                    
                    string op_tmp;
                    int sum=0,s=0,t=0;
                    s=i+2,t=i+1;
                    for(int j=i+1 ; j<len ; t=j,++j  ){
                        if(op[j]=='(') ++sum;
                        if(op[j]==')') --sum;
                        if(sum==0) break;
                    }
                    for(int j=s;j<=t;++j) op_tmp+=op[j];
                    i=t+1;

                    if(Name=="sqrt"){
                        sck_num[++cnt_num]=sqrt(get_value(op_tmp).second);
                    }
                    else if(Name=="exp"){
                        sck_num[++cnt_num]=exp(get_value(op_tmp).second);
                    }
                    else if(Name=="abs"){
                        sck_num[++cnt_num]=abs(get_value(op_tmp).second);
                    }
                    else if(Name=="sin"){
                        sck_num[++cnt_num]=sin(get_value(op_tmp).second);
                    }

                }
                else if(Name=="max"){
                    string op_tmp1,op_tmp2;
                    int sum=0,s=0,t=0,mid=0;
                    s=i+2,t=i+1;
                    for(int j=i+1 ; j<len ; t=j,++j  ){
                        if(op[j]=='(') ++sum;
                        if(op[j]==')') --sum;
                        if(op[j]==',') mid=j;
                        if(sum==0) break;
                    }
                    for(int j=s;j<mid;++j) op_tmp1+=op[j];
                    for(int j=mid+1;j<=t;++j) op_tmp2+=op[j];
                    i=t+1;
                    sck_num[++cnt_num]=max(get_value(op_tmp1).second,get_value(op_tmp2).second);
                }
                else if(Name=="Random"){
                    i+=2;
                    srand(time(0));
                    sck_num[++cnt_num]=rand();
                }
                //variable
                else {
                    if(vis[Name]==0) return make_pair(4,0);   
                    sck_num[++cnt_num]=val[Name];
                }

            }
        }
    }
    return make_pair(0,sck_num[cnt_num]);
}
//error message
bool check(pair<int,double> res){
    if(res.first==1) {
        cout<<"#INFINITE"<<'\n';
        return 1; 
    }    
    if(res.first==2){
        cout<<"The bracket is not matching!(error message)"<<'\n';
        return 1;
    }
    if(res.first==3){
        cout<<"The variable name is not valid!(error message)"<<'\n';
        return 1;
    } 
        
    if(res.first==4) {
        cout<<"The variable does not exist! (error message)"<<'\n';
        return 1;
    }
    return 0;
}
void sol(string op){
    int len=op.length();
    int ps=-1;
    for(int i=0 ; i<len ; ++i) if(op[i]=='=') ps=i;
    if(ps!=-1){
        string Name,op2;
        
        for(int i=0 ; i<ps ; ++i) Name+=op[i];
        if(vis[Name]==-1) {
            cout<<"This is constant value. Cannot be changed! (error message)"<<'\n';
            return ;
        }
        
        for(int i=ps+1; i<len ;++i) op2+=op[i];
        
        auto res=get_value(op2);
        if(check(res)) return ;
        vis[Name]=1;
        val[Name]=res.second;
    }
    else{
        auto res=get_value(op);
        if(check(res)) return ;
        cout<<res.second<<'\n';
    }
    return ;
}

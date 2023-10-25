#include<iostream>
#include<cstdio>
#include<map>
#include<cmath>
#include<ctime>
#include<cstring>
#include<algorithm>
#include"Calc.h"

using namespace std;

const double eps=1e-8;
bool flag=1;
const int MAXN=2e5+5;
char ch[MAXN];double val[MAXN];
int tail1,tail2;
map<string,char> ma;
map<char,int> ma2;

bool add()
{
    if(tail1<2)
    {
        puts("Error,illegal expression.");
        return 0;
    }
    double v1=val[tail1],v2=val[tail1-1];
    tail1--;tail1--;val[++tail1]=v1+v2;
    return 1;
}

bool del()
{
    if(tail1<2)
    {
        puts("Error,illegal expression.");
        return 0;
    }
    double v1=val[tail1],v2=val[tail1-1];
    tail1--;tail1--;val[++tail1]=v2-v1;
    return 1;
}

bool mul()
{
    if(tail1<2)
    {
        puts("Error,illegal expression.");
        return 0;
    }
    double v1=val[tail1],v2=val[tail1-1];
    tail1--;tail1--;val[++tail1]=v1*v2;
    return 1;
}

bool div()
{
    if(tail1<2)
    {
        puts("Error,illegal expression.");
        return 0;
    }
    double v1=val[tail1],v2=val[tail1-1];
    if(fabs(v1)<=eps)
    {
        puts("#INFINITE");
        flag=0;
        return 0;
    }
    tail1--;tail1--;val[++tail1]=v2/v1;
    return 1;
}

bool sqr()
{
    val[tail1]=sqrt(val[tail1]);
    return 1;
}

bool ex()
{
    val[tail1]=exp(val[tail1]);
    return 1;
}

bool ab()
{
    val[tail1]=fabs(val[tail1]);
    return 1;
}

bool Ma()
{
    if(tail1<2)
    {
        puts("Error,illegal expression.");
        return 0;
    }
    double v1=val[tail1],v2=val[tail1-1];
    tail1--;tail1--;val[++tail1]=max(v1,v2);
    return 1;
}

bool ra()
{
    srand(time(NULL));
    val[++tail1]=rand();
    return 1;
}

bool si()
{
    val[tail1]=sin(val[tail1]);
    return 1;
}

bool Calc(char t)
{
    if(t=='+') return add();
    if(t=='-') return del();
    if(t=='*') return mul();
    if(t=='/') return div();
    if(t=='a') return sqr();
    if(t=='b') return ex();
    if(t=='c') return ab();
    if(t=='d') return Ma();
    if(t=='e') return ra();
    if(t=='f') return si();
}

void init()
{
    tail1=tail2=0;flag=1;
    ma["sqrt"]='a';ma["exp"]='b';ma["abs"]='c';
    ma["max"]='d';ma["random"]='e';ma["sin"]='f';
    ma2['+']=1,ma2['-']=1;ma2['*']=2;ma2['/']=2;
    for(char i='a';i<='f';i++) ma2[i]=3;
    ma2['(']=0;
}

void addin(char c)
{
    while(tail2&&ma2[ch[tail2]]>ma2[c]&&flag) flag&=Calc(ch[tail2]),tail2--;
    ch[++tail2]=c;
}

bool Solve()
{
    init();
    char c=getchar(),last=0;
    while(c!='\n'&&c!=EOF)
    {
        if(!flag)
        {
            c=getchar();
            continue;
        }
        if(c>='0'&&c<='9')
        {
            double s=0;
            while(c>='0'&&c<='9') s=s*10+(c-'0'),last=c,c=getchar();
            if(c=='.')
            {
                last=c,c=getchar();
                double s2=0.1;
                while(c>='0'&&c<='9') s+=s2*(c-'0'),s2*=0.1,last=c,c=getchar();
            }
            val[++tail1]=s;
            continue;
        }
        else if(c=='-')
        {
            if(!last||last=='('||last==',') val[++tail1]=-1,addin('*');
            else addin(c);
        }
        else if(c=='+'||c=='*'||c=='/') addin(c);
        else if(c=='(') ch[++tail2]=c;
        else if(c==')')
        {
            if(last==','||last=='(')
            {
                flag=0;
                puts("Error,illegal expression.");
            }
            while(tail2&&ch[tail2]!='('&&flag) flag&=Calc(ch[tail2]),tail2--;
            if(!tail2&&flag)
            {
                flag=0;
                puts("The bracket is not matching.(error message)");
            }
            else tail2--;
        }
        else if(c==',')
        {
            if(last=='(')
            {
                flag=0;
                puts("Error,illegal expression.");
            }
        }
        else if(c=='r')
        {
            string s="";
            while(c>='a'&&c<='z') s+=c,last=c,c=getchar();
            c=getchar();ra();
        }
        else if(c>='a'&&c<='z')
        {
            string s="";
            while(c>='a'&&c<='z') s+=c,last=c,c=getchar();
            addin(ma[s]);
            continue;
        }
        else
        {
            if(flag) puts("Error,illegal expression."),flag=0;
        }
        last=c,c=getchar();
    }
    if(flag)
    {
        while(tail2&&flag)
        {
            if(ch[tail2]=='(')
            {
                puts("The bracket is not matching.");
                flag=0;
                break;
            }
            flag&=Calc(ch[tail2]),tail2--;
        }
        if(flag) cout<<val[tail1]<<endl;
    }
    if(c==EOF) return 0;
    else return 1;
}
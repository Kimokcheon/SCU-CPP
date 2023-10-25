#include "calculator.h"
#include <bits/stdc++.h>
using namespace std;
char s[1000006],c[1000006],d[1000006];
int main(){
    scanf("%s",s);
    int n=strlen(s),add=0,mnus=0,mul=0,pos;
    for(int i=0;i<n;i++){
        if(s[i]=='+') add++,pos=i;
        if(s[i]=='-'){ mnus++; if(i!=0) pos=i; }
        if(s[i]=='*') mul++,pos=i;
    }
    if(mul){
        if(mnus==1){
            for(int i=1;i<pos;i++) c[i-1]=s[i];
            for(int i=pos+1;i<n;i++) d[i-pos-1]=s[i];
            number A(c),B(d);
            A=A*B;
            cout<<'-';
            cout<<A<<endl;
            return 0;
        }
        for(int i=0;i<pos;i++) c[i]=s[i];
        for(int i=pos+1;i<n;i++) d[i-pos-1]=s[i];
        number A(c),B(d);
        A=A*B;
        cout<<A<<endl;
        return 0;
    }
    if(mnus==2){
        for(int i=1;i<pos;i++) c[i-1]=s[i];
        for(int i=pos+1;i<n;i++) d[i-pos-1]=s[i];
        number A(c),B(d);
        A=A+B;
        cout<<'-';
        cout<<A<<endl;
        return 0;
    }
//    return 0;
    for(int i=0;i<pos;i++) c[i]=s[i];
    if(s[pos]=='-') pos--;
    for(int i=pos+1;i<n;i++) d[i-pos-1]=s[i];
    number A(c),B(d);
    A=A+B;
    cout<<A<<endl;
    return 0;
}
#include<iostream>
#include<cstdio>
#include"stuinfo.h"

using namespace std;
const int MAXN=20000;
stuinfo a[MAXN+5];
int n;
char s[20];
int main()
{
    scanf("%d",&n);
    inputstu(a,n);
    showstu(a,n);
    sortstu(a,n);
    showstu(a,n);
    scanf("%s",s);
    if(findstu(a,n,s)) puts("Ok");
    else puts("Not Found");
}
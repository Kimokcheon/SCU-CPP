#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
int main(){
    char a[10]="123456789";
    int b[10];
    for(int i=0;i<10;++i) b[i]=i;
    
    a[-1]='1';
    a[10]='1';
    a[11]='1';
    
    b[-1]=-1;
    b[10]=10;
    b[11]=11;

    cout << "addr:" << hex << (void *)(b) << endl;
    for(int i=-1;i<=11;++i) cout << hex << (void *)(b + i) << ":" << b[i] << endl;


    return 0;
}
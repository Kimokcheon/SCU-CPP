#include <bits/stdc++.h>
#include "stuinfo.h"
//#include "stuinfo.cpp"
using namespace std;
stuinfo stu[20];
int n;
int main (){
    inputstu(stu,n);
    showstu(stu,n);
    sortstu(stu,n);
    showstu(stu,n);
    string ch;
    cout<<"Please input information"<<'\n';
    cin>>ch;
    if(findstu(stu,n,ch)) cout<<"The student is in the student list.";
    else cout<<"The student is NOT in the student list.";
}
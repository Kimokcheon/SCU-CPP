#include<iostream>

using namespace std;

void Swa(int& a,int& b)
{
    int t=a;
    a=b,b=t;
    return ;
}

int main()
{
    int a,b;
    cin>>a>>b;
    Swa(a,b);
    cout<<a<<" "<<b<<endl;
}
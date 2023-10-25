#include"RandomGenerator.h"
#include<iomanip>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<ctime>

using namespace std;

int main()
{
    int n;scanf("%d",&n);
    int* A=create(n);
    Print(A,n);
    Delete(A);
}
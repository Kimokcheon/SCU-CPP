#include"RandomGenerator.h"
#include<iomanip>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<ctime>
#include<stdlib.h>

using namespace std;

int* create(int n)
{
    int* A=new int[n];
    srand(time(NULL));
    for(int i=0;i<n;i++) A[i]=rand()%n;
    return A;
}

void Print(int* A,int n)
{
    int maxx=0,minn=n-1;
    for(int i=0;i<n;i++) maxx=max(maxx,A[i]),minn=min(minn,A[i]);
    printf("%d %d\n",minn,maxx);
}

void Delete(int* A)
{
    delete []A;
}
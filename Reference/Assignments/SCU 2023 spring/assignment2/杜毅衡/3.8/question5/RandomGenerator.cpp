#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string.h>
#include "RandomGenerator.h"
using namespace std;
int* create(int n){
    int *a=new int[n];
	srand(time(0));
    for(int i=0;i<n;++i) a[i]=rand()%n;
    return a;
}
int Max(int *a,int n){
    int mx=a[0];
    for(int i=0;i<n;++i) mx=max(mx,a[i]);
    return mx;
}
int Min(int *a,int n){
    int mn=a[0];
    for(int i=0;i<n;++i) mn=min(mn,a[i]);
    return mn;
}
void del(int *a){
 	delete []a;
    return ;
}
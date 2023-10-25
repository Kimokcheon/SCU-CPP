#include <iostream>
#include "RandomGenerator.h"
using namespace std;
int main(){
	int *a;
	a=create(10);
	for(int i=0;i<10;++i) cout<<a[i]<<' ';
    cout<<'\n';
   	cout<<Max(a,10)<<'\n';
   	cout<<Min(a,10)<<'\n';
   	del(a);
	return 0;
}
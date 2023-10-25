#include <iostream>
#include "stuinfo.h"
using namespace std;
int main(){

    stuinfo stu[10];
    int n=3;
    inputstu ( stu , n );
    showstu ( stu , n );
    sortstu ( stu , n );
    showstu ( stu , n );
    char *st;
    cin>>st;
    if(findstu ( stu, n , st)) cout<<"YES"<<'\n';
 
    return 0;
}
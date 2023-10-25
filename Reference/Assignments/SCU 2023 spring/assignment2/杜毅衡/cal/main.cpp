#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include "cal.h"
using namespace std;
int main(){
    char ch[1100];
    init();
    while(scanf("%s",ch)!=EOF){
        sol(ch);
    }
    return 0;
}
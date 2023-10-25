#include stuinfo.h
#include bitsstdc++.h
using namespace std;
stuinfo stu[100];
int main(){
    coutPlease enter the number of studentsendl;
    int n; cinn;
    inputstu(stu,n);
    showstu(stu,n);
    sortstu(stu,n);
    char ch[20];
    coutPlease enter the name of the student you want to findendl;
    scanf(%s,ch);
    findstu(stu,n,ch);
}
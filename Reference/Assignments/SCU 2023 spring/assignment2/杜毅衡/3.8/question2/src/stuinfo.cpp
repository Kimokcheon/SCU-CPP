#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string.h>
#include "stuinfo.h"
using namespace std;
void inputstu(stuinfo stu[] , int n){
    for(int i=1;i<=n;++i){
        cin>>stu[i].name;
        cin>>stu[i].score[0]>>stu[i].score[1]>>stu[i].score[2];
        stu[i].ave=(stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3.0;
    }
    return ;
}
// asks the user to enter each of the preceding items of
//information to set the corresponding members of the structure.


void showstu(stuinfo stu[] , int n){
    for(int i=1;i<=n;++i){
        cout<<stu[i].name<<' '<<stu[i].score[0]<<' '<<stu[i].score[1]<<' '<<stu[i].score[2]<<' '<<stu[i].ave;
        cout<<'\n';
    }
} 
//displays the contents of the structure, one student one line.


bool cmp(stuinfo a,stuinfo b){
    return a.ave>b.ave;
}
void sortstu(stuinfo stu[] , int n){
    sort(stu+1,stu+1+n,cmp);    
}
//sorts in descending order of average of three scores.


bool findstu(stuinfo stu[] , int n, char ch[]){
    for(int i=1;i<=n;++i){
        if(strcmp(stu[i].name,ch)==0) return 1;
    }
    return 0;
} 
//finds if given characters is the student’s name.
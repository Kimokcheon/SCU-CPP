#include <bits/stdc++.h>
#include "stuinfo.h"
using namespace std;
void inputstu(stuinfo stu[] , int &n){
    cout<<"Please input the number of students:"<<'\n';
    cin>>n;
    cout<<"Please input information of :name score1 score2 score3"<<'\n';
    for(int i=1;i<=n;i++){
        cin>>stu[i].name>>stu[i].score[0]>>stu[i].score[1]>>stu[i].score[2];
        stu[i].ave=(stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3.0;
    }
}
void showstu(stuinfo stu[] , int n){
    for(int i=1;i<=n;i++)
        cout<<stu[i].name<<"  ave  "<<stu[i].ave<<"  scores  "<<stu[i].score[0]<<' '<<stu[i].score[1]<<' '<<stu[i].score[2]<<'\n';
}
void sortstu(stuinfo stu[] , int n){
    sort(stu+1,stu+1+n);
}
bool findstu(stuinfo stu[] , int n, string ch){
    for(int i=1;i<=n;i++){
        if(stu[i].name==ch) return 1;
    }
    return 0;
}

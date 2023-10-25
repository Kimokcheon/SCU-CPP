#include "stuinfo.h"
#include <bits/stdc++.h>
using namespace std;
inline bool cmp(stuinfo x,stuinfo y){ return x.ave>y.ave; }
void inputstu(stuinfo stu[],int n){
    cout<<"Please enter student information"<<endl;
    for(int i=0;i<n;i++){
        scanf("%s",stu[i].name);
        cin>>stu[i].score[0]>>stu[i].score[1]>>stu[i].score[2];
        stu[i].ave=(stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3.0;
    }
}
void showstu(stuinfo stu[],int n){
    cout<<"The student information is displayed as follows"<<endl;
    for(int i=0;i<n;i++){
        printf("%s ",stu[i].name);
        cout<<stu[i].score[0]<<' '<<stu[i].score[1]<<' '<<stu[i].score[2]<<' '<<stu[i].ave<<endl;
    }
}
void sortstu(stuinfo stu[],int n){
    cout<<"The ranking of students by average score is as follows"<<endl;
    sort(stu,stu+n,cmp);
    for(int i=0;i<n;i++) printf("%s %lf\n",stu[i].name,stu[i].ave);
}
void findstu(stuinfo stu[],int n,char ch[]){
    int l=strlen(ch);
    for(int i=0;i<n;i++){
        bool tag=1;
        for(int j=0;j<l;j++){
            if(ch[j]!=stu[i].name[j]){ tag=0; break; }
        }
        if(tag){
            cout<<"Given characters is the student's name."<<endl;
            return;
        }
    }
    cout<<"Given characters is not the student's name."<<endl;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include"stuinfo.h"
using namespace std;

void inputstu(stuinfo stu[],int n)
{
    for(int i=0;i<n;i++)
    {
        scanf("%s",stu[i].name);
        double sum=0;
        for(int j=0;j<3;j++) scanf("%lf",&stu[i].score[j]),sum+=stu[i].score[j];
        stu[i].ave=sum/3;
    }
}

void showstu(stuinfo stu[],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<stu[i].name<<" ";
        for(int j=0;j<3;j++) printf("%0.2lf ",stu[i].score[j]);
        printf("%0.2lf\n",stu[i].ave);
    }
}

bool cmp(stuinfo a,stuinfo b)//定义结构体比较方法
{
    return a.ave>b.ave;
}
void sortstu(stuinfo stu[],int n)
{
    sort(stu,stu+n,cmp);//结构体快速排序,按平均分从大到小排序
}

bool check(char a[],char b[])//bool返回值为1代表a,b两char[]相同,为0代表不同
{
    int len=strlen(a),len2=strlen(b);
    if(len!=len2) return 0;
    for(int i=0;i<len;i++) if(a[i]!=b[i]) return 0;
    return 1;
}

bool findstu(stuinfo stu[],int n,char ch[])
{
    for(int i=0;i<n;i++) if(check(stu[i].name,ch)) return 1;
    return 0;
}
#pragma once

struct stuinfo
{
    char name[20];
    double score[3];
    double ave;   
};
void inputstu(stuinfo stu[],int n);
void showstu(stuinfo stu[],int n);
void sortstu(stuinfo stu[],int n);
bool findstu(stuinfo stu[],int n,char ch[]);
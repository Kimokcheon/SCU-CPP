#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm>
#include"exercise.h"
using namespace std;
Point A,B,C;
pair<bool, Point> S1,S2,S3,S4;
int main()
{
    scanf("%lf%lf%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y);
    S1=barycenter(A,B,C);
    S2=circumcenter(A,B,C);
    S3=incenter(A,B,C);
    S4=orthocenter(A,B,C);
    if(!S1.first) puts("Warning");
    else
    {
        printf("%lf %lf\n",S1.second.x,S1.second.y);
        printf("%lf %lf\n",S2.second.x,S2.second.y);
        printf("%lf %lf\n",S3.second.x,S3.second.y);
        printf("%lf %lf\n",S4.second.x,S4.second.y);
    }
}
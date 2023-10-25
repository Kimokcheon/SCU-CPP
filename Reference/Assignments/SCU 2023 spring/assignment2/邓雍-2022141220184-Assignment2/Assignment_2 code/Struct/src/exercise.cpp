#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#include"exercise.h"
using namespace std;

Point operator -(Point A,Point B){return {A.x-B.x,A.y-B.y};}
double Cross(Point A,Point B)
{
    return A.x*B.y-A.y*B.x;
}

double sqr(double x){return x*x;}

double dis(Point A,Point B)
{
    return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}

bool check(Point A,Point B,Point C)
{
    return fabs(Cross(B-A,C-A))>eps;
}

pair<bool, Point> barycenter(Point A, Point B, Point C)
{
    if(!check(A,B,C)) return {0,{0,0}};
    double X=(A.x+B.x+C.x)/3.0,Y=(A.y+B.y+C.y)/3.0;
    return {1,{X,Y}};
}

pair<bool, Point> circumcenter(Point A, Point B, Point C)
{
    if(!check(A,B,C)) return {0,{0,0}};
    double A1,B1,C1,A2,B2,C2;
    A1=2*(B.x-A.x);
    B1=2*(B.y-A.y);
    C1=B.x*B.x+B.y*B.y-A.x*A.x-A.y*A.y;
    A2=2*(C.x-B.x);
    B2=2*(C.y-B.y);
    C2=C.x*C.x+C.y*C.y-B.x*B.x-B.y*B.y;
    double X=(C1*B2-C2*B1)/(A1*B2-A2*B1);
    double Y=(A1*C2-A2*C1)/(A1*B2-A2*B1);
    return {1,{X,Y}};
}

pair<bool, Point> incenter(Point A, Point B, Point C)
{
    double d1=dis(B,C);
    double d2=dis(A,C);
    double d3=dis(A,B);
    double S=d1+d2+d3;
    double X=(d1*A.x+d2*B.x+d3*C.x)/S;
    double Y=(d1*A.y+d2*B.y+d3*C.y)/S;
    return {1,{X,Y}};
}

pair<bool, Point> orthocenter(Point A, Point B, Point C)
{
    double A1=C.x-B.x;
    double B1=C.y-B.y;
    double C1=0;

    double A2=C.x-A.x;
    double B2=C.y-A.y;
    double C2=(B.x-A.x)*A2+(B.y-A.y)*B2;
   
    double d=A1*B2-A2*B1;

    double X=A.x+(C1*B2-C2*B1)/d;
    double Y=A.y+(A1*C2-A2*C1)/d;
    return {1,{X,Y}};
}
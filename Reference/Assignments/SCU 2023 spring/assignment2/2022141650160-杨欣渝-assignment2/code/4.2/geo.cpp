#include "geo.h"
#include <bits/stdc++.h>
using namespace std;
inline bool chk(Point A,Point B,Point C){
    Vec a=B-A,b=C-A;
    if(abs(a*b)<=EPS) return 0;
    return 1;
}
double distance(Point A, Point B) {
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
// 三角形的重心
pair<bool, Point> barycenter(const Point &A, const Point &B, const Point &C){
    if(!chk(A,B,C)) return {0,{0,0}};
    Point BC=C+B,AC=C+A,AB=B+A;
    Point ans=BC+AC+AB;
    ans.x/=6.0,ans.y/=6.0;
    return {1,ans};
}
// 三角形的外心
pair<bool, Point> circumcenter(const Point &a, const Point &b, const Point &c){
    if(!chk(a,b,c)) return {0,{0,0}};
    double x1=a.x,y1=a.y,x2=b.x,y2=b.y,x3=c.x,y3=c.y;
	double a1=2*(x2-x1),b1=2*(y2-y1),c1=x2*x2+y2*y2-x1*x1-y1*y1;
	double a2=2*(x3-x2),b2=2*(y3-y2),c2=x3*x3+y3*y3-x2*x2-y2*y2;
	double x=(c1*b2-c2*b1)/(a1*b2-a2*b1);
	double y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
    return {1,{x,y}};
}
// 三角形的内心
pair<bool, Point> incenter(const Point &A, const Point &B, const Point &C){
    if(!chk(A,B,C)) return {0,{0,0}};
    double a=distance(B,C),b=distance(A,C),c=distance(A,B);
    double x=(a*A.x+b*B.x+c*C.x)/(a+b+c);
    double y=(a*A.y+b*B.y+c*C.y)/(a+b+c);
    Point ans={x,y};
    return {1,ans};
}
// 三角形的垂心
pair<bool, Point> orthocenter(const Point &A,const Point &B,const Point &C) {
    if(!chk(A,B,C)) return {0,{0,0}};
    double a=distance(B,C),b=distance(A,C),c=distance(A,B);
    double s=(a+b+c)/2;
    double area=sqrt(s*(s-a)*(s-b)*(s-c));
	double x=(a*a*(b*b+c*c-a*a)*A.x+b*b*(c*c+a*a-b*b)*B.x+c*c*(a*a+b*b-c*c)*C.x)/(16*area*area);
	double y=(a*a*(b*b+c*c-a*a)*A.y+b*b*(c*c+a*a-b*b)*B.y+c*c*(a*a+b*b-c*c)*C.y)/(16*area*area);
    return {1,{x,y}};
}
#include <iostream> 
#include <cmath>
#include "triangle.h"
using namespace std;

//三角形判断
bool check(const Point &A,const Point &B,const Point&C){
    return abs( ( B.y - A.y ) * ( C.x - A.x ) - ( C.y - A.y ) * ( B.x - A.x ) ) <= EPS ; 
}

// 三角形的重心
pair<bool, Point> barycenter(const Point &A, const Point &B, const Point &C){
    if( check( A , B , C ) ) return make_pair( 0 , O );
    Point ans = Point { ( A.x + B.x + C.x )/3.0 , ( A.y + B.y + C.y )/3.0 };
    return make_pair( 1, ans );
}

// 三角形的外心
double f(double x,double y){ return x*x+y*y; } 
pair<bool, Point> circumcenter(const Point &A, const Point &B, const Point &C){
    if( check( A , B , C ) ) return make_pair( 0 , O );
    double d1=f(B.x,B.y)-f(A.x,A.y),d2=f(C.x,C.y)-f(B.x,B.y);
    double fm=2*((C.y-B.y)*(B.x-A.x)-(B.y-A.y)*(C.x-B.x));
    double ans_x=((C.y-B.y)*d1-(B.y-A.y)*d2)/fm;
    double ans_y=((B.x-A.x)*d2-(C.x-B.x)*d1)/fm;
    Point ans = Point { ans_x , ans_y };
    return make_pair( 1 , ans );
}

double len (const Point &A ,const Point &B){
    return sqrt( ( A.x - B.x ) * ( A.x - B.x ) + ( A.y - B.y) * ( A.y - B.y ) );
}
// 三角形的内心
pair<bool, Point> incenter(const Point &A, const Point &B, const Point &C){
    if( check( A , B , C ) ) return make_pair( 0 , O );
    double a,b,c;
    a=len(B,C) , b=len(C,A) , c=len(A,B);
    double ans_x,ans_y;
    ans_x=(a * A.x + b * B.x + c * C.x ) / ( a + b + c );
    ans_y=(a * A.y + b * B.y + c * C.y ) / ( a + b + c );
    Point ans = Point { ans_x , ans_y };
    return make_pair( 1 , ans );
}

double Cos(double b,double c,double a){
    return (b*b+c*c-a*a)/(2.0*b*c);
}
// 三角形的垂心
pair<bool, Point> orthocenter(const Point &A, const Point &B, const Point &C){
    if( check( A , B , C ) ) return make_pair( 0 , O );
    double a,b,c;
    a=len(B,C) , b=len(C,A) , c=len(A,B);
    double d1,d2,d3;
    d1=a/Cos(b,c,a) , d2=b/Cos(c,a,b) , d3=c/Cos(a,b,c);
    double ans_x,ans_y;
    ans_x=(d1 * A.x + d2 * B.x + d3 * C.x ) / ( d1 + d2 + d3 );
    ans_y=(d1 * A.y + d2 * B.y + d3 * C.y ) / ( d1 + d2 + d3 );
    Point ans = Point { ans_x , ans_y };
    return make_pair( 1 , ans );
}

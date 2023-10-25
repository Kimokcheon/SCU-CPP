#include <bits/stdc++.h>
#define pr make_pair
using namespace std;
const double PI = acos(-1), eps = 1e-9; //PI 与偏差值
struct Point{ 
	double x,y; //横纵坐标
	Point(){}
	Point(double _x,double _y) {x=_x;y=_y;}
	Point operator -(const Point &b)const {return Point(x-b.x,y-b.y);} //减 
	Point operator +(const Point &b)const {return Point(x+b.x,y+b.y);} //加 
	double operator ^(const Point &b)const {return x*b.y-y*b.x;} //叉积 
	double operator *(const Point &b)const {return x*b.x+y*b.y;} //点积 
};
double pf(double x){return x*x;}
double dis(Point x,Point y){return sqrt(pf(x.x-y.x)+pf(x.y-y.y));}
int sgn(double x){ 
	if(fabs(x)<eps) return 0;
	if(x<0) return -1;
	return 1;
}
struct Line{
	Point s,e; //直线用两个点表示 
	Line(){}
	Line(Point _s,Point _e) {s=_s;e=_e;}
	pair<int,Point>operator &(const Line &b)const{ //判断两直线的关系 
		Point res=s;
		if(sgn((s-e)^(b.s-b.e))==0){
			if(sgn((s-b.e)^(b.s-b.e))==0) return make_pair(0,res); //两直线重合 
			else return make_pair(1,res); //两直线平行 
		}
		double t=((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
		res.x+=(e.x-s.x)*t;
		res.y+=(e.y-s.y)*t;
		return make_pair(2,res); //两直线有交点，交点为res 
	}
};
// 三角形的重心
pair<bool, Point> barycenter(Point A, Point B, Point C){
	Line P=Line(A,B),Q=Line(A,C);
	if((P&Q).first!=2) return make_pair(0,A);
	Point ret=A+B+C;
	ret.x/=3.0,ret.y/=3.0;
	return make_pair(1,ret);
}
// 三角形的外心
double MAX(double A,double B,double C){return max(A,max(B,C));}
double MIN(double A,double B,double C){return min(A,min(B,C));}
pair<bool, Point> circumcenter(Point A, Point B, Point C){
	Line P=Line(A,B),Q=Line(A,C);
	if((P&Q).first!=2) return make_pair(0,A);
	Point ret=barycenter(A,B,C).second;
	for(double T=dis(ret,A);T>eps;T*=0.96){
		double maxret=MAX(dis(ret,A),dis(ret,B),dis(ret,C));
		double minret=MIN(dis(ret,A),dis(ret,B),dis(ret,C));
		Point now=Point(ret.x+T*1.0*(rand()-rand())/RAND_MAX,ret.y+T*1.0*(rand()-rand())/RAND_MAX);
		double maxnow=MAX(dis(now,A),dis(now,B),dis(now,C));
		double minnow=MIN(dis(now,A),dis(now,B),dis(now,C));
		if(maxret-minret>maxnow-minnow) ret=now;
	}
	return make_pair(1,ret);
}
// 三角形的内心
pair<bool, Point> incenter(Point A, Point B, Point C){
	Line P=Line(A,B),Q=Line(A,C);
	if((P&Q).first!=2) return make_pair(0,A);
	double a=dis(B,C),b=dis(A,C),c=dis(A,B);
    double s=a+b+c; 
    double x=(a*A.x+b*B.x+c*C.x)/s;
    double y=(a*A.y+b*B.y+c*C.y)/s;
	return make_pair(1,Point(x,y));	
}
// 三角形的垂心
pair<bool, Point> orthocenter(Point A, Point B, Point C){
	Line P=Line(A,B),Q=Line(A,C);
	if((P&Q).first!=2) return make_pair(0,A);
	double A1=B.x-C.x;
	double B1=B.y-C.y;
	double C1=A1*A.y-B1*A.x;
	double A2=A.x-C.x;
	double B2=A.y-C.y;
	double C2=A2*B.y-B2*B.x;
	double x=(A1*C2-A2*C1)/(A2*B1-A1*B2);
	double y=(B1*C2-B2*C1)/(A2*B1-A1*B2);
	return make_pair(1,Point(x,y));	
}
void out(Point A){printf("%.3lf ",A.x);printf("%.3lf\n",A.y);}
int main (){
	srand(time(0));
	cout<<"Please input the triangle"<<'\n';
	Point x,y,z;
	cin>>x.x>>x.y>>y.x>>y.y>>z.x>>z.y;
	if(barycenter(x,y,z).first==0) return cout<<"ERROE!",0;
	cout<<"the barycenter is ";out(barycenter(x,y,z).second);
	cout<<"the circumcenter is ";out(circumcenter(x,y,z).second);
	cout<<"the incenter is ";out(incenter(x,y,z).second);
	cout<<"the orthocenter is ";out(orthocenter(x,y,z).second);
	return 0;
}

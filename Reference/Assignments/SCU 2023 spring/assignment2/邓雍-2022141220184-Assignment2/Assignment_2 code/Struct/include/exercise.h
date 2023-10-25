#pragma once
#include<cmath>
using namespace std;

const double eps=1e-7;

struct Point{double x,y;};
using Vec =Point;
struct Line {Point P;Vec v;};
struct Seg{Point A,B;};
struct Circle{Point O;double r;};
const Point O={0,0};
const Line Ox={O,{1,0}},Oy={O,{1,0}};
const double PI=acos(-1),EPS=1e-9;

pair<bool, Point> barycenter(Point A, Point B, Point C);
pair<bool, Point> circumcenter(Point A, Point B, Point C);
pair<bool, Point> incenter(Point A, Point B, Point C);
pair<bool, Point> orthocenter(Point A, Point B, Point C);
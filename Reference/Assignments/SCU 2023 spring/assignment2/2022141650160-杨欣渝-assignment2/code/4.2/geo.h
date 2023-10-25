#include <bits/stdc++.h>
using namespace std;
struct Point { 
    double x, y;
    Point operator+(const Point& other) const { return {x+other.x,y+other.y}; }
    Point operator-(const Point& other) const { return {x-other.x,y-other.y}; } 
    double operator*(const Point& other) const { return x*other.y-y*other.x; } 
    double len(){ return sqrt(x*x+y*y); }
}; // 点
using Vec = Point; // 向量
struct Line { Point P; Vec v; }; // 直线（点向式）
struct Seg { Point A, B; }; // 线段（存两个端点）
struct Circle { Point O; double r; }; // 圆（存圆心和半径）
const Point O = {0, 0}; // 原点
const Line Ox = {O, {1, 0}}, Oy = {O, {0, 1}}; // 坐标轴
const double PI = acos(-1),EPS = 1e-9; //PI
// 三角形的重心
pair<bool, Point> barycenter(const Point &A, const Point &B, const Point &C);
// 三角形的外心
pair<bool, Point> circumcenter(const Point &A, const Point &B, const Point &C);
// 三角形的内心
pair<bool, Point> incenter(const Point &A, const Point &B, const Point &C);
// 三角形的垂心
pair<bool, Point> orthocenter(const Point &A, const Point &B, const Point &C);
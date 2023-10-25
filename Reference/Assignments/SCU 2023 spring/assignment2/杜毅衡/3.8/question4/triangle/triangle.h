#pragma once
#include <cmath>
struct Point { double x, y; }; // 点
using Vec = Point; // 向量
struct Line { Point P; Vec v; }; // 直线（点向式）
struct Seg { Point A, B; }; // 线段（存两个端点）
struct Circle { Point O; double r; }; // 圆（存圆心和半径）
const Point O = {0, 0}; // 原点
const Line Ox = {O, {1, 0}}, Oy = {O, {0, 1}}; // 坐标轴
const double PI = acos(-1), EPS = 1e-9; //PI 与偏差值
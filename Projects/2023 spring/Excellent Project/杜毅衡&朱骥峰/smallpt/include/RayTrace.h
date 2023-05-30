#pragma once 
#include <iostream>
#include <cmath>
#include <chrono>
#include <climits>
#include <algorithm>
#include <random>
#include <utility>
using namespace std;

const double eps = 1e-4, inf = 1e20, pi = acos(-1.0);

//vector
class Vec {
public:
    double x, y, z;                             // position, also color (r,g,b)
public:
    Vec() = default;
    Vec(double x_, double y_, double z_) ;
    Vec operator+(const Vec &b) const ;
    Vec operator-(const Vec &b) const ;
    Vec operator*(double b) const ;
    Vec operator*(const Vec &b) const ;         // dot product
    Vec operator%(const Vec &b);                       // cross:
    double sum() const ;                        // x+y+z
    Vec norm() ;                                // normalization

};


class Ray { 
public:
    //o:exit point , d:exit direction
    Vec o, d; 
public:
    Ray() = default;
    Ray(Vec o_, Vec d_) ;
};

//material types
//diffuse,specular,refract
enum Refl_t { DIFF, SPEC, REFR }; 

class Sphere {
public:
    double rad;       // radius
    Vec p, e, c;      // position, emission, color
    Refl_t refl;      // reflection type (DIFFuse, SPECular, REFRactive)
    static int num;   // num
public:
    Sphere(){ num++; }
    Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_);

    // returns distance(the exit point of ray to sphere), 0 if nohit
    double intersect(const Ray &r) const ; 
    ~Sphere(){ num--; }

};

Vec radiance(const Ray &r, int depth);

unsigned int rng();
double rnd();
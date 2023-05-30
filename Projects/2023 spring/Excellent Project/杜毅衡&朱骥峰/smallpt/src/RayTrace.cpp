#include "../include/RayTrace.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <climits>
#include <algorithm>
#include <random>
#include <utility>
using namespace std;

mt19937 seed(chrono::steady_clock::now().time_since_epoch().count());
unsigned int rng(){ return seed(); }
double rnd( ) { return rng() * 1. / UINT_MAX; }     // [0,1] rand

Vec::Vec(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
Vec Vec::operator+(const Vec &b) const { return Vec(x+b.x, y+b.y, z+b.z); }
Vec Vec::operator-(const Vec &b) const { return Vec(x-b.x, y-b.y, z-b.z); }
Vec Vec::operator*(double b) const { return Vec(x*b, y*b, z*b); }
Vec Vec::operator*(const Vec &b) const { return Vec(x*b.x, y*b.y, z*b.z); }
Vec Vec::operator%(const Vec &b){ return Vec(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);}
Vec Vec::norm(){ return *this = *this * (1/sqrt(x*x + y*y + z*z)); }
double Vec::sum() const { return x+y+z; }

Ray::Ray(Vec o_, Vec d_) : o(o_), d(d_) {} 

Sphere::Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_):
    rad(rad_), p(p_), e(e_), c(c_), refl(refl_) { num++; }

int Sphere::num=0;

Sphere spheres[] = { //Scene: radius, position, emission, color, material
    Sphere(1e5, Vec( 1e5+1,40.8,81.6), Vec(),Vec(.75,.25,.25),DIFF),//Left
    Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(),Vec(.25,.25,.75),DIFF),//Rght
    Sphere(1e5, Vec(50,40.8, 1e5),     Vec(),Vec(.75,.75,.75),DIFF),//Back
    Sphere(1e5, Vec(50,40.8,-1e5+170), Vec(),Vec(),           DIFF),//Frnt
    Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(),Vec(.75,.75,.75),DIFF),//Botm
    Sphere(1e5, Vec(50,-1e5+81.6,81.6),Vec(),Vec(.75,.75,.75),DIFF),//Top
    Sphere(16.5,Vec(27,16.5,47),       Vec(),Vec(1,1,1)*.999, SPEC),//Mirr
    Sphere(16.5,Vec(73,16.5,78),       Vec(),Vec(1,1,1)*.999, REFR),//Glas
    Sphere(600, Vec(50,681.6-.27,81.6),Vec(12,12,12),  Vec(), DIFF) //Lite
};


double Sphere::intersect(const Ray &r) const{
    // Solve t^2*d.d + 2*t*(o-p).d + (o-p)*(o-p)-R^2 = 0
    Vec op = p-r.o;
    double b = (op*r.d).sum();
    double det = b*b - (op*op).sum() + rad*rad;
    if (det<0) return 0; 
    else det = sqrt(det);
    double t = b-det;
    if(t>eps) return t;
    t = b+det;
    if(t>eps) return t;
    return 0;
}

bool intersect(const Ray &r, double &t, int &id){
    int n=spheres[0].num;
    double d=0;
    t=inf;
    for(int i=0 ; i<n ; ++i) if( (d = spheres[i].intersect(r)) && d<t ){
        t=d;
        id=i;
    }
    return t<inf;
}

Vec radiance(const Ray &r, int depth){
    double t=0;                                 // distance to intersection
    int id=0;                                   // id of intersected object
    if (!intersect(r, t, id)) return Vec();     // if miss, return black
    const Sphere &obj = spheres[id];            // the hit object
    Vec x = r.o + r.d*t;
    Vec n = (x-obj.p).norm();
    Vec nl = (n*r.d).sum() < 0 ? n : n*-1;
    Vec f = obj.c;
    double p = max( max(f.x, f.y), f.z ); // max refl
    ++depth;
    if (depth>10) {
        if ( p > rnd() ) f = f * (1/p); 
        else return obj.e;
    }
    // Ideal DIFFUSE reflection
    if (obj.refl == DIFF){           
        // return obj.e;       
        double r1 = 2*pi*rnd();
        double r2 = rnd();
        double r2s = sqrt(1-r2*r2);
        Vec w = nl;
        Vec u = ( (fabs(w.x)>0.1? Vec(0,1,0) : Vec(1,0,0)) % w ).norm();
        Vec v = w%u;
        Vec d = ( u*cos(r1)*r2s + v*sin(r1)*r2s + w*r2 ).norm();
        return obj.e + f * radiance( Ray(x, d), depth )  ;
    }
    // Ideal SPECULAR reflection 
    else if (obj.refl == SPEC){ 
        Ray reflRay(x, r.d - n*2*(n*r.d).sum() );  
        return obj.e + f * radiance( reflRay, depth );
    }
    // Ideal dielectric REFRACTION            
    else{          
        // return obj.e;                         
        Ray reflRay(x, r.d - n*2*(n*r.d).sum() );     
        bool fl = (n*nl).sum()>0;                // Ray from outside going in?
        double nc = 1, nt = 1.5, cos2t=0 ;
        double nnt = fl? nc/nt : nt/nc;
        double ddn = (r.d*nl).sum();
        // Total internal reflection
        if ( (cos2t = 1 - nnt*nnt*(1-ddn*ddn) ) < 0)    
            return obj.e + f* radiance( reflRay, depth );
        double tmp = (ddn*nnt + sqrt(cos2t));
        Vec tdir = ( r.d*nnt - n*( (fl?1:-1) * tmp)).norm();
        double a = nt-nc, b = nt+nc, c = 1 - ( fl? -ddn : (tdir*n).sum() );
        double R0 = a*a/(b*b);
        double Re = R0 + (1-R0)*c*c*c*c*c;
        double Tr = 1-Re, P = 0.25+0.5*Re;
        double RP = Re/P, TP = Tr/(1-P);
        double r = rnd();
        if( depth > 2 ) {        
            if( r < P ) return obj.e + f * radiance(reflRay, depth) * RP;
            else return obj.e + f * radiance(Ray(x, tdir), depth) * TP;
        }
        else return obj.e + f * (radiance(reflRay, depth) * Re + radiance(Ray(x, tdir), depth) * Tr);        
    }                            
}


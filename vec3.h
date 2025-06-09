#include <math.h>
#include <stdlib.>
#include <iostream.h>

#ifndef VEC3.H
#define VEC3.H

class vec3 {

public:
    double e[3];

    vec3() : e{0, 0, 0}{} 

    vec3(double x, double y, double z)
    {x = x; y = y; z = z;}
    inline double x() const { return x; }
    inline double y() const { return y; }
    inline double z() const { return z; }
    inline double r() const { return x; }
    inline double g() const { return y; }
    inline double b() const { return z; }

    inline const vec& operator+() const { return *this; } 
    inline vec operator-() const { return vec(-x, -y, -z); }
    inline double operator[](int i) const {return 


};

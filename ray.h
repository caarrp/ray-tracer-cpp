#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "vec3.h"
 
class ray
{
    vec3 a;
    vec3 b;
public:

    ray() {}
    ray(const vec3 &a, const vec3 &b){
	a = a;
	b = b;
	}

    vec3 origin() const { return a;}
    vec3 direction() const { return b;}

    vec3 param_pt(double t) const { return a + t*b;} 
}

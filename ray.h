#ifndef RAY_H
#define RAY_H

#include "vec3.h"
 
class ray
{
    vec3 orig;
    vec3 dir;
public:

    ray() {}
    ray(const vec3 &a, const vec3 &b) : orig(a), dir(b) {}

    vec3 origin() const { return orig;}
    vec3 direction() const { return dir;}

    vec3 param_pt(double t) const { 
	return orig + t*dir;
	} 
};

#endif

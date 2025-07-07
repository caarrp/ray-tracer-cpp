#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"
//include ray bc its needed for hit function

struct hit_record {
    //stores details of ray/obj intersection
    double t;
    //distance along ray where hit occurs
    vec3 p;
    //position in space where ray hits obj
    vec3 normal;
    //important for shading/lighting calcs
};

class hitable {
    //abstract base class of objs that can be "hit"
    public:
	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
	//virtual allows other class to override
};

#endif

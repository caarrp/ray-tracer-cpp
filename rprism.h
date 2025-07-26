#ifndef RPRISM_H
#define RPRISM_H
//rectangle inclusion guards

#include "hitable.h"

class rprism : public hitable {

    vec3 origin;
    vec3 height;
    vec3 length;
    vec3 width;
    shared_ptr<material> mat;

public:

    rprism() {}

    rprism(double l, double w, double h, std::shared_ptr<material> m);

    virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const;
};

rprism :: rprism(vec3 o, double l, double w, double h, std::shared_ptr<material> m)
    {
    //+y axis is up, z is in/out, x is left/right
    origin = o; 
    height = vec3(o[0], o[1] + h, o[2]);
    width = vec3(o[0], o[1], o[2] + w); //essentially depth
    length = vec3(o[0] + l, o[1], o[2]);
    }


rprism :: virtual bool hit(const ray &r, interval ray_t, hit_record &rec) 
    const {

    }

#endif


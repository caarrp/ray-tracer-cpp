#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class sphere: public hitable {
    public:
	sphere() {}
	sphere(vec3 c, double r) : center(c), radius(r) {};
	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;
	vec3 center;
	double radius;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const{
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - a*c;

    if (discriminant > 0){
	float temp = (-b - sqrt(b*b - a*c))/a;
	if (temp < t_max && temp > t_min){
	    rec.t = temp;
	    rec.p = r.param_pt(rec.t);
	    rec.normal = (rec.p - center) / radius;
	    return true;
	    }
	temp = (-b + sqrt(b*b - a*c))/a;
	if (temp < t_max && temp > t_min){
	    rec.t = temp;
	    rec.p = r.param_pt(rec.t);
	    rec.normal = (rec.p - center) / radius; 
	    return true;
	    }
	}
    return false;
}

#endif

#ifndef SPHERE_H
#define SPHERE_H
//sphere inclusion guards

#include "hitable.h"

class sphere: public hitable {
//sphere inherits from hitable
    public:
	sphere() {}
	//default constructor defined
	sphere(vec3 c, double r) : center(c), radius(r) {};
	//parameterized constructor inits center and radius
	
	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;
	//declaring virtual function hit
	
	vec3 center;
	double radius;
	//notice these are still public
};
//ends class declaration


bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const{
    //hit checks if a ray intersects the sphere, if so 
    //we record the hit details in rec

    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - a*c;
    //computing components of quadratic eq. to solve 
    //for any ray - sphere intersection

    if (discriminant >= 0){
	//ray hits sphere including tangent pts
	
	double temp = (-b - sqrt(b*b - a*c))/a;
	//temp finds the closer of the hit points (if 2)
	if (temp < t_max && temp > t_min){
	    //if its in range:
	    //meaning its not too close to viewport
	    //or too far away
	    rec.t = temp; 
	    //records the scalar dist. along the ray
	    rec.p = r.param_pt(rec.t);
	    //records the point in space where ray hits object
	    rec.normal = (rec.p - center) / radius;
	    //saves normal of ray to sphere

	    return true;
	    }
	temp = (-b + sqrt(b*b - a*c))/a;
	//checking the other hit point just in case
	if (temp < t_max && temp > t_min){
	    rec.t = temp;
	    rec.p = r.param_pt(rec.t);
	    rec.normal = (rec.p - center) / radius; 
	    return true;
	    }
	}
    return false;
    //no hits then its not recorded
}

#endif

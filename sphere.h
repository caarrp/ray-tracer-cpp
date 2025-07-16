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
	
	virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const;
	//declaring virtual function hit
	
	vec3 center;
	double radius;
	//notice these are still public
};
//ends class declaration


bool sphere::hit(const ray &r, interval ray_t, hit_record &rec) const{
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.param_pt(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_n(r, outward_normal);

        return true;
}

#endif

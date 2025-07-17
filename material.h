#ifndef MATERIAL_H
#define MATERIAL_H

#include "hitable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(
	    const ray &r_in, const hit_record &rec, color &attentuation, ray &scatter) const {
	return false;
    }

class labertian : public material{

    vec3 albedo;//for material color
public:
    lambertian(const vec3 albedo) : albedo(albedo) {}
    //parameterized constructor

    bool scatter(const ray &r_min,
	    const hit_record &rec; vec3 &attentuation, ray &scatter)
	const override{
	    vec3 scatter_direction = rec.normal + random_unit();
	    
	    if (scatter_direction.near_zero()){
		scatter_direction = rec.normal;
	    }
	    scatter = ray(rec.p, scatter_direction);
	    attentuation = albedo;
	    return true;
	}
};

class metal : public material {
    vec3 albedo;
public:
    metal(const color &albedo) : albedo(albedo) {}
    //parameterized constructor

    bool scatter(const ray &r_in, 
	    const hit_record &rec, vec3 &attentuation, ray &scatter)
	const override{

	    vec3 reflected = reflect(r_in.direction(), rec.normal());
	    scatter = ray(rec.p, reflected);
	    attentuation = albedo;
	    return true
	}
};

#endif

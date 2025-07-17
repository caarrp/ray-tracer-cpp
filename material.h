#ifndef MATERIAL_H
#define MATERIAL_H

#include "hitable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(
	    const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scatter) const {
	return false;
    }
};



class lambertian : public material{

    vec3 albedo;//for material color
public:
    lambertian(const vec3 albedo) : albedo(albedo) {}
    //parameterized constructor

    bool scatter(const ray &r_min,
	    const hit_record &rec, vec3 &attenuation, ray &scatter)
	const override{
	    vec3 scatter_direction = rec.normal + random_unit();
	    
	    if (scatter_direction.near_zero()){
		scatter_direction = rec.normal;
	    }
	    scatter = ray(rec.p, scatter_direction);
	    attenuation = albedo;
	    return true;
	}
};



class metal : public material {
    vec3 albedo;
    double fuzz;
public:
    metal(const vec3 &albedo, double fuzz) : 
	albedo(albedo), fuzz(fuzz) {}
    //parameterized constructor

    bool scatter(const ray &r_in, 
	    const hit_record &rec, vec3 &attenuation, ray &scatter)
	const override{

	    vec3 reflected = reflect(r_in.direction(), rec.normal);
	    reflected = unit(reflected) + (fuzz*random_unit());
	    scatter = ray(rec.p, reflected);
	    attenuation = albedo;
	    return (dot(scatter.direction(), rec.normal) > 0);
	}
};



class dielectric : public material {

    double refractive_index;
public:

    dielectric(double ref_idx) : refractive_index(ref_idx) {}

    bool scatter(const ray &r_in,
	    const hit_record &rec, vec3 &attentuation, ray &scatter)
	const override{
	    attentuation = vec3(1.0, 1.0, 1.0);
	    double ri = rec.front_face ? (1.0/refractive_index) : refractive_index;

	    vec3 unit_direction = unit(r_in.direction());
	
	    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
	    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

	    bool cant_refract = ri*sin_theta > 1.0;
	    vec3 direction;

	    if (cant_refract){
		direction = reflect(unit_direction, rec.normal);
	    }
	    else{
		direction = refract(unit_direction, rec.normal, ri);
	    }

	    scatter = ray(rec.p, direction);
	    return true;
	}
};

#endif


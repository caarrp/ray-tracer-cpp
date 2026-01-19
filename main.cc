#include "extra.h"

#include "material.h"
#include "camera.h"
#include "hitable.h"
#include "hitable_list.h"
#include "texture.h"
#include "sphere.h"



double hit_sphere(const vec3 &center, double radius, const ray &r){
    vec3 oc = center - r.origin();
    double a = dot(r.direction(), r.direction());
    double b = -2.0*dot(r.direction(), oc);
    double c = dot(oc, oc) -radius*radius;
    double d = b*b - 4*a*c;
    //dicriminant

    if (d < 0) {
	return -1.0;
    }
    else{
	return (-b - std::sqrt(d))/(2.0*a);
    }
}

double hit_rprism(){}



int main() {

    //world
    hitable_list world;
    
    auto difflight = make_shared<diffuse_light>(vec3(4,4,4));
    world.add(make_shared<sphere>(vec3(3,1,-2), 0.25, difflight)); //light! 

    auto m_g = make_shared<lambertian>(vec3(0.4, 0.4, 0.4));
    auto m_c = make_shared<lambertian>(vec3(0.1, 0.3, 0.5));
    auto m_inner = make_shared<dielectric>(1.000/1.500);
    auto m_outer = make_shared<dielectric>(1.5);
    auto m_r = make_shared<metal>(vec3(0.0, 0.8, 0.8), 0.2);
    auto m_a = make_shared<metal>(vec3(0.0, 0.5, 0.1), 0.0);
    auto m_b = make_shared<dielectric>(1.518);

    world.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, m_g));
    world.add(make_shared<sphere>(vec3(0.0, 0.0, -1.5), 0.5, m_c));
    world.add(make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.5, m_outer));
    world.add(make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.3, m_inner));
    world.add(make_shared<sphere>(vec3(1.0, 0.0, 0.0), 0.5, m_r));
    world.add(make_shared<sphere>(vec3(2.0,-0.5, 3.0), 0.9, m_a));
    world.add(make_shared<sphere>(vec3(-2.0, 0.35, 2.0),1.0, m_b));

    camera nikon;

    nikon.aspect_ratio = 16.0/9.0;
    nikon.image_width = 1000;
    nikon.samples_per_pixel = 60;//antialiasing
    nikon.max_depth = 100;		//limiting raycolor recursion
	
    nikon.field_of_view = 80;
    nikon.origin_pt = vec3(0, 1, 5);
    nikon.focus_pt = vec3(0, 0, -1);
    nikon.v_up = vec3(0, 1, 0);

    nikon.defocus_angle = 0.001;
    nikon.focus_dist = 6;

    nikon.render(world);

}
	    







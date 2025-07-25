#include "extra.h"

#include "material.h"
#include "camera.h"
#include "hitable.h"
#include "hitable_list.h"
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




int main() {

    //world
    hitable_list world;
    
    
    auto m_g = make_shared<lambertian>(vec3(0.4, 0.7, 0.0));
    auto m_c = make_shared<lambertian>(vec3(0.1, 0.3, 0.5));
    auto m_inner = make_shared<dielectric>(1.000/1.500);
    auto m_outer = make_shared<dielectric>(1.5);
    auto m_r = make_shared<metal>(vec3(0.0, 0.8, 0.8), 0.2);

    //world.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, m_g));
    world.add(make_shared<sphere>(vec3(0.0, 0.0, -1.2), 0.5, m_c));
    //world.add(make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.5, m_outer));
    //world.add(make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.3, m_inner));
    //world.add(make_shared<sphere>(vec3(1.0, 0.0, -1.0), 0.5, m_r));


    camera bb;

    //bb.aspect_ratio = 16.0/9.0;
    bb.image_width = 500;
    bb.samples_per_pixel = 60;//antialiasing
    bb.max_depth = 50;		//limiting raycolor recursion
	
    bb.field_of_view = 90;
    bb.origin_pt = vec3(3, 2, 0);
    bb.focus_pt = vec3(0, 0, -1);
    //bb.v_up = vec3(0, 1, 0);

    //bb.defocus_angle = 10.0;
    //bb.focus_dist = 3.4;

    bb.render(world);

}
	    







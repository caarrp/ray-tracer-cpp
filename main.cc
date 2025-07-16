#include "extra.h"

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
    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));

    camera bob;

    bob.aspect_ratio = 16.0/9.0;
    bob.image_width = 400;

    bob.render(world);

}
	    







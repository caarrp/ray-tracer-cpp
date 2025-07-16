#include "extra.h"
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

vec3 ray_color(const ray& r){
    double t = hit_sphere(vec3(0,0,-1), 0.5, r);
    if (t > 0.0) {
	vec3 n = unit(r.param_pt(t) - vec3(0, 0, -1));
	return 0.5*vec3(n.x() + 1, n.y() + 1, n.z() + 1);
    }
    vec3 unit_direction = unit(r.direction());
    double a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*vec3(1.0,1.0,1.0) + a*vec3(0.7, 0.5, 1.0);
}
	



int main() {

    double aspect_ratio = 16.0/9.0;
    int image_width = 400;
 
    int image_height = int( image_width / aspect_ratio);

    image_height = (image_height < 1) ? 1 : image_height;
    //if the image height is less than one make it one, otherwise keep as is
 
    //CAMERA
    double focal_length = 1;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width)/image_height);
    vec3 camera_center = vec3(0,0,0);

    //U, V VECTORS
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    //U, V PIXELS
    vec3 pixel_u = viewport_u / image_width;
    vec3 pixel_v = viewport_v / image_height;

    //UPPERLEFT PIXEL
    vec3 viewport_ul = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel_ul = viewport_ul + 0.5 * (pixel_u + pixel_v);

    //RENDER
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++){
	for (int i = 0; i < image_width; i++){
	    vec3 pixel_center = pixel_ul + i*pixel_u + j*pixel_v;
	    vec3 ray_direction = pixel_center - camera_center;

	    ray r(camera_center, ray_direction);

	    vec3 pixel_color = ray_color(r);
	    write_color(std::cout, pixel_color);
	}
    }
    std::clog << "\rDone! \n";
}
	    







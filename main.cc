#include "color"
#include "ray.h"
#include "vec3.h"

#include <iostream>

color ray_color(const ray& r){
    return color(0,0,0);
}


int main() {

    double aspect_ratio = 16.0/9.0;
    int image_width = 400;
 
    image_height = int( image_width / aspect_ratio);

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

	    color pixel_color = ray_color(r);
	    write_color(std::cout, pixel_color);
	}
    }
    std::clog << "\rDone! \n";
}
	    





}

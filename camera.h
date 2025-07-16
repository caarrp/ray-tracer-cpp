#ifndef CAMERA_H
#define CAMERA_H



#include "hitable.h"


class camera {
public:
    //IMAGE
    double aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int samples_per_pixel = 10;

  
    void render(const hitable &world){
	initialize();	

	//RENDER
	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++){
	    for (int i = 0; i < image_width; i++){
		vec3 pixel_color(0,0,0);

		for (int sample = 0; sample < samples_per_pixel; sample++){
		    ray r = get_ray(i, j);
		    pixel_color += ray_color(r, world);
		}

		write_color(std::cout, pixel_sample_scale * pixel_color);
	    }
	}
	std::clog << "\rDone! \n";
    }
 

private:
    int image_height;
    vec3 camera_center;
    vec3 pixel_ul;
    vec3 pixel_u;
    vec3 pixel_v;
    double pixel_sample_scale;


    vec3 ray_color(const ray& r, const hitable &world){
	hit_record rec;
	if (world.hit(r, interval(0, infinity), rec)){
	    vec3 direction = random_on_hemisphere(rec.normal);
	    return 0.5 * ray_color(ray(rec.p, direction), world);
	}
    
	vec3 unit_direction = unit(r.direction());
	double a = 0.5*(unit_direction.y() + 1.0);
	return (1.0-a)*vec3(1.0,1.0,1.0) + a*vec3(0.6, 0.7, 1.0);
	}

    void initialize(){
	
	image_height = int( image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;
	//if imageheight is less than one its one, otherwise keep as is

	pixel_sample_scale = 1.0/samples_per_pixel;

	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * (double(image_width)/image_height);
	camera_center = vec3(0,0,0);

	//U, V VECTORS
	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);

	//U, V PIXELS
	pixel_u = viewport_u / image_width;
	pixel_v = viewport_v / image_height;

	//UPPERLEFT PIXEL
	vec3 viewport_ul = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
	pixel_ul = viewport_ul + 0.5 * (pixel_u + pixel_v);
    }

    ray get_ray(int i, int j) const{
        
	auto offset = sample_square();
        auto pixel_sample = pixel_ul
                          + ((i + offset.x()) * pixel_u)
                          + ((j + offset.y()) * pixel_v);

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    
};

#endif

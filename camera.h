#ifndef CAMERA_H
#define CAMERA_H



#include "hitable.h"
#include "material.h"


class camera {
    
    

public:
    //IMAGE
    double aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int samples_per_pixel = 10;
    int max_depth = 10; //num ray bounces into scene
    vec3 background;
    
    double field_of_view = 90; //field of view, vert view angle
    vec3 origin_pt = vec3(0,0,0);//pt camera is centerd at
    vec3 focus_pt = vec3(0,0,-1);//pt camera is pointing to
    vec3 v_up = vec3(0,1,0);//relative up direction
    
    double defocus_angle = 0;
    double focus_dist = 1;

    void render(const hitable &world, bool paralell = false){
	
	if (paralell){
	    init_paralell();
	}
	else{
	    init_perspective();
	}

	//RENDER
	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++){
	    for (int i = 0; i < image_width; i++){
		vec3 pixel_color(0,0,0);

		for (int sample = 0; sample < samples_per_pixel; sample++){
		    ray r = get_ray(i, j);
		    pixel_color += ray_color(r, max_depth, world);
		}

		write_color(std::cout, pixel_sample_scale * pixel_color);
	    }
	}
	std::clog << "\rDone! \n";
    }
 

private:

    int image_height;
    vec3 camera_center;
    vec3 pixel_00;
    vec3 pixel_u;
    vec3 pixel_v;
    double pixel_sample_scale;
    vec3 u, v, w;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;
    

    vec3 ray_color(const ray& r, int depth, const hitable &world){
	if (depth <= 0){
	    return vec3(0,0,0);
	}
	hit_record rec;
	if (world.hit(r, interval(0.001, infinity), rec)){

	    ray scatter;
	    vec3 attenuation;
	    
	    if (rec.mat->scatter(r, rec, attenuation, scatter)){
		return attenuation * ray_color(scatter, depth -1, world);
		}
	    return vec3(0, 0, 0);
	}

	if (!world.hit(r, interval(0.001, infinity), rec)){
	vec3 unit_direction = unit(r.direction());
	double a = 0.5*(unit_direction.y() + 1.0);
	return (1.0-a)*vec3(0.5,0.5,0.5) + a*vec3(0.0, 0.0, 0.5);
	}//technically this is my background atm

	ray scattered;
	vec3 attenuation;
	vec3 color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

	if (!rec.mat->scatter(r, rec, attenuation, scattered))
	    return color_from_emission;

	vec3 color_from_scatter = attenuation * ray_color(scattered, depth - 1, world);
	return color_from_emission + color_from_scatter;
	}


    void init_perspective(){
	
	image_height = int(image_width / (aspect_ratio));
	image_height = (image_height < 1) ? 1 : image_height;
	//if imageheight is less than one its one, otherwise keep as is
	//aspect_ratio = double(image_width) / double(image_height); 

	camera_center = origin_pt;

	pixel_sample_scale = 1.0/samples_per_pixel;

	//determining viewport dimensions
	//double focal_length = (origin_pt - focus_pt).length();
	double theta = degrees_to_radians(field_of_view);
	double h = std::tan(theta/2);
	double viewport_height = 2*h*focus_dist;
	double viewport_width = viewport_height * aspect_ratio;
#if DEBUG
	std::cerr << viewport_height << " x " << viewport_width << std::endl;
#endif
	//calculate v across horisontal and vertical
	w = unit(origin_pt - focus_pt);
	u = unit(cross(v_up, w));
	v = cross(w, u);
#if DEBUG
	w.print();
	u.print();
	v.print();
#endif
	//U, V VECTORS
	vec3 viewport_u = viewport_width * u;
	vec3 viewport_v = viewport_height * -v;

	//U, V PIXELS
	pixel_u = viewport_u / image_width;
	pixel_v = viewport_v / image_height;

	//UPPERLEFT PIXEL
	vec3 viewport_ul = camera_center - (focus_dist*w) - viewport_u/2 - viewport_v/2;
	pixel_00 = viewport_ul + 0.5 * (pixel_u + pixel_v);

	//DEFOCUS DISK BASIS V's
	double defocus_r = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
	defocus_disk_u = u * defocus_r;
	defocus_disk_v = v * defocus_r;

    }

    void init_paralell() {
	
    }


    ray get_ray(int i, int j) const{
        
	auto offset = sample_square();
        auto pixel_sample = pixel_00
                          + ((i + offset.x()) * pixel_u)
                          + ((j + offset.y()) * pixel_v);
	
	

        vec3 ray_origin = (defocus_angle <= 0)? camera_center : defocus_disk_sample();
        vec3 ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double(-0.5, 0.5), random_double(-0.5, 0.5), 0);
    }

    vec3 defocus_disk_sample() const {
	vec3 point = random_in_unit_disk();
	return camera_center + (point[0] * defocus_disk_u) + (point[1] * defocus_disk_v);
    }
    
};

#endif

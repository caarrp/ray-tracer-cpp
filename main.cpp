#include <iostream>
#include "sphere.h"
#include "hitable_list.h"




vec3 color(const ray &r, hitable *world){
    //a very key part of the ray tracer, colors pixels
    hit_record rec;
    //world conains all hitable objects
    if (world->hit(r, 0.0, 10000.0, rec)) {
	//if the ray intersects with anything in range
	return 0.5 * vec3(rec.normal.x()+1.0, rec.normal.y()+1.0, rec.normal.z()+1.0);
	//return a color based off the surface normal
	//maps to [-1,1] -> [0,1]
    }

    else{
	//if the ray did not hit anything
	vec3 unit_dir = unit(r.direction());
	double t = 0.5 *(unit_dir.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	//return a linear interpolation between light blue and white
    }	
}



int main(){

    int nx = 400;
    int ny = 200;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -2.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 1.0, 0.0);

    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1.0), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1.0), 100);
    hitable *world = new hitable_list(list, 2);

    for (int j = ny-1; j >= 0; j--){
	for (int i = 0; i < nx; i++){
	    
	    double u = double(i) / double(nx);
	    double v = double(j) / double(ny);

	    ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
	    
	    vec3 p = r.param_pt(2.0);
	    vec3 col = color(r, world);

	    int ir = int(255.99*col[0]);
	    int ig = int(255.99*col[1]);
	    int ib = int(255.99*col[2]);

	    std::cout << ir << " " << ig << " " << ib << '\n';
	}
    }
}

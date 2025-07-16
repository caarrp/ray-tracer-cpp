#ifndef  HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"
#include <vector>

using std::make_shared;
using std::shared_ptr;


class hitable_list: public hitable {
    //inherits from hitable

    public:
	std::vector<std::shared_ptr<hitable>> objects;

	hitable_list() {}
	//default constructor
	hitable_list(shared_ptr<hitable> object){add(object);}
	//parameterized constructor
	
	void clear() {objects.clear();}
	void add(std::shared_ptr<hitable> object){
	    objects.push_back(object);
	}

	virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const;
	//overriding hit from hitable
	
};


bool hitable_list::hit(const ray &r, interval ray_t, hit_record &rec) 
    const {
	
	hit_record temp_rec;
	//tmp to hold hit data from each obj
	bool hit_anything = false;
	// a hit/not hit flag
	double closest_so_far = ray_t.max;
	
	for (const auto &object : objects){
	    //looping through all the objects in the list
	    if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)){
		//if it is hit, adjust variables
		hit_anything = true;
		closest_so_far = temp_rec.t;
		rec = temp_rec;
	    }
	}
	return hit_anything;
    }//a brute force checking everything method

#endif

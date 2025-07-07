#ifndef  HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class hitable_list: public hitable {
    //inherits from hitable
    public:
	
	hitable_list() {}
	//default constructor
	hitable_list(hitable **l, int n){list = l, list_size = n;}
	//parameterized constructor
	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;
	//overriding hit from hitable
	
	hitable **list;
	//ptr to an array of ptrs of hitable objs
	int list_size;
	//way to index the size
};


bool hitable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) 
    const {
	
	hit_record temp_rec;
	//tmp to hold hit data from each obj
	bool hit_anything = false;
	// a hit/not hit flag
	double closest_so_far = t_max;
	
	for (int i = 0; i < list_size; i++){
	    //looping through all the objects in the list
	    if (list[i]->hit(r, t_min, closest_so_far, temp_rec)){
		//if it is hit, adjust variables
		hit_anything = true;
		closest_so_far = temp_rec.t;
		rec = temp_rec;
	    }
	}
	return hit_anything;
    }//a brute force checking everything method

#endif

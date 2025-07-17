#ifndef MATERIAL_H
#define MATERIAL_H

#include "hitable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(
	    const ray &r_in, const hit_record &rec, color &attentuation, ray &scatter) const {
	return false;
    }


#endif

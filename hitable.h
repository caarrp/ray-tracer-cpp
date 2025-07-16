#ifndef HITABLE_H
#define HITABLE_H


class hit_record {
public:
    //stores details of ray/obj intersection
    double t;
    //distance along ray where hit occurs
    vec3 p;
    //position in space where ray hits obj
    vec3 normal;
    //important for shading/lighting calcs
    bool front_face;

    void set_face_n(const ray &r, const vec3 &out_n){
	//out_n assumed unit. this sets normal vector
	front_face = dot(r.direction(), out_n) < 0;
	normal = front_face ? out_n : -out_n;
	//the front face is assigned to the outward normal given front_face
    }
};

class hitable {
    //abstract base class of objs that can be "hit"
    public:
	virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
	//virtual allows other class to override
};

#endif

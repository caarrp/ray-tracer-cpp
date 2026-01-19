#include <cmath>
#include <iostream>
#include "extra.h"

#ifndef VEC3_H
#define VEC3_H


class vec3 {

public:
    double e[3];

    vec3() : e{0, 0, 0}{} 

    vec3(double x, double y, double z)
    {e[0] = x; e[1] = y; e[2] = z;}
    
    double x() const { return e[0]; }
    
    double y() const { return e[1]; }
    
    double z() const { return e[2]; }

    void print(std::ostream &os = std::cerr) const{
	os << "< " << e[0] << ", " << e[1] << ", " << e[2] << ">" << std::endl;}


    //const vec& operator+() const { return *this; } 
    vec3 operator-() const { 
	return vec3(-e[0], -e[1], -e[2]); 
	}
    
    double operator[](int i) const {
	return e[i];
	}

    double operator[](int i) {
	return e[i];
	}

    vec3& operator+=(const vec3& v){
	//like a shifting operation
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
	}

    vec3& operator*=(double s){
	//like scalar operation
	e[0] *= s;
	e[1] *= s;
	e[2] += s;
	return *this;
	}

    vec3& operator/=(double t){
	//already using operator above wow
	return *this *= 1/t;
	}

    double length_squared() const{
	return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
	}

    double length() const{
	double len = sqrt(length_squared());
	return len;
	}	

    bool near_zero() const{
	double n = 1e-8;
	return (std::fabs(e[0] < n)) && (std::fabs(e[1] < n)) && (std::fabs(e[2] < n));
	}
    	
    static vec3 random(){
	return vec3(random_double(), random_double(), random_double());
	}		

    static vec3 random(double low, double high){
	return vec3(random_double(low, high), random_double(low, high), random_double(low, high));
	}
};

//vector utility functions
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << "<" << v.x() << ", " << v.y() << ", " << v.z() << ">";
}

inline vec3 operator+(const vec3 &u, const vec3 &v){
    return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v){
    return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v){
    return vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

inline vec3 operator*(const vec3 &u, double s){
    return vec3(u.e[0]*s, u.e[1]*s, u.e[2]*s);
}

inline vec3 operator*(double s, const vec3 &v){
    return vec3(s*v.e[0], s*v.e[1], s*v.e[2]);
}

inline vec3 operator/(const vec3 &u, double t){
    return u * (1/t);
}

inline double dot(const vec3 &u, const vec3 &v){
    return (u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2]);
}

inline vec3 cross(const vec3 &u, const vec3 &v){
    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1],
	        -(u.e[0]*v.e[2] - u.e[2]*v.e[0]),
		u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

inline vec3 unit(const vec3 &u){
    double len = u.length();
    return u/len;
}

inline vec3 random_in_unit_disk() {
    while (true) {
	auto m = vec3(random_double(-1, 1), random_double(-1, 1), 0);
	if (m.length_squared() < 1){
	    return m;
	}
    }
}

inline vec3 random_unit(){
    while (true) {
	auto m = vec3::random(-1, 1);
	auto len_sq = m.length_squared();
	if (1e-160 < len_sq && len_sq <= 1.0){
	    return m / sqrt(len_sq);
	}
    }
}

inline vec3 random_on_hemisphere(const vec3 &normal){
	vec3 on_unit_sphere = random_unit();
	if (dot(on_unit_sphere, normal) > 0.0){
	    return on_unit_sphere;
	    }
	else{
	    return -on_unit_sphere;
	    }
}

inline vec3 reflect(const vec3 &u, const vec3 &n){
    return u - 2*dot( u, n)*n;
}
inline vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat){
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_tangent = etai_over_etat * (uv + cos_theta*n);
    vec3 r_parallel = -std::sqrt(std::fabs(1.0 - r_tangent.length_squared()))*n;
    return r_tangent + r_parallel;
}

#endif



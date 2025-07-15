#ifndef EXTRA_H
#define EXTRA_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();


const double pi = 3.141592635897932385;

inline double random_double(){
    return std::rand() / (RAND_MAX + 1.0);
    }

inline double random_double(double min, double max){
    //random real number in [min, max)
    return min + (max-min)*random_double();
    }
inline double degrees_to_radians(double degrees){
    return degrees * pi / 180.0;
    }
#include "ray.h"
#include "vec3.h"


#endif

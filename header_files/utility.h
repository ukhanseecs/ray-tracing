#ifndef UTILITY_H
#define UTILITY_H

#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <random>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    static std::uniform_real_distribution<double> distribution(0.0, 1.0); // Random double between 0 and 1
    static std::mt19937 generator; // Mersenne Twister pseudo-random generator
    return distribution(generator); // Return random double
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return int(random_double(min, max + 1));
}
#include "ray.h"
#include "vec3.h"
#include "color.h"

#endif
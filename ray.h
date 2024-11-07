#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        const Vector3D& origin;
        const Vector3D& direction;

        Ray(const Vector3D& orig, const Vector3D& dir) : origin(orig),direction(dir) {}

        Vector3D point_at_t(double t){
            return origin+(t*direction);
        }
};

#endif
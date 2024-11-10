#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    private:
        Vector3D origin;
        Vector3D direction;
    public:
        Ray() {}

        Ray(const Vector3D& origin, const Vector3D& direction) : origin(origin),direction(direction) {}

        Vector3D point_at_t(double t){
            return origin + (t * direction);
        }

        const Vector3D& getorigin() const { return origin; }
        const Vector3D getdirection() const { return direction; }

};

#endif
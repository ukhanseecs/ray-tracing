#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/**
 * @brief Class representing a ray in 3D space
 * A ray is defined by an origin point and a direction vector
 */
class Ray {
    private:
        Vector3D origin;    // Starting point of the ray
        Vector3D direction; // Direction vector of the ray
        double tm;      
    public:
        // Default constructor
        Ray() : origin(Vector3D(0, 0, 0)), direction(Vector3D(0, 0, 0)) {}

        Ray(const Vector3D& origin, const Vector3D& direction, double time) 
            : origin(origin), direction(direction), tm(time) {}

            
        Ray(const Vector3D& origin, const Vector3D& direction) 
        : Ray(origin, direction, 0) {}

        /**
         * @brief Calculate a point along the ray at parameter t
         * @param t Parameter determining the distance along the ray
         * @return Point at position origin + t*direction
         */
        Vector3D point_at_t(double t) const {
            return origin + (t * direction);
        }

        // Getter methods
        const Vector3D& getOrigin() const { return origin; }
        const Vector3D getDirection() const { return direction; }

        double time() const { return tm;}

};

#endif
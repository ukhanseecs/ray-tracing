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
    public:
        // Default constructor
        Ray() {}

        /**
         * @brief Construct a ray with given origin and direction
         * @param origin Starting point of the ray
         * @param direction Direction vector of the ray
         */
        Ray(const Vector3D& origin, const Vector3D& direction) : origin(origin),direction(direction) {}

        /**
         * @brief Calculate a point along the ray at parameter t
         * @param t Parameter determining the distance along the ray
         * @return Point at position origin + t*direction
         */
        Vector3D point_at_t(double t) const {
            return origin + (t * direction);
        }

        // Getter methods
        const Vector3D& getorigin() const { return origin; }
        const Vector3D getdirection() const { return direction; }

};

#endif
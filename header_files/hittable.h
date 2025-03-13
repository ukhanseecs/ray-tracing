#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// Class to store information about a ray-object intersection
class hit_record {
    public:
        Vector3D p;      // Point of intersection
        Vector3D normal; // Surface normal at intersection point
        double t;        // Parameter t along the ray where intersection occurs
        bool front_face; // True if ray intersects front face of object
};

// Abstract base class for all hittable objects in the scene
class hittable {
    public :
        // Virtual destructor for proper cleanup of derived classes
        virtual ~hittable() = default;

        // Pure virtual function that determines if a ray hits the object
        // Parameters:
        //   r: The ray to test for intersection
        //   t_min: Minimum acceptable t value for intersection
        //   t_max: Maximum acceptable t value for intersection
        //   rec: Record to store intersection information
        // Returns: true if ray intersects the object, false otherwise
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif

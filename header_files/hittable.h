#ifndef HITTABLE_H
#define HITTABLE_H

#include "utility.h"
#include "interval.h"

class material;

// Class to store information about a ray-object intersection
class hit_record {
    public:
        Vector3D p;      // Point of intersection
        Vector3D normal; // Surface normal at intersection point
        double t;        // Parameter t along the ray where intersection occurs
        shared_ptr<material> mat; // Pointer to the material of the object
        bool front_face; // True if ray intersects front face of object
        // Set the normal and front_face values based on the ray and outward normal
        void set_face_normal(const Ray& r, const Vector3D& outward_normal) {
            front_face = dot(r.getDirection(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

// Abstract base class for all hittable objects in the scene
class hittable {
    public :
        // Virtual destructor for proper cleanup of derived classes
        virtual ~hittable() = default;

        // Pure virtual function that determines if a ray hits the object
        // Parameters:
        //   r: The ray to test for intersection
        //   ray_t: Interval of valid t values for the ray
        //   rec: Record to store intersection information
        // Returns: true if ray intersects the object, false otherwise
        virtual bool hit(const Ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif

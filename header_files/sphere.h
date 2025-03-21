#ifndef SPHERE_H
#define SPHERE_H

#include "utility.h"
#include "hittable.h"

// Sphere class that inherits from hittable, represents a 3D sphere object
class sphere : public hittable {
    private:
        Vector3D center;    // Center point of the sphere
        double radius;      // Radius of the sphere
    public:
        // Constructor: initializes sphere with center point and radius
        sphere(const Vector3D& cen, double r) : center(cen), radius(r) {}

        // Determines if a ray intersects with the sphere
        // Parameters:
        //   r: The ray to test intersection with
        //   t_min: Minimum acceptable intersection distance
        //   t_max: Maximum acceptable intersection distance
        //   rec: Record to store intersection information
        bool hit(const Ray& r, interval ray_t, hit_record& rec) const override{
            // Vector from ray origin to sphere center
            Vector3D oc = center - r.getOrigin();
            
            // Calculate quadratic equation coefficients
            auto a = r.getDirection().length_squared();
            auto h = dot(oc, r.getDirection());
            auto c = oc.length_squared() - radius * radius;
            
            // Calculate discriminant to determine if ray hits sphere
            auto discriminant = h * h - a * c;

            // If discriminant is negative, ray misses sphere
            if (discriminant < 0){
                return false;
            }
            
            auto sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range
            // Try first intersection point
            auto root = (h - sqrtd) / a;
            if (!ray_t.contains(root)) {
                // If first intersection is not in range, try second intersection
                root = (h + sqrtd) / a;
                // If both intersections are out of range, return false
                if (!ray_t.contains(root)) {
                    return false;
                }
            }

            // Record the intersection details
            rec.t = root;                       // Record intersection distance
            rec.p = r.point_at_t(rec.t);       // Calculate intersection point
            Vector3D normal = (rec.p - center) / radius; // Calculate normal
            rec.set_face_normal(r, normal); // Set front face normal

            return true;
        }
};

#endif
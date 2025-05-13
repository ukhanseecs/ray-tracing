#ifndef SPHERE_H
#define SPHERE_H

#include "utility.h"
#include "hittable.h"

// Sphere class that inherits from hittable, represents a 3D sphere object
class sphere : public hittable {
    private:
        Ray center;
        // Vector3D center;    // Center point of the sphere
        double radius;      // Radius of the sphere
        shared_ptr<material> mat; // Material of the sphere
        aabb bbox;   // 
    public:
        // Constructor: initializes sphere with center point, radius, and material
        sphere(const Vector3D& static_center, double r, shared_ptr<material> mat) 
            : center(static_center, Vector3D(0,0,0)), radius(std::fmax(0,r)), mat(mat)
            {
                auto rvec = Vector3D(radius, radius, radius);
                bbox = aabb(static_center - rvec, static_center + rvec);
            }


        sphere(const Vector3D& center1, const Vector3D& center2, double radius,
            shared_ptr<material> mat)
            : center(center1, center2- center1), radius (std::fmax(0, radius)), mat(mat) {} 
        aabb bounding_box() const override { return bbox; }


        //=============================
        // Determines if a ray intersects with the sphere
        //==============================

        bool hit(const Ray& r, interval ray_t, hit_record& rec) const override{
            // Vector from ray origin to sphere center
            Vector3D current_center = center.at(r.time());
            Vector3D oc = current_center - r.getOrigin();
            
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
            Vector3D outward_normal = (rec.p - current_center) / radius; // Calculate normal
            rec.set_face_normal(r, normal); // Set front face normal
            rec.mat = mat; // Set material pointer

            return true;
        }
};

#endif
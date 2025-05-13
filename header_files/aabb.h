#ifndef AABB_H
#define AABB_H
#include "interval.h"

class aabb {
    public:
        interval x, y, z; 

        aabb() {}

        aabb(const interval& x, const interval& y, const interval& z) 
            : x(x), y(y), z(z) {} // Constructor


        // Constructor to create an AABB from two points 
        aabb(const Vector3D& a, const Vector3D& b) {
            x = (a[0] <= b[0]) ? interval (a[0], b[0]) : interval(b[0], a[0]);
            y = (a[1] <= b[1]) ? interval (a[1], b[1]) : interval(b[1], a[1]);
            z = (a[2] <= b[2]) ? interval (a[2], b[2]) : interval(b[2], a[2]);
        }


        
        const interval& axis_interval(int n) const{ // Get the interval for the specified axis
            if (n == 1) return y;
            if (n == 2) return z;
            return x;
        }

        bool hit (const Ray& r, interval ray_t) const {
            const Vector3D& ray_orig = r.getOrigin();
            const Vector3D& ray_dir = r.getDirection();

            for (int axis= 0; axis < 3; axis ++) {
                const interval& ax = axis_interval(axis);
                const double adinv = 1.0 / ray_dir[axis];

                auto t0 = (ax.min - ray_orig[axis]) * adinv;
                auto t1 = (ax.max - ray_orig[axis]) * adinv;

                if (t0 < t1) {
                    if (t0 > ray_t.min) ray_t.min = t0;
                    if (t1 < ray_t.max) ray_t.max = t1;
                } else {
                    if (t1 > ray_t.min) ray_t.min = t1;
                    if (t0 < ray_t.max) ray_t.max = t0;
                }

                if (ray_t.max <= ray_t.min) return false; // No hit
            }
            return true; // Hit
        }
};

#endif
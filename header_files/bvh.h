#ifndef BVH_H
#define BVH_H

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"

class bvh_node : public hittable {
    private:
        shared_ptr<hittable> left; // Pointer to the left child node
        shared_ptr<hittable> right; // Pointer to the right child node
        aabb box; // Axis-aligned bounding box for the node
    public:
        // Constructor for building BVH from a list of hittable objects     
        bvh_node(HittableList list) : bvh_node(list.m_objects, 0, list.m_objects.size()) {} 

        bvh_node(std::vector<shared_ptr<hittable>>& objects, size_t start, size_t end) {
            if (!bbox.hit(r, ray_t)){
                return false;
            }

            bool hit_left = left->hit(r, ray_t, rec);
            bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

            return hit_left || hit_right;
        }

        aabb bounding_box() const override { return box; } // Get the bounding box of the node
}

#endif 
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
            int axis = random_int(0, 2); // Randomly choose an axis (0, 1, or 2)

            auto comparator = (axis == 0) ? box_x_compare
                              : (axis == 1) ? box_y_compare
                                            : box_z_compare;
            
            size_t object_span = end- start;

            if (object_span == 1){
                left = right = objects[start];
            } else if (object_span == 2) {
                left = objects[start];
                right = objects[start+1];
            } else {
                std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

                auto mid = start + object_span / 2;
                left = make_shared<bvh_node>(objects, start, mid); // Recursively build left child
                right = make_shared<bvh_node>(objects, mid, end); // Recursively build right child
            }

            bbox = aabb(left->bounding_box(), right->bounding_box()); // Combine bounding boxes of children
        }

        bool hit(const Ray& r, interval ray_t, hit_record& rec) const override {
            if (!bbox.hit(r, ray_t)){
                return false;
            }

            bool hit_left = left->hit(r, ray_t, rec); // Check if left child hit
            // If left child hit, check right child with updated ray_t
            bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

            return hit_left || hit_right; // Return true if either child hit
        }

        aabb bounding_box() const override { return box; } // Get the bounding box of the node
}

#endif 
#ifndef BVH_H
#define BVH_H

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"

#include <algorithm>

class bvh_node : public hittable {
    private:
        shared_ptr<hittable> left; // Pointer to the left child node
        shared_ptr<hittable> right; // Pointer to the right child node
        aabb bbox; // Axis-aligned bounding box for the node

        static bool box_compare(
            const shared_ptr<hittable>& a, const shared_ptr<hittable>& b, int axis) {
                auto a_axis_interval = a->bounding_box().axis_interval(axis);
                auto b_axis_interval = b->bounding_box().axis_interval(axis);
                return a_axis_interval.min < b_axis_interval.min;
            }

        static bool box_x_compare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) {
            return box_compare(a, b, 0);
        }

        static bool box_y_compare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) {
            return box_compare(a, b, 1);
        }

        static bool box_z_compare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) {
            return box_compare(a, b, 2);
        }


    public:
        // Changed to use const reference in both constructors
        bvh_node(const HittableList& list) : bvh_node(list.m_objects, 0, list.m_objects.size()) {}

        bvh_node(const std::vector<shared_ptr<hittable>>& src_objects, size_t start, size_t end) {
            // Make a modifiable copy of the objects for sorting
            auto objects = std::vector<shared_ptr<hittable>>(src_objects.begin() + start, src_objects.begin() + end);
            
            int axis = random_int(0, 2); // Randomly choose an axis (0, 1, or 2)

            auto comparator = (axis == 0) ? box_x_compare
                             :(axis == 1) ? box_y_compare
                                          : box_z_compare;
            
            size_t object_span = objects.size();

            if (object_span == 1){
                left = right = objects[0];
            } else if (object_span == 2) {
                if (comparator(objects[0], objects[1])) {
                    left = objects[0];
                    right = objects[1];
                } else {
                    left = objects[1];
                    right = objects[0];
                }
            } else {
                std::sort(objects.begin(), objects.end(), comparator);

                auto mid = object_span / 2;
                left = make_shared<bvh_node>(objects, 0, mid); 
                right = make_shared<bvh_node>(objects, mid, object_span);
            }

            bbox = aabb(left->bounding_box(), right->bounding_box());
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

        aabb bounding_box() const override { return bbox; } // Get the bounding box of the node
};

#endif
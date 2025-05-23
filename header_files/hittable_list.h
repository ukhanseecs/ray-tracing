#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "utility.h"
#include "hittable.h"
#include "interval.h"
#include "aabb.h"

#include <vector> // for vector

using std::make_shared;
using std::shared_ptr;

// Class to store a list of hittable objects
class HittableList : public hittable { 
    private:
        aabb bbox; // Axis-aligned bounding box for the list of objects
    public:
        std::vector<shared_ptr<hittable>> m_objects; // List of hittable objects

        HittableList() {} 
        HittableList(shared_ptr<hittable> object) { add(object); } 

        void clear() { m_objects.clear(); } // Clear the list of objects

        void add(shared_ptr<hittable> object) { 
            m_objects.push_back(object);  // Add an object to the list
            bbox = aabb(bbox, object->bounding_box()); // Update bounding box
        } 

        // Determine if a ray intersects any object in the list and store the intersection information
        // Parameters:
        //   r: The ray to test for intersection
        //   t_min: Minimum acceptable t value for intersection
        //   t_max: Maximum acceptable t value for intersection
        //   rec: Record to store intersection information
        // Returns: true if ray intersects any object in the list, false otherwise

        bool hit(const Ray& r, interval ray_t, hit_record& rec) const override{
            hit_record temp_rec; // Temporary record to store intersection information
            bool hit_anything = false; // Initialize hit flag to false
            auto closest_so_far = ray_t.max; // Initialize closest intersection distance to maximum value

            for (const auto& object: m_objects){ // Loop through all objects in the list
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)){ // If the ray intersects the object
                    hit_anything = true; // Set hit flag to true
                    closest_so_far = temp_rec.t; // Update closest intersection distance
                    rec = temp_rec; // Update intersection record
                }
            }

            return hit_anything; // Return hit flag
        } 


        aabb bounding_box() const override { return bbox; } // Get the bounding box of the list

};

#endif

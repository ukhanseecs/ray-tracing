#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.h"

#include <memory> // for shared_ptr and make_shared
#include <vector> // for vector

using std::make_shared;
using std::shared_ptr;

// Class to store a list of hittable objects
class hittable_list : public hittable { 
    public:
        std::vector<shared_ptr<hittable>> objects; // List of hittable objects

        hittable_list() {} 
        hittable_list(shared_ptr<hittable> object) { add(object); } 

        void clear() { objects.clear(); } // Clear the list of objects

        void add(shared_ptr<hittable> object) { objects.push_back(object); } // Add an object to the list

        // Determine if a ray intersects any object in the list and store the intersection information
        // Parameters:
        //   r: The ray to test for intersection
        //   t_min: Minimum acceptable t value for intersection
        //   t_max: Maximum acceptable t value for intersection
        //   rec: Record to store intersection information
        // Returns: true if ray intersects any object in the list, false otherwise

        bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override{
            hit_record temp_rec; // Temporary record to store intersection information
            bool hit_anything = false; // Initialize hit flag to false
            auto closest_so_far = t_max; // Initialize closest intersection distance to maximum value

            for (const auto& object: objects){ // Loop through all objects in the list
                if (object->hit(r, t_min, closest_so_far, temp_rec)){ // If the ray intersects the object
                    hit_anything = true; // Set hit flag to true
                    closest_so_far = temp_rec.t; // Update closest intersection distance
                    rec = temp_rec; // Update intersection record
                }
            }

            return hit_anything; // Return hit flag
        } 
};

#endif

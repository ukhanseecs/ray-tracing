#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "utility.h"
/*The camera class will be responsible for two important jobs:
Construct and dispatch rays into the world.
Use the results of these rays to construct the rendered image. */

class camera {
    private:
        int image_height;
        Vector3D center;
        Vector3D pixel00_loc;
        Vector3D delta_u;
        Vector3D delta_v;

        void initialize() {
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = Vector3D(0, 0, 0);

            //Set Up the Camera Parameters
            double viewport_height = 2.0;
            double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
            double focal_length = 1.0;
                    
            //Calculate Viewport Boundaries
            Vector3D viewport_u(viewport_width, 0, 0);
            Vector3D viewport_v(0, -viewport_height, 0);

                        
            //Determine Pixel Delta Values
            this->delta_u = viewport_u / image_width;
            this->delta_v = viewport_v / image_height;


            //Calculate Upper-Left Corner of the Viewport
            Vector3D viewport_upper_left = center - Vector3D(0, 0, focal_length) - Vector3D(viewport_width/2, 0, 0) - Vector3D(0, viewport_height/2, 0);
            this->pixel00_loc = viewport_upper_left + 0.5 * (delta_u + delta_v);

        }

        color ray_color(const Ray& r, const hittable& list) const{
            hit_record rec; // Record to store intersection information

            if (list.hit(r, interval(0, infinity), rec)) { // If the ray hits an object
                // Calculate the color based on the normal at the hit point
                color normal_color = rec.normal + color(1, 1, 1); 
                return 0.5 * normal_color; // Return normal map color 

                // return color(1,0,0); // Return red color
            }

            Vector3D unit_direction = unit_vec(r.getDirection()); // Get unit direction vector
            auto blend_factor = 0.5 * (unit_direction.gety() + 1.0); // Scale y component to [0,1]
            return (1.0 - blend_factor) * color(1.0, 1.0, 1.0) + blend_factor * color(0.5, 0.7, 1.0); // Linearly blend white and blue color
        }


    public:
        double aspect_ratio = 16.0 / 9.0;
        int image_width = 400;

        void render(const hittable& list){
            initialize();

            // Render
            cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                for (int i = 0; i < image_width; i++) {
                    Vector3D pixel_center = pixel00_loc + (i * delta_u) + (j * delta_v);
                    Vector3D ray_direction = unit_vec(pixel_center - center);
                    Ray r(center, ray_direction);

                    color pixel_color = ray_color(r, list);
                    write_color(cout, pixel_color);
                }
            }
            clog << "\rDone.\n";
        }
};


#endif

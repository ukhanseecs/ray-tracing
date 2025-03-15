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
        double pixel_samples_scale; // color scale for pixel samples

        void initialize(int samples_per_pixel) {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;
            pixel_samples_scale = 1.0 / samples_per_pixel;
    
            center = Vector3D(0, 0, 0);
    
            // Determine viewport dimensions.
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);
    
            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = Vector3D(viewport_width, 0, 0);
            auto viewport_v = Vector3D(0, -viewport_height, 0);
    
            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            delta_u = viewport_u / image_width;
            delta_v = viewport_v / image_height;
    
            // Calculate the location of the upper left pixel.
            auto viewport_upper_left =
                center - Vector3D(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (delta_u + delta_v);

        }


        // Function to get the ray for a given pixel
        Ray get_ray(int i, int j) const {
            auto offset = sample_square();  // Get a random vector in the square [-0.5, 0.5] x [-0.5, 0.5].

            auto pixel_smaple = pixel00_loc + 
                                (i + offset.getx()) * delta_u + 
                                (j + offset.gety()) * delta_v;  // Calculate the location of the pixel

            auto ray_origin = center;                       // Camera is at the center
            auto ray_direction = pixel_smaple - ray_origin; // Calculate the direction of the ray

            return Ray(ray_origin, ray_direction);
        }

        // Function to return a random vector in the square [-0.5, 0.5] x [-0.5, 0.5].
        // This is used to sample the pixel area for antialiasing.
        Vector3D sample_square() const{
            // Return a random vector in the square [-0.5, 0.5] x [-0.5, 0.5].
            return Vector3D(random_double()-0.5, random_double()-0.5, 0); 
        }

        color ray_color(const Ray& r, const hittable& list) const{
            hit_record rec; // Record to store intersection information

            if (list.hit(r, interval(0.001, infinity), rec)) { // If the ray hits an object
                // Calculate the color based on the normal at the hit point
                return 0.5 * (rec.normal + color(1, 1, 1)); // Return normal map color 
            }

            Vector3D unit_direction = unit_vec(r.getDirection()); // Get unit direction vector
            auto blend_factor = 0.5 * (unit_direction.gety() + 1.0); // Scale y component to [0,1]
            return (1.0 - blend_factor) * color(1.0, 1.0, 1.0) + blend_factor * color(0.5, 0.7, 1.0); // Linearly blend white and blue color
        }


    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        

        void render(const hittable& list, int samples_per_pixel){
            initialize(samples_per_pixel);

            // Render
            cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0, 0, 0);
                    for (int sample =0 ; sample < samples_per_pixel; sample ++){
                        Ray r = get_ray(i, j);
                        pixel_color += ray_color(r, list);
                    }
                    write_color(cout, pixel_samples_scale * pixel_color);
                }
            }
            clog << "\rDone.\n";
        }
};


#endif

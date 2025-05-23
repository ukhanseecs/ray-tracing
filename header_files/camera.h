#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "hittable.h"
#include "utility.h"
#include "vec3.h"
#include "material.h"

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
        Vector3D u, v, w; // camera frame basis vectors
        Vector3D defocus_disk_u;
        Vector3D defocus_disk_v;
        double pixel_samples_scale; // color scale for pixel samples
        



        //============================
        // Function to initialize the camera
        //============================

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;
            pixel_samples_scale = 1.0 / samples_per_pixel;
    
            center = lookfrom;
    
            // Determine viewport dimensions.
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta / 2);
            auto viewport_height = 2 *h* focus_dist;
            auto viewport_width = viewport_height * (double(image_width)/image_height);
    

            // Calculate the camera frame basis vectors.
            w = unit_vec(lookfrom - lookat); // w is the direction from camera to viewport
            u = unit_vec(cross(vup, w)); // u is the right direction
            v = cross(w, u); // v is the up direction

            
            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            // auto viewport_u = Vector3D(viewport_width, 0, 0);
            // auto viewport_v = Vector3D(0, -viewport_height, 0);
            auto viewport_u = viewport_width * u; // width of the viewport in world space
            auto viewport_v = viewport_height * v; // height of the viewport in world space


            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            delta_u = viewport_u / image_width;
            delta_v = viewport_v / image_height;
    
            // Calculate the location of the upper left pixel.
            // auto viewport_upper_left =
            //     center - Vector3D(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            auto viewport_upper_left = center - w * focus_dist - 0.5 * (viewport_u + viewport_v);
            pixel00_loc = viewport_upper_left + 0.5 * (delta_u + delta_v);


            auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle) / 2);
            defocus_disk_u = defocus_radius * u; // radius of the defocus disk in world space
            defocus_disk_v = defocus_radius * v; // radius of the defocus disk in world space

        }


        //============================
        // function to get a ray from the camera
        //============================


        Ray get_ray(int i, int j) const {
            auto offset = sample_square();  // Get a random vector in the square [-0.5, 0.5] x [-0.5, 0.5].

            auto pixel_sample = pixel00_loc + 
                                (i + offset.getx()) * delta_u + 
                                (j + offset.gety()) * delta_v;  // Calculate the location of the pixel

            auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();  // Camera is at the center
            auto ray_direction = pixel_sample - ray_origin; // Calculate the direction of the ray
            auto ray_time = random_double();

            return Ray(ray_origin, ray_direction, ray_time);
        }



        //============================
        // Function to return a random vector in the square [-0.5, 0.5] x [-0.5, 0.5].
        // This is used to sample the pixel area for antialiasing.
        //============================



        Vector3D sample_square() const{
            // Return a random vector in the square [-0.5, 0.5] x [-0.5, 0.5].
            return Vector3D(random_double()-0.5, random_double()-0.5, 0); 
        }


        //============================
        // Function to return a random point in the defocus disk
        //============================

        Vector3D defocus_disk_sample() const{
            // Return a random point in the defocus disk
            auto p = random_in_unit_disk();
            return center + (p[0]*defocus_disk_u) + (p[1]*defocus_disk_v); // Calculate the point in the disk
        }


        //============================
        // Function to return the color of the ray
        //=============================


        color ray_color(const Ray& r, int depth, const hittable& list) const{
            hit_record rec; // Record to store intersection information

            if (list.hit(r, interval(0.001, infinity), rec)) { // If the ray hits an object
                if (depth <= 0) { // If the ray has exceeded the bounce limit, no more light is gathered.
                    return color(0,0,0);
                }

                Ray scattered; // Ray to store the scattered ray
                color attenuation; // Color to store the attenuation
                if (rec.mat->scatter(r, rec, attenuation, scattered)) { // If the material scatters the ray
                    return attenuation * ray_color(scattered, depth - 1, list); // Return the color of the scattered ray
                return color(0,0,0); // If the material does not scatter, return black
                }


                // Calculate the color based on the normal at the hit point
                Vector3D direction = rec.normal  + random_unit_vector(); // Get random direction on hemisphere

                // this 0.5 factor is use   d to scale the color to [0,1]
                return 0.5 * ray_color(Ray(rec.p, direction), depth - 1, list); // Return normal map color 
            }

            Vector3D unit_direction = unit_vec(r.getDirection()); // Get unit direction vector
            auto blend_factor = 0.5 * (unit_direction.gety() + 1.0); // Scale y component to [0,1]
            return (1.0 - blend_factor) * color(1.0, 1.0, 1.0) + blend_factor * color(0.5, 0.7, 1.0); // Linearly blend white and blue color
        }


    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel; // number of samples per pixel
        int max_depth = 10;

        double vfov = 90; // Vertical field of view in degrees
        Vector3D lookfrom = Vector3D(0, 0, 0); // Camera position
        Vector3D lookat = Vector3D(0, 0, -1); // Point to look at
        Vector3D vup = Vector3D(0, 1, 0); // Up vector for the camera

        double defocus_angle = 0.0; // Defocus angle for depth of field
        double focus_dist = 10; // Focus distance for depth of field
        

        void render(const hittable& list, int samples_per_pixel){
            initialize();

            // Render
            cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0, 0, 0);
                    for (int sample =0 ; sample < samples_per_pixel; sample ++){
                        Ray r = get_ray(i, j);
                        pixel_color += ray_color(r,max_depth, list);
                    }
                    write_color(cout, pixel_samples_scale * pixel_color);
                }
            }
            clog << "\rDone.\n";
        }
};


#endif

using namespace std;

#include "header_files/utility.h"
#include "header_files/sphere.h"
#include "header_files/hittable.h"
#include "header_files/hittable_list.h"
#include "header_files/interval.h"
#include "header_files/camera.h"  
#include "header_files/material.h"

#include <chrono>


int main() {
    // Scene setup
    HittableList list; //list of hittable objects

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    list.add(make_shared<sphere>(Vector3D(0,-1000,0), 1000, ground_material));

    for (int a= -11; a < 11; a++){
        for (int b= -11; b < 11; b++){
            auto choose_mat = random_double();
            Vector3D center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Vector3D(4, 0.2, 0)).length() > 0.9){
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8){
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    list.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    //metal 
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    list.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    list.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    list.add(make_shared<sphere>(Vector3D(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    list.add(make_shared<sphere>(Vector3D(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    list.add(make_shared<sphere>(Vector3D(4, 1, 0), 1.0, material3));

    // // Materials
    // auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    // auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5)); 
    // // auto material_left =  make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    // auto material_left = make_shared<dielectric>(1.50);
    // auto material_bubble = make_shared<dielectric>(1.00/ 1.50);
    // auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    // //Spheres
    // list.add(make_shared<sphere>(Vector3D(0,-100.5, -1), 100, material_ground)); // Ground sphere
    // list.add(make_shared<sphere>(Vector3D(0,0, -1.2), 0.5, material_center));  // Main sphere
    // // additional spheres
    // list.add(make_shared<sphere>(Vector3D(1,0, -1), 0.5, material_right));  // Right sphere
    // list.add(make_shared<sphere>(Vector3D(-1,0, -1), 0.5, material_left)); // Left sphere
    // list.add(make_shared<sphere>(Vector3D(-1,0, -1), 0.4, material_bubble)); // Bubble sphere


    // // auto R = cos(pi/4);

    // // auto material_left = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    // // auto material_right = make_shared<lambertian>(color(0.8, 0.6, 0.2));

    // // list.add(make_shared<sphere>(Vector3D(-R, 0, -1), R, material_left));
    // // list.add(make_shared<sphere>(Vector3D(R, 0, -1), R, material_right));




    camera cam;

    cam.aspect_ratio = 16.0 / 9.0; // Aspect ratio of the image
    cam.image_width = 1200;
    cam.samples_per_pixel = 500; // Number of samples per pixel
    cam.max_depth = 50; // Maximum recursion depth for ray tracing

    cam.vfov= 20;
    cam.lookfrom = Vector3D(13, 2, 3); // Camera position
    cam.lookat = Vector3D(0, 0, 0); // Point to look at
    cam.vup = Vector3D(0, -1, 0); // Up vector for the camera

    cam.defocus_angle = 0.6; // Defocus angle for depth of field
    cam.focus_dist = 10.0; // Focus distance for depth of field

    // cam.aspect_ratio = 16.0/9.0;
    // cam.image_width = 400;
    // cam.max_depth = 50;
    // cam.vfov = 90.0;    // decrease to zoom in

    // // lookfrom
    // // - or + x, 2, 1 to flip horizontally
    // cam.lookfrom = Vector3D(2,2,1);
    // cam.lookat   = Vector3D(0,0,-1);

    // // vup
    // // 0,-1,0 for camera looking down
    // cam.vup      = Vector3D(0,-1,0);

    // cam.defocus_angle = 10.0;
    // cam.focus_dist = 3.4;

    auto start = std::chrono::high_resolution_clock::now(); // Start time measurement
    cam.render(list, 100);
    auto end = std::chrono::high_resolution_clock::now(); // End time measurement
    std::chrono::duration<double> elapsed = end - start; // Calculate elapsed time
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n"; // Print elapsed time
}

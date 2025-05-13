using namespace std;

#include "header_files/utility.h"
#include "header_files/sphere.h"
#include "header_files/hittable.h"
#include "header_files/hittable_list.h"
#include "header_files/interval.h"
#include "header_files/camera.h"  
#include "header_files/material.h"


int main() {
    // Scene setup
    HittableList list; //list of hittable objects

    // Materials
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5)); 
    // auto material_left =  make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_left = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00/ 1.50);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    //Spheres
    list.add(make_shared<sphere>(Vector3D(0,-100.5, -1), 100, material_ground)); // Ground sphere
    list.add(make_shared<sphere>(Vector3D(0,0, -1.2), 0.5, material_center));  // Main sphere
    // additional spheres
    list.add(make_shared<sphere>(Vector3D(1,0, -1), 0.5, material_right));  // Right sphere
    list.add(make_shared<sphere>(Vector3D(-1,0, -1), 0.5, material_left)); // Left sphere
    list.add(make_shared<sphere>(Vector3D(-1,0, -1), 0.4, material_bubble)); // Bubble sphere


    // auto R = cos(pi/4);

    // auto material_left = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    // auto material_right = make_shared<lambertian>(color(0.8, 0.6, 0.2));

    // list.add(make_shared<sphere>(Vector3D(-R, 0, -1), R, material_left));
    // list.add(make_shared<sphere>(Vector3D(R, 0, -1), R, material_right));




    camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.max_depth = 50;
    cam.vfov = 90.0;    // decrease to zoom in

    // lookfrom
    // - or + x, 2, 1 to flip horizontally
    cam.lookfrom = Vector3D(-2,2,1);
    cam.lookat   = Vector3D(0,0,-1);

    // vup
    // 0,-1,0 for camera looking down
    cam.vup      = Vector3D(0,-1,0);

    cam.render(list, 100);
    

}
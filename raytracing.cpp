using namespace std;

#include "header_files/color.h"
#include "header_files/vec3.h"
#include "header_files/ray.h"
#include "header_files/vec3.h"
#include "header_files/sphere.h"
#include "header_files/hittable.h"

#include <cmath>
#include <iostream>


color ray_color(const Ray& r) {
    //check for sphere intersection
    // if t>0, ray hits the sphere
    auto t = hit(Vector3D(0, 0, -1), 0.5, r);
    //calculate the normal and visualize it for when t>0
    if (t > 0.0) {
        Vector3D hit_point = r.point_at_t(t);
        Vector3D normal = unit_vec(hit_point - Vector3D(0, 0, -1));
        return 0.5 * color(normal.getx() + 1, normal.gety() + 1, normal.getz() + 1);
    }

    //bg color
    Vector3D unit_direction = unit_vec(r.getdirection());
    auto a = 0.5 * (unit_direction.gety() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}





int main() {
    //Set Up Image Parameters
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = static_cast<int>(image_width / aspect_ratio);

    //Set Up the Camera Parameters
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    double focal_length = 1.0;
    Vector3D camera_center(0, 0, 0);

    //Calculate Viewport Boundaries
    Vector3D viewport_u(viewport_width, 0, 0);
    Vector3D viewport_v(0, -viewport_height, 0);

    //Determine Pixel Delta Values
    Vector3D delta_u = viewport_u / image_width;
    Vector3D delta_v = viewport_v / image_height;

    //Calculate Upper-Left Corner of the Viewport
    Vector3D viewport_upper_left = camera_center - Vector3D(viewport_width/2, -viewport_height/2, focal_length);
    Vector3D pixel00_loc = viewport_upper_left + 0.5 * (delta_u - delta_v);

    // Render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            Vector3D pixel_center = pixel00_loc + (i * delta_u) + (j * delta_v);
            Vector3D ray_direction = unit_vec(pixel_center - camera_center);
            Ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }
    clog << "\rDone.                 \n";
}
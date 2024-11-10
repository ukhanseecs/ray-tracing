using namespace std;

#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>
#include "vec3.h"

color ray_color(const Ray& r) {
    //compute the color based on the ray r
    Vector3D unitVector = unit_vec(r.direction);
    auto a = 0.5*(unitVector.gety()+1);
    return (1-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1);
    // different color as r's direction will always be different
}

int main() {
    //Set Up Image Parameters
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width/aspect_ratio);

    //Set Up the Camera Parameters
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (double(image_width) / image_height);
    Vector3D camera_center = Vector3D(0, 0, 0);

    //Calculate Viewport Boundaries
    Vector3D viewport_u = Vector3D(viewport_width, 0, 0);
    Vector3D viewport_v = Vector3D(0, -viewport_height, 0);

    //Determine Pixel Delta Values
    Vector3D delta_u = viewport_u / image_width;
    Vector3D delta_v = viewport_v / image_height;


    //Calculate Upper-Left Corner of the Viewport
    Vector3D center_viewport = camera_center - Vector3D(0, 0, -focal_length);
    Vector3D upper_left_viewport = center_viewport + Vector3D(0, viewport_height / 2, 0) + Vector3D(-viewport_width / 2, 0, 0);
    auto upper_left_pixel_center = upper_left_viewport + delta_u / 2 - delta_v / 2;


    // Render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            Vector3D pixel_center = upper_left_pixel_center + i * delta_u + j * delta_v;
            Vector3D ray_direction = pixel_center - camera_center;

            // create a ray r that has dir and origin
            Ray r(camera_center, ray_direction);
            // the color computed is stored as pixel_color
            Vector3D pixel_color = ray_color(r);
            write_color(cout, pixel_color);

    }
    clog << "\rDone.                 \n";
    }
}
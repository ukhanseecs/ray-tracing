using namespace std;

#include "header_files/utility.h"
#include "header_files/sphere.h"
#include "header_files/hittable.h"
#include "header_files/hittable_list.h"
#include "header_files/interval.h"

color ray_color(const Ray& r, const hittable& list) { 
    hit_record rec; // Record to store intersection information

    if (list.hit(r, interval(0, infinity), rec)) { // If the ray hits an object
        // Calculate the color based on the normal at the hit point
        color normal_color = rec.normal + color(1, 1, 1); // Map normal to RGB [0,1]
        return 0.5 * normal_color; // Return normal map color 

        // return color(1,0,0); // Return red color
    }

    Vector3D unit_direction = unit_vec(r.getDirection()); // Get unit direction vector
    auto blend_factor = 0.5 * (unit_direction.gety() + 1.0); // Scale y component to [0,1]
    return (1.0 - blend_factor) * color(1.0, 1.0, 1.0) + blend_factor * color(0.5, 0.7, 1.0); // Linearly blend white and blue color
}





int main() {
    // %params:
    // make z > 1.5 to see the sphere completely
    HittableList list; //list of hittable objects
    list.add(make_shared<sphere>(Vector3D(0,100.5, 1), 100));
    list.add(make_shared<sphere>(Vector3D(0,0, 1.5), 1)); 

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
    Vector3D viewport_upper_left = camera_center - Vector3D(0, 0, focal_length) - Vector3D(viewport_width/2, -viewport_height/2, 0);
    Vector3D pixel00_loc = viewport_upper_left + 0.5 * (delta_u + delta_v);

    // Render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            Vector3D pixel_center = pixel00_loc + (i * delta_u) + (j * delta_v);
            Vector3D ray_direction = unit_vec(pixel_center - camera_center);
            Ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, list);
            write_color(cout, pixel_color);
        }
    }
    clog << "\rDone.\n";
}
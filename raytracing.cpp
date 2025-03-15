using namespace std;

#include "header_files/utility.h"
#include "header_files/sphere.h"
#include "header_files/hittable.h"
#include "header_files/hittable_list.h"
#include "header_files/interval.h"
#include "header_files/camera.h"


int main() {
    // Scene setup
    HittableList list; //list of hittable objects
    // Ground sphere (large sphere below)
    list.add(make_shared<sphere>(Vector3D(0,-100.5, -1), 100));
    
    // Main sphere in view
    list.add(make_shared<sphere>(Vector3D(0,0, -1), 0.5));  // Main sphere

    // additional spheres
    list.add(make_shared<sphere>(Vector3D(1,0, -1), 0.5));  // Right sphere
    list.add(make_shared<sphere>(Vector3D(-1,0, -1), 0.5)); // Left sphere
    

    camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.render(list);
    
}
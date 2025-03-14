using namespace std;

#include "header_files/utility.h"
#include "header_files/sphere.h"
#include "header_files/hittable.h"
#include "header_files/hittable_list.h"
#include "header_files/interval.h"
#include "header_files/camera.h"


int main() {
    // %params:
    // make z > 1.5 to see the sphere completely
    HittableList list; //list of hittable objects
    list.add(make_shared<sphere>(Vector3D(0,100.5, 1), 100));
    list.add(make_shared<sphere>(Vector3D(0,0, 1.5), 1)); 

    camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.render(list);
    
}
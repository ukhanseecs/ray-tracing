#include "ray.h"
#include "vec3.h"
#include <iostream>

void test_ray() {
    Vector3D origin(1.0, 2.0, 3.0);
    Vector3D direction(4.0, 5.0, 6.0);
    Ray ray(origin, direction);

    Vector3D point = ray.point_at_t(2.0);
    std::cout << "Point at t=2.0: (" << point.getx() << ", " << point.gety() << ", " << point.getz() << ")\n";
}

int main() {
    test_ray();
    return 0;
}
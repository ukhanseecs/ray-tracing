using namespace std;
#include <iostream>
#include "vec3.h"

int main() {
    Vector3D vec1(3.0, 4.0, 5.0);
    Vector3D negv = -vec1;
    negv.display();
    return 0;
}
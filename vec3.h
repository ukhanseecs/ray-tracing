using namespace std;

#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vector3D{
//constructors
    public:
        double vec[3];
        Vector3D() {
            vec[0] = 0; vec[1] = 0; vec[2] = 0;
        }
        Vector3D(float x, float y, float z) {
            vec[0] = x; vec[1] = y; vec[2] = z;
        }
//component access

};
#endif
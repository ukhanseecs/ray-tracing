using namespace std;

#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vector3D{
    private:
        double vec[3];
//constructors
    public:
        Vector3D() {
            vec[0] = 0; vec[1] = 0; vec[2] = 0;
        }
        Vector3D(float x, float y, float z) {
            vec[0] = x; vec[1] = y; vec[2] = z;
        }
//component access
    double getx() const{
        return vec[0];
    }
    double gety() const{
        return vec[1];
    }
    double getz() const{
        return vec[2];
    }
// display vector
    void display() const{
        cout << vec[0] <<','<< vec[1] <<',' << vec[2];
    }
// operator overloading
    // negating a vector
    Vector3D operator-() const{
        return Vector3D(-vec[0], -vec[1], -vec[2]);
    }
};
#endif
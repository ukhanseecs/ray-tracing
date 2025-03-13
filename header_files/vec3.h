using namespace std;

#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>


class Vector3D{
    private:
        double vec[3];
//constructors
    public:
        Vector3D() {
            vec[0] = 0; vec[1] = 0; vec[2] = 0;
        }
        Vector3D(double x, double y, double z) {
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
    // adding two vectors
    Vector3D& operator+=(const Vector3D other){
        vec[0] += other.vec[0];
        vec[1] += other.vec[1];
        vec[2] += other.vec[2];
        return *this;   // returns reference to the current object
    }
    //subtracting two vectors
    Vector3D& operator-=(const Vector3D& other) {
        vec[0] -= other.vec[0];
        vec[1] -= other.vec[1];
        vec[2] -= other.vec[2];
        return *this;
    }
    // read only access
    double operator[](int i) const {
        return vec[i];
    }
    //read write access
    double& operator[](int i){
        return vec[i];
    }
    // scalar multiplication
    Vector3D& operator*=(double t) {
        vec[0] *= t;
        vec[1] *= t;
        vec[2] *= t;
        return *this;
    }
    // scalar division
    Vector3D& operator/=(double t) {
        vec[0] *= 1/t;
        vec[1] *= 1/t;
        vec[2] *= 1/t;
        return *this;
    }
    // length
    double length() const{
        return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    }
    // lenght squared
    double length_squared() const{
        return (vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    }
// output vector as string <<
inline friend ostream& operator<<(ostream& out, const Vector3D& other){
    return out<<other.vec[0] << ' ' <<other.vec[1]<< ' ' <<other.vec[2]<< ' ';
}
// vector addition
inline friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.vec[0]+v2.vec[0],
        v1.vec[1]+v2.vec[1],
        v1.vec[2]+v2.vec[2]);
}
//vector subtraction
inline friend Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.vec[0]-v2.vec[0],
        v1.vec[1]-v2.vec[1],
        v1.vec[2]-v2.vec[2]);
}
//element wise multiplication
inline friend Vector3D operator*(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.vec[0]*v2.vec[0],
        v1.vec[1]*v2.vec[1],
        v1.vec[2]*v2.vec[2]);
}
//scalar into vector
inline friend Vector3D operator*(double t, const Vector3D& v1) {
    return Vector3D(t* v1.vec[0],
        t*v1.vec[1],
        t*v1.vec[2]);
}
//vector into scalar
inline friend Vector3D operator*(const Vector3D& v1, double t) {
    return t * v1; // calls the above scalar into vector
}
// scalar division
inline friend Vector3D operator/(const Vector3D& v2, double t) {
    return Vector3D(1/t*v2.vec[0],
        1/t*v2.vec[1],
        1/t*v2.vec[2]);
}
//dot product
double friend dot(const Vector3D& v1, const Vector3D& v2){
    return v1.vec[0]*v2.vec[0]
           + v1.vec[1]*v2.vec[1]
           + v1.vec[2]*v2.vec[2];
}
//cross product
inline friend Vector3D scalar(const Vector3D& v1, const Vector3D& v2) {
        return Vector3D(
        v1.vec[1] * v2.vec[2] - v1.vec[2] * v2.vec[1],   // x-component
        v1.vec[2] * v2.vec[0] - v1.vec[0] * v2.vec[2],   // y-component
        v1.vec[0] * v2.vec[1] - v1.vec[1] * v2.vec[0]);  // z-component
}
//unit vector
inline friend Vector3D unit_vec(const Vector3D& v1) {
        return v1/v1.length();
}


};
#endif
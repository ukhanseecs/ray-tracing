using namespace std;
#include <iostream>
#include "vec3.h"

int main() {
    Vector3D vec1(3.0, 4.0, 5.0);
    Vector3D vec2(7.0, 6.0, 7.0);
    Vector3D negvec1 = -vec1;
    vec1 += vec2;
    cout<<"negated vec1 \n";
    negvec1.display();
    cout << "\n vec1+vec2 \n";
    vec1.display();
    cout << "\n vec1-vec2 \n";
    vec1 -= vec2;
    vec1.display();
    cout << "\n read only access \n"<< vec1[0];
    vec1[0] = 8;
    cout << "\n read write access \n"<< vec1[0];

    // Test scalar multiplication
    vec1 *= 2.0;
    cout << "\nAfter scalar multiplication by 2: ";
    vec1.display();
    cout << endl;

    // Test scalar division
    vec1 /= 2.0;
    cout << "After scalar division by 2: ";
    vec1.display();
    cout << endl;

    // Test length and length squared
    cout << "Length of vec1: " << vec1.length() << endl;
    cout << "Length squared of vec1: " << vec1.length_squared() << endl;

    // Test <<
    cout << "vec1 :"<< vec1 << endl;

    // New tests for overloaded arithmetic operators
    Vector3D sum = vec1 + vec2;
    cout << "Sum: " << sum << endl;

    Vector3D difference = vec1 - vec2;
    cout << "Difference: " << difference << endl;

    Vector3D product = vec1 * vec2;
    cout << "Element-wise Product: " << product << endl;

    Vector3D scalarintovector = 2.0 * vec1;
    cout << "Scalar Product (2 * vec1): " << scalarintovector << endl;

    Vector3D vectorintoscalar = 2.0 * vec1;
    cout << "Scalar Product (vec1 * 2): " << vectorintoscalar << endl;

    Vector3D scalarDivision = vec1 / 2.0;
    cout << "Scalar Division (vec1 / 2): " << scalarDivision << endl;

    // Test dot product
    double dotProduct = dot(vec1, vec2);
    cout << "Dot Product of vec1 and vec2: " << dotProduct << endl;

    // Test cross product
    Vector3D crossProduct = scalar(vec1, vec2);
    cout << "Cross Product of vec1 and vec2: " << crossProduct << endl;

    // Test unit vector
    Vector3D unitVector = scalar(vec1);
    cout << "Unit Vector of vec1: " << unitVector << endl;

    return 0;
}
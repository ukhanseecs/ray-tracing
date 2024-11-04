using namespace std;
#include <iostream>
#include "vec3.h"

int main() {
    Vector3D vec1(3.0, 4.0, 5.0);
    Vector3D vec2(7.0, 6.0, 5.0);
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

    return 0;
}
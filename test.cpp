using namespace std;
#include <iostream>
#include "vec3.h"

int main() {
    Vector3D vec1(3.0, 4.0, 5.0);
    Vector3D vec2(7.0, 6.0, 5.0);
    Vector3D negvec1 = -vec1;
    vec1 += vec2;
    negvec1.display();
    cout << "\n";
    vec1.display();
    return 0;
}
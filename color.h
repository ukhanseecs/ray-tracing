#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = Vector3D;

// function to output the color vector values
void write_color(ostream& out, const color& pixel_color) {
// pixel_color is now a vector with x,y,z=r,g,b
// pixel_color = color(0.4,0.6,0.1)

    auto r = pixel_color.getx();
    auto g = pixel_color.gety();
    auto b = pixel_color.getz();

    int ir = int(255.999*r);
    int ig = int(255.999*g);
    int ib = int(255.999*b);

    cout << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif
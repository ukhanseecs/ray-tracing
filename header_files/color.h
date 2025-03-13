#ifndef COLOR_H
#define COLOR_H

#include "utility.h"

using color = Vector3D;

// function to output the color vector values
void write_color(ostream& out, const color& pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.getx()) << ' '
        << static_cast<int>(255.999 * pixel_color.gety()) << ' '
        << static_cast<int>(255.999 * pixel_color.getz()) << '\n';
}

#endif
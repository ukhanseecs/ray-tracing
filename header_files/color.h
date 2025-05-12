#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "utility.h"

using color = Vector3D;

// function to convert linear color to gamma color
inline double linear_to_gamma(double linear_component){
    if (linear_component > 0)
        return std::sqrt(linear_component);
    
    return 0.0;
}

// function to output the color vector values
void write_color(std::ostream& out, color pixel_color) {
    // apply gamma correction
    pixel_color = color(linear_to_gamma(pixel_color.getx()),
                        linear_to_gamma(pixel_color.gety()),
                        linear_to_gamma(pixel_color.getz()));

    // Write the translated [0,255] value of each color component
    static const interval color_range(0.0, 0.999);
    out << static_cast<int>(255.999 * color_range.clamp(pixel_color.getx())) << ' '
        << static_cast<int>(255.999 * color_range.clamp(pixel_color.gety())) << ' '
        << static_cast<int>(255.999 * color_range.clamp(pixel_color.getz())) << '\n';


}

#endif
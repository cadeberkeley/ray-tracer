#ifndef COLOR_H
#define COLOR_H

#include "vector.h"

#include <iostream>

#define Color Vec3

void write_color(std::ostream &out, Color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.elements[0]) << ' '
        << static_cast<int>(255.999 * pixel_color.elements[1]) << ' '
        << static_cast<int>(255.999 * pixel_color.elements[2]) << '\n';
}

#endif
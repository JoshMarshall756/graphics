#pragma once

#include <iostream>

#include "vec3.h"

// A utility function to write a single pixels colour out to the standard output stream
void write_color(std::ostream &out, color pixel_color)
{
    out << static_cast<int>(255.99 * pixel_color.x()) << ' '
        << static_cast<int>(255.99 * pixel_color.y()) << ' '
        << static_cast<int>(255.99 * pixel_color.z()) << '\n';
}
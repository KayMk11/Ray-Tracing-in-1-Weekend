#pragma once
#include "vec3.h"

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color)
{
    out << int(255.999 * pixel_color.x) << ' '
        << int(255.999 * pixel_color.y) << ' '
        << int(255.999 * pixel_color.z) << '\n';
}
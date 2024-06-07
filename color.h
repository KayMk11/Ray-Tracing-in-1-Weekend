#pragma once
#include "interval.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;

    static const interval intensity(0.0, 0.999);
    out << int(255.999 * intensity.clamp(r)) << ' '
        << int(255.999 * intensity.clamp(g)) << ' '
        << int(255.999 * intensity.clamp(b)) << '\n';
}
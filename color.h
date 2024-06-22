#pragma once
#include "interval.h"
#include "vec3.h"

using color = vec3;
inline float linear_to_gamma(float linear_component)
{
    if (linear_component > 0)
        return sqrt(linear_component);
    return 0;
}
void write_color(std::ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.0, 0.999);
    out << int(255.999 * intensity.clamp(r)) << ' '
        << int(255.999 * intensity.clamp(g)) << ' '
        << int(255.999 * intensity.clamp(b)) << '\n';
}
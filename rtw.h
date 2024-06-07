#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float PI = 3.1415926535897932385;

inline float to_radians(float degrees) { return degrees * PI / 180.0; }

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

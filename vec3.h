#pragma once

#include <math.h>
#include <iostream>

using std::sqrt;

class vec3
{
public:
    float x, y, z;
    vec3() : x(0.f), y(0.f), z(0.f) {}
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    vec3 operator-() const { return vec3(-x, -y, -z); }

    vec3 &operator+=(const vec3 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3 &operator*=(float t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3 &operator/=(float t) { return *this *= 1 / t; }
    float length() const { return sqrt(length_squared()); }
    float length_squared() const { return x * x + y * y + z * z; }
};

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) { return out << v.x << ' ' << v.y << ' ' << v.z; }
inline vec3 operator+(const vec3 &a, const vec3 &b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline vec3 operator-(const vec3 &a, const vec3 &b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline vec3 operator*(float t, const vec3 &v) { return vec3(v.x * t, v.y * t, v.z * t); }
inline vec3 operator*(const vec3 &v, float t) { return t * v; }
inline vec3 operator/(const vec3 &v, float t) { return (1.0f / t) * v; }
inline float dot(const vec3 &u, const vec3 &v) { return u.x * v.x + u.y * v.y + u.z * v.z; }
inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}
inline vec3 unit(const vec3 &v) { return v / v.length(); }

inline vec3 random_vec3() { return vec3(random_float(), random_float(), random_float()); }

inline vec3 random_vec3(float min, float max)
{
    return vec3(random_float(min, max),
                random_float(min, max),
                random_float(min, max));
}

inline vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = random_vec3(-1, 1);
        if (p.length_squared() < 1) // if we are going to normalise this vector anyway, why is this required?
            return p;
    }
}

inline vec3 random_unit_vector() { return unit(random_in_unit_sphere()); }

inline vec3 random_on_hemisphere(const vec3 &normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0, 0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}
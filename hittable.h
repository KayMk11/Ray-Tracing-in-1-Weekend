#pragma once

struct hitrecord
{
    vec3 position;
    vec3 normal;
    double t;
    bool frontface;

    void setNormal(const ray &r, const vec3 &outwardNormal)
    {
        frontface = dot(r.direction(), outwardNormal) < 0;
        normal = frontface ? outwardNormal : -outwardNormal;
    }
};

class hittable
{
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray &r, interval ray_t, hitrecord &record) const = 0;
};
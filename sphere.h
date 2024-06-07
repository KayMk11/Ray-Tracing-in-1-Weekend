#pragma once

#include "hittable.h"

class sphere : public hittable
{
private:
    vec3 mCenter;
    float mRadius;
    shared_ptr<material> mat;

public:
    sphere(const vec3 &center, float radius) : mCenter(center), mRadius(radius)
    {
    }
    virtual bool hit(const ray &r, interval ray_t, hitrecord &record) const override
    {
        vec3 oc = mCenter - r.origin();
        float a = r.direction().length_squared();
        float h = dot(r.direction(), oc);
        float c = oc.length_squared() - mRadius * mRadius;

        float discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;

        auto sqrtd = sqrt(discriminant);

        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        record.t = root;
        record.position = r.at(root);
        vec3 normal = (record.position - mCenter) / mRadius;
        record.setNormal(r, normal);
        record.mat = mat;
        return true;
    }
};

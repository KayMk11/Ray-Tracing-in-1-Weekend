#pragma once

#include "rtw.h"
#include "hittable.h"

class material
{
public:
    virtual ~material() = default;
    virtual bool scatter(const ray &r_in, const hitrecord &rec, color &attenuation, ray &scattered) const
    {
        return false;
    }
};

class lambertian : public material
{
    color albedo;

public:
    lambertian(const color &albedo) : albedo(albedo) {}
    virtual bool scatter(const ray &r_in, const hitrecord &rec, color &attenuation, ray &scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        scattered = ray(rec.position, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal : public material
{
    color albedo;
    float fuzziness;

public:
    metal(const color &albedo, float fuzz) : albedo(albedo), fuzziness(fuzz < 1 ? fuzz : 1) {}
    virtual bool scatter(const ray &r_in, const hitrecord &rec, color &attenuation, ray &scattered) const override
    {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit(reflected) + (fuzziness * random_unit_vector());
        scattered = ray(rec.position, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
};
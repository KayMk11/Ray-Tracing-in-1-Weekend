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

class dielectric : public material
{
    float refractive_index;

    static float reflectance(float cosine, float refractive_index)
    {
        auto r0 = (1 - refractive_index) / (1 + refractive_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

public:
    dielectric(float refractive_index) : refractive_index(refractive_index) {}
    virtual bool scatter(const ray &r_in, const hitrecord &rec, color &attenuation, ray &scattered) const override
    {
        attenuation = vec3(1., 1., 1.);
        float ri = rec.frontface ? (1. / refractive_index) : refractive_index;
        vec3 unit_direction = unit(r_in.direction());

        auto cos_theta = fminf(dot(-unit_direction, rec.normal), 1.0);
        auto sin_theta = sqrt(1 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;

        vec3 direction;
        if (cannot_refract || reflectance(cos_theta, ri) > random_float())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered = ray(rec.position, direction);
        return true;
    }
};
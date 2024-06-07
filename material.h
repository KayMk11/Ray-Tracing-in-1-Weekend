#pragma once

#include "rtw.h"

class hitrecord;
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
};
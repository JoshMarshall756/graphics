#pragma once

#include "ray.h"
#include "hittable.h"

// An abstraction of materials
class material
{
public:
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
};
#pragma once

#include "ray.h"
class material;

// A record of useful information computed and avoid lots of arguments
struct hit_record
{
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal)
    {
        // Determine whether the ray is inside the sphere or not
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// An abstract class for anything that a ray might hit 
class hittable
{
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};




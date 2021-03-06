#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "vec3.h"

class lambertian: public material{
public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    )   const{
        vec3 scatter_direction = normalize(rec.normal + random_unit_vector());
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};

#endif //LAMBERTIAN_H
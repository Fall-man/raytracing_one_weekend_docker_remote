#ifndef METAL_H
#define METAL_H

#include "material.h"

class metal: public material{
public:
    metal(const color& a): albedo(a){}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    )   const{
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0.0);
    }

public:
    color albedo;

};
#endif //METAL_H

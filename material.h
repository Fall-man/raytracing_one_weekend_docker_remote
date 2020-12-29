#ifndef MATERIAL_H
#define MATERIAL_H

class material{
public:
    virtual ~material(){}
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
};

// ランバートマテリアル
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

// 金属マテリアル
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

// 完全誘電体
class dielectric: public material{
public:
    dielectric(float ri): ref_idx(ri) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    )   const{
        attenuation = color(1.0, 1.0, 1.0);
        float etai_over_etat;
        if(rec.front_face){
            // std::cerr << "outside!\n";
            etai_over_etat = 1.0 / ref_idx;
        } else {
            // std::cerr << "inside!";
            etai_over_etat = ref_idx;
        }


        vec3 normalized_direction = normalize(r_in.direction());
        // vec3 refracted = refract(normalized_direction, rec.normal, etai_over_etat);
        // scattered = ray(rec.p, refracted);
        // return true;
        float cos_theta = fmin(dot(-normalized_direction, rec.normal), 1.0);
        // std::cerr << cos_theta << "\n";
        float sin_theta = sqrt(1.0 - cos_theta*cos_theta);
        if(etai_over_etat * sin_theta >1.0){
            // 反射する
            vec3 reflected = reflect(normalized_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            // std::cerr << "reflected!";
            return true;
        } else {
            // 屈折する
            vec3 refracted = refract(normalized_direction, rec.normal, etai_over_etat);
            // std::cerr << "input direction: " << normalized_direction << "\n";
            // std::cerr << "rec.normal: " << rec.normal << "\n";
            // std::cerr << "norm * refracted ray: " << dot(normalize(refracted), normalize(rec.normal)) << "\n";
            scattered = ray(rec.p, refracted);
            // std::cerr << "refracted!";
            return true;
        }

    }

public:
    float ref_idx;
};

#endif //MATERIAL_H

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable{
// コンストラクタ
public:
    sphere() {}
    sphere(point3 cen, float r, shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(m) {}

    virtual bool hit(
        const ray& r, float t_min, float t_max, hit_record& rec
    )   const;

// メンバ
public:
    point3 center;  //  球の中心座標
    float radius;   //  球の半径
    shared_ptr<material> mat_ptr;   //  球のマテリアル
};

// 球と光線が衝突したか調べる
bool sphere::hit(
    const ray& r, float t_min, float t_max, hit_record& rec
)   const{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if(discriminant > 0){   //  虚数解なら自動的に衝突点はなし
        auto root = sqrt(discriminant);

        // 近い方の点でぶつかるか調べる
        auto tmp = (-half_b - root)/a;
        if(tmp < t_max && tmp > t_min){
            // ぶつかっていたらhit_record構造体に衝突点の情報を送る
            rec.t = tmp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = normalize(rec.p - center);
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }

        // 遠い方の点でぶつかるか調べる
        tmp = (-half_b + root)/a;
        if(tmp < t_max && tmp > t_min){
            // ぶつかっていたらhit_record構造体に衝突点の情報を送る
            rec.t = tmp;
            vec3 outward_normal = normalize(rec.p - center);
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;   //  ぶつからなかったらfalse
}

#endif //SPHERE_H

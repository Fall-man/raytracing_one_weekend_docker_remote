#ifndef HITTABLE_H
#define HITTABLE_H

#include "rt_utility.h"
#include "ray.h"

class material;

// 光線が物体とぶつかった時に情報を格納する構造体
struct hit_record{
    point3 p;   //  衝突点の座標
    vec3 normal;    //  衝突点での物体の法線ベクトル
    shared_ptr<material> mat_ptr;   //  衝突した物体のマテリアルデータ
    float t;    //  光線の方向ベクトルにかけるパラメータ
    bool front_face;    //  光線の入射方向

    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;    //  光線が物体の外側から入射するならtrue, 内側からならfalse
        normal = front_face ? outward_normal : -outward_normal; //  法線は常に光線と反対の方向を向くようにする
    }
};

// 光線が衝突可能な物体を表す抽象クラス
class hittable{
public:
    virtual ~hittable() {}
    virtual bool hit(
        // 光線，衝突可能な範囲，衝突時に記録する構造体を渡す
        const ray& r, float t_min, float t_max, hit_record& rec
    )   const = 0;
};

#endif //HITTABLE_H

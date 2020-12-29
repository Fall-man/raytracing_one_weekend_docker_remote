#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(normalize(direction))  {}

    point3 origin() const {return orig; }   //  始点の座標を返す
    vec3 direction() const {return dir; }   //  方向ベクトルを返す

    // パラメータtに対する光線軌道上の点座標を返す
    point3 at(float t) const{
        return orig + t*dir;
    }

public:
    point3 orig;  //  始点
    vec3 dir;     //  方向ベクトル(正規化済)
};
#endif //RAY_H
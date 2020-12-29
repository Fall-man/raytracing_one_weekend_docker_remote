#ifndef CAMERA_H
#define CAMERA_H

#include "rt_utility.h"

class camera{
public:
    camera(){
        const auto aspect_ratio = 16.0/9.0; //   画面アスペクト比
        auto viewport_height = 2.0; //  スクリーン高さ
        auto viewport_width = aspect_ratio * viewport_height;   //  スクリーン横幅
        auto focal_length = 1.0;    //  焦点距離(焦点とスクリーンの距離)

        origin = point3(0.0,0.0,0.0);  //  カメラ座標(=光線を飛ばす原点)
        horizontal = vec3(viewport_width, 0.0, 0.0);   //  カメラの水平方向ベクトル
        vertical = vec3(0.0, viewport_height, 0.0);    //  カメラの鉛直方向ベクトル
        lower_left_corner = origin - horizontal/2.0 - vertical/2.0 -vec3(0.0, 0.0, focal_length);  //  ビューポートの左下の点の座標
    }
    ray get_ray(float u, float v) const{
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
    
private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif //CAMERA_H

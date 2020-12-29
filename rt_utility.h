#ifndef RT_UTILITY_H
#define RT_UTILITY_H

#include <cmath>
#include <cstdlib>
#include <random>
#include <limits>
#include <memory>

using std::shared_ptr;  //  インスタンス生成時のメモリ共有化のため
using std::make_shared; //  同上
using std::sqrt;

// 定数
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535;
const float half_pi = pi * 0.5;
const float two_pi = pi * 2.0;
const float eps = 0.001;

// ユーティリティ関数
// clamp関数
inline float clamp(float x, float min, float max){
    if(x < min) return min;
    if(x > max) return max;
    return x;
}
// 度数法から弧度法に変換
inline float degrees_to_radians(float degrees){
    return degrees * pi / 180.0;
}

// [0, 1)の乱数を生成
inline float random_float(){
    return rand() / (RAND_MAX+1.0);
}

// 任意の範囲の乱数を生成
inline float random_float(float min, float max){
    return min + (max-min)*random_float();
}

// // [0, 1)の乱数を生成(randomライブラリを使用)
// inline float random_float2(){
//     static std::uniform_real_distribution<float> distribution(0.0, 1.0);
//     static std::mt19937 generator;
//     return generator(distribution);
// }

// // 任意の範囲の乱数を生成(randomライブラリを使用)
// inline float random_float2(float min, float max){
//     return min + (max-min)*random_float2();
// }

// 共通ヘッダ
#include "ray.h"
#include "vec3.h"

#endif //RT_UTILITY_H

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;    //  平方根を取れるようにしておく

class vec3 {
public:
    vec3() : e{0,0,0} {}    //  初期成分の
    vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

    float x() const {return e[0]; } //  hoge.x()でx成分を取り出せるようにする
    float y() const {return e[1]; } //  hoge.y()でy成分を取り出せるようにする
    float z() const {return e[2]; } //  hoge.z()でz成分を取り出せるようにする
    float r() const {return e[0]; } //  hoge.r()でr成分を取り出せるようにする
    float g() const {return e[1]; } //  hoge.g()でg成分を取り出せるようにする
    float b() const {return e[2]; } //  hoge.b()でb成分を取り出せるようにする

    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]); } //反転ベクトルの生成
    float operator[](int i) const {return e[i]; }   //ベクトル成分の呼び出し    eg.) e[2]: eのz成分
    float& operator[](int i){return e[i]; }   //ベクトル成分の参照呼び出し

    //  ベクトル版の+=
    vec3& operator+=(const vec3 &v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;        
    }

    //  ベクトル版の*=
    vec3& operator*=(const float t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;        
    }

    //  ベクトル版の/=
    vec3& operator/=(const float t){
        return *this *= 1/t;
    }

    //  自身の長さを返す
    float length() const{
        return sqrt(length_squared());
    }

    //  自身の長さの2乗を返す
    float length_squared() const{
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline static vec3 random(){
        return vec3(random_float(), random_float(), random_float());
    }

    inline static vec3 random(float min, float max){
        return vec3(random_float(min, max), 
                    random_float(min, max), 
                    random_float(min, max));
    }

public:
    float e[3]; // x, y, z座標が要素  
};

// エイリアスの定義
using point3 = vec3; // 点の座標
using color = vec3; // RGBによるピクセルカラー表現

// =====================================================================================================================
// vec3 ユーティリティ関数

// 標準出力へベクトル成分の値を流す
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// 和算
inline vec3 operator+ (const vec3 &u, const vec3 &v){
    return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2] );
}

// 減算
inline vec3 operator- (const vec3 &u, const vec3 &v){
    return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2] );
}

// ベクトルxベクトル
inline vec3 operator* (const vec3 &u, const vec3 &v){
    return vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2] );
}

// ベクトルx定数その1
inline vec3 operator* (float t, const vec3 &v){
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2] );
}

// ベクトルx定数その2
inline vec3 operator* (const vec3 &v, float t){
    return t * v;
}

// 除算
inline vec3 operator/ (vec3 v, float t){
    return (1/t) * v;
}

// 内積
inline float dot(const vec3 &u, const vec3 &v){
    return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
}

// 外積
inline vec3 cross(const vec3 &u, const vec3 &v){
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2], 
                u.e[0] * v.e[1] - u.e[1] * u.e[0]);
}

// 単位ベクトル化
inline vec3 normalize(vec3 v){
    return v/v.length();
}

// ランダム化された成分を持つ単位ベクトルの生成
vec3 random_unit_vector(){
    auto a = random_float(0, two_pi);
    auto z = random_float(-1.0, 1.0);
    auto r = sqrt(1.0 - z*z);
    return vec3(r*cos(a), r*sin(a), z);
}

// 長さが１未満のランダム化されたベクトルの生成
vec3 random_in_unit_sphere(){
    while(true){
        auto p = vec3::random(-1.0, 1.0);
        if(p.length_squared() >=1) continue;
        return p;
    }
}


// 法線方向によらない長さが１未満のランダム化された反射ベクトルの生成
vec3 random_in_hemisphere(const vec3& normal){
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// 完全鏡面反射方向ベクトルの算出
vec3 reflect(const vec3& v_in, const vec3& n_out){
    return normalize(v_in - 2.0 * dot(v_in, n_out) * n_out);
}

// 完全鏡面屈折
vec3 refract(const vec3& v_in, const vec3& n_out, float etai_over_etat){
    auto cos_theta = dot(-normalize(v_in), normalize(n_out));
    vec3 r_out_parallel = etai_over_etat * (v_in + cos_theta*n_out);
    // std::cerr << r_out_parallel.length() << " ";
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n_out;
    // std::cerr << r_out_perp.length() << "\n";
    return r_out_parallel + r_out_perp;
}

#endif //VEC3_H
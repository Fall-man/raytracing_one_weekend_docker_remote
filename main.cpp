#include "rt_utility.h"

#include "color.h"

#include "camera.h"

#include "hittable_list.h"
#include "sphere.h"

#include "material.h"

#include <fstream>
#include <iostream>
#include <string>

// 光線の色を決める
color ray_color(const ray& r, const hittable& world, int depth){
    hit_record rec;

    // 反射回数が一定以上になったら，その光線の寄与は無視する
    if(depth <= 0){
        std::cerr << "hogehoge\n";
        return color(0.0, 0.0, 0.0);
    }

    if(world.hit(r, eps, infinity, rec)){
        ray scattered;
        color attenuation;
        
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            // std::cerr << rec.t << "\n";
            return attenuation * ray_color(scattered, world, depth-1);
        }
        // std::cerr << "fugafuga\n";
        return color(0.0, 0.0, 0.0);

        // return 0.5 * (rec.normal + color(1.0, 1.0, 1.0)); // [-1.0, 1.0] -> [0.0, 1.0]に変換して色として表示できるようにする
    }

    vec3 direction = normalize(r.direction());
    auto t = 0.5 * (direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);

    // return (0.0, 0.0, 0.0);  //  真っ黒な背景
}

int main() {

    // PPM画像ファイルと標準出力ストリームをつなぐ
    std::ofstream out("output.ppm");
    // std::ofstream out("output2.ppm");
    std::streambuf *coutbuf = std::cout.rdbuf();  //save old buf
    std::cout.rdbuf(out.rdbuf());                 //redirect std::cout to output.ppm!

    // パラメータ入力部
    //
    const auto aspect_ratio = 16.0/9.0; //   画面アスペクト比
    const int image_width = 512;       //  画面横幅
    const int image_height = static_cast<int>(image_width / aspect_ratio);  //  画面縦幅

    // カメラ設定
    camera cam;

    // ジオメトリ設定
    hittable_list world;
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, make_shared<lambertian>(color(0.7, 0.3, 0.3))));
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, make_shared<lambertian>(color(0.8, 0.8, 0.0))));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, make_shared<metal>(color(0.8, 0.6, 0.2))));
    // world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, make_shared<metal>(color(0.8, 0.8, 0.8))));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, make_shared<dielectric>(1.5)));

    // サンプリング設定
    const int samples_per_pixel = 100;  //  各ピクセルごとのサンプリング回数
    const int max_depth = 50;   //  １本の光線の最大反射・透過回数

    // PPMファイルのヘッダ部
    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";
    // std::cout << "P3\n"
            //   << "1" << " " << "1" << "\n255\n";

    // レイトレ部
    for (int j = image_height - 1; j >= 0; j--) {
    // for (int j = 223; j >= 223; j--) {
        std::cerr << "\nScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
        // for (int i = 48; i < 49; i++) {
            color tmp_pixel_color(0.0, 0.0, 0.0);
            for(int s = 0; s < samples_per_pixel; s++){
            // for(int s = 0; s < 100; s++){
                std::cerr << "Ray: " << j << ", " << i << ", " << s << "\n";
                auto u = (i+random_float()) / (image_width-1);
                auto v = (j+random_float()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                tmp_pixel_color += ray_color(r, world, max_depth);
            }
            color pixel_color = average_color(tmp_pixel_color, samples_per_pixel);
            write_color(std::cout, pixel_color);
        }
    }

    // 標準出力先をコンソールに戻す
    std::cout.rdbuf(coutbuf);  //reset to standard output again

    // エラー出力ストリームに終了を出力する
    std::cerr << "\nDone.\n";

    return 0;
}

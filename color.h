#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// ピクセルごとに指定された色を出力する
color average_color(color pixel_color, int samples_per_pixel){
    auto scale = 1.0 / samples_per_pixel;
    return pixel_color *= scale;
}

void write_color(std::ostream &out, color pixel_color){
    out << static_cast<int>(256.0 * clamp(pixel_color.r(), 0.0, 0.999)) << ' '
        << static_cast<int>(256.0 * clamp(pixel_color.g(), 0.0, 0.999)) << ' '
        << static_cast<int>(256.0 * clamp(pixel_color.b(), 0.0, 0.999)) << '\n';
}

#endif //COLOR_H


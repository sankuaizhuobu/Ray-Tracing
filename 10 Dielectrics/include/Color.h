// Color.h

#ifndef COLOR_H
#define COLOR_H

#include"Vec3.h"
#include<iostream>
#include<fstream>

// 写入RGB
void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel) {
	
	// 反走样
	//......
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();  // 0.几
	
	// Divide the color by the number of samples.  反走样的本质：调整边缘像素颜色，使过渡更平缓
	// gamma矫正  提亮或变暗
	// gamma = 2  提亮
	auto scale = 1.0 / samples_per_pixel;  // 每个像素周围拿n个点，每个点 RGB 平分
	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);  // 很小的 0.几

	// Write the translated
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << ' ';

}

#endif
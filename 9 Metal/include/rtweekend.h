// rtweekend.h

#ifndef RTWEEKEND_H  // 放一些常用的常量、函数
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>


// ********************* Constants 常量 ********************** //

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// ********************* Utility Functions 常用函数 ********************** //

inline double degrees_to_radians(double degrees) {  // 角度制转换为弧度制
	return degrees / 180 * pi;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }  // 取较小值
inline double ffmax(double a, double b) { return a >= b ? a : b; }  // 取较大值


inline double random_double() {
	// Returns a random real in [0,1)
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	// Returns a random real in [min,max)
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {  // x 超出范围的话限制一下
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// Common Headers 通用头文件

#include "Ray.h"
#include "Vec3.h"
#include "Hittable.h"

#endif
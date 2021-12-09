// rtweekend.h

#ifndef RTWEEKEND_H  // ��һЩ���õĳ���������
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>


// ********************* Constants ���� ********************** //

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// ********************* Utility Functions ���ú��� ********************** //

inline double degrees_to_radians(double degrees) {  // �Ƕ���ת��Ϊ������
	return degrees / 180 * pi;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }  // ȡ��Сֵ
inline double ffmax(double a, double b) { return a >= b ? a : b; }  // ȡ�ϴ�ֵ


inline double random_double() {
	// Returns a random real in [0,1)
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	// Returns a random real in [min,max)
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {  // x ������Χ�Ļ�����һ��
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// Common Headers ͨ��ͷ�ļ�

#include "Ray.h"
#include "Vec3.h"
#include "Hittable.h"

#endif
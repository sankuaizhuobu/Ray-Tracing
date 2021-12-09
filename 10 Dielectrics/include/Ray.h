// Ray.h

#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
public:

	// ***** 成员变量 ***** //

	Point3 orig;  // 起点
	Vec3 dir;  // 方向

public:

	// ***** 成员函数 ***** //

	// 默认构造函数
	Ray() {}
	// 构造函数，指定起点和方向
	Ray(const Point3& origin, const Vec3& direction) :orig(origin), dir(direction) {}

	// 获取起点
	Point3 origin() const { return orig; }
	// 获取方向
	Vec3 direction() const { return dir; }

	// 得到光线上的参数
	Point3 at(TYPE t) const {
		return orig + t * dir;
	}
};

#endif
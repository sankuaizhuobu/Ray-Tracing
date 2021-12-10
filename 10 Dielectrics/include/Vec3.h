// Vec3.h

//#pragma once  // 同一个文件（物理位置相同）不会被包含两次
#ifndef VEC3_H  // 保护符，相同的宏不会重复包含
#define VEC3_H

#include<cmath>
#include<iostream>

typedef float TYPE;

using std::sqrt;

class Vec3 {
public:

	// ***** 变量 ***** //
	TYPE e[3];

	// ***** 函数 ***** //
	
	// 构造函数1
	Vec3() : e{ 0,0,0 } {}  // 构造函数初始值列表
	// 构造函数2
	Vec3(TYPE e0, TYPE e1, TYPE e2) :e{ e0, e1, e2 } {}  // 带参数的构造函数
	// 获取分量x,y,z
	TYPE x() const { return e[0]; }  // const function member
	TYPE y() const { return e[1]; }
	TYPE z() const { return e[2]; }

	// 取反
	Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }  // 返回相反向量；运算符重载
	// 使用下标0,1,2获取分量
	TYPE operator[](int i) const { return e[i]; }
	// 使用下标0,1,2获取分量的引用
	TYPE& operator[](int i) { return e[i]; }

	// 向量自增
	Vec3& operator+=(const Vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;  // 对 this 指针解引用，得到对象
	}

	// 向量自乘
	Vec3& operator*=(const TYPE t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	// 向量自除
	Vec3& operator/=(const TYPE t) {
		//e[0] /= t;
		//e[1] /= t;
		//e[2] /= t;
		//return *this;
		return *this *= 1 / t;  // 用前面定义的乘法来定义除法
	}

	// 获取向量长度
	TYPE length() const {
		return std::sqrt(length_squared());
	}

	// 获取向量长度平方
	TYPE length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	// 判断Vec3是否为0 / 非常接近0
	bool near_zero() const {
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return fabs(e[0] < s) && fabs(e[1] < s) && fabs(e[2] < s);
	}

	// Vec3 random utility functions
	inline static Vec3 random() {
		return Vec3(random_double(), random_double(), random_double());
	}

	inline static Vec3 random(double min, double max) {
		return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}
};

// Type aliases for Vec3 类型别名
using Point3 = Vec3;  // 3D point
using Color = Vec3;  // RGB color


// ***** Vec3 Utility Functions 常用函数，一些非成员函数 ***** //

// 打印向量
inline std::ostream& operator<<(std::ostream &out, const Vec3& v) {
	return out << v.e[0] << ", " << v.e[1] << ", " << v.e[2];
}

// 向量相加
inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);  // 返回的时候调用了构造函数~
}

// 向量相减
inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// 向量乘法：分量分别相乘
inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// 向量数乘：数*向量
inline Vec3 operator*(const TYPE t, const Vec3 u) {
	return Vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

// 向量数乘：向量*数
inline Vec3 operator*(const Vec3 u, const TYPE t) {
	return t * u;
}

// 向量除以数
inline Vec3 operator/(const Vec3 u, const TYPE t) {
	return 1 / t * u;
}

// 向量点乘
inline TYPE dot(const Vec3 u, const Vec3 v) {
	return (u.e[0] * v.e[0]
		  + u.e[1] * v.e[1]
		  + u.e[2] * v.e[2]);
}

// 向量叉乘
inline Vec3 cross(const Vec3 u, const Vec3 v) {
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		        u.e[2] * v.e[0] - u.e[0] * v.e[2],
		        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// 规范化的向量
inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

// The random_in_unit_sphere() function
// 在 “ 单位球面 ” 内部随机找一个点，使之与球心连成单位向量
Vec3 random_in_unit_sphere() {
	while (true) {
		auto p = Vec3::random(-1, 1);  // 生成一个 Vec3，每个分量为 -1~1 的随机值
		if (p.length_squared() >= 1) continue;  // Vec3终点在球外，则拒绝.
		return p;
	}
}

// 将 “ 单位球面 ” 内部的随机向量进行规范化，从而找到 “ 单位球面 ” 上的随机单位向量
Vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

// 返回 “单位半球面” 内部的随机点
Vec3 random_in_hemisphere(Vec3 normal) {
	Vec3 in_unit_shpere = random_in_unit_sphere();
	if (dot(in_unit_shpere, normal) > 0) {
		return in_unit_shpere;
	}
	return -in_unit_shpere;
}

// 镜面反射向量  【需要画图理解】
// 参数1.入射光单位向量（视线） 参数2.单位法向量
Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * n * dot(v, n);
}

// 折射向量  【需要画图+推导】
// Snell's Law （仅用于各向同性介质构成的静止界面）
// 参数1.入射光  参数2.法向量  参数3.光在介质中的折射率n1/n2
Vec3 refract(const Vec3& r_in_unit, const Vec3& normal, double eta) {
	auto cos_theta = fmin(dot(-r_in_unit, normal), 1.0);  // 返回较小值
	Vec3 r_out_perpendicular = eta * (r_in_unit + cos_theta * normal);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perpendicular.length_squared())) * normal;
	return r_out_perpendicular + r_out_parallel;
}

#endif // !VEC3_H
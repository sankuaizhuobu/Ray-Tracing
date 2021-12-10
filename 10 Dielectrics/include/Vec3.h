// Vec3.h

//#pragma once  // ͬһ���ļ�������λ����ͬ�����ᱻ��������
#ifndef VEC3_H  // ����������ͬ�ĺ겻���ظ�����
#define VEC3_H

#include<cmath>
#include<iostream>

typedef float TYPE;

using std::sqrt;

class Vec3 {
public:

	// ***** ���� ***** //
	TYPE e[3];

	// ***** ���� ***** //
	
	// ���캯��1
	Vec3() : e{ 0,0,0 } {}  // ���캯����ʼֵ�б�
	// ���캯��2
	Vec3(TYPE e0, TYPE e1, TYPE e2) :e{ e0, e1, e2 } {}  // �������Ĺ��캯��
	// ��ȡ����x,y,z
	TYPE x() const { return e[0]; }  // const function member
	TYPE y() const { return e[1]; }
	TYPE z() const { return e[2]; }

	// ȡ��
	Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }  // �����෴���������������
	// ʹ���±�0,1,2��ȡ����
	TYPE operator[](int i) const { return e[i]; }
	// ʹ���±�0,1,2��ȡ����������
	TYPE& operator[](int i) { return e[i]; }

	// ��������
	Vec3& operator+=(const Vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;  // �� this ָ������ã��õ�����
	}

	// �����Գ�
	Vec3& operator*=(const TYPE t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	// �����Գ�
	Vec3& operator/=(const TYPE t) {
		//e[0] /= t;
		//e[1] /= t;
		//e[2] /= t;
		//return *this;
		return *this *= 1 / t;  // ��ǰ�涨��ĳ˷����������
	}

	// ��ȡ��������
	TYPE length() const {
		return std::sqrt(length_squared());
	}

	// ��ȡ��������ƽ��
	TYPE length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	// �ж�Vec3�Ƿ�Ϊ0 / �ǳ��ӽ�0
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

// Type aliases for Vec3 ���ͱ���
using Point3 = Vec3;  // 3D point
using Color = Vec3;  // RGB color


// ***** Vec3 Utility Functions ���ú�����һЩ�ǳ�Ա���� ***** //

// ��ӡ����
inline std::ostream& operator<<(std::ostream &out, const Vec3& v) {
	return out << v.e[0] << ", " << v.e[1] << ", " << v.e[2];
}

// �������
inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);  // ���ص�ʱ������˹��캯��~
}

// �������
inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// �����˷��������ֱ����
inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// �������ˣ���*����
inline Vec3 operator*(const TYPE t, const Vec3 u) {
	return Vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

// �������ˣ�����*��
inline Vec3 operator*(const Vec3 u, const TYPE t) {
	return t * u;
}

// ����������
inline Vec3 operator/(const Vec3 u, const TYPE t) {
	return 1 / t * u;
}

// �������
inline TYPE dot(const Vec3 u, const Vec3 v) {
	return (u.e[0] * v.e[0]
		  + u.e[1] * v.e[1]
		  + u.e[2] * v.e[2]);
}

// �������
inline Vec3 cross(const Vec3 u, const Vec3 v) {
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		        u.e[2] * v.e[0] - u.e[0] * v.e[2],
		        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// �淶��������
inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

// The random_in_unit_sphere() function
// �� �� ��λ���� �� �ڲ������һ���㣬ʹ֮���������ɵ�λ����
Vec3 random_in_unit_sphere() {
	while (true) {
		auto p = Vec3::random(-1, 1);  // ����һ�� Vec3��ÿ������Ϊ -1~1 �����ֵ
		if (p.length_squared() >= 1) continue;  // Vec3�յ������⣬��ܾ�.
		return p;
	}
}

// �� �� ��λ���� �� �ڲ�������������й淶�����Ӷ��ҵ� �� ��λ���� �� �ϵ������λ����
Vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

// ���� ����λ�����桱 �ڲ��������
Vec3 random_in_hemisphere(Vec3 normal) {
	Vec3 in_unit_shpere = random_in_unit_sphere();
	if (dot(in_unit_shpere, normal) > 0) {
		return in_unit_shpere;
	}
	return -in_unit_shpere;
}

// ���淴������  ����Ҫ��ͼ��⡿
// ����1.����ⵥλ���������ߣ� ����2.��λ������
Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * n * dot(v, n);
}

// ��������  ����Ҫ��ͼ+�Ƶ���
// Snell's Law �������ڸ���ͬ�Խ��ʹ��ɵľ�ֹ���棩
// ����1.�����  ����2.������  ����3.���ڽ����е�������n1/n2
Vec3 refract(const Vec3& r_in_unit, const Vec3& normal, double eta) {
	auto cos_theta = fmin(dot(-r_in_unit, normal), 1.0);  // ���ؽ�Сֵ
	Vec3 r_out_perpendicular = eta * (r_in_unit + cos_theta * normal);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perpendicular.length_squared())) * normal;
	return r_out_perpendicular + r_out_parallel;
}

#endif // !VEC3_H
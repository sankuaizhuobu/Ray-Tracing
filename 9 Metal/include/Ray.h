// Ray.h

#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
public:

	// ***** ��Ա���� ***** //

	Point3 orig;  // ���
	Vec3 dir;  // ����

public:

	// ***** ��Ա���� ***** //

	// Ĭ�Ϲ��캯��
	Ray() {}
	// ���캯����ָ�����ͷ���
	Ray(const Point3& origin, const Vec3& direction) :orig(origin), dir(direction) {}

	// ��ȡ���
	Point3 origin() const { return orig; }
	// ��ȡ����
	Vec3 direction() const { return dir; }

	// �õ������ϵĲ���
	Point3 at(TYPE t) const {
		return orig + t * dir;
	}
};

#endif
// Hittable.h

#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class Material;

// һ���ṹ��    ��¼������Hittable����ײ
struct Hit_record {
	Point3 p;  // ��
	Vec3 normal;  // ���淨����
	std::shared_ptr<Material> materials;  // *** ����ָ�� ***

	TYPE t;  // ��������Ĳ���
	bool front_face;  // �Ƿ������棨ǰ�桢������棩

	// ���ñ��淨����    �жϹ�����֮��ײ�ı������ڱ��滹������棬Ȼ��õ����淨����
	inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
		// �ڻ� < 0�����ߴ�������棬���淨���� = ����ķ�����
		// �ڻ� > 0�����ߴ����ڱ��棬���淨���� = -����ķ�����
	}
};

class Hittable {
public:
	// ���麯��    ��������������и�д
	virtual bool hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const = 0;
};

#endif
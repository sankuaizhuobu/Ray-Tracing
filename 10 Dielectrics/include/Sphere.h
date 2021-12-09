// Sphere.h

#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"


class Sphere : public Hittable {
public:
	Sphere() {};
	Sphere(Point3 c, TYPE r, std::shared_ptr<Material> m) :center(c), radius(r), materials(m) {};


	virtual bool hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const override;
	
public:
	Point3 center;
	double radius;
	std::shared_ptr<Material> materials;  // *** ����ָ�� ***
};


// �����Ƿ��������ײ    ����ײ�㷶Χ����
bool Sphere::hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const {
	
	Vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// �ҵ�����Ľ��㣬��Ӧ���ں���Χ֮��
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outward_normal = (rec.p - center) / radius;  // �ȼ�������ķ�����
	rec.set_face_normal(r, outward_normal);  // Ϊ�����ཻ���ñ��淨������������������ⷨ���������������������һ�µı��淨������
	rec.materials = materials;  // *** ��ײ��¼�еĲ���ָ�� ��������ָ��һ��ָ����� ***

	return true;
}



#endif
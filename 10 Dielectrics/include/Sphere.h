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
	std::shared_ptr<Material> materials;  // *** 材质指针 ***
};


// 表面是否与光线碰撞    且碰撞点范围合理
bool Sphere::hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const {
	
	Vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// 找到最近的交点，它应该在合理范围之内
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outward_normal = (rec.p - center) / radius;  // 先计算向外的方向量
	rec.set_face_normal(r, outward_normal);  // 为本次相交设置表面法向量（根据入射光与外法向量，返回与入射光来向一致的表面法向量）
	rec.materials = materials;  // *** 碰撞记录中的材质指针 与表面材质指针一起指向材质 ***

	return true;
}



#endif
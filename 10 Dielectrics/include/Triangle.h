// Triangle.h

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "rtweekend.h"


class Triangle : public Hittable {
public:
	Triangle() {};
	Triangle(Point3 a, Point3 b, Point3 c, std::shared_ptr<Material> m) :p0(a), p1(b), p2(c), materials(m) {};


	virtual bool hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const override;
	
public:
	Point3 p0;
	Point3 p1;
    Point3 p2;
	std::shared_ptr<Material> materials;  // *** 材质指针 ***
};


// 三角面是否与光线碰撞    且碰撞点范围合理
bool Triangle::hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const {



	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outward_normal = (rec.p - center) / radius;  // 先计算向外的方向量
	rec.set_face_normal(r, outward_normal);  // 为本次相交设置表面法向量（根据入射光与外法向量，返回与入射光来向一致的表面法向量）
	rec.materials = materials;  // *** 碰撞记录中的材质指针 与表面材质指针一起指向材质 ***

	return true;
}



#endif
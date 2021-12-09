// Hittable.h

#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class Material;

// 一个结构体    记录光线与Hittable的碰撞
struct Hit_record {
	Point3 p;  // 点
	Vec3 normal;  // 表面法向量
	std::shared_ptr<Material> materials;  // *** 材质指针 ***

	TYPE t;  // 光线里面的参数
	bool front_face;  // 是否是正面（前面、球的外面）

	// 设置表面法向量    判断光线与之碰撞的表面是内表面还是外表面，然后得到表面法向量
	inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
		// 内积 < 0：光线打在外表面，表面法向量 = 向外的法向量
		// 内积 > 0：光线打在内表面，表面法向量 = -向外的法向量
	}
};

class Hittable {
public:
	// 纯虚函数    必须由派生类进行复写
	virtual bool hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const = 0;
};

#endif
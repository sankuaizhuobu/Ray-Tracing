// Hittable_list.h

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

// 一张清单    记录场景中所有可以与光线碰撞的物体
class Hittable_list :public Hittable {
public:
	// 构造函数
	Hittable_list() {}  // 默认构造函数
	Hittable_list(std::shared_ptr<Hittable> object) {  // 使用一个物体进行构造
		add(object);
	}

	// 清除所有物体
	void clear() { objects.clear(); }
	// 加入物体
	void add(std::shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	// 光线与物体碰撞    对父类纯虚函数的复写
	virtual bool hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const override;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
};


bool Hittable_list::hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const {
	Hit_record temp_rec;  // 记录相交信息
	bool hit_anything = false;  // 记录光线是否碰撞到物体
	auto closest_so_far = t_max;  // 记录 目前光线碰到场景的最近位置（参数t）

	// 遍历物体vector
	for (const auto& object : objects) {
		if (object->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}




#endif // ! HITTABLE_LIST_H
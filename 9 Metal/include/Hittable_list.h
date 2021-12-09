// Hittable_list.h

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

// һ���嵥    ��¼���������п����������ײ������
class Hittable_list :public Hittable {
public:
	// ���캯��
	Hittable_list() {}  // Ĭ�Ϲ��캯��
	Hittable_list(std::shared_ptr<Hittable> object) {  // ʹ��һ��������й���
		add(object);
	}

	// �����������
	void clear() { objects.clear(); }
	// ��������
	void add(std::shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	// ������������ײ    �Ը��ി�麯���ĸ�д
	virtual bool hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const override;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
};


bool Hittable_list::hit(const Ray& r, TYPE t_min, TYPE t_max, Hit_record& rec) const {
	Hit_record temp_rec;  // ��¼�ཻ��Ϣ
	bool hit_anything = false;  // ��¼�����Ƿ���ײ������
	auto closest_so_far = t_max;  // ��¼ Ŀǰ�����������������λ�ã�����t��

	// ��������vector
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
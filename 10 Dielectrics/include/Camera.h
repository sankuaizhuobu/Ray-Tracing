// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class Camera {
public:
	Camera() {
		auto aspect_ratio = 16.0 / 9.0;  // �ӿڿ�߱�
		auto viewport_height = 2.0;  // �ӿڸ߶ȣ�����ӿں�С�ģ�
		auto viewport_width = aspect_ratio * viewport_height;  // �ӿڿ�ȣ��ӿ������Ŀ�߱�һ����
		auto focal_length = 1.0;

		origin = Point3(0, 0, 0);  // ���λ�ã�ԭ��
		horizontal = Vec3(viewport_width, 0, 0);  // ˮƽ����������Ϊ�ӿڿ��
		vertical = Vec3(0, viewport_height, 0);  // ��ֱ����������Ϊ�ӿڸ߶�
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);  // ��������½�
	}

	Ray get_ray(TYPE u, TYPE v) {
		// ������㣺Ϊԭ��(0,0)��Ļ���ģ�Ҳ�������/���۵�λ�ã�z = 0����
		// ���߷����յ� - ��㣬���ߵ��յ�Ϊ�����ϵĵ㣨z = - focalLength��
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);  // С�� * �ӿڳ�/��
	}

private:
	Point3 origin;
	Point3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
};


#endif
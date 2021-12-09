// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class Camera {
public:
	Camera() {
		auto aspect_ratio = 16.0 / 9.0;  // 视口宽高比
		auto viewport_height = 2.0;  // 视口高度（相机视口很小的）
		auto viewport_width = aspect_ratio * viewport_height;  // 视口宽度（视口与成像的宽高比一样）
		auto focal_length = 1.0;

		origin = Point3(0, 0, 0);  // 相机位置，原点
		horizontal = Vec3(viewport_width, 0, 0);  // 水平向量，长度为视口宽度
		vertical = Vec3(0, viewport_height, 0);  // 垂直向量，长度为视口高度
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);  // 成像的左下角
	}

	Ray get_ray(TYPE u, TYPE v) {
		// 光线起点：为原点(0,0)屏幕中心，也就是相机/人眼的位置（z = 0）；
		// 光线方向：终点 - 起点，光线的终点为成像上的点（z = - focalLength）
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);  // 小数 * 视口长/宽
	}

private:
	Point3 origin;
	Point3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
};


#endif
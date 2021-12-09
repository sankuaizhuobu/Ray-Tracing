// main_8.cpp

#include "include/rtweekend.h"
#include "include/Color.h"
#include "include/Hittable_list.h"
#include "include/Sphere.h"
#include "include/Camera.h"
#include "include/Material.h"

#include <iostream>
#include <fstream>


Color ray_color(const Ray& r, const Hittable& world, int depth) {  // 注：返回的像素 RGB 值都是0.0-1.0的小数
	
	Hit_record rec;

	// *** 递归出口  不超过一定递归深度 ***
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0) {
		return Color(0, 0, 0);
	}

	if (world.hit(r, 0.001, infinity, rec)) {  // 打在场景上的话，返回计算出的像素值

		//Point3 target = rec.p + rec.normal + random_in_unit_sphere();  // 单位球中的随机点
		//Point3 target = rec.p + rec.normal + random_unit_vector();  // 单位球面上的随机点[Lambertian distribution]
		//Point3 target = rec.p + random_in_hemisphere(rec.normal);  // The initial hack
		//Ray r_reflect(rec.p, target - rec.p);  // 得到反射光线
		//return 0.5 * ray_color(r_reflect, world, depth - 1);  // 递归

		Ray scattered;  // *** 定义散射光 ***
		Color attenuation;  // *** 定义散射光的衰减系数 ***
		// 若材质产生散射，则递归散射光；若没有散射（全吸收），则直接返回黑色
		if(rec.materials->scatter(r, rec, scattered, attenuation))
		{
			// 注意不要忘记散射光的衰减
			return attenuation * ray_color(scattered, world, depth - 1);  // 递归
		}
		return Color(0, 0, 0);
	}

	// ****** 递归出口 没有打在场景上的话，返回背景色 ******
	// 由 t（其实是 y）决定的颜色值，y 为 -1 时像素为 startValue（白色），y 为 1 时像素为 endValue（RGB 为以上数组）。
	// 线性插值
	Vec3 unit_direction = unit_vector(r.direction());  // 将光线向量规范化（化为单位向量）
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);  // 【注意！像素RGB值为 0.0 - 1.0】
}


// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {

	// ********************************************************************************************** //
	// ************                                                                        ********** //

	// Image
	//........
	const auto aspect_ratio = 16.0 / 9.0;  // 最终成像的宽高比
	const int image_width = 400;  // 图像宽度（像素个数）【调整这个可以自由地调整窗口大小~】
	const int image_height = static_cast<int>(image_width / aspect_ratio);  // 图像高度（像素个数）
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World    整个场景~
	//.........
	Hittable_list world;  // 报错解决：hit() 重写时形参列表不一样
	
	// *** 定义材质  计数=1
	auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0));
	auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
	auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.2);
	auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

	// *** 添加物体
	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

	// Camera
	Camera camera;

	// Render
	// ......
	std::ofstream fout("output/Image14.ppm");  // ppm文件  里面是像素的RGB
	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";  // .ppm 文件的格式信息

	for (int y = image_height - 1; y >= 0; --y) {  // y从下到上
		std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
		for (int x = 0; x < image_width; ++x) {  // x从左到右

			// 反走样
			// .......
			Color pixel_color(0, 0, 0);
			
			// 对像素进行周边采样与修改    反走样
			for (int s = 0; s < samples_per_pixel; ++s) {
				
				// 以下两行相当于在一个像素左边和上边进行随机采样
				auto u = TYPE(x + random_double()) / (image_width - 1);  // u：成像上像素的 x 坐标（小数）
				auto v = TYPE(y + random_double()) / (image_height - 1);  // v：成像上像素的 y 坐标（小数）
			
				Ray r = camera.get_ray(u, v);  // 从相机位置打到采样处的光线（原点一样：光线.origin = 相机.origin）
				pixel_color += ray_color(r, world, max_depth);
				// 对成像上的每一个像素发出光线，打在场景上，并计算像素颜色.
				// 原本的像素颜色 += 光的颜色，最终累加，合成该像素的颜色

			}
			write_color(fout, pixel_color, samples_per_pixel);  // 写入ppm文件. 
			// [注意：一个像素颜色的写入放在采样循环外面...]
		}
		fout << "\n";  // 写入ppm文件
	}
	std::cerr << "\nDone.\n" << std::endl;
	std::cout << "End." << std::endl;

	// >>>................................ End ..................................<<<
	// *****************************************************************************

	// End the program
	return 0;
}
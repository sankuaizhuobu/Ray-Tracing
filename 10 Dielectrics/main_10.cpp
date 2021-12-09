// main_8.cpp

#include "include/rtweekend.h"
#include "include/Color.h"
#include "include/Hittable_list.h"
#include "include/Sphere.h"
#include "include/Camera.h"
#include "include/Material.h"

#include <iostream>
#include <fstream>


Color ray_color(const Ray& r, const Hittable& world, int depth) {  // ע�����ص����� RGB ֵ����0.0-1.0��С��
	
	Hit_record rec;

	// *** �ݹ����  ������һ���ݹ���� ***
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0) {
		return Color(0, 0, 0);
	}

	if (world.hit(r, 0.001, infinity, rec)) {  // ���ڳ����ϵĻ������ؼ����������ֵ

		//Point3 target = rec.p + rec.normal + random_in_unit_sphere();  // ��λ���е������
		//Point3 target = rec.p + rec.normal + random_unit_vector();  // ��λ�����ϵ������[Lambertian distribution]
		//Point3 target = rec.p + random_in_hemisphere(rec.normal);  // The initial hack
		//Ray r_reflect(rec.p, target - rec.p);  // �õ��������
		//return 0.5 * ray_color(r_reflect, world, depth - 1);  // �ݹ�

		Ray scattered;  // *** ����ɢ��� ***
		Color attenuation;  // *** ����ɢ����˥��ϵ�� ***
		// �����ʲ���ɢ�䣬��ݹ�ɢ��⣻��û��ɢ�䣨ȫ���գ�����ֱ�ӷ��غ�ɫ
		if(rec.materials->scatter(r, rec, scattered, attenuation))
		{
			// ע�ⲻҪ����ɢ����˥��
			return attenuation * ray_color(scattered, world, depth - 1);  // �ݹ�
		}
		return Color(0, 0, 0);
	}

	// ****** �ݹ���� û�д��ڳ����ϵĻ������ر���ɫ ******
	// �� t����ʵ�� y����������ɫֵ��y Ϊ -1 ʱ����Ϊ startValue����ɫ����y Ϊ 1 ʱ����Ϊ endValue��RGB Ϊ�������飩��
	// ���Բ�ֵ
	Vec3 unit_direction = unit_vector(r.direction());  // �����������淶������Ϊ��λ������
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);  // ��ע�⣡����RGBֵΪ 0.0 - 1.0��
}


// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {

	// ********************************************************************************************** //
	// ************                                                                        ********** //

	// Image
	//........
	const auto aspect_ratio = 16.0 / 9.0;  // ���ճ���Ŀ�߱�
	const int image_width = 400;  // ͼ���ȣ����ظ���������������������ɵص������ڴ�С~��
	const int image_height = static_cast<int>(image_width / aspect_ratio);  // ͼ��߶ȣ����ظ�����
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World    ��������~
	//.........
	Hittable_list world;  // ��������hit() ��дʱ�β��б�һ��
	
	// *** �������  ����=1
	auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0));
	auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
	auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.2);
	auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

	// *** �������
	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

	// Camera
	Camera camera;

	// Render
	// ......
	std::ofstream fout("output/Image14.ppm");  // ppm�ļ�  ���������ص�RGB
	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";  // .ppm �ļ��ĸ�ʽ��Ϣ

	for (int y = image_height - 1; y >= 0; --y) {  // y���µ���
		std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
		for (int x = 0; x < image_width; ++x) {  // x������

			// ������
			// .......
			Color pixel_color(0, 0, 0);
			
			// �����ؽ����ܱ߲������޸�    ������
			for (int s = 0; s < samples_per_pixel; ++s) {
				
				// ���������൱����һ��������ߺ��ϱ߽����������
				auto u = TYPE(x + random_double()) / (image_width - 1);  // u�����������ص� x ���꣨С����
				auto v = TYPE(y + random_double()) / (image_height - 1);  // v�����������ص� y ���꣨С����
			
				Ray r = camera.get_ray(u, v);  // �����λ�ô򵽲������Ĺ��ߣ�ԭ��һ��������.origin = ���.origin��
				pixel_color += ray_color(r, world, max_depth);
				// �Գ����ϵ�ÿһ�����ط������ߣ����ڳ����ϣ�������������ɫ.
				// ԭ����������ɫ += �����ɫ�������ۼӣ��ϳɸ����ص���ɫ

			}
			write_color(fout, pixel_color, samples_per_pixel);  // д��ppm�ļ�. 
			// [ע�⣺һ��������ɫ��д����ڲ���ѭ������...]
		}
		fout << "\n";  // д��ppm�ļ�
	}
	std::cerr << "\nDone.\n" << std::endl;
	std::cout << "End." << std::endl;

	// >>>................................ End ..................................<<<
	// *****************************************************************************

	// End the program
	return 0;
}
#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

struct Hit_record;

class Material {
    public:
    // 纯虚函数  是否散射    参数：1、入射光 2、碰撞记录 3、散射光 4、散射衰减
    virtual bool scatter(const Ray& r_in, const Hit_record& rec, 
                        Ray& scattered, Color& attenuation) const = 0;
};

// Lambertian漫反射材质
// 属性1.RGB反射率
class Lambertian: public Material{
public:
    Lambertian(const Color& a): albedo(a) {}
    // 该材质是否散射  并计算：1、碰撞记录 2、散射光线 3、衰减系数
    virtual bool scatter(const Ray& r_in, const Hit_record& rec, Ray& scattered, Color& attenuation) const override 
    {
        // 设置散射方向
        // ...........
        
        // 法一：单位球中的随机点 
        //auto scatter_direction = rec.p + rec.normal + random_in_unit_sphere();
		
        // 法二：半球面上的随机点 [The initial hack, Lambertian distribution的不正确近似]
        //auto scatter_direction = rec.p + random_in_hemisphere(rec.normal);
        
        // 法三：单位球面上的随机点 [Lambertian distribution]
        auto scatter_direction = rec.normal + random_unit_vector();  // 注意这里Hit_record为前向声明，应#include它的定义所在的头文件，否则无法访问rec.normal
        // Catch degenerate scatter direction 抓住退化的散射方向
        if(scatter_direction.near_zero()) {
            scatter_direction = rec.normal;  // 如果散射方向接近于(0,0,0)，则设置为normal
        }
        
        // *** 计算散射光 ***
        scattered = Ray(rec.p, scatter_direction);
        // 衰减系数
        attenuation = albedo;
        return true;
    }
    
public:
    Color albedo;  // RGB 反射率 [反射率+吸收率=1]
};




// 金属材质
// 属性1.RGB反射率  属性2.模糊系数
class Metal: public Material {
public: 
    Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const Ray& r_in, const Hit_record& rec, 
                        Ray& scattered, Color& attenuation) const override
    {
        // 计算反射光线  先单位化入射光线
        Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        // *** 计算散射光 ***
        scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        // 衰减系数
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }

public:
    Color albedo;  // RGB 反射率 [反射率+吸收率=1]
    double fuzz;  // 模糊系数 <=1
};





// 电介质材质
// 属性1.折射率
class Dielectric: public Material {
public: 
    Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(const Ray& r_in, const Hit_record& rec, 
                        Ray& scattered, Color& attenuation) const override
    {
        // *** 衰减系数 ***
        attenuation = Color(1.0, 1.0, 1.0);  // 认为不衰减，全透射
        
        // *** 计算折射率 ***
        // 光线击中外表面：1/ir；光线击中内表面：ir（假设外部是真空）
        double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

        // *** 计算折射光线 ***
        // *** 全反射 or 折射 ***
        Vec3 r_in_unit = unit_vector(r_in.direction());

        double cos_theta = fmin(dot(r_in_unit, rec.normal), 1.0);
        double sin_theta = sqrt(1 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vec3 direction;

        if (cannot_refract) {
            // Must Reflect 全反射
            direction = reflect(r_in_unit, rec.normal);
        } else {
            // Can Refract 发生折射
            direction = refract(r_in_unit, rec.normal, refraction_ratio);
        }
        scattered = Ray(rec.p, direction);
        return true;
    }

public:
    double ir;  // Index of Refraction 折射率
};

#endif
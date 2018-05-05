#ifndef DIELECTRICH
#define DIELECTRICH

#include "material.h"


// 折射函数：
// v: 入射光线方向向量
// n: 折射点法向量
// ni_over_nt：入射介质的折射指数和折射介质的折射指数的比值
// refracted: 折射光线方向向量
// return: 发生折射时返回true
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
	
	if (discriminant > 0)
	{// TODO 待理解
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	//当discriminant小于零，说明折射光线的方向向量无实根，没有折射光线，即出现全反射。
	else return false;
}
float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}
class dielectric :public material {
public:
	dielectric(float ri) :ref_idx(ri) {}
	// r_in: 入射光线
	// rec: 入射点
	// attenuation: 介质的衰减变量
	// scattered: 折射光线
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(),rec.normal);
		float ni_over_nt;//入射介质的折射指数和折射介质的折射指数的比值
		
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;//散射光线方向向量
		float reflect_prob;
		float cosine;
		if (dot(r_in.direction(), rec.normal) > 0)
		{//光线的方向向量和球的法向量的点乘大于零，说明光线是从球体内部射入空气。所以入射时的法向量与球的法向量方向相反；
		 //ref_idx是指光密介质的折射指数和光疏介质的折射指数的比值，此时入射介质是光密介质，折射介质是光疏介质，所以ni_over_nt=ref_idx
			outward_normal = -rec.normal;//
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal)/r_in.direction().length();
		}
		else 
		{//此时入射时的法向量和球的法向量方向相反，入射介质为光疏介质，折射介质为光密介质，所以ni_over_nt=1.0/ref_idx
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_prob = schlick(cosine, ref_idx);
		}
		else
		{
			//scattered = ray(rec.p, reflected);
			reflect_prob = 1.0;
		}
		if (rand() % (100) / (float)(100)<reflect_prob)
		{
			scattered = ray(rec.p, reflected);
		}
		else {
			scattered = ray(rec.p, refracted);
		}
		return true;
	}
	float ref_idx;
};


#endif
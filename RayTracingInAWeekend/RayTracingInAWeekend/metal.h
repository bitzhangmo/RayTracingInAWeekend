#ifndef METALH
#define METALH

#include "material.h"
class metal :public material {
public:
	metal(const vec3& a,float f) :albedo(a) { if (f < 1)fuzz = f; else fuzz = 1; }
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
	vec3 albedo;
	float fuzz;
};
// 用于计算反射光线方向向量
//
// v：入射光线
// n：入射点法向量
// 返回反射光线方向向量
vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n)*n;
}

bool metal::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
	attenuation = albedo;
	return(dot(scattered.direction(), rec.normal) > 0);
}
#endif
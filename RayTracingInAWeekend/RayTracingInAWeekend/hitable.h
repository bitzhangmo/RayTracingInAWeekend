#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
class material;

struct hit_record {
	float t;//与光线起点的距离t
	vec3 p;//光线与物体接触点的坐标
	vec3 normal;//接触点的法向量
	material *mat_ptr;
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)const = 0;
	/*hit在这里为虚函数，hitable为抽象类，其子类必须实现其虚函数*/

};
#endif
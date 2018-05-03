#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
class material;

struct hit_record {
	float t;//��������ľ���t
	vec3 p;//����������Ӵ��������
	vec3 normal;//�Ӵ���ķ�����
	material *mat_ptr;
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)const = 0;
	/*hit������Ϊ�麯����hitableΪ�����࣬���������ʵ�����麯��*/

};
#endif
#ifndef RAYH
#define RAYH
#include "vec3.h"
class ray//射线
{
	public:
		ray(){}
		ray(const vec3& a, const vec3& b) { A = a; B = b; }
		vec3 origin() const { return A; }//向量起点
		vec3 direction() const { return B; }//向量的方向
		vec3 point_at_parameter(float t)const { return A + t * B; }

		vec3 A;
		vec3 B;

};

#endif
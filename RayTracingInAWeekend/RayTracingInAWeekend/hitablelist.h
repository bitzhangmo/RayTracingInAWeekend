#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list :public hitable {
public:
	hitable_list(){}
	hitable_list(hitable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	hitable **list;//所有能被光线撞击到的物体的列表
	int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;//用于记录当前光线撞击到的物体的信息，包括光线长度t，接触点坐标与法向量n
	bool hit_anything = false;//是否撞击到物体

	double closest_so_far = t_max;//一条光线可以击中多个物体，选取最短（距离相机最近）的点作为有效点
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
		{//如果新的点比当前的点近，则将信息更新为较近的点
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif
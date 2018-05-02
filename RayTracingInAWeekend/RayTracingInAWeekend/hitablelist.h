#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list :public hitable {
public:
	hitable_list(){}
	hitable_list(hitable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	hitable **list;//�����ܱ�����ײ������������б�
	int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;//���ڼ�¼��ǰ����ײ�������������Ϣ���������߳���t���Ӵ��������뷨����n
	bool hit_anything = false;//�Ƿ�ײ��������

	double closest_so_far = t_max;//һ�����߿��Ի��ж�����壬ѡȡ��̣��������������ĵ���Ϊ��Ч��
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
		{//����µĵ�ȵ�ǰ�ĵ��������Ϣ����Ϊ�Ͻ��ĵ�
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif
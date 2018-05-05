#ifndef DIELECTRICH
#define DIELECTRICH

#include "material.h"


// ���亯����
// v: ������߷�������
// n: ����㷨����
// ni_over_nt��������ʵ�����ָ����������ʵ�����ָ���ı�ֵ
// refracted: ������߷�������
// return: ��������ʱ����true
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
	
	if (discriminant > 0)
	{// TODO �����
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	//��discriminantС���㣬˵��������ߵķ���������ʵ����û��������ߣ�������ȫ���䡣
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
	// r_in: �������
	// rec: �����
	// attenuation: ���ʵ�˥������
	// scattered: �������
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(),rec.normal);
		float ni_over_nt;//������ʵ�����ָ����������ʵ�����ָ���ı�ֵ
		
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;//ɢ����߷�������
		float reflect_prob;
		float cosine;
		if (dot(r_in.direction(), rec.normal) > 0)
		{//���ߵķ�����������ķ������ĵ�˴����㣬˵�������Ǵ������ڲ������������������ʱ�ķ���������ķ����������෴��
		 //ref_idx��ָ���ܽ��ʵ�����ָ���͹�����ʵ�����ָ���ı�ֵ����ʱ��������ǹ��ܽ��ʣ���������ǹ�����ʣ�����ni_over_nt=ref_idx
			outward_normal = -rec.normal;//
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal)/r_in.direction().length();
		}
		else 
		{//��ʱ����ʱ�ķ���������ķ����������෴���������Ϊ������ʣ��������Ϊ���ܽ��ʣ�����ni_over_nt=1.0/ref_idx
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
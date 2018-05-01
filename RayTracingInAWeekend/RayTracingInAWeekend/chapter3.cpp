#include "stdafx.h"
#include "ray.h"
#include <iostream>
#include <fstream>
using namespace std;

vec3 color(const ray& r) 
{//以rgb格式返回某点的颜色
	vec3 unit_direction = unit_vector(r.direction());//计算单位向量
	float t = 0.5*(unit_direction.y() + 1.0);//
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}


bool hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discrimnant = b * b - 4 * a*c;
	return (discrimnant > 0);
}

vec3 color_Sphere(const ray& r)
{
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(0, 1, 0);
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main() {
	int nx = 200;
	int ny = 100;
	ofstream outfile(".\\result\\thechapter4.txt", ios_base::out);
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);	//左下角
	vec3 horizontal(4.0, 0.0, 0.0);				//长？（横向）
	vec3 vertical(0.0, 2.0, 0.0);				//宽？（纵向）
	vec3 origin(0.0, 0.0, 0.0);					//起点
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col=color_Sphere(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outfile << ir << " " << ig << " " << ib << "\n";
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}



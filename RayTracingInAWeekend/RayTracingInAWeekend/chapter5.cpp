#include "stdafx.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include <iostream>
#include <fstream>
using namespace std;

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0, (numeric_limits<float>::max)(), rec))
	{
		return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}
/*vec3 color(const ray& r)
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
float discriminant = b * b - 4 * a*c;

return (discriminant > 0);
}
*/

float hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discrimnant = b * b - 4 * a*c;
	if (discrimnant < 0)
	{
		return -1.0;
	}
	else {
		return (-b - sqrt(discrimnant)) / (2.0*a);
	}
}

vec3 color_Sphere(const ray& r)
{
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(0, 1, 0);
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

vec3 color_shade(const ray& r)
{
	float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = unit_vector(r.direction());

	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main() {
	int nx = 200;
	int ny = 100;
	ofstream outfile(".\\result\\thechapter5pictest.txt", ios_base::out);
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);	//左下角
	vec3 horizontal(4.0, 0.0, 0.0);				//长？（横向）
	vec3 vertical(0.0, 2.0, 0.0);				//宽？（纵向）
	vec3 origin(0.0, 0.0, 0.0);					//起点

	hitable *list[2];//可被撞击的两个球
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);

	/*hitable *list[3];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	list[2] = new sphere(vec3(-0.5, 2, -3), 0.3);
	hitable *world = new hitable_list(list, 3);

	测试：可被撞击的三个球
	*/
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 p = (r.point_at_parameter(2.0));
			vec3 col = color(r, world);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outfile << ir << " " << ig << " " << ib << "\n";
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}



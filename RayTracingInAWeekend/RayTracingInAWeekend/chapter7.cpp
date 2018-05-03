#include "stdafx.h"
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "lambertian.h"
#include "metal.h"
#include <iostream>
#include <fstream>
#include "camera.h"
using namespace std;

/*vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		float random0 = rand() % (100) / (float)(100);
		float random1 = rand() % (100) / (float)(100);
		float random2 = rand() % (100) / (float)(100);
		p = 2.0*vec3(random0, random1, random2) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}*/

vec3 color(const ray& r, hitable *world,int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, (numeric_limits<float>::max)(), rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		vec3 tmp = (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
		return tmp;
	}
}



int main() {
	int nx = 200;
	int ny = 100;
	int ns = 100;
	ofstream outfile(".\\result\\thechapter8.txt", ios_base::out);
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	hitable *list[4];//可被撞击的两个球
	list[0] = new sphere(vec3(0, 0, -1), 0.5,new lambertian(vec3(0.8,0.3,0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8,0.8,0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
	hitable *world = new hitable_list(list, 4);
	camera cam;


	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{/*每个像素区域采样ns次*/
				float random = rand() % (100) / (float)(100);
				/*每个像素点的区域是以像素中心点为中心向外距离为1的范围。中心点位置+random相当于在这个像素点的区域内采样*/
				float u = float(i + random) / float(nx);
				float v = float(j + random) / float(ny);

				ray r = cam.get_ray(u, v);
				vec3 p = (r.point_at_parameter(2.0));
				col += color(r, world,0);
				/*将ns个采样的值累加并除以平均值作为该点最终的像素值*/
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outfile << ir << " " << ig << " " << ib << "\n";
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}



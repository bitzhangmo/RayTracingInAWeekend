#include "stdafx.h"
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include <iostream>
#include <fstream>
#include "camera.h"
using namespace std;


vec3 color(const ray& r, hitable *world, int depth)
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

hitable *random_scene()
{
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = rand() % (100) / (float)(100);
			vec3 center((a + 0.9*(rand() % (100) / (float)(100))), 0.2, (b + 0.9*(rand() % (100) / (float)(100))));
			if ((center - vec3(4, 0, 2.0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{
					float random0 = rand() % (100) / (float)(100);
					float random1 = rand() % (100) / (float)(100);
					float random2 = rand() % (100) / (float)(100);
					float random3 = rand() % (100) / (float)(100);
					float random4 = rand() % (100) / (float)(100);
					float random5 = rand() % (100) / (float)(100);
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(random0*random1, random2*random3, random4*random5)));
				}
				else if (choose_mat < 0.95)
				{
					float random0 = rand() % (100) / (float)(100);
					float random1 = rand() % (100) / (float)(100);
					float random2 = rand() % (100) / (float)(100);
					float random3 = rand() % (100) / (float)(100);
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1 + random0), 0.5*(1 + random1), 0.5*(1 + random2)), 0.5*random3));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}

int main() {
	int nx = 2000;
	int ny = 1000;
	int ns = 100;
	ofstream outfile(".\\result\\thechapter12two.txt", ios_base::out);
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	//hitable *list= random_scene();//可被撞击的两个球
	/*list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));*/
	hitable *world = random_scene();
	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 0.0;
	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, 0.7*dist_to_focus);
	/*float R = cos(M_PI / 4);
	hitable *list[2];
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
	hitable *world = new hitable_list(list, 2);*/
	int index = 0;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			index++;
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{/*每个像素区域采样ns次*/
				float random = rand() % (100) / (float)(100);
				/*每个像素点的区域是以像素中心点为中心向外距离为1的范围。中心点位置+random相当于在这个像素点的区域内采样*/
				float u = float(i + random) / float(nx);
				float v = float(j + random) / float(ny);

				ray r = cam.get_ray(u, v);
				vec3 p = (r.point_at_parameter(2.0));
				col += color(r, world, 0);
				/*将ns个采样的值累加并除以平均值作为该点最终的像素值*/
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outfile << ir << " " << ig << " " << ib << "\n";
			//std::cout << ir << " " << ig << " " << ib << "\n";
			std::cout << index << "\n";
		}
	}
}



#include <iostream>
#include "tuple.h"
#include "Canvas.h"
#include "Sphere.h"
#include "intersections.h"

int main()
{
	auto ray_origin = point(0, 0, -15);
	double wall_z = 10;
	double wall_size = 7;
	int canvas_pixels = 100;
	auto pixel_size = wall_size / canvas_pixels;
	auto half = wall_size / 2;

	auto canvas = Canvas(canvas_pixels, canvas_pixels);
	auto colour = color(1, 0, 0);
	Sphere shape;

	for (int y = 0; y < canvas_pixels; y++)
	{
		auto world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels; x++)
		{
			auto world_x = -half + pixel_size * x;
			auto position = point(world_x, world_y, wall_z);
			Ray r(ray_origin, normalize(position - ray_origin));
			auto xs = intersect(shape, r);
			if (hit(xs))
			{
				canvas.write_pixel(x, y, colour);
			}
		}
	}

	canvas.make_ppm("casting.ppm");
}
#include "intersections.h"

#include <iostream>
#include <cmath>

using std::cout;
using std::sqrt;

std::vector<intersection> intersections(const std::initializer_list<intersection>& xs)
{
	return std::vector<intersection>(xs);
}

std::vector<intersection> intersect(const Sphere& sphere, const Ray& ray)
{
	Ray new_ray = ray.transform(sphere.transform().inverse());
	tuple sphere_to_ray = new_ray.origin - point(0, 0, 0);
	double a = dot(new_ray.direction, new_ray.direction);
	double b = 2 * dot(new_ray.direction, sphere_to_ray);
	double c = dot(sphere_to_ray, sphere_to_ray) - 1;
	double d = b * b - 4 * a * c;

	if (d < 0) return intersections({});

	double t1 = (-b - sqrt(d)) / (2 * a);
	double t2 = (-b + sqrt(d)) / (2 * a);
	return intersections({ intersection(t1, sphere), intersection(t2, sphere) });
}

bool intersection::operator==(const intersection& b) const
{
	return t == b.t && _object == b._object;
}
bool intersection::operator<(const intersection& b) const
{
	return t < b.t;
}
bool intersection::operator>(const intersection& b) const
{
	return t > b.t;
}
bool intersection::operator<=(const intersection& b) const
{
	return t <= b.t;
}
bool intersection::operator>=(const intersection& b) const
{
	return t >= b.t;
}

std::optional<intersection> hit(const std::vector<intersection>& xs)
{
	std::optional<intersection> lowest = std::nullopt;
	double lt = std::numeric_limits<double>::infinity();
	for (const intersection& x : xs)
	{
		if (x.t >= 0 && x.t < lt)
		{
			lowest = x;
			lt = x.t;
		}
	}
	return lowest;
}
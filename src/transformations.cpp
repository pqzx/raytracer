#include "transformations.h"

#include <cmath>

using std::cos;
using std::sin;

Matrix transformations::translation(double x, double y, double z)
{
	return Matrix({
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1 });
}

Matrix transformations::scaling(double x, double y, double z)
{
	return Matrix({
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1 });
}

Matrix transformations::rotation_x(double r)
{
	return Matrix({
		1, 0, 0, 0,
		0, cos(r), -sin(r), 0,
		0, sin(r), cos(r), 0,
		0, 0, 0, 1 });
}

Matrix transformations::rotation_y(double r)
{
	return Matrix({
		cos(r), 0, sin(r), 0,
		0, 1, 0, 0,
		-sin(r), 0, cos(r), 0,
		0, 0, 0, 1 });
}

Matrix transformations::rotation_z(double r)
{
	return Matrix({
		cos(r), -sin(r), 0, 0,
		sin(r), cos(r), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 });
}

Matrix transformations::shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
{
	return Matrix({
		1, x_y, x_z, 0,
		y_x, 1, y_z, 0,
		z_x, z_y, 1, 0,
		0, 0, 0, 1 });
}

#pragma once
#include "matrix.h"

namespace transformations
{
	Matrix translation(double x, double y, double z);
	Matrix scaling(double x, double y, double z);
	Matrix rotation_x(double r);
	Matrix rotation_y(double r);
	Matrix rotation_z(double r);
	Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);
}
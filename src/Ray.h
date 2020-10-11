#pragma once

#include "tuple.h"
#include "matrix.h"

class Ray
{
public:
	tuple origin;
	tuple direction;
	Ray(tuple origin, tuple direction);

	tuple position(double time) const;
	Ray transform(const Matrix& transformation) const;
};
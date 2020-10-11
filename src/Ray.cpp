#include "Ray.h"

Ray::Ray(tuple origin, tuple direction) :
	origin(origin), direction(direction) {}

tuple Ray::position(double time) const
{
	return origin + direction * time;
}

Ray Ray::transform(const Matrix& transformation) const
{
	return Ray(transformation * origin, transformation * direction);
}
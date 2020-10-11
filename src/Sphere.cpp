#include "Sphere.h"

#include <iostream>
using std::cout;

Sphere::Sphere()
{}

bool Sphere::operator==(const Sphere& b) const
{
	return this->_transform == b._transform;
}

void Sphere::set_transform(const Matrix& transform)
{
	_transform = transform;
}

Matrix Sphere::transform() const
{
	return _transform;
}

tuple Sphere::normal_at(const tuple& world_point) const
{
	tuple object_point = this->transform().inverse() * world_point;
	tuple object_normal = object_point - point(0, 0, 0);
	tuple world_normal = this->transform().inverse().transpose() * object_normal;
	world_normal.w = 0;
	return normalize(world_normal);
}
#pragma once

#include "Ray.h"

#include<vector>

class Sphere
{
private:
	int id = 0;
	Matrix _transform = Matrix::id(4);
public:
	Sphere();

	bool operator==(const Sphere& b) const;

	void set_transform(const Matrix& transform);
	Matrix transform() const;
	tuple normal_at(const tuple& world_point) const;
};
#include "tuple.h"
#include "constants.h"

#include <cmath>

bool tuple::operator==(const tuple& b) const
{
	return std::abs(x - b.x) < epsilon
		&& std::abs(y - b.y) < epsilon
		&& std::abs(z - b.z) < epsilon
		&& std::abs(w - b.w) < epsilon;
}

tuple tuple::operator+(const tuple& b) const
{
	return tuple{ x + b.x, y + b.y, z + b.z, w + b.w };
}

tuple tuple::operator-(const tuple& b) const
{
	return tuple{x - b.x, y - b.y, z - b.z, w - b.w};
}

tuple tuple::operator-() const
{
	return tuple{-x, -y, -z, -w};
}

tuple tuple::operator*(double b) const
{
	return tuple{x * b, y * b, z * b, w * b};
}

tuple tuple::operator/(double b) const
{
	return tuple{x / b, y / b, z / b, w / b};
}

bool isPoint(const tuple& t)
{
	return t.w == 1;
}

bool isVector(const tuple& t)
{
	return t.w == 0;
}

tuple point(double x, double y, double z)
{
	return tuple{ x, y, z, 1 };
}

tuple vector(double x, double y, double z)
{
	return tuple{ x, y, z, 0 };
}

double magnitude(const tuple& t)
{
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

tuple normalize(const tuple& t)
{
	double mag = magnitude(t);
	return tuple{ t.x / mag, t.y / mag, t.z / mag, t.w / mag };
}

double dot(const tuple& a, const tuple& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

tuple cross(const tuple& a, const tuple& b)
{
	return vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

color color::operator*(double b) const
{
	return color{ x * b, y * b, z * b };
}

color color::operator*(const color& c) const
{
	// hadamard product
	return color{ x * c.x, y * c.y, z * c.z };
}

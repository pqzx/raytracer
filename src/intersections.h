#pragma once
#include "Sphere.h"

#include <vector>
#include <memory>
#include <optional>

using std::shared_ptr;

class intersection
{
private:
	shared_ptr<Sphere> _object;	// intersected object

public:
	double t;		// time of intersection
	intersection(double t, const Sphere& object) : t(t), _object(std::make_shared<Sphere>(object)) {};

	Sphere& object() const { return *_object; }

	bool operator==(const intersection& b) const;
	bool operator<(const intersection& b) const;
	bool operator>(const intersection& b) const;
	bool operator<=(const intersection& b) const;
	bool operator>=(const intersection& b) const;
};

std::vector<intersection> intersections(const std::initializer_list<intersection>& xs);

std::vector<intersection> intersect(const Sphere& sphere, const Ray& ray);

std::optional<intersection> hit(const std::vector<intersection>& xs);
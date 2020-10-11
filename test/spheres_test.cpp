#pragma once
#include "catch.hpp"

#include "Sphere.h"
#include "tuple.h"
#include "Ray.h"
#include "intersections.h"
#include "transformations.h"

#include <iostream>
#include "constants.h"
using std::cout;
using namespace transformations;

void print_vector(std::vector<double> xs)
{
	for (double el : xs)
	{
		cout << el << ", ";
	}
	cout << "\n";
}

TEST_CASE("a ray intersects a sphere at 2 points")
{
	Ray r(point(0, 0, -5), vector(0, 0, 1));
	Sphere s;
	auto xs = intersect(s, r);
	REQUIRE(xs.size() == 2);
	REQUIRE(xs[0].t == 4);
	REQUIRE(xs[1].t == 6);
}

TEST_CASE("a ray intersects a sphere at a tangent")
{
	Ray r(point(0, 1, -5), vector(0, 0, 1));
	Sphere s = Sphere();
	auto xs = intersect(s, r);
	REQUIRE(xs.size() == 2);
	REQUIRE(xs[0].t == 5);
	REQUIRE(xs[1].t == 5);
}

TEST_CASE("a ray misses a sphere")
{
	Ray r(point(0, 2, -5), vector(0, 0, 1));
	Sphere s = Sphere();
	auto xs = intersect(s, r);
	REQUIRE(xs.size() == 0);
}

TEST_CASE("a ray originates inside a sphere")
{
	Ray r(point(0, 0, 0), vector(0, 0, 1));
	Sphere s = Sphere();
	auto xs = intersect(s, r);
	REQUIRE(xs.size() == 2);
	REQUIRE(xs[0].t == -1);
	REQUIRE(xs[1].t == 1);
}

TEST_CASE("a sphere is behind a ray")
{
	Ray r(point(0, 0, 5), vector(0, 0, 1));
	Sphere s = Sphere();
	auto xs = intersect(s, r);
	REQUIRE(xs.size() == 2);
	REQUIRE(xs[0].t == -6);
	REQUIRE(xs[1].t == -4);
}

TEST_CASE("intersect sets the object on the intersection")
{
	Ray r(point(0, 0, -5), vector(0, 0, 1));
	Sphere s = Sphere();
	auto xs = intersect(s, r);
	REQUIRE(xs.size() == 2);
	REQUIRE(xs[0].object() == s);
	REQUIRE(xs[1].object() == s);
}

TEST_CASE("sphere has id matrix as default transformation")
{
	Sphere s;
	REQUIRE(s.transform() == Matrix::id(4));
}

TEST_CASE("can change a sphere's transformation")
{
	Sphere s;
	Matrix t = translation(2, 3, 4);
	s.set_transform(t);
	REQUIRE(s.transform() == t);
}

TEST_CASE("intersecting transformed sphere's with rays")
{
	Ray r(point(0, 0, -5), vector(0, 0, 1));
	Sphere s;

	SECTION("can intersect scaled sphere with ray")
	{
		s.set_transform(scaling(2, 2, 2));
		auto xs = intersect(s, r);
		REQUIRE(xs.size() == 2);
		REQUIRE(xs[0].t == 3);
		REQUIRE(xs[1].t == 7);
	}

	SECTION("can intersect translated sphere with ray")
	{
		s.set_transform(translation(5, 0, 0));
		auto xs = intersect(s, r);
		REQUIRE(xs.size() == 0);
	}
}

TEST_CASE("normals")
{
	Sphere s;

	SECTION("normal at point on x axis")
	{
		tuple n = s.normal_at(point(1, 0, 0));
		REQUIRE(n == vector(1, 0, 0));
	}
	SECTION("normal at point on y axis")
	{
		tuple n = s.normal_at(point(0, 1, 0));
		REQUIRE(n == vector(0, 1, 0));
	}
	SECTION("normal at point on z axis")
	{
		tuple n = s.normal_at(point(0, 0, 1));
		REQUIRE(n == vector(0, 0, 1));
	}
	SECTION("normal at nonaxial point")
	{
		tuple n = s.normal_at(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
		REQUIRE(n == vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	}
	SECTION("normal is a normalized vector")
	{
		tuple n = s.normal_at(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
		REQUIRE(n == normalize(n));
	}
}

TEST_CASE("computing normal on translated sphere")
{
	Sphere s;
	s.set_transform(translation(0, 1, 0));
	tuple n = s.normal_at(point(0, 1.70711, -0.70711));
	REQUIRE(n == vector(0, 0.70711, -0.70711));
}

TEST_CASE("computing normal on transformed sphere")
{
	Sphere s;
	Matrix transform = scaling(1, 0.5, 1) * rotation_z(pi / 5);
	s.set_transform(transform);
	tuple n = s.normal_at(point(0, sqrt(2) / 2, -sqrt(2) / 2));
	REQUIRE(n == vector(0, 0.97014, -0.24254));
}
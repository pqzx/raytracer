#include "catch.hpp"

#include "transformations.h"
#include "tuple.h"
#include "constants.h"

#include <iostream>
using std::cout;
using namespace transformations;

TEST_CASE("translations")
{
	Matrix transform = translation(5, -3, 2);
	tuple p = point(-3, 4, 5);

	SECTION("multiplying by a translation matrix")
	{
		REQUIRE(transform * p == point(2, 1, 7));
	}

	SECTION("multiplying the inverse of a translation matrix")
	{
		Matrix inv = transform.inverse();
		REQUIRE(inv * p == point(-8, 7, 3));
	}

	SECTION("translation does not affect vectors")
	{
		tuple v = vector(-3, 4, 5);
		REQUIRE(transform * v == v);
	}
}

TEST_CASE("scaling")
{
	Matrix transform = scaling(2, 3, 4);
	tuple p = point(-4, 6, 8);
	tuple v = vector(-4, 6, 8);

	SECTION("a scaling matrix applied to a point")
	{
		REQUIRE(transform * p == point(-8, 18, 32));
	}

	SECTION("a scaling matrix applied to a vector")
	{
		REQUIRE(transform * v == vector(-8, 18, 32));
	}

	SECTION("multiplying by the inverse of a scaling matrix")
	{
		Matrix inv = transform.inverse();
		REQUIRE(inv * v == vector(-2, 2, 2));
	}
}

TEST_CASE("reflection is scaling by a negative value")
{
	Matrix transform = scaling(-1, 1, 1);
	tuple p = point(2, 3, 4);
	REQUIRE(transform * p == point(-2, 3, 4));
}

TEST_CASE("rotation around x axis")
{
	tuple p = point(0, 1, 0);
	Matrix half_quarter = rotation_x(pi / 4);
	Matrix full_quarter = rotation_x(pi / 2);

	SECTION("rotating a point around the x axis")
	{
		REQUIRE(half_quarter * p == point(0, sqrt(2) / 2, sqrt(2) / 2));
		REQUIRE(full_quarter * p == point(0, 0, 1));
	}

	SECTION("inverse of an x rotation rotates in opposite direction")
	{
		Matrix inv = half_quarter.inverse();
		REQUIRE(inv * p == point(0, sqrt(2) / 2, -sqrt(2) / 2));
	}
}

TEST_CASE("rotation a point around the y axis")
{
	tuple p = point(0, 0, 1);
	Matrix half_quarter = rotation_y(pi / 4);
	Matrix full_quarter = rotation_y(pi / 2);
	REQUIRE(half_quarter * p == point(sqrt(2) / 2, 0, sqrt(2) / 2));
	REQUIRE(full_quarter * p == point(1, 0, 0));
}

TEST_CASE("rotating a point around z axis")
{
	tuple p = point(0, 1, 0);
	Matrix half_quarter = rotation_z(pi / 4);
	Matrix full_quarter = rotation_z(pi / 2);
	REQUIRE(half_quarter * p == point(-sqrt(2) / 2, sqrt(2) / 2, 0));
	REQUIRE(full_quarter * p == point(-1, 0, 0));
}

TEST_CASE("shearing")
{
	tuple p = point(2, 3, 4);

	SECTION("shearing transformation moves x in proportion to y")
	{
		Matrix transform = shearing(1, 0, 0, 0, 0, 0);
		REQUIRE(transform * p == point(5, 3, 4));
	}

	SECTION("shearing transformation moves x in proportion to z")
	{
		Matrix transform = shearing(0, 1, 0, 0, 0, 0);
		REQUIRE(transform * p == point(6, 3, 4));
	}

	SECTION("shearing transformation moves y in proportion to x")
	{
		Matrix transform = shearing(0, 0, 1, 0, 0, 0);
		REQUIRE(transform * p == point(2, 5, 4));
	}

	SECTION("shearing transformation moves y in proportion to z")
	{
		Matrix transform = shearing(0, 0, 0, 1, 0, 0);
		REQUIRE(transform * p == point(2, 7, 4));
	}

	SECTION("shearing transformation moves z in proportion to x")
	{
		Matrix transform = shearing(0, 0, 0, 0, 1, 0);
		REQUIRE(transform * p == point(2, 3, 6));
	}

	SECTION("shearing transformation moves z in proportion to y")
	{
		Matrix transform = shearing(0, 0, 0, 0, 0, 1);
		REQUIRE(transform * p == point(2, 3, 7));
	}
}

TEST_CASE("chaining transformations")
{
	tuple p = point(1, 0, 1);
	Matrix A = rotation_x(pi / 2);
	Matrix B = scaling(5, 5, 5);
	Matrix C = translation(10, 5, 7);

	SECTION("individual transformations are applied in sequence")
	{
		tuple p2 = A * p;
		REQUIRE(p2 == point(1, -1, 0));

		tuple p3 = B * p2;
		REQUIRE(p3 == point(5, -5, 0));

		tuple p4 = C * p3;
		REQUIRE(p4 == point(15, 0, 7));
	}

	SECTION("chained transformations must be applied in reverse order")
	{
		Matrix transforms = C * B * A;
		REQUIRE(transforms * p == point(15, 0, 7));
	}
	
	SECTION("matrix `apply` convenience method allows transformations to be applied in sequence")
	{
		Matrix transforms = A.apply(B).apply(C);
		REQUIRE(transforms * p == point(15, 0, 7));
	}

}

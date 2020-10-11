#include "catch.hpp"

#include "tuple.h"
#include "Ray.h"
#include "matrix.h"
#include "transformations.h"

using namespace transformations;

TEST_CASE("creating and querying a ray")
{
	tuple origin = point(1, 2, 3);
	tuple direction = vector(4, 5, 6);
	Ray r(origin, direction);
	REQUIRE(r.origin == origin);
	REQUIRE(r.direction == direction);
}

TEST_CASE("computing a point from a distance")
{
	Ray r(point(2, 3, 4), vector(1, 0, 0));
	REQUIRE(r.position(0) == point(2, 3, 4));
	REQUIRE(r.position(1) == point(3, 3, 4));
	REQUIRE(r.position(-1) == point(1, 3, 4));
	REQUIRE(r.position(2.5) == point(4.5, 3, 4));
}

TEST_CASE("transforming rays")
{
	Ray r(point(1, 2, 3), vector(0, 1, 0));

	SECTION("translating a ray shifts the origin")
	{
		Ray r2 = r.transform(translation(3, 4, 5));
		REQUIRE(r2.origin == point(4, 6, 8));
		REQUIRE(r2.direction == vector(0, 1, 0));
	}

	SECTION("scaling a ray affects origin and direction")
	{
		Ray r2 = r.transform(scaling(2, 3, 4));
		REQUIRE(r2.origin == point(2, 6, 12));
		REQUIRE(r2.direction == vector(0, 3, 0));
	}
}
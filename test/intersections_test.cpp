#pragma once
#include "catch.hpp"

#include "intersections.h"

#include <iostream>
using std::cout;

TEST_CASE("an intersection encapsulates time and object")
{
	Sphere s = Sphere();
	intersection i(3.5, s);
	REQUIRE(i.t == 3.5);
	REQUIRE(i.object() == s);
}

TEST_CASE("aggregating intersections")
{
	Sphere s = Sphere();
	intersection i1(1, s);
	intersection i2(2, s);
	auto xs = intersections({ i1, i2 });
	REQUIRE(xs.size() == 2);
	REQUIRE(xs[0].t == 1);
	REQUIRE(xs[1].t == 2);
}

TEST_CASE("hits")
{
	Sphere s = Sphere();

	SECTION("returns intersection with lowest t for all positive t")
	{
		auto i1 = intersection(1, s);
		auto i2 = intersection(2, s);
		auto xs = intersections({ i2, i1 });
		REQUIRE(hit(xs) == i1);
	}

	SECTION("returns intersection with lowest positive t for positive & negative ts")
	{
		auto i1 = intersection(-1, s);
		auto i2 = intersection(1, s);
		auto xs = intersections({ i2, i1 });
		REQUIRE(hit(xs) == i2);
	}

	SECTION("returns nothing for all negative ts")
	{
		auto i1 = intersection(-2, s);
		auto i2 = intersection(-1, s);
		auto xs = intersections({ i2, i1 });
		REQUIRE(hit(xs) == std::nullopt);
	}

	SECTION("returns intersection with lowest nonnegative t")
	{
		auto i1 = intersection(5, s);
		auto i2 = intersection(7, s);
		auto i3 = intersection(-3, s);
		auto i4 = intersection(2, s);
		auto xs = intersections({ i1, i2, i3, i4 });
		REQUIRE(hit(xs) == i4);
	}
}

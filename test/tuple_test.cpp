#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "tuple.h"

TEST_CASE("a tuple with w=1.0 is a point")
{
	tuple a{ 4.3, -4.2, 3.1, 1.0 };
	REQUIRE(a.x == 4.3);
	REQUIRE(a.y == -4.2);
	REQUIRE(a.z == 3.1);
	REQUIRE(a.w == 1.0);
	REQUIRE(isPoint(a) == true);
	REQUIRE(isVector(a) == false);
}

TEST_CASE("a tuple with w=0.0 is a vector")
{
	tuple a{ 4.3, -4.2, 3.1, 0.0 };
	REQUIRE(a.x == 4.3);
	REQUIRE(a.y == -4.2);
	REQUIRE(a.z == 3.1);
	REQUIRE(a.w == 0.0);
	REQUIRE(isPoint(a) == false);
	REQUIRE(isVector(a) == true);
}

TEST_CASE("point() creates tuples with w=1")
{
	auto p = point(4, -4, 3);
	REQUIRE(p == tuple{ 4, -4, 3, 1 });
}

TEST_CASE("vector() creates tuples with w=0")
{
	auto v = vector(4, -4, 3);
	REQUIRE(v == tuple{ 4, -4, 3, 0 });
}

TEST_CASE("adding two tuples")
{
	tuple a1{ 3, -2, 5, 1 };
	tuple a2{ -2, 3, 1, 0 };
	REQUIRE(a1 + a2 == tuple{1, 1, 6, 1});
}

TEST_CASE("subtracting two points")
{
	tuple p1 = point(3, 2, 1);
	tuple p2 = point(5, 6, 7);
	REQUIRE(p1 - p2 == vector(-2, -4, -6));
}

TEST_CASE("subtracting a vector from a point")
{
	tuple p = point(3, 2, 1);
	tuple v = vector(5, 6, 7);
	REQUIRE(p - v == point(-2, -4, -6));
}

TEST_CASE("subtracting two vectors")
{
	tuple v1 = vector(3, 2, 1);
	tuple v2 = vector(5, 6, 7);
	REQUIRE(v1 - v2 == vector(-2, -4, -6));
}

TEST_CASE("subtracting vector from zero vector")
{
	tuple zero = vector(0, 0, 0);
	tuple v = vector(1, -2, 3);
	REQUIRE(zero - v == vector(-1, 2, -3));
}

TEST_CASE("negating a tuple")
{
	tuple a{ 1, -2, 3, -4 };
	REQUIRE(-a == tuple{ -1, 2, -3, 4 });
}

TEST_CASE("multiplying a tuple by a scalar")
{
	tuple a{ 1, -2, 3, -4 };
	REQUIRE(a * 3.5 == tuple{3.5, -7, 10.5, -14});
}

TEST_CASE("multiplying a tuple by a fraction")
{
	tuple a{ 1, -2, 3, -4 };
	REQUIRE(a * 0.5 == tuple{0.5, -1, 1.5, -2});
}

TEST_CASE("dividing a tuple by a scalar")
{
	tuple a{ 1, -2, 3, -4 };
	REQUIRE(a / 2 == tuple{0.5, -1, 1.5, -2});
}

TEST_CASE("computing magnitude of vector(1,0,0)")
{
	tuple v = vector(1, 0, 0);
	REQUIRE(magnitude(v) == 1);
}

TEST_CASE("computing magnitude of vector(0,1,0)")
{
	tuple v = vector(0, 1, 0);
	REQUIRE(magnitude(v) == 1);
}

TEST_CASE("computing magnitude of vector(0,0,1)")
{
	tuple v = vector(0, 0, 1);
	REQUIRE(magnitude(v) == 1);
}

TEST_CASE("computing magnitude of vector(1,2,3)")
{
	tuple v = vector(1, 2, 3);
	REQUIRE(magnitude(v) == sqrt(14));
}

TEST_CASE("computing magnitude of vector(-1,-2,-3)")
{
	tuple v = vector(-1, -2, -3);
	REQUIRE(magnitude(v) == sqrt(14));
}

TEST_CASE("normalizing vector(4,0,0) gives (1,0,0)")
{
	tuple v = vector(4, 0, 0);
	REQUIRE(normalize(v) == vector(1, 0, 0));
}

TEST_CASE("normalizing vector(1,2,3)")
{
	tuple v = vector(1, 2, 3);
	REQUIRE(normalize(v) == vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
}

TEST_CASE("magnitude of normalized vector")
{
	tuple v = vector(1, 2, 3);
	tuple norm = normalize(v);
	REQUIRE(magnitude(norm) == 1);
}

TEST_CASE("dot product of two tuples")
{
	tuple a = vector(1, 2, 3);
	tuple b = vector(2, 3, 4);
	REQUIRE(dot(a, b) == 20);
}

TEST_CASE("cross product of two vectors")
{
	tuple a = vector(1, 2, 3);
	tuple b = vector(2, 3, 4);
	REQUIRE(cross(a, b) == vector(-1, 2, -1));
	REQUIRE(cross(b, a) == vector(1, -2, 1));
}

TEST_CASE("colors are (red, green, blue) tuples")
{
	color a{ -0.5, 0.4, 1.7 };
	REQUIRE(a.red() == -0.5);
	REQUIRE(a.green() == 0.4);
	REQUIRE(a.blue() == 1.7);
}

TEST_CASE("adding colors")
{
	color c1{ 0.9, 0.6, 0.75 };
	color c2{ 0.7, 0.1, 0.25 };
	REQUIRE(c1 + c2 == color{ 1.6, 0.7, 1.0 });
}

TEST_CASE("subtracting colors")
{
	color c1{ 0.9, 0.6, 0.75 };
	color c2{ 0.7, 0.1, 0.25 };
	REQUIRE(c1 - c2 == color{ 0.2, 0.5, 0.5 });
}

TEST_CASE("multiplying color by scalar")
{
	color c{ 0.2, 0.3, 0.4 };
	REQUIRE(c * 2.0 == color{ 0.4, 0.6, 0.8 });
}

TEST_CASE("multiplying colors")
{
	color c1{ 1, 0.2, 0.4 };
	color c2{ 0.9, 1, 0.1 };
	REQUIRE(c1 * c2 == color{ 0.9, 0.2, 0.04 });
}
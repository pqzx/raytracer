#include "catch.hpp"

#include "Canvas.h"

#include <sstream>

TEST_CASE("canvas is created with width and height values")
{
	Canvas c(10, 20);
	REQUIRE(c.get_width() == 10);
	REQUIRE(c.get_height() == 20);
	for (int i = 0; i < c.get_width(); i++)
	{
		for (int j = 0; j < c.get_height(); j++)
		{
			REQUIRE(c.pixel_at(i, j) == color(0, 0, 0));
		}
	}
}

TEST_CASE("writing pixels to a canvas")
{
	Canvas c(10, 20);
	color red{ 1, 0, 0 };
	c.write_pixel(2, 3, red);
	REQUIRE(c.pixel_at(2, 3) == red);
}

TEST_CASE("constructing the ppm header")
{
	Canvas c(5, 3);
	std::string ppm = c.to_ppm();
	std::istringstream iss(ppm);
	std::string line;

	std::getline(iss, line);
	REQUIRE(line == "P3");

	std::getline(iss, line);
	REQUIRE(line == "5 3");

	std::getline(iss, line);
	REQUIRE(line == "255");
}

TEST_CASE("constructing the ppm pixel data")
{
	Canvas c(5, 3);
	color c1(1.5, 0, 0);
	color c2(0, 0.5, 0);
	color c3(-0.5, 0, 1);
	c.write_pixel(0, 0, c1);
	c.write_pixel(2, 1, c2);
	c.write_pixel(4, 2, c3);

	std::string ppm = c.to_ppm();
	std::istringstream iss(ppm);
	std::string line;
	for (int i : {0, 1, 2}) // skip first 3 lines
	{
		std::getline(iss, line);
	}
	std::getline(iss, line);
	REQUIRE(line == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

	std::getline(iss, line);
	REQUIRE(line == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");

	std::getline(iss, line);
	REQUIRE(line == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

TEST_CASE("splitting long lines in PPM files")
{
	Canvas c(10, 2);
	color pixel(1, 0.8, 0.6);
	c.write_all(pixel);
	std::string ppm = c.to_ppm();
	
	std::istringstream iss(ppm);
	std::string line;
	for (int i : {0, 1, 2}) // skip first 3 lines
	{
		std::getline(iss, line);
	}
	std::getline(iss, line);
	REQUIRE(line == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");

	std::getline(iss, line);
	REQUIRE(line == "153 255 204 153 255 204 153 255 204 153 255 204 153");

	std::getline(iss, line);
	REQUIRE(line == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");

	std::getline(iss, line);
	REQUIRE(line == "153 255 204 153 255 204 153 255 204 153 255 204 153");
}
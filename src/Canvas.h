#pragma once
#include "tuple.h"

#include <vector>
#include <memory>
#include <string>


using std::shared_ptr;

class Canvas
{
private:
	int width;
	int height;
	std::vector<std::vector<shared_ptr<color>>> pixels;
	void _write_pixel(int x, int y, shared_ptr<color> color);

public:
	Canvas(int width, int height);
	int get_width() const { return width; }
	int get_height() const { return height; }

	color pixel_at(int x, int y) const;
	void write_pixel(int x, int y, const color& colour);
	void write_all(color const& colour);

	std::string to_ppm() const;
	void make_ppm() const;
	void make_ppm(std::string filename) const;
	
};
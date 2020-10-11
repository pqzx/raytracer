#include "Canvas.h"

#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>


Canvas::Canvas(int width, int height) : width(width), height(height)
{
	shared_ptr<color> black = std::make_shared<color>(color(0, 0, 0));
	pixels.resize(width, std::vector<shared_ptr<color>>(height, black));
}

color Canvas::pixel_at(int x, int y) const
{
	return *pixels[x][y];
}

void Canvas::_write_pixel(int x, int y, shared_ptr<color> color)
{
	pixels.at(x).at(y) = color;
}

void Canvas::write_pixel(int x, int y, const color& colour)
{
	shared_ptr<color> c = std::make_shared<color>(colour);
	_write_pixel(x, y, c);
}

void Canvas::write_all(color const& colour)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			write_pixel(i, j, colour);
		}
	}
}

int double_to_8bit_value(double x)
{
	return std::max(0, std::min(255, static_cast<int>(std::round(x * 255))));
}

std::string Canvas::to_ppm() const
{
	std::stringstream ss;
	// make header
	ss << "P3\n" << width << " " << height << "\n255\n"; // header
	for (int j = 0; j < height; j++)
	{
		std::stringstream line;
		int line_length = 0;
		for (int i = 0; i < width; i++)
		{
			color c = pixel_at(i, j);
			for (double f : {c.x, c.y, c.z})
			{
				int intensity = double_to_8bit_value(f);
				int int_length = std::to_string(intensity).length();
				if (line_length + int_length > 70)
				{
					// append current line to stream and reset line
					std::string line_str = line.str();
					line_str.erase(line_str.length() - 1);
					ss << line_str << "\n";  
					line.str("");
					line.clear();
					line_length = 0;
				}

				line << intensity << " ";
				line_length += int_length + 1;
			}
		}
		// add rest of line to stream
		std::string line_str = line.str();
		line_str.erase(line_str.length() - 1);
		ss << line_str << "\n";
	}
	return ss.str();
}

void Canvas::make_ppm(std::string filename) const
{
	std::string ppm = to_ppm();
	std::ofstream out(filename);
	out << ppm;
	out.close();
}

void Canvas::make_ppm() const
{
	make_ppm("untitled.ppm");
}

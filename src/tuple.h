#pragma once

struct tuple {
	const double x;
	const double y;
	const double z;
	double w;

	bool operator==(const tuple& b) const;
	tuple operator+(const tuple& b) const;
	tuple operator-(const tuple& b) const;
	tuple operator-() const;
	tuple operator*(double b) const;
	tuple operator/(double b) const;

};

bool isPoint(const tuple& t);
bool isVector(const tuple& t);

tuple point(double x, double y, double z);
tuple vector(double x, double y, double z);

double magnitude(const tuple& t);
tuple normalize(const tuple& t);
double dot(const tuple& a, const tuple& b);
tuple cross(const tuple& a, const tuple& b);
#pragma once

#include "tuple.h"

#include <array>
#include <vector>

using std::array;

class Matrix
{
private:
	int dim;
	std::vector<double> m;

public:
	Matrix(std::vector<double> m);

	static Matrix id(int size);

	std::vector<double> get_array() const {
		return m;
	}
	double at(int row, int col) const;
	void set(int row, int col, double value);

	bool operator==(const Matrix& b) const;
	bool operator!=(const Matrix& b) const;
	Matrix operator*(const Matrix& b) const;
	tuple operator*(const tuple& t) const;

	Matrix transpose() const;
	double determinant() const;
	Matrix submatrix(int row, int col) const;
	double minor(int row, int col) const;
	double cofactor(int row, int col) const;
	bool is_invertible() const;
	Matrix inverse() const;

	Matrix apply(const Matrix& transformation) const;
};

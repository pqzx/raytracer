#include "matrix.h"
#include "constants.h"

#include <stdexcept>
#include <iostream>
#include <cmath>

using std::cout;


Matrix::Matrix(std::vector<double> m) : m(m) 
{
	dim = std::round(std::sqrt(m.size()));
}

Matrix Matrix::id(int size)
{
	std::vector<double> arr(size * size, 0);
	for (int i = 0; i < size; i++)
	{
		int position = i * size + i;
		arr[position] = 1;
	}
	return Matrix(arr);
}

double Matrix::at(int row, int col) const
{
	return m[row * dim + col];
}

void Matrix::set(int row, int col, double value)
{
	m[row * dim + col] = value;
}

bool Matrix::operator==(const Matrix& b) const
{
	if (dim != b.dim) { return false; }
	for (int i = 0; i < m.size(); i++)
	{
		if (abs(m[i] - b.m[i]) > epsilon) { return false; }
	}
	return true;
}

bool Matrix::operator!=(const Matrix& b) const
{
	return m != b.m;
}

Matrix Matrix::operator*(const Matrix& b) const
{
	std::vector<double> mat(dim * dim);
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			mat[r * dim + c] = m[r * dim] * b.m[c] + 
				m[r * dim + 1] * b.m[1 * dim + c] +
				m[r * dim + 2] * b.m[2 * dim + c] + 
				m[r * dim + 3] * b.m[3 * dim + c];
		}
	}
	return Matrix(mat);
}
tuple Matrix::operator*(const tuple& t) const
{
	std::vector<double> tup{ t.x, t.y, t.z, t.w };
	double x = 0, y = 0, z= 0, w = 0;
	for (int i = 0; i < dim; i++)
	{
		x += m[i] * tup[i];
		y += m[i + 1 * dim] * tup[i];
		z += m[i + 2 * dim] * tup[i];
		w += m[i + 3 * dim] * tup[i];
	}
	return tuple{ x, y, z, w };

}

Matrix Matrix::transpose() const
{
	std::vector<double> m(dim * dim);
	for (int n = 0; n < dim * dim; n++)
	{
		m[n] = this->at(n % dim, n / dim); // at(col, row)
	}
	return Matrix(m);
}

double Matrix::determinant() const
{
	if (dim == 2)
	{
		return m[0] * m[3] - m[1] * m[2];
	}

	double det = 0;
	for (int i = 0; i < dim; i++)
	{
		det += m[i] * this->cofactor(0, i);
	}
	return det;
}

Matrix Matrix::submatrix(int row, int col) const
{
	int size = dim - (int) 1;
	std::vector<double> arr(size * size);
	int k = 0;
	for (int i = 0; i < m.size(); i++)
	{
		if (i / dim == row or i % dim == col)
		{
			continue;
		}
		arr[k++] = m[i];
	}
	return Matrix(arr);
}

double Matrix::minor(int row, int col) const
{
	return this->submatrix(row, col).determinant();
}

double Matrix::cofactor(int row, int col) const
{
	double minor = this->minor(row, col);
	return (row + col) % 2 == 0 ? minor : -minor;
}

bool Matrix::is_invertible() const
{
	return this->determinant() != 0;
}

Matrix Matrix::inverse() const
{
	if (!this->is_invertible())
	{
		throw std::runtime_error("inverse cannot be applied to non invertible matrix");
	}

	double det = this->determinant();
	std::vector<double> arr(dim * dim);
	for (int n = 0; n < m.size(); n++)
	{
		int row = n / dim;
		int col = n % dim;
		double cofac = this->cofactor(row, col);
		arr[col * dim + row] = cofac / det;
	}
	return Matrix(arr);
}

Matrix Matrix::apply(const Matrix& transformation) const
{
	return transformation * *this;
}

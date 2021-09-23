#pragma once
#include "Tuple.h"
#include <stdexcept>
#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "..\Utils.h"
#include <iomanip>

namespace RayTracer
{
	// for future not hardcoded dimension matrix and how to overload () operator
	//https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op

	/// <summary>
	/// A matrix implementation (defaults to 4x4)
	/// </summary>
	class Matrix
	{				
	private:
		float* data;		
		int columns;
		int rows;
		int maxIndex;		

	public:
		~Matrix()
		{
			delete[] data;
			data = 0;
		}

		// default constructor
		Matrix() : columns(4), rows(4)
		{			
			maxIndex = columns * rows;
			data = new float[maxIndex];

			clear();
		}		

		// parameter constructor
		Matrix(int lColumns, int lRows, float* values = 0)
		{
			columns = lColumns;
			rows = lRows;
			maxIndex = columns * rows;

			if (values == 0)
			{
				data = new float[maxIndex];
				clear();
			}
			else
			{
				data = values;
			}
		}
		
		// Tuple to Matrix constructor
		Matrix(const Tuple& t) : Matrix(1, 4, new float[4] { t.x, t.y, t.z, t.w })
		{
		}

		// copy constructur
		Matrix(const Matrix&other) {
			columns = other.columns;
			rows = other.rows;
			maxIndex = columns * rows;
			data = new float[maxIndex];

			for (int i = 0; i < maxIndex; i++)
			{
				data[i] = other.data[i];
			}
		}

		// assignment operator
		Matrix& operator=(const Matrix& other)
		{
			if (this == &other)
				return *this;

			columns = other.columns;
			rows = other.rows;
			maxIndex = columns * rows;
			data = new float[maxIndex];

			for (int i = 0; i < maxIndex; i++)
			{
				data[i] = other.data[i];
			}

			return *this;
		}

		// () overload to access matrix data
		float operator()(const int& index) const
		{
			if (index < 0 || index > maxIndex - 1)
			{
				std::cout << "invalid matrix coord\n";
				throw std::invalid_argument("invalid matrix coord");
			}
			
			return data[index];
		}

		// () overload to access matrix data
		float operator()(const int& x, const int& y) const
		{
			if (x < 0 || x > columns - 1 || y < 0 || y > rows - 1)
			{
				std::cout << "invalid matrix coord\n";
				throw std::invalid_argument("invalid matrix coord");
			}

			int index = x + y * columns;
			return data[index];
		}

		// () overload to set matrix data
		void operator()(const int& x, const int& y, const float& value) const
		{
			if (x < 0 || x > columns - 1 || y < 0 || y > rows - 1)
			{
				std::cout << "invalid matrix coord\n";
				throw std::invalid_argument("invalid matrix coord");
			}

			int index = x + y * columns;
			data[index] = value;
		}

		int getNumColumns() const { return columns; }
		int getNumRows() const { return rows; }

		// converts the first column of a matrix to a point
		// TODO...maybe add parameter to specify the column
		// TODO...don't assume to be 4 rows
		Tuple toTuple() const
		{
			Tuple t((*this)(0, 0), (*this)(0, 1), (*this)(0, 2), (*this)(0, 3));
			return t;
		}

		// converts the first column of a matrix to a point
		// TODO...maybe add parameter to specify the column
		// TODO...don't assume to be 4 rows
		Point toPoint() const
		{
			Point p((*this)(0, 0), (*this)(0, 1), (*this)(0, 2));
			return p;
		}

		// converts the first column of a matrix to a vector
		// TODO...maybe add parameter to specify the column
		// TODO...don't assume to be 4 rows
		Vector toVector() const
		{
			Vector v((*this)(0, 0), (*this)(0, 1), (*this)(0, 2));
			return v;
		}

		// all elements are 0.0f
		bool isZeroMatrix()
		{
			for (int i = 0; i < maxIndex; i++)
			{
				if (!FloatEquals(data[i], 0.0f)) return false;
			}

			return true;
		}
		
		static Matrix get4x4IdentityMatrix()
		{			
			Matrix m(4, 4, new float[16]{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0 ,0 ,0, 1
				});
			return m;
		}

		static Matrix get4x4TranslationMatrix(const float x, const float y, const float z)
		{
			Matrix m(4, 4, new float[16]{
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1
			});
			return m;
		}
		

		static Matrix get4x4ScalingMatrix(const float x, const float y, const float z)
		{
			Matrix m(4, 4, new float[16]{
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1
				});
			return m;
		}

		static Matrix get4x4RotationMatrix_X(const float r)
		{
			float cosr = std::cos(r);
			float sinr = std::sin(r);

			Matrix m(4, 4, new float[16]{
				1, 0, 0, 0,
				0, cosr, -sinr, 0,
				0, sinr, cosr, 0,
				0, 0, 0, 1
				});
			return m;
		}

		static Matrix get4x4RotationMatrix_Y(const float r)
		{
			float cosr = std::cos(r);
			float sinr = std::sin(r);

			Matrix m(4, 4, new float[16]{
				cosr, 0, sinr, 0,
				0, 1, 0, 0,
				-sinr, 0, cosr, 0,
				0, 0, 0, 1
				});
			return m;
		}

		static Matrix get4x4RotationMatrix_Z(const float r)
		{
			float cosr = std::cos(r);
			float sinr = std::sin(r);

			Matrix m(4, 4, new float[16]{
				cosr, -sinr, 0, 0,
				sinr, cosr, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				});
			return m;
		}

		static Matrix get4x4ShearingMatrix(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy)
		{
			Matrix m(4, 4, new float[16]{
				1,  xy, xz, 0,
				yx, 1,  yz, 0,
				zx, zy, 1, 0,
				0, 0, 0, 1
				});
			return m;
		}

		// equality
		bool operator==(const Matrix& m)
		{
			if (m.columns != columns || m.rows != rows)
				return false;

			for (int i = 0; i < maxIndex; i++)
			{
				if (!FloatEquals(data[i], m(i))) return false;
			}

			return true;
		}

		// inequality
		bool operator!=(const Matrix& m)
		{
			return !(*this == m);
		}

		//             C   R   C   R
		// multiply => K x N * M x K = N x M
		//             4 x 4 * 4 x 4 = 4 x 4
		//             4 x 4 * 1 x 4 = 4 x 1
		Matrix& operator*=(const Matrix& b)
		{				
			if(getNumColumns() != b.getNumRows())
			{
				std::cout << "invalid matrix dimensions for multiply\n";
				throw std::invalid_argument("invalid matrix dimensions for multiply");
			}				

			int cols = b.getNumColumns();
			int rows = getNumRows();
			Matrix m(cols, rows);

			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < cols; c++)
				{
					float sum = 0.0f;
					for (int i = 0; i < rows; i++)
					{
						sum += ((*this)(i, r) * b(c, i));						
					}	
					m(c, r, sum);
				}				
			}			

			*this = m; // ??? better way to do this than copying to *this
			return *this;
			//return m;
		}

		// multiply by tuple
		Matrix& operator*=(Tuple const& t)
		{			
			Matrix b(t);
			return *this *= b;
		}

		Matrix transpose() const
		{
			Matrix mt(getNumColumns(), getNumRows());

			for (int r = 0; r < getNumRows(); r++)
			{
				for (int c = 0; c < getNumColumns(); c++)
				{
					mt(r, c, (*this)(c, r));
				}
			}

			return mt;
		}

		// calculate determinant of a matrix
		float determinant() const
		{
			float d = 0;
			if (getNumColumns() == 2 && getNumRows() == 2)
			{
				d = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));				
			}
			else
			{
				for (int c = 0; c < getNumColumns(); c++)
				{
					d += (*this)(c, 0) * cofactor(0, c);
				}
			}

			return d;
		}

		Matrix submatrix(int row, int col) const
		{
			Matrix m(*this);
			Matrix sub(m.getNumColumns() - 1, m.getNumRows() - 1);

			int ir = 0;
			int ic = 0;
			for (int r = 0; r < m.getNumRows(); r++)
			{
				if (r == row) continue;

				for (int c = 0; c < m.getNumColumns(); c++)
				{
					if (c == col) continue;

					sub(ic, ir, m(c, r));
					ic++;
				}

				ic = 0;
				ir++;
			}

			return sub;
		}

		float minor(int row, int col) const
		{
			Matrix b = submatrix(row, col);
			float d = b.determinant();
			return d;		
		}

		float cofactor(int row, int col) const
		{
			float m = minor(row, col);
			float cf = ((row + col) % 2 == 0) ? m : -m;
			return cf;
		}

		Matrix inverse() const
		{
			float d = determinant();
			if (FloatEquals(d, 0)) {
				std::cout << "matrix cannot be inverted\n";
				throw std::invalid_argument("matrix cannot be inverted");
			}

			Matrix m(*this);

			for (int r = 0; r < m.getNumRows(); r++)
			{
				for (int c = 0; c < m.getNumColumns(); c++)
				{
					// note: not m.cofactor...since we're updating that guy
					float cof = cofactor(r, c);					
					
					// (r, c) in matrix on purpose to perform transpose
					m(r, c, cof / d);
				}
			}

			return m;
		}

		static void print(const Matrix& matrix)
		{
			std::cout << std::fixed << std::setprecision(2);

			for (int y = 0; y < matrix.getNumRows(); y++)
			{
				for (int x = 0; x < matrix.getNumColumns(); x++)
				{
					std::cout << "   |" << std::setw(8) << matrix(x, y);
				}
				std::cout << "   |\n";
			}

			std::cout.unsetf(std::ios::fixed);
		}		

	private:
		void clear(float value = 0.0f)
		{
			for (int i = 0; i < maxIndex; i++)
			{
				data[i] = value;
			}
		}
	};

	Matrix operator*(Matrix const& a, Matrix const& b) 
	{ 
		// create temp so that "this" isn't changed
		Matrix temp(a);
		return temp *= b; 
	}

	Matrix operator*(Matrix& a, Tuple const& t) 
	{
		// create temp so that "this" isn't changed
		Matrix temp(a);
		Matrix b(t);
		return temp *= b;
	}	
}

std::ostream& operator<<(std::ostream& os, const RayTracer::Matrix& matrix)
{
	os << std::fixed << std::setprecision(2);
	
	for (int y = 0; y < matrix.getNumRows(); y++)
	{
		for (int x = 0; x < matrix.getNumColumns(); x++)
		{
			os << "   |" << std::setw(8) << matrix(x, y);
		}
		os << "   |\n";
	}	
	
	os.unsetf(std::ios::fixed);

	return os;
}
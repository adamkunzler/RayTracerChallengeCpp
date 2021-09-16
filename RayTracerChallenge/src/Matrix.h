#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

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
			data = NULL;
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

			if (values == NULL)
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
			if (index < 0  || index > maxIndex - 1)
				throw std::invalid_argument("invalid matrix coord");
			
			return data[index];
		}

		// () overload to access matrix data
		float operator()(const int& x, const int& y) const
		{
			if (x < 0 || x > columns - 1 || y < 0 || y > rows - 1)
				throw std::invalid_argument("invalid matrix coord");

			int index = x + y * columns;
			return data[index];
		}

		// () overload to set matrix data
		void operator()(const int& x, const int& y, const float& value) const
		{
			if (x < 0 || x > columns - 1 || y < 0 || y > rows - 1)
				throw std::invalid_argument("invalid matrix coord");

			int index = x + y * columns;
			data[index] = value;
		}

		int getNumColumns() const { return columns; }
		int getNumRows() const { return rows; }

		// all elements are 0.0f
		bool isZeroMatrix()
		{
			for (int i = 0; i < maxIndex; i++)
			{
				if (!FloatEquals(data[i], 0.0f)) return false;
			}

			return true;
		}

		// get 4x4 identity matrix
		static Matrix get4x4IdentiyMatrix()
		{			
			Matrix m(4, 4, new float[16]{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0 ,0 ,0, 1
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
		Matrix operator*=(const Matrix& b)
		{				
			if(getNumColumns() != b.getNumRows())
				throw std::invalid_argument("invalid matrix dimensions for multiply");

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

	Matrix operator*(Matrix& a, Matrix const& b) { return a *= b; }

	Matrix operator*(Matrix& a, Tuple const& t) 
	{
		Matrix b(t);
		return a *= b;
	}

	Matrix operator*=(Matrix& a, Tuple const& t)
	{
		Matrix b(t);
		return a *= b;
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
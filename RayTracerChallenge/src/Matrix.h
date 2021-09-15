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
		int width;
		int height;
		int maxIndex;

	public:
		~Matrix()
		{
			delete[] data;
			data = NULL;
		}

		// default constructor
		Matrix() : width(4), height(4)
		{			
			maxIndex = width * height;
			data = new float[maxIndex];

			clear();
		}		

		// parameter constructor
		Matrix(int lWidth, int lHeight, float* values = 0)
		{
			width = lWidth;
			height = lHeight;
			maxIndex = width * height;

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
		
		// copy constructur
		Matrix(const Matrix&other) {
			width = other.width;
			height = other.height;
			maxIndex = width * height;
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

			width = other.width;
			height = other.height;
			maxIndex = width * height;
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
			if (x < 0 || x > width - 1 || y < 0 || y > height - 1)				
				throw std::invalid_argument("invalid matrix coord");

			int index = x + y * width;
			return data[index];
		}

		// () overload to set matrix data
		void operator()(const int& x, const int& y, const float& value) const
		{
			if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
				throw std::invalid_argument("invalid matrix coord");

			int index = x + y * width;
			data[index] = value;
		}

		int getWidth() const { return width; }
		int getHeight() const { return height; }

		// all elements are 0.0f
		bool isZeroMatrix()
		{
			for (int i = 0; i < maxIndex; i++)
			{
				if (!FloatEquals(data[i], 0.0f)) return false;
			}

			return true;
		}

		// equality
		bool operator==(const Matrix& m)
		{
			if (m.width != width || m.height != height) 
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

	private:
		void clear(float value = 0.0f)
		{
			for (int i = 0; i < maxIndex; i++)
			{
				data[i] = value;
			}
		}
	};
}

std::ostream& operator<<(std::ostream& os, const RayTracer::Matrix& matrix)
{
	os << std::fixed << std::setprecision(2);
	
	for (int y = 0; y < matrix.getHeight(); y++)
	{
		for (int x = 0; x < matrix.getWidth(); x++)
		{
			os << "   |" << std::setw(8) << matrix(x, y);
		}
		os << "   |\n";
	}	
	
	os.unsetf(std::ios::fixed);

	return os;
}
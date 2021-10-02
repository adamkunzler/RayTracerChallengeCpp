#pragma once

//#include <ostream>
//#include <algorithm>

namespace RayTracer
{
	struct Color
	{
		float r;
		float g;
		float b;

		Color() : r(0.0f), g(0.0f), b(0.0f) {}
		Color(float lr, float lg, float lb) : r(lr), g(lg), b(lb) {}
		Color(float l) : r(l), g(l), b(l) {}
		Color(const Color& copy) : r(copy.r), g(copy.g), b(copy.b) {}

		// assignment
		Color& operator=(const Color& rhs)
		{
			r = rhs.r; g = rhs.g; b = rhs.b;
			return *this;
		}

		// equality
		bool operator==(const Color & rhs) const
		{
			return r == rhs.r && g == rhs.g && b == rhs.b;
		}

		// approximate equality
		bool equals(const Color& rhs) const
		{
			return feq(r, rhs.r) && feq(g, rhs.g) && feq(b, rhs.b);
		}

		// inequality
		bool operator!=(const Color& rhs) const
		{
			return r != rhs.r || g != rhs.g || b != rhs.b;
		}

		// addition
		Color operator+(const Color& rhs) const
		{
			return Color(r + rhs.r, g + rhs.g, b + rhs.b);
		}

		// addition (modify lhs)
		Color& operator+=(const Color& rhs)
		{
			r += rhs.r; g += rhs.g; b += rhs.b;
			return *this;
		}

		// subtraction
		Color operator-(const Color& rhs) const
		{
			return Color(r - rhs.r, g - rhs.g, b - rhs.b);
		}

		// subtraction (modify lhs)
		Color& operator-=(const Color& rhs)
		{
			r -= rhs.r; g -= rhs.g; b -= rhs.b;
			return *this;
		}

		// multiply (hadamard product)
		Color operator*(const Color& rhs) const
		{
			return Color(r * rhs.r, g * rhs.g, b * rhs.b);
		}

		// multiply (hadamard product) (modify lhs)
		Color& operator*=(const Color& rhs)
		{
			r *= rhs.r;  g *= rhs.g;  b *= rhs.b;
			return *this;
		}

		// multiply by scalar
		Color operator*(const float& scalar) const
		{
			return Color(r * scalar, g * scalar, b * scalar);
		}

		// multiply by scalar (modify lhs)
		Color& operator*=(const float& scalar)
		{
			r *= scalar; g *= scalar; b *= scalar;
			return *this;
		}

		// divide by scalar
		Color operator/(const float& scalar) const
		{
			return Color(r / scalar, g / scalar, b / scalar);
		}

		// divide by scalar (modify lhs)
		Color& operator/=(const float& scalar)
		{
			r /= scalar; g /= scalar; b /= scalar;
			return *this;
		}
	};

	// get rgb values from (0 - 255) to (0.0 - 1.0)
	// e.g. rgb(255,255,255) would return Color(1.0f, 1.0f, 1.0f)
	Color rgb(const int r, const int g, const int b)
	{
		return Color (
			std::clamp(r / 256.0f, 0.0f, 1.0f),
			std::clamp(g / 256.0f, 0.0f, 1.0f),
			std::clamp(b / 256.0f, 0.0f, 1.0f)
		);		
	}

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Color& color)
	{
		os << "(" << color.r << ", " << color.g << ", " << color.b << ")";
		return os;
	}
}
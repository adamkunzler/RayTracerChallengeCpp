#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{	
	// assignment
	Color& Color::operator=(const Color& rhs)
	{
		r = rhs.r; g = rhs.g; b = rhs.b;
		return *this;
	}

	// equality
	bool Color::operator==(const Color& rhs) const
	{
		return r == rhs.r && g == rhs.g && b == rhs.b;
	}

	// approximate equality
	bool Color::equals(const Color& rhs) const
	{
		return feq(r, rhs.r) && feq(g, rhs.g) && feq(b, rhs.b);
	}

	// inequality
	bool Color::operator!=(const Color& rhs) const
	{
		return r != rhs.r || g != rhs.g || b != rhs.b;
	}

	// addition
	Color Color::operator+(const Color& rhs) const
	{
		return Color(r + rhs.r, g + rhs.g, b + rhs.b);
	}

	// addition (modify lhs)
	Color& Color::operator+=(const Color& rhs)
	{
		r += rhs.r; g += rhs.g; b += rhs.b;
		return *this;
	}

	// subtraction
	Color Color::operator-(const Color& rhs) const
	{
		return Color(r - rhs.r, g - rhs.g, b - rhs.b);
	}

	// subtraction (modify lhs)
	Color& Color::operator-=(const Color& rhs)
	{
		r -= rhs.r; g -= rhs.g; b -= rhs.b;
		return *this;
	}

	// multiply (hadamard product)
	Color Color::operator*(const Color& rhs) const
	{
		return Color(r * rhs.r, g * rhs.g, b * rhs.b);
	}

	// multiply (hadamard product) (modify lhs)
	Color& Color::operator*=(const Color& rhs)
	{
		r *= rhs.r;  g *= rhs.g;  b *= rhs.b;
		return *this;
	}

	// multiply by scalar
	Color Color::operator*(const float& scalar) const
	{
		return Color(r * scalar, g * scalar, b * scalar);
	}

	// multiply by scalar (modify lhs)
	Color& Color::operator*=(const float& scalar)
	{
		r *= scalar; g *= scalar; b *= scalar;
		return *this;
	}

	// divide by scalar
	Color Color::operator/(const float& scalar) const
	{
		return Color(r / scalar, g / scalar, b / scalar);
	}

	// divide by scalar (modify lhs)
	Color& Color::operator/=(const float& scalar)
	{
		r /= scalar; g /= scalar; b /= scalar;
		return *this;
	}


	// NON-MEMBER FUNCTIONS -------------------------------------------------------------

	// get rgb values from (0 - 255) to (0.0 - 1.0)
	// e.g. rgb(255,255,255) would return Color(1.0f, 1.0f, 1.0f)
	Color rgb(const int r, const int g, const int b)
	{
		return Color(
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
#pragma once

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
		Color& operator=(const Color& rhs);

		// equality
		bool operator==(const Color& rhs) const;

		// approximate equality
		bool equals(const Color& rhs) const;

		// inequality
		bool operator!=(const Color& rhs) const;

		// addition
		Color operator+(const Color& rhs) const;

		// addition (modify lhs)
		Color& operator+=(const Color& rhs);

		// subtraction
		Color operator-(const Color& rhs) const;

		// subtraction (modify lhs)
		Color& operator-=(const Color& rhs);

		// multiply (hadamard product)
		Color operator*(const Color& rhs) const;

		// multiply (hadamard product) (modify lhs)
		Color& operator*=(const Color& rhs);

		// multiply by scalar
		Color operator*(const float& scalar) const;

		// multiply by scalar (modify lhs)
		Color& operator*=(const float& scalar);

		// divide by scalar
		Color operator/(const float& scalar) const;

		// divide by scalar (modify lhs)
		Color& operator/=(const float& scalar);
	};

	// NON-MEMBER FUNCTIONS -------------------------------------------------------------

	// get rgb values from (0 - 255) to (0.0 - 1.0)
	// e.g. rgb(255,255,255) would return Color(1.0f, 1.0f, 1.0f)
	Color rgb(const int r, const int g, const int b);

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Color& color);
}
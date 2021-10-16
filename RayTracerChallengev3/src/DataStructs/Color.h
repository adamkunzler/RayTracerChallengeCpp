#pragma once

namespace RayTracer
{
	struct Color
	{
		double r;
		double g;
		double b;

		Color() : r(0.0), g(0.0), b(0.0) {}
		Color(double lr, double lg, double lb) : r(lr), g(lg), b(lb) {}
		Color(double l) : r(l), g(l), b(l) {}
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
		Color operator*(const double& scalar) const;

		// multiply by scalar (modify lhs)
		Color& operator*=(const double& scalar);

		// divide by scalar
		Color operator/(const double& scalar) const;

		// divide by scalar (modify lhs)
		Color& operator/=(const double& scalar);
	};

	//
	// NON-MEMBER FUNCTIONS -------------------------------------------------------------
	//

	// get rgb values from (0 - 255) to (0.0 - 1.0)
	// e.g. rgb(255,255,255) would return Color(1.0, 1.0, 1.0)
	Color rgb(const int r, const int g, const int b);

	void get32BitColor(const Color& color, int& r, int& g, int& b);

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Color& color);
}

#pragma once
#include <algorithm>
#include "..\Utils.h"
#include <ostream>

namespace RayTracer
{
	/// <summary>
	/// A color represented by RGB with each value in the range of 0.0 to 1.0 inclusive
	/// </summary>
	class Color
	{	
	public:
		float r;
		float g;
		float b;

	public:
		Color() : r(0.0f), g(0.0f), b(0.0f)
		{
		}

		Color(float gray) : r(gray), g(gray), b(gray)
		{
		}

		Color(float lr, float lg, float lb) : r(lr), g(lg), b(lb)
		{}

		Color(const Color& other) {
			r = other.r;
			g = other.g;
			b = other.b;
		}
			
		// assignment operator
		Color& operator=(const Color& other)
		{
			if (this == &other)
				return *this;

			r = other.r;
			g = other.g;
			b = other.b;
			
			return *this;
		}

		//
		// Convert an RGB color in the range of 0 - 255 to a range of 0 - 1
		//
		static Color fromRGB(const int r, const int g, const int b)
		{
			Color c(
				std::clamp(r / 256.0f, 0.0f, 1.0f),
				std::clamp(g / 256.0f, 0.0f, 1.0f),
				std::clamp(b / 256.0f, 0.0f, 1.0f));
			return c;
		}

		bool isBlack() const
		{
			return FloatEquals(r, 0) && FloatEquals(g, 0) && FloatEquals(b, 0);
		}

		bool isWhite() const
		{
			return FloatEquals(r, 1) && FloatEquals(g, 1) && FloatEquals(b, 1);
		}
				
		// Multiply a Color by a Color
		Color operator*=(const Color& other)
		{
			Color c = hadamardProduct(*this, other);
			r = c.r;
			b = c.b;
			g = c.g;
			return *this;
		}

		Color hadamardProduct(Color& a, const Color& b)
		{
			Color c(a.r * b.r, a.g * b.g, a.b * b.b);			
			return c;
		}

		// equality
		bool operator==(const Color& color)
		{
			return FloatEquals(r, color.r) && FloatEquals(g, color.g) && FloatEquals(b, color.b);
		}

		// inequality
		bool operator!=(const Color& color)
		{
			return !(*this == color);
		}

		// Add two Colors		
		Color& operator+=(const Color& other)
		{
			r += other.r;
			g += other.g;
			b += other.b;
			return *this;
		}

		// Subtract two Colors				
		Color& operator-=(const Color& other)
		{
			r -= other.r;
			g -= other.g; 
			b -= other.b;
			return *this;
		}

		// multiply color by a scalar
		Color operator*=(const float& scalar)
		{
			r *= scalar; 
			g *= scalar; 
			b *= scalar;
			return *this;
		}

		// Divide Color by a scalar
		Color& operator/=(const float& scalar)
		{
			r /= scalar;
			g /= scalar;
			b /= scalar;
			return *this;
		}
	};
	
	
	Color operator+(Color a, Color const& b) 
	{ 
		Color temp(a);
		return temp += b; 
	}
	
	Color operator-(Color a, Color const& b) 
	{ 
		Color temp(a);
		return temp -= b; 
	}

	Color operator*(Color& a, Color const& b) 
	{
		Color temp(a);
		return temp *= b; 
	}

	Color operator*(Color a, float const& scalar) 
	{ 
		Color temp(a);
		return temp *= scalar; 
	}
	
	Color operator/(Color a, float const& scalar) 
	{ 
		Color temp(a);
		return temp /= scalar; 
	}
}

std::ostream& operator<<(std::ostream& os, const RayTracer::Color& color)
{
	os << "(" << color.r << ", " << color.g << ", " << color.b << ")";
	return os;
}
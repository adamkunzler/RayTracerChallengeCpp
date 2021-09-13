#pragma once

#include <iostream>
#include "Utils.h"
#include "Tuple.h"

namespace RayTracer
{
	/// <summary>
	/// A color represented by a Tuple
	/// </summary>
	class Color : public Tuple
	{
	public:
		Color() : Tuple()
		{
		}

		Color(float lr, float lg, float lb) : Tuple(lr, lg, lb, 0)
		{}

		Color(float lr, float lg, float lb, float lalpha) : Tuple(lr, lg, lb, lalpha)
		{}

		Color(const Tuple& t) : Tuple(t)
		{}

		const float& red() { return x; }
		const float& green() { return y; }
		const float& blue() { return z; }
		const float& alpha() { return w; }

		Color& operator*=(const float& scalar)
		{
			// not sure why the Tuple function didn't get called
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		//
		// Multiply a Tuple by a scalar
		//
		Color& operator*=(Color& other)
		{
			Color c = hadamardProduct(*this, other);
			x = c.x;
			y = c.y;
			z = c.z;
			w = c.w;
			return *this;
		}

		Color& hadamardProduct(Color& a, Color& b)
		{
			Color c;

			c.x = a.red() * b.red();
			c.y = a.green() * b.green();
			c.z = a.blue() * b.blue();
			c.w = a.w * b.w;
			
			return c;
		}
	};

	//
	// Multiply two Colors
	//
	Color operator*(Color a, Color& b) { return a *= b; }
}
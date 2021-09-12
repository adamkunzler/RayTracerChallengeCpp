#pragma once

#include <typeinfo>
#include <iostream>
#include "Utils.h"

namespace RayTracer
{	

	// -------------------------------------------------------------------------------------------------------------------------------------------

	
	
	// -------------------------------------------------------------------------------------------------------------------------------------------

	/// <summary>
	/// Represents an Ordered List of values (x, y, z, w)
	/// </summary>
	class Tuple
	{		
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Tuple() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
		{
		}

		Tuple(float lx, float ly, float lz, float lw) : x(lx), y(ly), z(lz), w(lw)
		{
		}

		Tuple(const Tuple& other) {			
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}
		
		Tuple& operator=(const Tuple& other)
		{
			if (this == &other)
				return *this;

			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;

			return *this;
		}

		static Tuple createPoint(float lx, float ly, float lz)
		{
			return Tuple(lx, ly, lz, 1.0f);
		}

		static Tuple createVector(float lx, float ly, float lz)
		{
			return Tuple(lx, ly, lz, 0.0f);
		}

		bool isPoint() const { return w == 1.0; }
		bool isVector() const { return w == 0; }

		//
		// Computes the magnitude of a Tuple
		// 
		float magnitude() const
		{			
			return magnitude(*this);
		}

		//
		// Computes the magnitude of a Tuple
		// 
		static float magnitude(const Tuple& t)
		{
			return std::sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
		}

		//
		// Normalize a tuple so that it has a magnitude of 1.0.
		//
		Tuple& normalize()
		{			
			return Tuple::normalize(*this);
		}

		//
		// Normalize a tuple so that it has a magnitude of 1.0.
		//
		static Tuple& normalize(Tuple& t)
		{			
			float m = t.magnitude();			
			Tuple tn(t.x / m, t.y / m, t.z / m, t.w / m);
			return tn;
		}

		//
		// Calculates Dot product of two tuples (the cosine of the angle between 2 unit vectors)
		// 
		// Given a unit vector (magnitude of 1):
		//	-1 = pointing in opposite directions
		//   1 = identical vectors
		//   
		float dot(const Tuple& other) const
		{
			return Tuple::dot(*this, other);
		}

		//
		// Calculates Dot product of two tuples (the cosine of the angle between 2 unit vectors)
		// 
		// Given a unit vector (magnitude of 1):
		//	-1 = pointing in opposite directions
		//   1 = identical vectors
		//   
		static float dot(const Tuple& a, const Tuple& b)
		{
			return a.x * b.x +
				   a.y * b.y +
				   a.z * b.z +
				   a.w * b.w;
		}

		//
		// Calculate Cross Product between two Vectors.
		// 
		// The Cross Product is a Vector that is perpendicular to both input Vectors
		//
		Tuple& cross(const Tuple& other) const
		{
			return Tuple::cross(*this, other);
		}
		
		//
		// Calculate Cross Product between two Vectors.
		// 
		// The Cross Product is a Vector that is perpendicular to both input Vectors
		//
		static Tuple& cross(const Tuple& a, const Tuple& b)
		{
			Tuple t = Tuple::createVector(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
			return t;
		}

		//
		// Compares two Tuples for equality
		// 
		bool operator==(const Tuple& other)
		{									
			return FloatEquals(x, other.x) && FloatEquals(y, other.y) && FloatEquals(z, other.z) && FloatEquals(w, other.w);
		}

		//
		// Implemented by calling !(operator== overload)
		//
		bool operator!=(const Tuple& other)
		{						
			return !(*this == other);
		}			

		//
		// Add two Tuples together
		//
		Tuple& operator+=(const Tuple& other)
		{			
			Tuple t(x + other.x, y + other.y, z + other.z, w + other.w);
			return t;
		}				

		//
		// Subtract two Tuples together		
		// 
		Tuple& operator-=(const Tuple& other)
		{			
			Tuple t(x - other.x, y - other.y, z - other.z, w - other.w);
			return t;
		}

		//
		// Negate Operator - the negative of a Tuple.
		// 
		Tuple& operator-()
		{
			Tuple t(-x, -y, -z, -w);
			return t;
		}
				
		//
		// Multiply a Tuple by a scalar
		//
		Tuple& operator*=(const float& scalar)
		{									
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;			
			return *this;
		}
		
		//
		// Divide a Tuple by a scalar
		//
		Tuple& operator/=(const float& scalar)
		{
			x /= scalar; 
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}	
	};

	// -------------------------------------------------------------------------------------------------------------------------------------------

	/// <summary>
	/// Tuple with a w=1
	/// </summary>
	class Point : public Tuple
	{
	public:
		Point() : Tuple()
		{
		}

		Point(float lx, float ly, float lz) : Tuple(lx, ly, lz, 1)
		{}

		Point(const Tuple& t) : Tuple(t)
		{}
	};

	// -------------------------------------------------------------------------------------------------------------------------------------------

	/// <summary>
	/// Tuple with a w=0
	/// </summary>
	class Vector : public Tuple
	{
	public:
		Vector() : Tuple()
		{
		}

		Vector(float lx, float ly, float lz) : Tuple(lx, ly, lz, 0)
		{}

		Vector(const Tuple& t) : Tuple(t)
		{}
	};	

	//
	// Add two Tuples together
	//
	Tuple operator+(Tuple a, Tuple const& b) { return a += b; }

	//
	// Subtract two Tuples together		
	// 		
	Tuple operator-(Tuple a, Tuple const& b) { return a -= b; }

	//
	// Multiply a Tuple by a scalar
	//
	Tuple operator*(Tuple a, float const& scalar) { return a *= scalar; }

	//
	// Divide a Tuple by a scalar
	//
	Tuple operator/(Tuple a, float const& scalar) { return a /= scalar; }
} // end namespace

// -------------------------------------------------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const RayTracer::Tuple& tuple)
{
	os << "(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ")";
	return os;
}

// -------------------------------------------------------------------------------------------------------------------------------------------
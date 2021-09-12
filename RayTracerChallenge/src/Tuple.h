#pragma once

#include <typeinfo>
#include <iostream>
#include "Utils.h"

namespace RayTracer
{
	/// <summary>
	/// Represents an Ordered List of values (x, y, z, w)
	/// 
	/// Vector has w = 0
	/// Point has w = 1
	/// </summary>
	class Tuple
	{		
	public:
		Tuple(float lx, float ly, float lz, float lw) : x(lx), y(ly), z(lz), w(lw)
		{
		}

		Tuple(const Tuple& other) {
			// i think???
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			this->w = other.w;
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
		// point - is okay
		// vector - is okay
		// tuple - is okay
		//
		float magnitude() const
		{
			//return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
			return magnitude(*this);
		}

		//
		// Computes the magnitude of a Tuple
		// 
		// point - is okay
		// vector - is okay
		// tuple - is okay
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
			//float m = this->magnitude();
			//return *this / m;
			return Tuple::normalize(*this);
		}

		//
		// Normalize a tuple so that it has a magnitude of 1.0.
		//
		static Tuple& normalize(const Tuple& t)
		{
			Tuple t2(t);
			float m = t2.magnitude();			
			return t2 / m;
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
			/*return this->x * other.x + 
				   this->y * other.y + 
				   this->z * other.z + 
				   this->w * other.w;*/
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
			/*Tuple t = Tuple::createVector(
				this->y * other.z - this->z * other.y,
				this->z * other.x - this->x * other.z,
				this->x * other.y - this->y * other.x);
			return t;*/
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
		// Tuple a(1,2,3,0)
		// Tuple b(1,2,3,0)
		// a == b
		//
		bool operator==(const Tuple& other)
		{						
			//std::cout << "Tuple ==\n";
			return FloatEquals(this->x, other.x) && FloatEquals(this->y, other.y) && FloatEquals(this->z, other.z) && FloatEquals(this->w, other.w);
		}

		//
		// Implemented by calling !(operator== overload)
		//
		bool operator!=(const Tuple& other)
		{			
			//std::cout << "Tuple !=\n";
			return !(*this == other);
		}

		//
		// Add two Tuples together		
		// 
		// point + vector is okay => result is point
		// vector + vector is okay => result is vector
		// point + point NOT okay => result is unknown (w would = 2)
		//
		Tuple& operator+(const Tuple& other)
		{			
			//std::cout << "Tuple +\n";
			Tuple t(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
			return t;
		}

		//
		// Subtract two Tuples together		
		// 
		// point - point is okay => result is vector
		// vector - vector is okay => result is vector
		// point - vector is okay => result is point
		// vector - point NOT okay => result is unknown (w = -1)
		//
		Tuple& operator-(const Tuple& other)
		{
			//std::cout << "Tuple -\n";
			Tuple t(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
			return t;
		}

		//
		// Negate Operator - the negative of a Tuple.
		// 
		// tuple - is okay
		// vector - is okay
		// point - NOT okay => result is unknown (w = -1)
		//
		Tuple& operator-()
		{
			Tuple t(-this->x, -this->y, -this->z, -this->w);
			return t;
		}

		//
		// Multiply a Tuple by a scalar
		//
		Tuple& operator*(const float &scalar)
		{
			Tuple t(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
			return t;
		}

		//
		// Multiply a Tuple by a scalar
		//
		Tuple& operator*=(const float& scalar)
		{			
			*this = (*this) * scalar;			
			return *this;
		}

		//
		// Divide a Tuple by a scalar
		//
		Tuple& operator/(const float& scalar)
		{
			Tuple t(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
			return t;
		}

		//
		// Divide a Tuple by a scalar
		//
		Tuple& operator/=(const float& scalar)
		{
			*this = (*this) / scalar;
			return *this;
		}

	public: 
		float x;
		float y;
		float z;
		float w;
	};

	class Point : public Tuple
	{
	public:
		Point(float lx, float ly, float lz) : Tuple(lx, ly, lz, 1)
		{}

		Point(const Tuple& t) : Tuple(t)
		{}
	};

	class Vector : public Tuple
	{
	public:
		Vector(float lx, float ly, float lz) : Tuple(lx, ly, lz, 0)
		{}
		
		Vector(const Tuple& t) : Tuple(t)
		{}
	};
}

std::ostream& operator<<(std::ostream& os, const RayTracer::Tuple& tuple)
{
	os << "(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ")";
	return os;
}
#pragma once

#include <typeinfo>
#include <iostream>
#include "Utils.h"

//
// Represents an Ordered List of values (x, y, z, w)
// 
//
namespace RayTracer
{
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
				
		static Tuple CreatePoint(float lx, float ly, float lz)
		{
			return Tuple(lx, ly, lz, 1.0f);
		}

		static Tuple CreateVector(float lx, float ly, float lz)
		{
			return Tuple(lx, ly, lz, 0.0f);
		}

		bool IsPoint() const { return w == 1.0; }
		bool IsVector() const { return w == 0; }

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
		// vector - point NOT okay => result is unknown (w would = -1)
		//
		Tuple& operator-(const Tuple& other)
		{
			//std::cout << "Tuple -\n";
			Tuple t(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
			return t;
		}

		//
		// Negate Operator - the negative of a Tuple. Does not affect w component.
		//
		Tuple& operator-()
		{
			Tuple t(-this->x, -this->y, -this->z, this->w);
			return t;
		}

	public: 
		float x;
		float y;
		float z;
		float w;
	};
}

std::ostream& operator<<(std::ostream& os, const RayTracer::Tuple& tuple)
{
	os << "(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ")";
	return os;
}
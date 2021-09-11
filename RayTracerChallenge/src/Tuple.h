#pragma once

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
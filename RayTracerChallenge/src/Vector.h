#pragma once

#include "Tuple.h"

namespace RayTracer
{
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
}

std::ostream& operator<<(std::ostream& os, const RayTracer::Vector& vector)
{
	os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return os;
}
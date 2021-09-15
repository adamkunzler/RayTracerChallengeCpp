#pragma once

#include "Tuple.h"

namespace RayTracer
{
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
}

std::ostream& operator<<(std::ostream& os, const RayTracer::Point& point)
{
	os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
	return os;
}
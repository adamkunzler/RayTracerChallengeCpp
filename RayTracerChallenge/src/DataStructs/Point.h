#pragma once

namespace RayTracer
{
	/// <summary>
	/// Tuple with a w=1
	/// </summary>
	class Point : public Tuple
	{
	public:
		Point() : Tuple(0.0f, 0.0f, 0.0f, 1.0f)
		{
		}

		Point(float lx, float ly, float lz) : Tuple(lx, ly, lz, 1.0f)
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
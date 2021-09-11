#pragma once

#include "Tuple.h"


namespace RayTracer
{
	/// <summary>
	/// Represents a point in space. A Tuple with W=1
	/// </summary>
	class Point : public Tuple
	{
	public:
		Point(float lx, float ly, float lz) : Tuple(lx, ly, lz, 1.0)
		{}
	};
}
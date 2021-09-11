#pragma once

#include "Tuple.h"

namespace RayTracer
{
	/// <summary>
	/// Represents direction and magnitude. A tuple with w=0.
	/// </summary>
	class Vector : public Tuple
	{
	public:
		Vector(float lx, float ly, float lz) : Tuple(lx, ly, lz, 0.0)
		{}
	};
}
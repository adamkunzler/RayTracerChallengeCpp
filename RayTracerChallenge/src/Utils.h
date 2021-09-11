#pragma once

#include <cmath>

namespace RayTracer
{
	const float EPSILON(0.00001);

	bool FloatEquals(float a, float b)
	{
		return std::abs(a - b) < EPSILON;
	}
}
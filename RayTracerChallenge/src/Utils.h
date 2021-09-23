#pragma once

namespace RayTracer
{
	const float PI(3.14159265358979323846264338327950288419716939937510f); // 50 digits
	const float EPSILON(0.00001f);

	bool FloatEquals(float a, float b)
	{
		return std::abs(a - b) < EPSILON;
	}
}
#pragma once

#include "Point.h"

namespace RayTracer
{
	struct Sphere
	{
		Point origin;
		float radius;

		Sphere() : origin(Point(0,0,0)), radius(1)
		{
		}

		Sphere(const Point& lOrigin, const float lRadius) : origin(lOrigin), radius(lRadius)
		{}

	};
}
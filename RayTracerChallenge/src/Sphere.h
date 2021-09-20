#pragma once

#include "Point.h"
#include "IShape.h"

namespace RayTracer
{
	struct Sphere : public IShape
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
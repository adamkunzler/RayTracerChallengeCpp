#pragma once

#include "Point.h"
#include "Vector.h"
#include "IShape.h"

namespace RayTracer
{
	struct Sphere : public IShape
	{
		Point origin;
		float radius;

		Sphere() : origin(Point(0,0,0)), radius(1)
		{
			material = Material();
		}

		Sphere(const Point& lOrigin, const float lRadius) : origin(lOrigin), radius(lRadius)
		{}

		Vector normalAt(const Point& worldPoint)
		{
			Point objectPoint = (transform.inverse() * worldPoint).toPoint();
			Vector objectNormal = objectPoint - origin;
			Vector worldNormal = (transform.inverse().transpose() * objectNormal).toVector();
			worldNormal.w = 0;
			return worldNormal.normalize();
		}
	};
}
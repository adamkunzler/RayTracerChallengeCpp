#pragma once

namespace RayTracer
{
	struct Ray
	{	
		Point4 origin;
		Vector4 direction;

		Ray(const Point4& lOrigin, const Vector4& lDirection) : origin(lOrigin), direction(lDirection) {}
		Ray(const Ray& copy) : origin(copy.origin), direction(copy.direction) {}

		Point4 position(const double t) const;
		
		Ray transform(const Matrix4x4& matrix) const;
	};
}

#ifndef RAY_H
#define RAY_H

namespace RayTracer
{
	struct Ray
	{	
		Point4 origin;
		Vector4 direction;

		Ray(const Point4& lOrigin, const Vector4& lDirection) : origin(lOrigin), direction(lDirection) {}
		Ray(const Ray& copy) : origin(copy.origin), direction(copy.direction) {}

		Point4 position(const float t) const;
		
		Ray transform(const Matrix4x4& matrix) const;
	};
}

#endif
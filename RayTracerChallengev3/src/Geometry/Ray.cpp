#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{

	Point4 Ray::position(const double t) const
	{
		return origin + (direction * t);
	}

	Ray Ray::transform(const Matrix4x4& matrix) const
	{
		return Ray(
			origin * matrix,
			direction * matrix
		);
	}

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Ray& r)
	{
		os << "origin (" << r.origin.x << ", " << r.origin.y << ", " << r.origin.z << ")\tdirection: " << r.direction.x << ", " << r.direction.y << ", " << r.direction.z << ")";
		return os;
	}
}
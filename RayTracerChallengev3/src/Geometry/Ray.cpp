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
}
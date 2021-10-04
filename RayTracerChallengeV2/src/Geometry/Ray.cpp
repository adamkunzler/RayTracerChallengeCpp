#include "../Utils.h"
#include "Ray.h"

#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"
#include "../DataStructs/Matrix4x4.h"

namespace RayTracer
{

	Point4 Ray::position(const float t) const
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
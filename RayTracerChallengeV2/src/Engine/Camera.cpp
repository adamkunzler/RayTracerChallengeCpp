#include <cmath>

#include "../Utils.h"
#include "Camera.h"

#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"
#include "../DataStructs/Matrix4x4.h"

#include "../Geometry/Ray.h"

namespace RayTracer
{
	Camera::Camera(int lHSize, int lVSize, float lFov)
	{
		hSize = lHSize;
		vSize = lVSize;
		fov = lFov;
		setTransform(identity4x4());

		float halfView = std::tanf(fov / 2);
		float aspect = (float)hSize / (float)vSize;

		if (aspect >= 1)
		{
			halfWidth = halfView;
			halfHeight = halfView / aspect;
		}
		else
		{
			halfWidth = halfView * aspect;
			halfHeight = halfView;
		}

		pixelSize = (halfWidth * 2) / (float)hSize;
	}

	void Camera::setTransform(const Matrix4x4& lTransform)
	{
		transform = lTransform;
		inverseTransform = inverse(transform);
	}

	Ray Camera::rayForPixel(int x, int y) const
	{
		float xOffset = (x + 0.5f) * pixelSize;
		float yOffset = (y + 0.5f) * pixelSize;

		float wx = halfWidth - xOffset;
		float wy = halfHeight - yOffset;

		Point4 pixel = Point4(wx, wy, -1.0f) * inverseTransform;
		Point4 origin = Point4(0.0f, 0.0f, 0.0f) * inverseTransform;
		Vector4 direction = normalize(pixel - origin);

		return Ray(origin, direction);
	}

	//
	// NON-MEMBER FUNCTIONS ------------------------------------------------------------
	//

	Matrix4x4 viewTransform(const Vector4& from, const Vector4& to, const Vector4& up)
	{
		Vector4 forward = normalize(to - from);
		Vector4 nUp = normalize(up);
		Vector4 left = cross(forward, nUp);
		Vector4 trueUp = cross(left, forward);

		Matrix4x4 orientation(
			left.x, left.y, left.z, 0.0f,
			trueUp.x, trueUp.y, trueUp.z, 0.0f,
			-forward.x, -forward.y, -forward.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Matrix4x4 translationTransform = translation(-from.x, -from.y, -from.z);
		Matrix4x4 vt = orientation * translationTransform;

		return vt;
	}
}
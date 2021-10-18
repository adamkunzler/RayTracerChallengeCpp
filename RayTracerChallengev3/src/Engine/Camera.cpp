#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Camera::Camera(int lHSize, int lVSize, double lFov)
	{
		hSize = lHSize;
		vSize = lVSize;
		fov = lFov;
		setTransform(identity4x4());

		double halfView = std::tan(fov / 2.0);
		double aspect = (double)hSize / (double)vSize;

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

		pixelSize = (halfWidth * 2.0) / (double)hSize;
	}

	void Camera::setTransform(const Matrix4x4& lTransform)
	{
		transform = lTransform;
		inverseTransform = inverse(transform);
	}

	Ray Camera::rayForPixel(const double& x, const double& y) const
	{
		double xOffset = (x + 0.5) * pixelSize;
		double yOffset = (y + 0.5) * pixelSize;

		double wx = halfWidth - xOffset;
		double wy = halfHeight - yOffset;

		Point4 pixel = Point4(wx, wy, -1.0) * inverseTransform;
		Point4 origin = Point4(0.0, 0.0, 0.0) * inverseTransform;
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
			left.x, left.y, left.z, 0.0,
			trueUp.x, trueUp.y, trueUp.z, 0.0,
			-forward.x, -forward.y, -forward.z, 0.0,
			0.0, 0.0, 0.0, 1.0
		);

		Matrix4x4 translationTransform = translation(-from.x, -from.y, -from.z);
		Matrix4x4 vt = orientation * translationTransform;

		return vt;
	}
}
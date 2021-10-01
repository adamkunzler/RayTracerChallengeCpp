#pragma once

#include "../DataStructs/Matrix4x4.h"
#include "../Geometry/Ray.h"

namespace RayTracer
{
	struct Ray;

	struct Camera
	{	
		float hSize;
		float vSize;
		float fov;
		Matrix4x4 transform;

		float pixelSize;
		float halfWidth;
		float halfHeight;

		Camera(float lHSize, float lVSize, float lFov)
		{
			hSize = lHSize;
			vSize = lVSize;
			fov = lFov;
			transform = identity4x4();

			float halfView = std::tanf(fov / 2);
			float aspect = hSize / vSize;

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

			pixelSize = (halfWidth * 2) / hSize;
		}

		Ray rayForPixel(int x, int y) const
		{
			float xOffset = (x + 0.5f) * pixelSize;
			float yOffset = (y + 0.5f) * pixelSize;

			float wx = halfWidth - xOffset;
			float wy = halfHeight - yOffset;
			
			Point4 pixel = Point4(wx, wy, -1.0f) * inverse(transform);			
			Point4 origin = Point4(0.0f, 0.0f, 0.0f) * inverse(transform);
			Vector4 direction = normalize(pixel - origin);

			return Ray(origin, direction);
		}
	};

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
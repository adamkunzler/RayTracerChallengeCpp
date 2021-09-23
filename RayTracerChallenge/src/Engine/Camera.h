#pragma once

#include "../Geometry/Ray.h"

namespace RayTracer
{
	class Ray;

	class Camera
	{	
	public:

		float hSize;
		float vSize;
		float fov;
		Matrix transform;

		float pixelSize;
		float halfWidth;
		float halfHeight;

		Camera(float lHSize, float lVSize, float lFov) : hSize(lHSize), vSize(lVSize), fov(lFov)
		{
			transform = Matrix::get4x4IdentityMatrix();

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
			
			Point pixel = (transform.inverse() * Point(wx, wy, -1)).toPoint();
			Point origin = (transform.inverse() * Point(0,0,0)).toPoint();
			Vector direction = Vector::normalize(pixel - origin);

			Ray r(origin, direction);
			return r;
		}
	};
}
#pragma once

namespace RayTracer
{	
	struct Camera
	{	
	private:
		Matrix4x4 transform;
		Matrix4x4 inverseTransform;

	public:
		int hSize;
		int vSize;
		double fov;
		
		double pixelSize;
		double halfWidth;
		double halfHeight;

		Camera(int lHSize = 800, int lVSize = 600, double lFov = 1.152);

		void setTransform(const Matrix4x4& lTransform);

		Ray rayForPixel(const double& x, const double& y) const;
	};

	Matrix4x4 viewTransform(const Vector4& from, const Vector4& to, const Vector4& up);
}

#ifndef CAMERA_H
#define CAMERA_H

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
		float fov;
		
		float pixelSize;
		float halfWidth;
		float halfHeight;

		Camera(int lHSize = 800, int lVSize = 600, float lFov = 1.152f);

		void setTransform(const Matrix4x4& lTransform);

		Ray rayForPixel(int x, int y) const;
	};

	Matrix4x4 viewTransform(const Vector4& from, const Vector4& to, const Vector4& up);
}

#endif
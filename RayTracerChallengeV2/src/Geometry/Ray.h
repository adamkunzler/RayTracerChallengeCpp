#pragma once

//#include "..\DataStructs\Vector4.h"
//#include "..\DataStructs\Matrix4x4.h"

namespace RayTracer
{
	struct Ray
	{	
		Point4 origin;
		Vector4 direction;

		Ray(const Point4& lOrigin, const Vector4& lDirection) : origin(lOrigin), direction(lDirection) {}
		Ray(const Ray& copy) : origin(copy.origin), direction(copy.direction) {}

		Point4 position(const float t) const
		{
			return origin + (direction * t);
		}
		
		Ray transform(Matrix4x4& matrix) const
		{
			return Ray(
				origin * matrix, 
				direction * matrix
			);
		}		
	};
}
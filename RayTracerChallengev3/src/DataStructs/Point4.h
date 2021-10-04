#ifndef POINT4_H
#define POINT4_H

namespace RayTracer
{		
	struct Point4 : public Vector4
	{
		Point4() : Vector4(0.0f, 0.0f, 0.0f, 1.0f) {}
		Point4(float lx, float ly, float lz) : Vector4(lx, ly, lz, 1.0f) {}
		Point4(const Vector4& v) : Vector4(v.x, v.y, v.z, 1.0f) {}
	};
}

#endif
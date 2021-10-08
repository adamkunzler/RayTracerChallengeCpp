#pragma once

namespace RayTracer
{		
	struct Point4 : public Vector4
	{
		Point4() : Vector4(0.0, 0.0, 0.0, 1.0) {}
		Point4(double lx, double ly, double lz) : Vector4(lx, ly, lz, 1.0) {}
		Point4(const Vector4& v) : Vector4(v.x, v.y, v.z, 1.0) {}
	};
}


#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	double PointLight::intensityAt(const Point4& point, const World& world) const
	{
		return world.isShadowed(position, point) ? 0.0 : 1.0;
	}
}
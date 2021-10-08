#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Color GradientPattern::patternAt(const Point4& p) const
	{
		Color distance = color2 - color1;
		double fraction = p.x - std::floor(p.x);

		return color1 + (distance * fraction);
	}
}
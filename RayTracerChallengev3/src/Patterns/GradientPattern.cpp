#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Color GradientPattern::patternAt(const Point4& p) const
	{
		Color distance = color2 - color1;
		float fraction = p.x - std::floorf(p.x);

		return color1 + (distance * fraction);
	}
}
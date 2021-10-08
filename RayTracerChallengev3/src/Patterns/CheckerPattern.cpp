#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Color CheckerPattern::patternAt(const Point4& p) const
	{
		int val = (int)(std::floor(p.x) + std::floor(p.y) + std::floor(p.z));
		if (val % 2 == 0)
		{
			return color1;
		}

		return color2;
	}
}
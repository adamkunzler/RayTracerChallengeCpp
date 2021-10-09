#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Color StripePattern::patternAt(const Point4& p) const
	{
		int x = (int)std::floor(p.x);
		if (x % 2 == 0)
		{
			return color1;
		}

		return color2;
	}
}
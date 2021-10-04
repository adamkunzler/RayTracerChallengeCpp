#include "../Headers.h"

namespace RayTracer
{
	Color StripePattern::patternAt(const Point4& p) const
	{
		int x = (int)std::floorf(p.x);
		if (x % 2 == 0)
		{
			return color1;
		}

		return color2;
	}
}
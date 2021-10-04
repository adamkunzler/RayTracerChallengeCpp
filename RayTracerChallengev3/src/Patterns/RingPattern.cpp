#include "../Headers.h"

namespace RayTracer
{
	Color RingPattern::patternAt(const Point4& p) const
	{
		int val = (int)std::floor(std::sqrtf(p.x * p.x + p.z * p.z));
		if (val % 2 == 0)
		{
			return color1;
		}

		return color2;
	}
}
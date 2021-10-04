#include <cmath>

#include "../Utils.h"
#include "CheckerPattern.h"

#include "IPattern.h"
#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"

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
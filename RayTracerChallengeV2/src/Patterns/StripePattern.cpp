#include <cmath>

#include "../Utils.h"
#include "StripePattern.h"

#include "IPattern.h"
#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"

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
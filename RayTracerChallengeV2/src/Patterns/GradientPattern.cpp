#include <cmath>

#include "../Utils.h"
#include "GradientPattern.h"

#include "IPattern.h"
#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"

namespace RayTracer
{
	Color GradientPattern::patternAt(const Point4& p) const
	{
		Color distance = color2 - color1;
		float fraction = p.x - std::floorf(p.x);

		return color1 + (distance * fraction);
	}
}
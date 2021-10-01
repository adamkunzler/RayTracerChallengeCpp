#pragma once

//#include "..\DataStructs\Color.h"
//#include "..\DataStructs\Vector4.h"
//#include "IPattern.h"

namespace RayTracer
{
	class StripePattern : public IPattern
	{
	public:
		Color color1;
		Color color2;

		StripePattern() : color1(Color(1.0f)), color2(Color(0.0f)) { }
		StripePattern(Color c1, Color c2) : color1(c1), color2(c2) {}
		~StripePattern() {}

		Color patternAt(const Vector4& p) const
		{
			int x = (int)std::floorf(p.x);
			if (x % 2 == 0)
			{
				return color1;
			}

			return color2;
		}
	};
}
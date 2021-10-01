#pragma once

//#include "..\DataStructs\Color.h"
//#include "..\DataStructs\Vector4.h"
//#include "IPattern.h"

namespace RayTracer
{
	struct RingPattern : public IPattern
	{	
		Color color1;
		Color color2;

		RingPattern() : color1(Color(1.0f)), color2(Color(0.0f)) { }
		RingPattern(Color c1, Color c2) : color1(c1), color2(c2) {}
		~RingPattern() {}

		Color patternAt(const Vector4& p) const
		{
			int val = (int)std::floor(std::sqrtf(p.x * p.x + p.z * p.z));
			if (val % 2 == 0)
			{
				return color1;
			}
			
			return color2;
		}
	};
}
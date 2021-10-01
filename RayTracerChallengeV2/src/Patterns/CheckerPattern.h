#pragma once

//#include "..\DataStructs\Color.h"
//#include "..\DataStructs\Vector4.h"
//#include "IPattern.h"

namespace RayTracer
{
	struct CheckerPattern : public IPattern
	{	
		Color color1;
		Color color2;

		CheckerPattern() : color1(Color(0)), color2(Color(1)) { }
		CheckerPattern(Color c1, Color c2) : color1(c1), color2(c2) { }

		~CheckerPattern() {}

		Color patternAt(const Point4& p) const
		{
			int val = (int)(std::floor(p.x) + std::floor(p.y) + std::floor(p.z));
			if (val % 2 == 0)
			{
				return color1;
			}

			return color2;
		}
	};
}
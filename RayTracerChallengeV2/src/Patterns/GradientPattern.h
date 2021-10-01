#pragma once

//#include "..\DataStructs\Color.h"
//#include "..\DataStructs\Vector4.h"
//#include "IPattern.h"

namespace RayTracer
{
	struct GradientPattern : public IPattern
	{	
		Color color1;
		Color color2;

		GradientPattern() : color1(Color(1.0f)), color2(Color(0.0f)) { }
		GradientPattern(Color c1, Color c2) : color1(c1), color2(c2) {}
		~GradientPattern() {}

		Color patternAt(const Vector4& p) const
		{
			Color distance = color2 - color1;
			float fraction = p.x - std::floorf(p.x);

			return color1 + (distance * fraction);
		}
	};
}
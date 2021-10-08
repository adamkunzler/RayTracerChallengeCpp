#pragma once

namespace RayTracer
{
	struct RingPattern : public IPattern
	{	
		Color color1;
		Color color2;

		RingPattern() : color1(Color(1.0f)), color2(Color(0.0f)) { }
		RingPattern(Color c1, Color c2) : color1(c1), color2(c2) {}
		~RingPattern() {}

		Color patternAt(const Point4& p) const;
	};
}

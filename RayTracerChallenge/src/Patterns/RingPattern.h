#pragma once

namespace RayTracer
{
	class RingPattern : public IPattern
	{
	public:
		Color color1;
		Color color2;

		RingPattern()
		{
			color1 = Color::white();
			color2 = Color::black();
		}

		RingPattern(Color c1, Color c2) : color1(c1), color2(c2) {}

		~RingPattern() {}

		Color patternAt(const Point& p) const
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
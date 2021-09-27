#pragma once

namespace RayTracer
{
	class CheckerPattern : public IPattern
	{
	public:
		Color color1;
		Color color2;

		CheckerPattern()
		{
			color1 = Color::white();
			color2 = Color::black();
		}

		CheckerPattern(Color c1, Color c2) : color1(c1), color2(c2) {}

		~CheckerPattern() {}

		Color patternAt(const Point& p) const
		{
			int val = std::floor(p.x) + std::floor(p.y) + std::floor(p.z);
			if (val % 2 == 0)
			{
				return color1;
			}

			return color2;
		}
	};
}
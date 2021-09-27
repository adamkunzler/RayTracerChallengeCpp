#pragma once

namespace RayTracer
{
	class GradientPattern : public IPattern
	{
	public:
		Color color1;
		Color color2;

		GradientPattern()
		{
			color1 = Color::white();
			color2 = Color::black();
		}

		GradientPattern(Color c1, Color c2) : color1(c1), color2(c2) {}

		~GradientPattern() {}

		Color patternAt(const Point& p) const
		{
			Color distance = color2 - color1;
			float fraction = p.x - std::floorf(p.x);

			return color1 + (distance * fraction);
		}
	};
}
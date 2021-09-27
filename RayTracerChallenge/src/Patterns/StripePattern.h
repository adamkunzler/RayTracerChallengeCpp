#pragma once

namespace RayTracer
{
	class StripePattern : public IPattern
	{
	public:
		Color color1;
		Color color2;

		StripePattern()
		{
			color1 = Color::white();
			color2 = Color::black();
		}

		StripePattern(Color c1, Color c2) : color1(c1), color2(c2) {}

		~StripePattern() {}

		Color patternAt(const Point& p) const
		{
			int x = std::floorf(p.x);
			if (x % 2 == 0)
			{
				return color1;
			}

			return color2;
		}
	};
}
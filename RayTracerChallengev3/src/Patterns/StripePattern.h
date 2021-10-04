#ifndef STRIPEPATTERN_H
#define STRIPEPATTERN_H

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

		Color patternAt(const Point4& p) const;
	};
}

#endif
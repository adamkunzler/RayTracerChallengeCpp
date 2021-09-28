#pragma once

namespace RayTracer
{
	class TestPattern : public IPattern
	{
	public:				
		TestPattern()
		{			
		}		

		~TestPattern() {}

		Color patternAt(const Point& p) const
		{			
			return Color(p.x, p.y, p.z);
		}
	};
}
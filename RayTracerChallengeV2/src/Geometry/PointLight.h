#pragma once

namespace RayTracer
{			
	struct PointLight
	{	
		Point4 position;
		Color intensity;
	
		PointLight() { }
		PointLight(const Point4& lPosition, const Color& lIntensity) : position(lPosition), intensity(lIntensity) { }
	};
}

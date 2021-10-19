#pragma once

namespace RayTracer
{			
	struct PointLight : public ILight
	{			
					
		PointLight(const Point4& lPosition, const Color& lIntensity) : ILight(lPosition, lIntensity) { }		

		double intensityAt(const Point4& point, const World& world) const;
	};
}

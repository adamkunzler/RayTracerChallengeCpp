#pragma once

namespace RayTracer
{
	struct World;

	struct ILight
	{
		Point4 position;
		Color intensity;
		
		ILight(const Point4& lPosition, const Color& lIntensity) : position(lPosition), intensity(lIntensity) {}
		virtual ~ILight() {}
				
		virtual double intensityAt(const Point4& point, const World& world) const = 0;
	};
}
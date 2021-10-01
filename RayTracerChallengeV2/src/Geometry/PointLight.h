#pragma once

namespace RayTracer
{			
	struct PointLight
	{	
		Vector4 position;
		Color intensity;
	
		PointLight() { }
		PointLight(const Vector4& lPosition, const Color& lIntensity) : position(lPosition), intensity(lIntensity) { }			
	};
}

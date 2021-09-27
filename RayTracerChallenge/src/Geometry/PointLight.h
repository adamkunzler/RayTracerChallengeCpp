#pragma once

#include "../Patterns/IPattern.h"

namespace RayTracer
{			
	class PointLight
	{
	public:
		Point position;
		Color intensity;
	
		PointLight()
		{
		}

		PointLight(const Point& lPosition, const Color& lIntensity) : position(lPosition), intensity(lIntensity)
		{
		}	

		Color phong(const Material& m, const IShape& shape, const Point& p, const Vector& eye, const Vector& normalV, bool inShadow) const
		{
			Color ambient;
			Color diffuse;
			Color specular;

			Color baseColor = m.color;

			if(m.pattern)
			{ 
				baseColor = m.pattern->patternAt(shape, p);
			}

			// combine surface color with lights color/intensity
			Color effectiveColor = intensity * baseColor;
			
			// find the direction to the light source
			Vector lightV = (position - p).normalize();

			// compute the ambient contriubtion
			ambient = effectiveColor * m.ambient;
			if (inShadow)
			{
				// skip diffuse and specular if in shadow
				return ambient;
			}

			// lightDotNormal represents the cosine of the angle betwen
			// the light vector and the normal vector. A negative number 
			// means the light is on the other side of the surface
			float lightDotNormal = lightV.dot(normalV);
			if (lightDotNormal < 0)
			{
				diffuse = Color(0, 0, 0);
				specular = Color(0, 0, 0);
			}
			else
			{ 
				// compute the diffuse contribution
				diffuse = effectiveColor * m.diffuse * lightDotNormal;

				// reflectDotEye represents the cosine of the angle between the reflection
				// vector and the eye vector. A negative number means the light reflects 
				// away from the eye				
				Vector negLightV = -lightV;
				Vector reflectV = negLightV.reflect(normalV);
				float reflectDotEye = reflectV.dot(eye);
				if (reflectDotEye <= 0) 
				{
					specular = Color(0, 0, 0);
				}
				else
				{
					// compute specular contribution
					float factor = std::pow(reflectDotEye, m.shininess);					
					specular = intensity * (m.specular * factor);					
				}
			}
			
			Color finalColor = ambient + diffuse + specular;			
			return finalColor;			
		}
	};
}

std::ostream& operator<<(std::ostream& os, const RayTracer::PointLight& pointLight)
{
	os << "Position: (" << pointLight.position.x << ", " << pointLight.position.y << ", " << pointLight.position.z << ")";
	os << "\nIntensity : (" << pointLight.intensity.r << ", " << pointLight.intensity.g << ", " << pointLight.intensity.b << ")";
	return os;
}
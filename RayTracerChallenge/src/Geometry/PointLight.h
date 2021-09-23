#pragma once

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

		Color phong(const Material& m, const Point& p, const Vector& eye, const Vector& normalV)
		{
			Color ambient;
			Color diffuse;
			Color specular;

			// combine surface color with lights color/intensity
			Color effectiveColor = intensity * m.color;
			
			// find the direction to the light source
			Vector lightV = (position - p).normalize();

			// compute the ambient contriubtion
			ambient = effectiveColor * m.ambient;

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
				//Vector negLightV = -lightV; // doesn't work...specular highlight doesn't show up
				Vector negLightV = lightV;
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
					//std::cout << "  s->" << specular.r;
				}
			}

			//Color finalColor = specular;
			Color finalColor = ambient + diffuse + specular;
			//std::cout << "\n" << finalColor;
			return finalColor;
			//return specular;
		}
	};
}

std::ostream& operator<<(std::ostream& os, const RayTracer::PointLight& pointLight)
{
	os << "Position: (" << pointLight.position.x << ", " << pointLight.position.y << ", " << pointLight.position.z << ")";
	os << "\nIntensity : (" << pointLight.intensity.r << ", " << pointLight.intensity.g << ", " << pointLight.intensity.b << ")";
	return os;
}
#pragma once
#include "..\DataStructs\Color.h"

namespace RayTracer
{
	class Material
	{
	public:		
		Color color;
		float ambient;
		float diffuse;
		float specular;
		float shininess;

	public:		
		Material()
		{
			color = Color(1, 1, 1);
			ambient = 0.1f;
			diffuse = 0.9f;
			specular = 0.9f;
			shininess = 200.0f;
		}

		Material(const Color& lColor, const float& lAmbient, const float& lDiffuse, const float& lSpecular, const float& lShininess) :
			color(lColor), ambient(lAmbient), diffuse(lDiffuse), specular(lSpecular), shininess(lShininess)
		{
		}

		bool operator==(const Material& m)
		{
			return (color == m.color)
				&& RayTracer::FloatEquals(ambient, m.ambient)
				&& FloatEquals(diffuse, m.diffuse)
				&& FloatEquals(specular, m.specular)
				&& FloatEquals(shininess, m.shininess);
		}

		bool operator!=(const Material& m)
		{
			return !((*this) == m);
		}
	};
}

#pragma once
#include "..\DataStructs\Color.h"

namespace RayTracer
{	
	class IPattern;

	class Material
	{
	public:		
		Color color;
		float ambient;
		float diffuse;
		float specular;
		float shininess;
		IPattern* pattern;
		float reflective; // 0 non reflective, 1 mirror

	public:		
		Material()
		{
			color = Color(1, 1, 1);
			ambient = 0.1f;
			diffuse = 0.9f;
			specular = 0.9f;
			shininess = 200.0f;
			pattern = NULL;
			reflective = 0.0f;
		}
		
		Material(const Material& m)
		{
			color = Color(m.color.r, m.color.g, m.color.b);
			ambient = m.ambient;
			diffuse = m.diffuse;
			specular = m.specular;
			shininess = m.shininess;
			pattern = m.pattern;
			reflective = m.reflective;
		}

		~Material() 
		{			
		}

		bool operator==(const Material& m)
		{
			return (color == m.color)
				&& RayTracer::FloatEquals(ambient, m.ambient)
				&& FloatEquals(diffuse, m.diffuse)
				&& FloatEquals(specular, m.specular)
				&& FloatEquals(shininess, m.shininess)
				&& FloatEquals(reflective, m.reflective);
		}

		bool operator!=(const Material& m)
		{
			return !((*this) == m);
		}
	};
}

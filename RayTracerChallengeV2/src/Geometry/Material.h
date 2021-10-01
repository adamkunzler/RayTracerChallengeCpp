#pragma once

//#include "../DataStructs/Color.h"
//#include "../Patterns/IPattern.h"

namespace RayTracer
{		
	struct IPattern;

	struct Material
	{	
		Color color;
		IPattern* pattern;
		float ambient;
		float diffuse;
		float specular;
		float shininess;		
		float reflective; // 0 non reflective, 1 mirror
		float transparency;
		float refractiveIndex;
	
		Material()
		{
			color = Color(1, 1, 1);
			pattern = NULL;
			ambient = 0.1f;
			diffuse = 0.9f;
			specular = 0.9f;
			shininess = 200.0f;			
			reflective = 0.0f;
			transparency = 0.0f;
			refractiveIndex = 1.0f;
		}			
	};
}

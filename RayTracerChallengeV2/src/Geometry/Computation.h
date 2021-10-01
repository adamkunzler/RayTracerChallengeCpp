#pragma once

#include "../Shapes/IShape.h"
//#include "../DataStructs/Vector4.h"

namespace RayTracer
{	
	struct Computation
	{	
		IShape* object;
		float t;
		
		Vector4 point;
		Vector4 overPoint;
		Vector4 underPoint;
		
		bool isInside;
		Vector4 eyeV;
		Vector4 normalV;		
		Vector4 reflectV;

		float n1;
		float n2;
	};
}
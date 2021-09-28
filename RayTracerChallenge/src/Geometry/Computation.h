#pragma once

#include "Intersection.h"

namespace RayTracer
{	
	class Computation
	{
	public:
		IShape* object;
		float t;
		Point point;
		Vector eyeV;
		Vector normalV;
		bool isInside;
		Point overPoint;
		Vector reflectV;
		float n1;
		float n2;
		
		Computation()
		{		
		}		
	};
}
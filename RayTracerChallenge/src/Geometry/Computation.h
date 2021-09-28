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
		Point overPoint;
		Point underPoint;
		Vector eyeV;
		Vector normalV;
		bool isInside;		
		Vector reflectV;
		float n1;
		float n2;
		
		Computation()
		{		
		}		
	};
}
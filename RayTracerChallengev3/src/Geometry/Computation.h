#pragma once

namespace RayTracer
{	
	struct Computation
	{	
		IShape* object;
		double t;
		
		Point4 point;
		Point4 overPoint;
		Point4 farOverPoint;
		Point4 underPoint;
		
		bool isInside;
		Vector4 eyeV;
		Vector4 normalV;		
		Vector4 reflectV;

		double n1;
		double n2;
	};
}

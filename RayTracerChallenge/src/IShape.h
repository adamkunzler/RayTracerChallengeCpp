#pragma once

#include "Matrix.h"

namespace RayTracer
{
	class IShape
	{
	public:
		Matrix transform;

	public:
		IShape() 
		{
			transform = Matrix::get4x4IdentityMatrix();
		}

		virtual ~IShape() {}		
	};
}
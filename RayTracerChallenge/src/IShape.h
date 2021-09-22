#pragma once

#include "Matrix.h"
#include "Material.h"

namespace RayTracer
{
	class IShape
	{
	public:
		Matrix transform;
		Material material;

	public:
		IShape() 
		{
			transform = Matrix::get4x4IdentityMatrix();
		}

		virtual ~IShape() {}		
	};
}
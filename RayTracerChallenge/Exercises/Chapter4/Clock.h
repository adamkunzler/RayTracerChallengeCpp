#pragma once

#include <iostream>
#include "../../src/Color.h"
#include "../../src/Canvas.h"
#include "../../src/Utils.h"
#include "../../src/Tuple.h"
#include "../../src/Point.h"
#include "../../src/Vector.h"
#include "../../src/Matrix.h"

namespace Exercises
{
	namespace Chapter4
	{		
		void Clock()
		{
			std::cout << "\nClock\n";

			const bool isDebug = false;

			const int size = 250;
			float radius = size * (7.0f / 16.0f);
			const int hours = 12;
			const float stepSize = (2 * RayTracer::PI) / hours;

			RayTracer::Canvas canvas(size, size);
			RayTracer::Color color = RayTracer::Color::fromRGB(129, 19, 240); // purple

			RayTracer::Matrix localToWorld = RayTracer::Matrix::get4x4TranslationMatrix(size / 2, size / 2, 0);
			RayTracer::Matrix translate = RayTracer::Matrix::get4x4TranslationMatrix(0, 1, 0); // move to 12:00 position			
			RayTracer::Matrix scale = RayTracer::Matrix::get4x4ScalingMatrix(radius, radius, 1); // scale to radius of clock

			for (int j = 0; j < 1; j++)
			{
				for (int i = 0; i < hours; i++)
				{
					if (isDebug) std::cout << "\n\nHour: " << i << std::endl;
					
					RayTracer::Point p(0, 0, 0); // start at origin					
					RayTracer::Matrix rotate = RayTracer::Matrix::get4x4RotationMatrix_Z(-stepSize * i); // rotate on z-axis
					
					RayTracer::Matrix t = localToWorld * scale * rotate * translate; // translate first, then rotate, then scale, last localToWorld
					RayTracer::Point pt = (t * p).toPoint();
					
					canvas.setPixel((int)pt.x, size - (int)pt.y, color);
				}
			}

			canvas.toPPM("images/chapter4.ppm");
		}
	}
}
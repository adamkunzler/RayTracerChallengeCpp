#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include "../../src/Canvas.h"
#include "../../src/Color.h"
#include "../../src/Sphere.h"
#include "../../src/Point.h"

namespace Exercises
{
	namespace Chapter5
	{		
		void RayTraceSphere()
		{
			std::cout << "\nRay Trace Sphere\n";

			const bool isDebug = true;

			const int size = 128;
			RayTracer::Point rayOrigin(0, 0, -5); // normal
			//RayTracer::Point rayOrigin(0, 0, -9); // far
			//RayTracer::Point rayOrigin(0, 0, -3); // close
			float wallZ(10);
			float wallHeight(7);
			float wallHalf = wallHeight / 2.0f;
			float pixelSize = wallHeight / (float)size;

			RayTracer::Canvas canvas(size, size);
			RayTracer::Color color = RayTracer::Color::fromRGB(129, 19, 240); // purple
			RayTracer::Color missColor = RayTracer::Color::fromRGB(253,242,231); // light orange
			
			RayTracer::Sphere s;
			//s.transform = RayTracer::Matrix::get4x4ScalingMatrix(1, 0.5f, 1); // shrink y
			//s.transform = RayTracer::Matrix::get4x4ScalingMatrix(0.5f, 1, 1); // shrink x
			//s.transform = RayTracer::Matrix::get4x4ShearingMatrix(1, 0, 0, 0, 0,0); // shear			

			if (isDebug)
			{
				std::cout << "\nCanvas Size: " << size;
				std::cout << "\nray Origin: " << rayOrigin;
				std::cout << "\nwallZ: " << wallZ;
				std::cout << "\nwallHeight: " << wallHeight;
				std::cout << "\nwallHalf: " << wallHalf;
				std::cout << "\npixelSize: " << pixelSize;
				std::cout << "\n";
			}
			
			auto start = std::chrono::high_resolution_clock::now();

			for (int y = 0; y < size; y++)
			{
				float worldY = wallHalf - (pixelSize * y);

				for (int x = 0; x < size; x++)
				{
					float worldX = -wallHalf + (pixelSize * x);
					
					// position on the wall
					RayTracer::Point position(worldX, worldY, wallZ);

					// ray from origin to point on the wall
					RayTracer::Vector v = position - rayOrigin;
					RayTracer::Ray r(rayOrigin, v.normalize());

					// check for intersections with sphere
					std::vector<RayTracer::Intersection> inters = r.intersects(s);
					RayTracer::Intersection hit = RayTracer::Intersection::hit(inters);
					if (!hit.isNull())
					{
						// hit the object...set the pixel
						canvas.setPixel(x, y, color);
					}
					else
					{
						canvas.setPixel(x, y, missColor);
					}

					//std::cout << "\n" << (hit.isNull() ? "miss" : "HIT");
				}
			}

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

			canvas.toPPM("images/chapter5.ppm");
		}
	}
}
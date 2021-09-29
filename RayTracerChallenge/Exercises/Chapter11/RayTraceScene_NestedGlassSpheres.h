#pragma once

#include "vector"

using namespace RayTracer;

namespace Exercises
{
	namespace Chapter11
	{
		void RayTraceScene_NestedGlassSpheres()
		{
			std::cout << "\nRay Trace Scene Chapter 11 - Book\n";

			const bool isDebug = false;

			// 400/200
			const int hsize = 200;
			const int vsize = hsize;
			std::cout << hsize << " x " << vsize << " => " << (hsize * vsize) << " pixels\n\n";

			World w;

			//
			// calculate view transform and setup camera			
			//
			Camera camera(hsize, vsize, 0.45f);
			camera.transform = viewTransform(Point(0, 0, -5), Point(0, 0, 0), Vector(0, 1, 0));

			//
			// add the light sources
			//
			PointLight light(Point(2, 10, -5), Color(0.9f));
			w.lights.push_back(light);

			
			Plane wall;
			wall.transform = Matrix::get4x4TranslationMatrix(0, 0, 10)
				* Matrix::get4x4RotationMatrix_X(1.5708f);
			CheckerPattern wallPattern(Color(0.15f, 0.15f, 0.15f), Color(0.85f, 0.85f, 0.85f));
			wall.material.pattern = &wallPattern;
			wall.material.ambient = 0.8f;
			wall.material.diffuse = 0.2f;
			wall.material.specular = 0;
			w.objects.push_back(&wall);

			Sphere ball;
			ball.material.color = Color(1);
			ball.material.ambient = 0;
			ball.material.diffuse = 0;
			ball.material.specular = 0.9f;
			ball.material.shininess = 300;
			ball.material.reflective = 0.9f;
			ball.material.transparency = 0.9f;
			ball.material.refractiveIndex = 1.5f;
			w.objects.push_back(&ball);

			Sphere hollow;
			hollow.transform = Matrix::get4x4ScalingMatrix(0.5f, 0.5f, 0.5f);
			hollow.material.color = Color(1);
			hollow.material.ambient = 0;
			hollow.material.diffuse = 0;
			hollow.material.specular = 0.9f;
			hollow.material.shininess = 300;
			hollow.material.reflective = 0.9f;
			hollow.material.transparency = 0.9f;
			hollow.material.refractiveIndex = 1.0000034f;
			w.objects.push_back(&hollow);

			// run the ray tracer...
			auto start = std::chrono::high_resolution_clock::now();

			Canvas image = render(camera, w);

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

			// save the image to disk
			std::string filename = "images/nestedGlassSpheres_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
			image.toPPM(filename);
		}
	}
}
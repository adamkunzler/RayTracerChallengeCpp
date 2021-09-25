#pragma once

#include "vector";
using namespace RayTracer;

namespace Exercises
{
	namespace Chapter9
	{
		void RayTraceScene()
		{
			std::cout << "\nRay Trace Scene Chapter 9 - Planes\n";

			const bool isDebug = false;

			const int hsize = 100;
			const int vsize = hsize / 2;
			std::cout << hsize << " x " << vsize << " => " << (hsize * vsize) << " pixels";

			World w;

			// add the light
			PointLight light1(Point(-20, 20, -10), Color(1, 1, 1));
			w.lights.push_back(light1);

			// calculate view transform and setup camera			
			Camera camera(hsize, vsize, PI / 3.0f);
			camera.transform = World::viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

			// add the walls/floor		
			Plane floor;
			floor.material.color = Color::fromRGB(180, 205, 205);
			floor.material.specular = 0;
			floor.material.diffuse = 0.97f;
			w.objects.push_back(&floor);

			Plane backWall;
			backWall.transform = Matrix::get4x4TranslationMatrix(0, 0, 50)
				* Matrix::get4x4RotationMatrix_X(-PI / 2);
			backWall.material.color = Color::fromRGB(178, 223, 238);
			backWall.material.specular = 0.2f;			
			w.objects.push_back(&backWall);

			// add the spheres
			Sphere middle;
			middle.transform = Matrix::get4x4TranslationMatrix(-0.5f, 1, 0.5f);
			middle.material.color = Color(0.1f, 1, 0.5f);
			middle.material.diffuse = 0.7f;
			middle.material.specular = 0.3f;
			w.objects.push_back(&middle);

			Sphere right;
			right.transform = Matrix::get4x4TranslationMatrix(1.5f, 0.5f, -0.5f)
				* Matrix::get4x4ScalingMatrix(0.5f, 0.5f, 0.5f);
			right.material.color = Color(0.5f, 1, 0.1f);
			right.material.diffuse = 0.7f;
			right.material.specular = 0.3f;
			w.objects.push_back(&right);

			Sphere left;
			left.transform = Matrix::get4x4TranslationMatrix(-1.5f, 0.33f, -0.75f)
				* Matrix::get4x4ScalingMatrix(0.33f, 0.33f, 0.33f);
			left.material.color = Color(1, 0.8f, 0.1f);
			left.material.diffuse = 0.7f;
			left.material.specular = 0.3f;
			w.objects.push_back(&left);

			// run the ray tracer...
			auto start = std::chrono::high_resolution_clock::now();

			Canvas image = w.render(camera);

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

			// save the image to disk
			std::string filename = "images/chapter9_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
			image.toPPM(filename);
		}
	}
}
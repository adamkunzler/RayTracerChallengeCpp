#pragma once

#include "vector";
using namespace RayTracer;

namespace Exercises
{
	namespace Chapter7
	{
		void RayTraceScene()
		{
			std::cout << "\nRay Trace Sphere\n";

			const bool isDebug = false;
			
			const int hsize = 500;
			const int vsize = hsize / 2;
			std::cout << hsize << " x " << vsize << " => " << (hsize * vsize) << " pixels";

			World w;

			// add the light
			PointLight light1(Point(-10, 10, -10), Color(1, 1, 1));
			w.lights.push_back(light1);

			// calculate view transform and setup camera			
			Camera camera(hsize, vsize, PI / 3.0f);
			camera.transform = World::viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

			// add the walls/floor
			Sphere floor;
			floor.transform = Matrix::get4x4ScalingMatrix(10, 0.01f, 10);
			floor.material.color = Color(1, 0.9f, 0.9f);
			floor.material.specular = 0;
			w.objects.push_back(&floor);

			Sphere wallLeft;
			wallLeft.transform = Matrix::get4x4TranslationMatrix(0, 0, 5)
				* Matrix::get4x4RotationMatrix_Y(-PI / 4)
				* Matrix::get4x4RotationMatrix_X(PI / 2)
				* Matrix::get4x4ScalingMatrix(10, 0.01f, 10);
			wallLeft.material = floor.material;
			w.objects.push_back(&wallLeft);

			Sphere wallRight;
			wallRight.transform = Matrix::get4x4TranslationMatrix(0, 0, 5)
				* Matrix::get4x4RotationMatrix_Y(PI / 4)
				* Matrix::get4x4RotationMatrix_X(PI / 2)
				* Matrix::get4x4ScalingMatrix(10, 0.01f, 10);
			wallRight.material = floor.material;
			w.objects.push_back(&wallRight);

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
			image.toPPM("images/chapter7.ppm");
		}
	}
}
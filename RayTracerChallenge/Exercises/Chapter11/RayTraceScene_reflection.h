#pragma once

#include "vector"

using namespace RayTracer;

namespace Exercises
{
	namespace Chapter11
	{
		void RayTraceScene_Reflection()
		{
			std::cout << "\nRay Trace Scene Chapter 11 - Reflection\n";

			const bool isDebug = false;

			const int hsize = 1024;
			const int vsize = hsize / 2;
			std::cout << hsize << " x " << vsize << " => " << (hsize * vsize) << " pixels\n\n";

			World w;

			// add the light
			//PointLight light1(Point(-10, 10, -10), Color(1, 1, 1));
			//w.lights.push_back(light1);
			PointLight light2(Point(-5, 5, -10), Color(1, 1, 1));
			w.lights.push_back(light2);

			// calculate view transform and setup camera			
			Camera camera(hsize, vsize, PI / 3.0f);
			camera.transform = World::viewTransform(Point(0, 1.5, -7), Point(0, 1, 0), Vector(0, 1, 0));
			//camera.transform = World::viewTransform(Point(1, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

			// add the walls/floor		
			Plane floor;
			//floor.material.color = Color::fromRGB(180, 205, 205);
			floor.material.specular = 0.1f;
			floor.material.shininess = 100;
			floor.material.diffuse = 0.97f;
			floor.material.reflective = 0.5f;
			CheckerPattern checkers(Color::fromRGB(255, 255, 255), Color::fromRGB(0, 0, 0));
			floor.material.pattern = &checkers;
			w.objects.push_back(&floor);

			Plane backWall;
			backWall.transform = Matrix::get4x4TranslationMatrix(0, 0, 10) * Matrix::get4x4RotationMatrix_X(-PI / 2);
			backWall.material.specular = 0;
			backWall.material.diffuse = 0.7f;			
			CheckerPattern checkers2(Color::fromRGB(102, 153, 204), Color::fromRGB(192, 192, 192));
			backWall.material.pattern = &checkers2;
			w.objects.push_back(&backWall);

			// add the spheres
			Sphere middle;
			middle.transform = Matrix::get4x4TranslationMatrix(-0.5f, 1, 1);
			middle.material.diffuse = 0.7f;
			middle.material.specular = 0.3f;			
			StripePattern stripes2(Color::fromRGB(11, 100, 50), Color::fromRGB(100, 50, 11));
			stripes2.transform = Matrix::get4x4RotationMatrix_Z(PI / 2)
				* Matrix::get4x4ScalingMatrix(0.25f, 1, 1);
			middle.material.pattern = &stripes2;
			w.objects.push_back(&middle);

			Sphere right;
			right.transform = Matrix::get4x4TranslationMatrix(1.5f, 0.75f, -0.75)
				* Matrix::get4x4ScalingMatrix(0.75f, 0.75f, 0.75f);
			right.material.diffuse = 0.7f;
			right.material.specular = 0.3f;
			GradientPattern gradient(Color::fromRGB(11, 100, 50), Color::fromRGB(100, 50, 11));
			gradient.transform = Matrix::get4x4RotationMatrix_Y(0.5f) * Matrix::get4x4TranslationMatrix(-1, 0, 0) * Matrix::get4x4ScalingMatrix(2, 2, 2);
			right.material.pattern = &gradient;
			w.objects.push_back(&right);

			Sphere left;
			left.transform = Matrix::get4x4TranslationMatrix(-2.25f, 0.75f, -0.5)
				* Matrix::get4x4ScalingMatrix(0.75f, 0.75f, 0.75f);
			left.material.diffuse = 0.7f;
			left.material.specular = 0.3f;
			RingPattern ring(Color(1, 0.8f, 0.1f), Color(1, 1, 1));
			ring.transform = Matrix::get4x4RotationMatrix_X(-PI / 3) * Matrix::get4x4ScalingMatrix(0.25f, 0.25f, 0.25f);
			left.material.pattern = &ring;
			w.objects.push_back(&left);

			// run the ray tracer...
			auto start = std::chrono::high_resolution_clock::now();

			Canvas image = w.render(camera);

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

			// save the image to disk
			std::string filename = "images/reflection_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
			image.toPPM(filename);
		}
	}
}
#pragma once

#include "vector";
using namespace RayTracer;

namespace Exercises
{
	namespace Chapter7
	{
		void RayTraceSphere()
		{
			std::cout << "\nRay Trace Sphere\n";

			const bool isDebug = false;
			const int size = 512;
			std::cout << size << " x " << size << " => " << (size * size) << " pixels";
					
			World w;

			// add the light
			PointLight light1(Point(-10, 15, -1), Color(1, 1, 1));			
			w.lights.push_back(light1);
			

			// calculate view transform and setup camera
			Matrix viewTransform = World::viewTransform(Point(0, 2, -7), Point(0, 2, 1), Vector(0, 1, 0));
			Camera camera(size, size, PI / 3.0f);
			camera.transform = viewTransform;
			
			// add a sphere
			RayTracer::Sphere s;			
			s.material.color = RayTracer::Color::fromRGB(0, 0, 225);
			s.material.shininess = 100.0f;
			s.material.specular = 0.9f;			
			s.material.diffuse = 0.9f;
			s.material.ambient = 0.1f;
			w.objects.push_back(&s);

			RayTracer::Sphere s2;
			s2.transform = Matrix::get4x4TranslationMatrix(0, 2, 0);
			s2.material.color = RayTracer::Color::fromRGB(0, 225, 0);
			s2.material.shininess = 150.0f;
			s2.material.specular = 0.9f;
			s2.material.diffuse = 0.9f;
			s2.material.ambient = 0.1f;
			w.objects.push_back(&s2);

			RayTracer::Sphere s3;
			s3.transform = Matrix::get4x4TranslationMatrix(0, 4, 0);
			s3.material.color = RayTracer::Color::fromRGB(225, 0, 0);
			s3.material.shininess = 200.0f;
			s3.material.specular = 0.9f;
			s3.material.diffuse = 0.9f;
			s3.material.ambient = 0.1f;
			w.objects.push_back(&s3);
			
			
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
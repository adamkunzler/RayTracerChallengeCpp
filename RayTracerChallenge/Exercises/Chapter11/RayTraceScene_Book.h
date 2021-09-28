#pragma once

#include "vector"

using namespace RayTracer;

namespace Exercises
{
	namespace Chapter11
	{
		void RayTraceScene_Book()
		{
			std::cout << "\nRay Trace Scene Chapter 11 - Book\n";

			const bool isDebug = false;

			// 400/200
			const int hsize = 400;
			const int vsize = hsize / 2;
			std::cout << hsize << " x " << vsize << " => " << (hsize * vsize) << " pixels\n\n";

			World w;

			//
			// calculate view transform and setup camera			
			//
			Camera camera(hsize, vsize, 1.152f);
			camera.transform = World::viewTransform(Point(-2.6f, 1.5f, -3.9f), Point(-0.6f, 1.0f, -0.8f), Vector(0, 1, 0));
						
			//
			// add the light sources
			//
			PointLight light(Point(-4.9f, 4.9f, -1.0f), Color(1, 1, 1));
			w.lights.push_back(light);
			
			//
			// pre-define materials
			//
			
			

			//
			// floors, ceiling, and walls
			//
			Plane floor;
			floor.transform = Matrix::get4x4RotationMatrix_Y(0.31415f);
			CheckerPattern floorPattern(Color(0.35f, 0.35f, 0.35f), Color(0.65f, 0.65f, 0.65f));
			floor.material.pattern = &floorPattern;
			floor.material.specular = 0;
			floor.material.reflective = 0.4f;
			w.objects.push_back(&floor);

			/*Plane ceiling;
			ceiling.transform = Matrix::get4x4TranslationMatrix(0, 5, 0);
			ceiling.material.color = Color(0.8f, 0.8f, 0.8f);
			ceiling.material.ambient = 0.3f;
			ceiling.material.specular = 0;
			w.objects.push_back(&ceiling);*/

			Plane westWall;			
			westWall.transform = Matrix::get4x4TranslationMatrix(-5, 0, 0)
				* Matrix::get4x4RotationMatrix_Z(1.5708f)
				* Matrix::get4x4RotationMatrix_Y(1.5708f);
			StripePattern stripePatternWW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
			stripePatternWW.transform = Matrix::get4x4RotationMatrix_Y(1.5708f)
				* Matrix::get4x4ScalingMatrix(0.25f, 0.25f, 0.25f);
			westWall.material.pattern = &stripePatternWW;
			westWall.material.ambient = 0;
			westWall.material.diffuse = 0.4f;
			westWall.material.specular = 0;
			westWall.material.reflective = 0.3f;
			w.objects.push_back(&westWall);
			
			Plane eastWall;			
			eastWall.transform = Matrix::get4x4TranslationMatrix(5, 0, 0)
				* Matrix::get4x4RotationMatrix_Z(1.5708f)
				* Matrix::get4x4RotationMatrix_Y(1.5708f);
			StripePattern stripePatternEW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
			stripePatternEW.transform = Matrix::get4x4RotationMatrix_Y(1.5708f)
				* Matrix::get4x4ScalingMatrix(0.25f, 0.25f, 0.25f);
			eastWall.material.pattern = &stripePatternEW;
			eastWall.material.ambient = 0;
			eastWall.material.diffuse = 0.4f;
			eastWall.material.specular = 0;
			eastWall.material.reflective = 0.3f;
			w.objects.push_back(&eastWall);

			Plane northWall;			
			northWall.transform = Matrix::get4x4TranslationMatrix(0, 0, 5)
				* Matrix::get4x4RotationMatrix_X(-1.5708f);
			StripePattern stripePatternNW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
			stripePatternNW.transform = Matrix::get4x4RotationMatrix_Y(1.5708f)
				* Matrix::get4x4ScalingMatrix(0.25f, 0.25f, 0.25f);
			northWall.material.pattern = &stripePatternNW;
			northWall.material.ambient = 0;
			northWall.material.diffuse = 0.4f;
			northWall.material.specular = 0;
			northWall.material.reflective = 0.3f;
			w.objects.push_back(&northWall);

			Plane southWall;			
			southWall.transform = Matrix::get4x4TranslationMatrix(0, 0, -5)
				* Matrix::get4x4RotationMatrix_X(1.5708f);
			StripePattern stripePatternSW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
			stripePatternSW.transform = Matrix::get4x4RotationMatrix_Y(1.5708f)
				* Matrix::get4x4ScalingMatrix(0.25f, 0.25f, 0.25f);
			southWall.material.pattern = &stripePatternSW;
			southWall.material.ambient = 0;
			southWall.material.diffuse = 0.4f;
			southWall.material.specular = 0;
			southWall.material.reflective = 0.3f;
			w.objects.push_back(&southWall);

			//
			// Big Red Ball
			// 
			Sphere red;
			red.transform = Matrix::get4x4TranslationMatrix(-0.6f, 1, 0.6f);
			red.material.color = Color(1, 0.3f, 0.2f);
			red.material.specular = 0.4f;
			red.material.shininess = 5;
			w.objects.push_back(&red);

			//
			// Glass Marbles
			// 

			Sphere blueMarble;
			blueMarble.transform = Matrix::get4x4TranslationMatrix(0.6f, 0.7f, -0.6f)
				* Matrix::get4x4ScalingMatrix(0.7f, 0.7f, 0.7f);
			blueMarble.material.color = Color(0, 0, 0.2f);
			blueMarble.material.ambient = 0.0f;
			blueMarble.material.diffuse = 0.4f;
			blueMarble.material.specular = 0.9f;
			blueMarble.material.shininess = 300;
			blueMarble.material.reflective = 0.4f;
			//blueMarble.material.transparency = 0.9f;
			//blueMarble.material.refractiveIndex = 1.5f;			
			w.objects.push_back(&blueMarble);
			
			Sphere greenMarble;
			greenMarble.transform = Matrix::get4x4TranslationMatrix(-0.7f, 0.5f, -0.8f)
				* Matrix::get4x4ScalingMatrix(0.5f, 0.5f, 0.5f);
			greenMarble.material.color = Color(0, 0.2f, 0);
			greenMarble.material.ambient = 0.0f;
			greenMarble.material.diffuse = 0.4f;
			greenMarble.material.specular = 0.9f;
			greenMarble.material.shininess = 300;
			greenMarble.material.reflective = 0.9f;
			//greenMarble.material.transparency = 0.9f;
			//greenMarble.material.refractiveIndex = 1.5f;			
			w.objects.push_back(&greenMarble);
									
			//
			// Background balls
			//
			Sphere s1;
			s1.transform = Matrix::get4x4TranslationMatrix(4.6f, 0.4f, 1)
				* Matrix::get4x4ScalingMatrix(0.4f, 0.4f, 0.4f);
			s1.material.color = Color(0.8f, 0.5f, 0.3f);
			s1.material.shininess = 50;
			w.objects.push_back(&s1);
			
			Sphere s2;
			s2.transform = Matrix::get4x4TranslationMatrix(4.7f, 0.3f, 0.4f)
				* Matrix::get4x4ScalingMatrix(0.3f, 0.3f, 0.3f);
			s2.material.color = Color(0.9f, 0.4f, 0.5f);
			s2.material.shininess = 50;
			w.objects.push_back(&s2);

			Sphere s3;
			s3.transform = Matrix::get4x4TranslationMatrix(-1.0f, 0.5f, 4.5f)
				* Matrix::get4x4ScalingMatrix(0.5f, 0.5f, 0.5f);
			s3.material.color = Color(0.4f, 0.9f, 0.6f);
			s3.material.shininess = 50;
			w.objects.push_back(&s3);

			Sphere s4;
			s4.transform = Matrix::get4x4TranslationMatrix(-1.7f, 0.3f, 4.7)
				* Matrix::get4x4ScalingMatrix(0.3f, 0.3f, 0.3f);
			s4.material.color = Color(0.4f, 0.6f, 0.9f);
			s4.material.shininess = 50;
			w.objects.push_back(&s4);

			// run the ray tracer...
			auto start = std::chrono::high_resolution_clock::now();

			Canvas image = w.render(camera);

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

			// save the image to disk
			std::string filename = "images/ch11BookScene_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
			image.toPPM(filename);
		}
	}
}
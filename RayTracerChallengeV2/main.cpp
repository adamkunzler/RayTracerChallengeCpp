void showProgressBar(float progress);
void DoSomething();
void Clock();

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <cassert>

#include "src/Utils.h"
#include "src/DataStructs/Color.h"
#include "src/DataStructs/Matrix4x4.h"
#include "src/DataStructs/Vector4.h"

#include "src/Engine/Engine.h"
#include "src/Engine/Camera.h"
#include "src/Engine/Canvas.h"
#include "src/Engine/World.h"

#include "src/Geometry/Intersection.h"
#include "src/Geometry/Material.h"
#include "src/Geometry/PointLight.h"
#include "src/Geometry/Ray.h"
#include "src/Geometry/Computation.h"

#include "src/Shapes/IShape.h"
#include "src/Shapes/Sphere.h"
#include "src/Shapes/Plane.h"

#include "src/Patterns/IPattern.h"
#include "src/Patterns/StripePattern.h"
#include "src/Patterns/GradientPattern.h"
#include "src/Patterns/RingPattern.h"
#include "src/Patterns/CheckerPattern.h"

#include "Benchmarks\benchmarks.h"

#include "tests/_testHarness.h"

void RayTraceScene_Book();

int main()
{
	std::cout << "\n\n --- Ray Tracer Challenge V2 --- \n\n";

	//benchmarkVector4(10000000); // 1.6s
	//benchmarkMatrix4x4(10000000); // 6.7s
	//benchmarkMatrix4x4Inversions(10000000); // 5.8s
	// 
	//RayTracer::Tests::RunTests();

	RayTraceScene_Book();
	
	return 0;
}

void DoSomething()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "\n\nRunning Ray Tracer...\n\n";

	std::cout << "NOT IMPLEMENTED\n\n";

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\nRay Tracer Completed in " << duration.count() << "ms.\n";

	return;
}

void RayTraceScene_Book()
{
	std::cout << " --- Ray Trace Scene --- ";
		
	const int hsize = 384 * 2;
	const int vsize = 216 * 2;
	std::cout << hsize << " x " << vsize << " => " << (hsize * vsize) << " pixels\n\n";

	RayTracer::World w;

	//
	// calculate view transform and setup camera			
	//
	RayTracer::Camera camera(hsize, vsize, 1.152f);	
	camera.transform = RayTracer::viewTransform(
		RayTracer::Vector4(-2.6f, 1.5f, -3.9f, 1.0f),
		RayTracer::Vector4(-0.6f, 1.0f, -0.8f, 1.0f),
		RayTracer::Vector4(0.0f, 1.0f, 0.0f, 0.0f));
	
	camera.transform *= RayTracer::yRotation4x4(PI / 2.0f);

	//
	// add the light sources
	//
	RayTracer::PointLight light(RayTracer::Vector4(-4.9f, 4.9f, -1.0f, 1.0f), RayTracer::Color(1.0f));
	w.lights.push_back(light);

	{
		//
		// floors, ceiling, and walls
		//
		RayTracer::Plane floor;
		floor.transform = RayTracer::yRotation4x4(0.31415f);
		RayTracer::CheckerPattern floorPattern(RayTracer::Color(0.35f, 0.35f, 0.35f), RayTracer::Color(0.65f, 0.65f, 0.65f));
		floor.material.pattern = &floorPattern;
		floor.material.specular = 0.0f;
		floor.material.reflective = 0.4f;
		w.objects.push_back(&floor);

		RayTracer::Plane westWall;
		westWall.transform = RayTracer::translation(-5, 0, 0)
			* RayTracer::zRotation4x4(1.5708f)
			* RayTracer::yRotation4x4(1.5708f);
		RayTracer::StripePattern stripePatternWW(RayTracer::Color(0.45f, 0.45f, 0.45f), RayTracer::Color(0.55f, 0.55f, 0.55f));
		stripePatternWW.transform = RayTracer::yRotation4x4(-1.5708f)
			* RayTracer::scaling(0.25f, 0.25f, 0.25f);
		westWall.material.pattern = &stripePatternWW;
		westWall.material.ambient = 0;
		westWall.material.diffuse = 0.4f;
		westWall.material.specular = 0;
		westWall.material.reflective = 0.3f;
		w.objects.push_back(&westWall);

		RayTracer::Plane eastWall;
		eastWall.transform = RayTracer::translation(5, 0, 0)
			* RayTracer::zRotation4x4(1.5708f)
			* RayTracer::yRotation4x4(1.5708f);
		RayTracer::StripePattern stripePatternEW(RayTracer::Color(0.45f, 0.45f, 0.45f), RayTracer::Color(0.55f, 0.55f, 0.55f));
		stripePatternEW.transform = RayTracer::yRotation4x4(1.5708f)
			* RayTracer::scaling(0.25f, 0.25f, 0.25f);
		eastWall.material.pattern = &stripePatternEW;
		eastWall.material.ambient = 0;
		eastWall.material.diffuse = 0.4f;
		eastWall.material.specular = 0;
		eastWall.material.reflective = 0.3f;
		w.objects.push_back(&eastWall);

		RayTracer::Plane northWall;
		northWall.transform = RayTracer::translation(0, 0, 5)
			* RayTracer::xRotation4x4(-1.5708f);
		RayTracer::StripePattern stripePatternNW(RayTracer::Color(0.45f, 0.45f, 0.45f), RayTracer::Color(0.55f, 0.55f, 0.55f));
		stripePatternNW.transform = RayTracer::yRotation4x4(1.5708f)
			* RayTracer::scaling(0.25f, 0.25f, 0.25f);
		northWall.material.pattern = &stripePatternNW;
		northWall.material.ambient = 0;
		northWall.material.diffuse = 0.4f;
		northWall.material.specular = 0;
		northWall.material.reflective = 0.3f;
		w.objects.push_back(&northWall);

		RayTracer::Plane southWall;
		southWall.transform = RayTracer::translation(0, 0, -5)
			* RayTracer::xRotation4x4(1.5708f);
		RayTracer::StripePattern stripePatternSW(RayTracer::Color(0.45f, 0.45f, 0.45f), RayTracer::Color(0.55f, 0.55f, 0.55f));
		stripePatternSW.transform = RayTracer::yRotation4x4(1.5708f)
			* RayTracer::scaling(0.25f, 0.25f, 0.25f);
		southWall.material.pattern = &stripePatternSW;
		southWall.material.ambient = 0;
		southWall.material.diffuse = 0.4f;
		southWall.material.specular = 0;
		southWall.material.reflective = 0.3f;
		w.objects.push_back(&southWall);

		//
		// Big Red Ball
		//
		RayTracer::Sphere redSphere;
		redSphere.transform = RayTracer::translation(-0.6f, 1.0f, 0.6f);
		redSphere.material.color = RayTracer::Color(1.0f, 0.3f, 0.2f);
		redSphere.material.specular = 0.4f;
		redSphere.material.shininess = 5;
		w.objects.push_back(&redSphere);

		//
		// Glass Marbles
		// 

		RayTracer::Sphere blueMarble;
		blueMarble.transform = RayTracer::translation(0.6f, 0.7f, -0.6f)
			* RayTracer::scaling(0.7f, 0.7f, 0.7f);
		blueMarble.material.color = RayTracer::Color(0, 0, 0.2f);
		blueMarble.material.ambient = 0.0f;
		blueMarble.material.diffuse = 0.4f;
		blueMarble.material.specular = 0.9f;
		blueMarble.material.shininess = 300;
		blueMarble.material.reflective = 0.4f;
		blueMarble.material.transparency = 0.9f;
		blueMarble.material.refractiveIndex = 1.5f;
		w.objects.push_back(&blueMarble);

		RayTracer::Sphere greenMarble;
		greenMarble.transform = RayTracer::translation(-0.7f, 0.5f, -0.8f)
			* RayTracer::scaling(0.5f, 0.5f, 0.5f);
		greenMarble.material.color = RayTracer::Color(0, 0.2f, 0);
		greenMarble.material.ambient = 0.0f;
		greenMarble.material.diffuse = 0.4f;
		greenMarble.material.specular = 0.9f;
		greenMarble.material.shininess = 300;
		greenMarble.material.reflective = 0.9f;
		greenMarble.material.transparency = 0.9f;
		greenMarble.material.refractiveIndex = 1.5f;
		w.objects.push_back(&greenMarble);

		//
		// Background balls
		//
		RayTracer::Sphere s1;
		s1.transform = RayTracer::translation(4.6f, 0.4f, 1)
			* RayTracer::scaling(0.4f, 0.4f, 0.4f);
		s1.material.color = RayTracer::Color(0.8f, 0.5f, 0.3f);
		s1.material.shininess = 50;
		w.objects.push_back(&s1);

		RayTracer::Sphere s2;
		s2.transform = RayTracer::translation(4.7f, 0.3f, 0.4f)
			* RayTracer::scaling(0.3f, 0.3f, 0.3f);
		s2.material.color = RayTracer::Color(0.9f, 0.4f, 0.5f);
		s2.material.shininess = 50;
		w.objects.push_back(&s2);

		RayTracer::Sphere s3;
		s3.transform = RayTracer::translation(-1.0f, 0.5f, 4.5f)
			* RayTracer::scaling(0.5f, 0.5f, 0.5f);
		s3.material.color = RayTracer::Color(0.4f, 0.9f, 0.6f);
		s3.material.shininess = 50;
		w.objects.push_back(&s3);

		RayTracer::Sphere s4;
		s4.transform = RayTracer::translation(-1.7f, 0.3f, 4.7f)
			* RayTracer::scaling(0.3f, 0.3f, 0.3f);
		s4.material.color = RayTracer::Color(0.4f, 0.6f, 0.9f);
		s4.material.shininess = 50;
		w.objects.push_back(&s4);
	}

	// run the ray tracer...
	auto start = std::chrono::high_resolution_clock::now();

	//RayTracer::Canvas image = render(camera, w);
	RayTracer::Canvas image = RayTracer::renderMultiThread(camera, w, 32);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

	// save the image to disk
	std::string filename = "images/redSphere_multithread_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
	image.toPPM(filename);
}

//
// Chapter 4 Exercise
//
void Clock()
{
	std::cout << "\nClock\n";

	const bool isDebug = false;

	const int size = 500;
	float radius = size * (7.0f / 16.0f);
	const int hours = 12;
	const float stepSize = (2 * PI) / hours;

	RayTracer::Canvas canvas(size, size);
	RayTracer::Color color = RayTracer::rgb(129, 19, 240); // purple

	RayTracer::Matrix4x4 localToWorld = RayTracer::translation(size / 2, size / 2, 0);
	RayTracer::Matrix4x4 translate = RayTracer::translation(0, 1, 0); // move to 12:00 position			
	RayTracer::Matrix4x4 scale = RayTracer::scaling(radius, radius, 1); // scale to radius of clock

	for (int j = 0; j < 1; j++)
	{
		for (int i = 0; i < hours; i++)
		{
			if (isDebug) std::cout << "\n\nHour: " << i << std::endl;

			RayTracer::Point4 p(0, 0, 0); // start at origin					
			RayTracer::Matrix4x4 rotate = RayTracer::zRotation4x4(-stepSize * i); // rotate on z-axis

			RayTracer::Matrix4x4 t = localToWorld * scale * rotate * translate; // translate first, then rotate, then scale, last localToWorld
			RayTracer::Point4 pt = t * p;

			canvas.setPixel((int)pt.x, size - (int)pt.y, color);
		}
	}

	canvas.toPPM("images/chapter4_clock.ppm");
}
extern const int MAX_RECURSION(5);

void showProgressBar(float progress);
void DoSomething();

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

	RayTracer::Tests::RunTests();
	
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

/// <summary>
/// Write a progress bar out to std::cout
/// </summary>
/// <param name="progress">a value between 0 and 1 inclusive</param>
void showProgressBar(float progress)
{
	//https://stackoverflow.com/a/14539953

	if (progress < 0) progress = 0;
	if (progress > 1) progress = 1;

	int barWidth = 70;

	std::cout << "[";
	int pos = (int)(barWidth * progress);
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
}

void RayTraceScene_Book()
{
	std::cout << " --- Ray Trace Scene --- ";
	
	const int hsize = 384;
	const int vsize = 216;
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

	//
	// add the light sources
	//
	RayTracer::PointLight light(RayTracer::Vector4(-4.9f, 4.9f, -1.0f, 1.0f), RayTracer::Color(1.0f));
	w.lights.push_back(light);

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

	RayTracer::Sphere redSphere;
	redSphere.transform = RayTracer::translation(-0.6f, 1.0f, 0.6f);
	redSphere.material.color = RayTracer::Color(1.0f, 0.3f, 0.2f);
	redSphere.material.specular = 0.4f;
	redSphere.material.shininess = 5;
	w.objects.push_back(&redSphere);

	// run the ray tracer...
	auto start = std::chrono::high_resolution_clock::now();

	RayTracer::Canvas image = render(camera, w);
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

	// save the image to disk
	std::string filename = "images/redSphere_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
	image.toPPM(filename);
}
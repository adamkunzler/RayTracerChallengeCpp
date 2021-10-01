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

void RayTraceScene_Book();

int main()
{
	std::cout << "\n\n --- Ray Tracer Challenge V2 --- \n\n";
	
	//benchmarkVector4(10000000); // 1.6s
	//benchmarkMatrix4x4(10000000); // 6.7s
	//benchmarkMatrix4x4Inversions(10000000); // 5.8s

	/*RayTracer::Sphere red;
	red.transform = RayTracer::translation(-0.6f, 1, 0.6f);
	red.material.color = RayTracer::Color(1, 0.3f, 0.2f);
	red.material.specular = 0.4f;
	red.material.shininess = 5;*/

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
	std::cout << "\n --- Ray Trace Scene --- \n";

	const bool isDebug = false;

	// 400/200
	//const int hsize = 384;
	//const int vsize = 216;// hsize / 2;
	const int hsize = 96;
	const int vsize = 54;// hsize / 2;
	std::cout << hsize << " x " << vsize << " => " << (hsize * vsize) << " pixels\n\n";

	RayTracer::World w;

	//
	// calculate view transform and setup camera			
	//
	RayTracer::Camera camera(hsize, vsize, 1.152f);
	camera.transform = RayTracer::viewTransform(
		RayTracer::Vector4(-2.6f, 1.5f, -3.9f, 1.0f), 
		RayTracer::Vector4(-0.6f, 1.0f, -0.8f, 1.0f), 
		RayTracer::Vector4(0.0f, 1.0f, 0.0f, 1.0f));

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

	/*Plane ceiling;
	ceiling.transform = Matrix::get4x4TranslationMatrix(0, 5, 0);
	ceiling.material.color = Color(0.8f, 0.8f, 0.8f);
	ceiling.material.ambient = 0.3f;
	ceiling.material.specular = 0;
	w.objects.push_back(&ceiling);*/

	RayTracer::Plane westWall;
	westWall.transform = RayTracer::translation(-5.0f, 0.0f, 0.0f)
		* RayTracer::zRotation4x4(1.5708f)
		* RayTracer::yRotation4x4(1.5708f);
	RayTracer::StripePattern stripePatternWW(RayTracer::Color(0.45f, 0.45f, 0.45f), RayTracer::Color(0.55f, 0.55f, 0.55f));
	stripePatternWW.transform = RayTracer::yRotation4x4(1.5708f)
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
	RayTracer::Sphere red;
	red.transform = RayTracer::translation(-0.6f, 1, 0.6f);
	red.material.color = RayTracer::Color(1, 0.3f, 0.2f);
	red.material.specular = 0.4f;
	red.material.shininess = 5;
	w.objects.push_back(&red);

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

	////
	//// Background balls
	////
	//RayTracer::Sphere s1;
	//s1.transform = Matrix::get4x4TranslationMatrix(4.6f, 0.4f, 1)
	//	* Matrix::get4x4ScalingMatrix(0.4f, 0.4f, 0.4f);
	//s1.material.color = RayTracer::Color(0.8f, 0.5f, 0.3f);
	//s1.material.shininess = 50;
	//w.objects.push_back(&s1);

	//RayTracer::Sphere s2;
	//s2.transform = Matrix::get4x4TranslationMatrix(4.7f, 0.3f, 0.4f)
	//	* Matrix::get4x4ScalingMatrix(0.3f, 0.3f, 0.3f);
	//s2.material.color = Color(0.9f, 0.4f, 0.5f);
	//s2.material.shininess = 50;
	//w.objects.push_back(&s2);

	//RayTracer::Sphere s3;
	//s3.transform = Matrix::get4x4TranslationMatrix(-1.0f, 0.5f, 4.5f)
	//	* Matrix::get4x4ScalingMatrix(0.5f, 0.5f, 0.5f);
	//s3.material.color = RayTracer::Color(0.4f, 0.9f, 0.6f);
	//s3.material.shininess = 50;
	//w.objects.push_back(&s3);

	//RayTracer::Sphere s4;
	//s4.transform = Matrix::get4x4TranslationMatrix(-1.7f, 0.3f, 4.7f)
	//	* Matrix::get4x4ScalingMatrix(0.3f, 0.3f, 0.3f);
	//s4.material.color = RayTracer::Color(0.4f, 0.6f, 0.9f);
	//s4.material.shininess = 50;
	//w.objects.push_back(&s4);

	// run the ray tracer...
	auto start = std::chrono::high_resolution_clock::now();

	RayTracer::Canvas image = render(camera, w);
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

	// save the image to disk
	std::string filename = "images/refactored_chapter11Scene_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
	image.toPPM(filename);
}
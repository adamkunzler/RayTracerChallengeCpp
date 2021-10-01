
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

#include "src/Utils.h"

#include "tests\_testHarness.h"

//#include "Exercises\Chapter1\VirtualCannon.h"
//#include "Exercises\Chapter2\ProjectilePPM.h"
//#include "Exercises\Chapter4\Clock.h"
//#include "Exercises\Chapter5\RayTraceSphere.h"
//#include "Exercises\Chapter6\RayTraceSphere.h"
//#include "Exercises\Chapter7\RayTraceSphere.h"
//#include "Exercises\Chapter7\RayTraceScene.h"
//#include "Exercises\Chapter9\RayTraceScene.h"
//#include "Exercises\Chapter10\RayTraceScene_Stripe.h"
//#include "Exercises\Chapter11\RayTraceScene_reflection.h"
#include "Exercises\Chapter11\RayTraceScene_Book.h"
#include "Exercises\Chapter11\RayTraceScene_NestedGlassSpheres.h"

#include "Benchmarks\benchmark.h"

void RunRayTracer();

int main()
{
	std::cout << "\nThe Ray Tracer Challenge\n\n\n";

	//benchmarkVector(10000000); //3.6s
	//benchmarkMatrix(10000000); //6.2min
	//benchmarkMatrixInversions(10000000); //53.9min

	//bool result = RayTracer::Tests::RunTests(false);

	//RayTracer::Tests::Refraction_RefractedColorWithARefractedRay();
	//RayTracer::Tests::Refraction_ShadeHit_TransparentMaterial();

	//Exercises::Chapter1::FireCannon();
	//Exercises::Chapter2::ProjectilePPM();
	//Exercises::Chapter4::Clock();
	//Exercises::Chapter5::RayTraceSphere();
	//Exercises::Chapter6::RayTraceSphere();
	//Exercises::Chapter7::RayTraceSphere();
	//Exercises::Chapter7::RayTraceScene();
	//Exercises::Chapter9::RayTraceScene();
	//Exercises::Chapter10::RayTraceScene_Stripe();
	//Exercises::Chapter11::RayTraceScene_Reflection();
	//Exercises::Chapter11::RayTraceScene_Book();
	//Exercises::Chapter11::RayTraceScene_NestedGlassSpheres();

	//if(result) RunRayTracer();

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
		RayTracer::Point(-2.6f, 1.5f, -3.9f),
		RayTracer::Point(-0.6f, 1.0f, -0.8f),
		RayTracer::Vector(0.0f, 1.0f, 0.0f));

	//
	// add the light sources
	//
	RayTracer::PointLight light(RayTracer::Point(-4.9f, 4.9f, -1.0f), RayTracer::Color(1.0f));
	w.lights.push_back(light);

	//
	// floors, ceiling, and walls
	//
	RayTracer::Plane floor;
	floor.transform = RayTracer::Matrix::get4x4RotationMatrix_Y(0.31415f);
	RayTracer::CheckerPattern floorPattern(RayTracer::Color(0.35f, 0.35f, 0.35f), RayTracer::Color(0.65f, 0.65f, 0.65f));
	floor.material.pattern = &floorPattern;
	floor.material.specular = 0.0f;
	floor.material.reflective = 0.4f;
	w.objects.push_back(&floor);

	RayTracer::Sphere redSphere;
	redSphere.transform = RayTracer::Matrix::get4x4TranslationMatrix(-0.6f, 1.0f, 0.6f);
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


	std::cout << "\n\n\n";
	return 0;
}



void RunRayTracer()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "\n\nRunning Ray Tracer...\n\n";

	std::cout << "NOT IMPLEMENTED\n\n";

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\nRay Tracer Completed in " << duration.count() << "ms.\n";

	return;
}
void showProgressBar(float progress);

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
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
#include "src/Engine/Scene.h"

#include "src/Geometry/Intersection.h"
#include "src/Geometry/Material.h"
#include "src/Geometry/PointLight.h"
#include "src/Geometry/Ray.h"
#include "src/Geometry/Computation.h"

#include "src/Shapes/IShape.h"
#include "src/Shapes/Sphere.h"
#include "src/Shapes/Plane.h"
#include "src/Shapes/Cube.h"
#include "src/Shapes/Cylinder.h"

#include "src/Patterns/IPattern.h"
#include "src/Patterns/StripePattern.h"
#include "src/Patterns/GradientPattern.h"
#include "src/Patterns/RingPattern.h"
#include "src/Patterns/CheckerPattern.h"

#include "Benchmarks\benchmarks.h"
#include "tests/_testHarness.h"

using namespace RayTracer;

void RayTraceScene_Benchmark();
void spheres(const int sizeScale);
void cubes(const int sizeScale);
void cylinders(const int sizeScale);

int main()
{
	//Tests::RunTests();

	RayTraceScene_Benchmark();
	//spheres(2);
	//cubes(2);
	//cylinders(2);

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
	return 0;
}

//namespace RayTracer
//{
//	namespace Scenes
//	{
void RayTraceScene_Benchmark()
{
	SceneConfig config;

	// dimensions and fov
	config.width = 3000;
	config.height = 1600;
	config.fov = 1.152f;

	// camera
	config.from = Vector4(-2.6f, 1.5f, -3.9f, 1.0f);
	config.to = Vector4(-0.6f, 1.0f, -0.8f, 1.0f);
	config.up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Vector4(-4.9f, 4.9f, -1.0f, 1.0f),
		Color(1.0f)
	));

	// add the shapes
	{
		//
		// floors, ceiling, and walls
		//
		Plane floor;
		floor.setTransform(yRotation4x4(0.31415f));
		CheckerPattern floorPattern(Color(0.35f, 0.35f, 0.35f), Color(0.65f, 0.65f, 0.65f));
		floor.material.pattern = &floorPattern;
		floor.material.specular = 0.0f;
		floor.material.reflective = 0.4f;
		scene.addShape(floor);

		Plane westWall;
		westWall.setTransform(translation(-5, 0, 0)
			* zRotation4x4(1.5708f)
			* yRotation4x4(1.5708f));
		StripePattern stripePatternWW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternWW.setTransform(yRotation4x4(-1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		westWall.material.pattern = &stripePatternWW;
		westWall.material.ambient = 0;
		westWall.material.diffuse = 0.4f;
		westWall.material.specular = 0;
		westWall.material.reflective = 0.3f;
		scene.addShape(westWall);

		Plane eastWall;
		eastWall.setTransform(translation(5, 0, 0)
			* zRotation4x4(1.5708f)
			* yRotation4x4(1.5708f));
		StripePattern stripePatternEW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternEW.setTransform(yRotation4x4(1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		eastWall.material.pattern = &stripePatternEW;
		eastWall.material.ambient = 0;
		eastWall.material.diffuse = 0.4f;
		eastWall.material.specular = 0;
		eastWall.material.reflective = 0.3f;
		scene.addShape(eastWall);

		Plane northWall;
		northWall.setTransform(translation(0, 0, 5)
			* xRotation4x4(-1.5708f));
		StripePattern stripePatternNW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternNW.setTransform(yRotation4x4(1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		northWall.material.pattern = &stripePatternNW;
		northWall.material.ambient = 0;
		northWall.material.diffuse = 0.4f;
		northWall.material.specular = 0;
		northWall.material.reflective = 0.3f;
		scene.addShape(northWall);

		Plane southWall;
		southWall.setTransform(translation(0, 0, -5)
			* xRotation4x4(1.5708f));
		StripePattern stripePatternSW(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternSW.setTransform(yRotation4x4(1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		southWall.material.pattern = &stripePatternSW;
		southWall.material.ambient = 0;
		southWall.material.diffuse = 0.4f;
		southWall.material.specular = 0;
		southWall.material.reflective = 0.3f;
		scene.addShape(southWall);

		//
		// Big Red Ball
		//
		Sphere redSphere;
		redSphere.setTransform(translation(-0.6f, 1.0f, 0.6f));
		redSphere.material.color = Color(1.0f, 0.3f, 0.2f);
		redSphere.material.specular = 0.4f;
		redSphere.material.shininess = 5;
		scene.addShape(redSphere);

		//
		// Glass Marbles
		// 

		Sphere blueMarble;
		blueMarble.setTransform(translation(0.6f, 0.7f, -0.6f)
			* scaling(0.7f, 0.7f, 0.7f));
		blueMarble.material.color = Color(0, 0, 0.2f);
		blueMarble.material.ambient = 0.0f;
		blueMarble.material.diffuse = 0.4f;
		blueMarble.material.specular = 0.9f;
		blueMarble.material.shininess = 300;
		blueMarble.material.reflective = 0.4f;
		blueMarble.material.transparency = 0.9f;
		blueMarble.material.refractiveIndex = 1.5f;
		scene.addShape(blueMarble);

		Sphere greenMarble;
		greenMarble.setTransform(translation(-0.7f, 0.5f, -0.8f)
			* scaling(0.5f, 0.5f, 0.5f));
		greenMarble.material.color = Color(0, 0.2f, 0);
		greenMarble.material.ambient = 0.0f;
		greenMarble.material.diffuse = 0.4f;
		greenMarble.material.specular = 0.9f;
		greenMarble.material.shininess = 300;
		greenMarble.material.reflective = 0.9f;
		greenMarble.material.transparency = 0.9f;
		greenMarble.material.refractiveIndex = 1.5f;
		scene.addShape(greenMarble);

		//
		// Background balls
		//
		Sphere s1;
		s1.setTransform(translation(4.6f, 0.4f, 1)
			* scaling(0.4f, 0.4f, 0.4f));
		s1.material.color = Color(0.8f, 0.5f, 0.3f);
		s1.material.shininess = 50;
		scene.addShape(s1);

		Sphere s2;
		s2.setTransform(translation(4.7f, 0.3f, 0.4f)
			* scaling(0.3f, 0.3f, 0.3f));
		s2.material.color = Color(0.9f, 0.4f, 0.5f);
		s2.material.shininess = 50;
		scene.addShape(s2);

		Sphere s3;
		s3.setTransform(translation(-1.0f, 0.5f, 4.5f)
			* scaling(0.5f, 0.5f, 0.5f));
		s3.material.color = Color(0.4f, 0.9f, 0.6f);
		s3.material.shininess = 50;
		scene.addShape(s3);

		Sphere s4;
		s4.setTransform(translation(-1.7f, 0.3f, 4.7f)
			* scaling(0.3f, 0.3f, 0.3f));
		s4.material.color = Color(0.4f, 0.6f, 0.9f);
		s4.material.shininess = 50;
		scene.addShape(s4);
	}

	scene.renderToPPM("rayTraceScene_benchmark");
}

/*
void spheres(const int sizeScale)
{
	std::cout << " --- Ray Trace Scene: Materials --- ";

	const int hsize = 800 * sizeScale;
	const int vsize = 300 * sizeScale;

	World w;

	Camera camera(hsize, vsize, PI / 2.7f);
	camera.transform(viewTransform(
		Point4(0.0f, 5.0f, -6.0f), // from
		Point4(0.0f, 1.0f, 5.0f),  // to
		Vector4(0.0f, 1.0f, 0.0f)));

	PointLight lightM(Point4(0.0f, 7.0f, 0.0f), Color(0.9f));
	//PointLight lightL(Point4(-5.0f, 15.0f, -5.0f), Color(0.35f));
	//PointLight lightR(Point4(5.0f, 2.0f, -5.0f), Color(0.35f));
	w.lights.push_back(lightM);
	//w.lights.push_back(lightL);
	//w.lights.push_back(lightR);

	// setup objects
	{
		Color checkerColor1(0.99f);
		Color checkerColor2(0.95f);
		Color babyBlue = rgb(137, 207, 240);

		{
			Plane floor;
			CheckerPattern floorPattern(checkerColor1, checkerColor2);
			floor.material.pattern = &floorPattern;
			floor.material.ambient = 0.1f;
			floor.material.reflective = 0.0f;
			w.objects.push_back(&floor);

			Plane ceiling;
			ceiling.setTransform(translation(0.0f, 20.0f, 0.0f) * xRotation4x4(PI));
			ceiling.material.color = Color(1.0f);
			ceiling.material.ambient = 0.1f;
			ceiling.material.reflective = 0.0f;
			w.objects.push_back(&ceiling);

			Plane backWall;
			backWall.setTransform(translation(1.0f, 0.0f, 15.0f) * xRotation4x4(PI / 2.0f));
			CheckerPattern backWallPattern(checkerColor1, checkerColor2);
			backWall.material.pattern = &backWallPattern;
			backWall.material.ambient = 0.1f;
			backWall.material.reflective = 0.0f;
			backWall.material.specular = 0;
			w.objects.push_back(&backWall);

			Plane behindWall;
			behindWall.setTransform(translation(1.0f, 0.0f, -25.0f) * xRotation4x4(-PI / 2.0f));
			behindWall.material.color = Color(1.0f);
			behindWall.material.ambient = 0.1f;
			behindWall.material.reflective = 0.0f;
			behindWall.material.specular = 0;
			w.objects.push_back(&behindWall);
		}

		Sphere glassSphere;
		glassSphere.material = glass(glassSphere.material);
		glassSphere.setTransform(translation(-6.0f, 1.0f, 4.0f));
		w.objects.push_back(&glassSphere);

		Sphere glassSphereInside;
		glassSphereInside.material = glass(glassSphereInside.material);
		glassSphereInside.setTransform(translation(-6.0f, 1.0f, 4.0f) * scaling(0.9f, 0.9f, 0.9f));
		w.objects.push_back(&glassSphereInside);

		Sphere matteSphere;
		matteSphere.material = matte(matteSphere.material, babyBlue);
		matteSphere.setTransform(translation(-3.0f, 1.0f, 5.0f));
		w.objects.push_back(&matteSphere);

		Sphere reflectiveMetalSphere;
		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
		reflectiveMetalSphere.setTransform(translation(0.0f, 1.0f, 6.0f));
		w.objects.push_back(&reflectiveMetalSphere);

		Sphere glossySphere;
		glossySphere.material = gloss(glossySphere.material, babyBlue);
		glossySphere.setTransform(translation(3.0f, 1.0f, 5.0f));
		w.objects.push_back(&glossySphere);

		Sphere flatMetalSphere;
		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
		flatMetalSphere.setTransform(translation(6.0f, 1.0f, 4.0f));
		w.objects.push_back(&flatMetalSphere);
	}

	// run the ray tracer...
	auto start = std::chrono::high_resolution_clock::now();

	Canvas image = renderMultiThread(camera, w, 16);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

	// save the image to disk
	std::string filename = "images/spheres_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
	image.toPPM(filename);
}

//
// Chapter 12 - cubes
//
void cubes(const int sizeScale)
{
	std::cout << " --- Ray Trace Scene: Materials --- ";

	const int hsize = 800 * sizeScale;
	const int vsize = 300 * sizeScale;

	World w;

	Camera camera(hsize, vsize, PI / 2.3f);
	camera.setTransform(viewTransform(
		Point4(0.0f, 5.0f, -6.0f), // from
		Point4(0.0f, 1.0f, 5.0f),  // to
		Vector4(0.0f, 1.0f, 0.0f));

	PointLight lightM(Point4(0.0f, 7.0f, 0.0f), Color(0.9f));
	//PointLight lightL(Point4(-5.0f, 15.0f, -5.0f), Color(0.35f));
	//PointLight lightR(Point4(5.0f, 2.0f, -5.0f), Color(0.35f));
	w.lights.push_back(lightM);
	//w.lights.push_back(lightL);
	//w.lights.push_back(lightR);

	// setup objects
	{
		Color checkerColor1(0.99f);
		Color checkerColor2(0.95f);
		Color babyBlue = rgb(137, 207, 240);


		{
			Plane floor;
			CheckerPattern floorPattern(checkerColor1, checkerColor2);
			floor.material.pattern = &floorPattern;
			floor.material.ambient = 0.1f;
			floor.material.reflective = 0.0f;
			w.objects.push_back(&floor);

			Plane ceiling;
			ceiling.setTransform(translation(0.0f, 20.0f, 0.0f) * xRotation4x4(PI));
			ceiling.material.color = Color(1.0f);
			ceiling.material.ambient = 0.1f;
			ceiling.material.reflective = 0.0f;
			w.objects.push_back(&ceiling);

			Plane backWall;
			backWall.setTransform(translation(1.0f, 0.0f, 15.0f) * xRotation4x4(PI / 2.0f));
			CheckerPattern backWallPattern(checkerColor1, checkerColor2);
			backWall.material.pattern = &backWallPattern;
			backWall.material.ambient = 0.1f;
			backWall.material.reflective = 0.0f;
			backWall.material.specular = 0;
			w.objects.push_back(&backWall);

			Plane behindWall;
			behindWall.setTransform(translation(1.0f, 0.0f, -25.0f) * xRotation4x4(-PI / 2.0f));
			behindWall.material.color = Color(1.0f);
			behindWall.material.ambient = 0.1f;
			behindWall.material.reflective = 0.0f;
			behindWall.material.specular = 0;
			w.objects.push_back(&behindWall);
		}

		Cube glassSphere;
		glassSphere.material = glass(glassSphere.material);
		glassSphere.setTransform(translation(-6.0f, 1.0f, 4.0f));
		w.objects.push_back(&glassSphere);

		Cube glassSphereInside;
		glassSphereInside.material = glass(glassSphereInside.material);
		glassSphereInside.setTransform(translation(-6.0f, 1.0f, 4.0f) * scaling(0.99999f, 0.99999f, 0.99999f));
		w.objects.push_back(&glassSphereInside);

		Cube matteSphere;
		matteSphere.material = matte(matteSphere.material, babyBlue);
		matteSphere.setTransform(translation(-3.0f, 1.0f, 5.0f));
		w.objects.push_back(&matteSphere);

		Cube reflectiveMetalSphere;
		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
		reflectiveMetalSphere.material.reflective = 0.8f;
		reflectiveMetalSphere.setTransform(translation(0.0f, 1.0f, 6.0f) * yRotation4x4(PI / 4.0f));
		w.objects.push_back(&reflectiveMetalSphere);

		Cube glossySphere;
		glossySphere.material = gloss(glossySphere.material, babyBlue);
		glossySphere.setTransform(translation(3.0f, 1.0f, 5.0f));
		w.objects.push_back(&glossySphere);

		Cube flatMetalSphere;
		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
		flatMetalSphere.setTransform(translation(6.0f, 1.0f, 4.0f));
		w.objects.push_back(&flatMetalSphere);
	}

	// run the ray tracer...
	auto start = std::chrono::high_resolution_clock::now();

	Canvas image = renderMultiThread(camera, w, 16);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

	// save the image to disk
	std::string filename = "images/cubes_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
	image.toPPM(filename);
}

//
// Chapter 13 - cylinders
//
void cylinders(const int sizeScale)
{
	std::cout << " --- Ray Trace Scene: Cylinders --- ";

	const int hsize = 800 * sizeScale;
	const int vsize = 800 * sizeScale;

	World w;

	Camera camera(hsize, vsize, PI / 2.3f);
	camera.setTransform(viewTransform(
		Point4(0.0f, 5.0f, -6.0f), // from
		Point4(0.0f, 1.0f, 5.0f),  // to
		Vector4(0.0f, 1.0f, 0.0f));

	PointLight lightM(Point4(0.0f, 7.0f, 0.0f), Color(0.9f));
	//PointLight lightL(Point4(-5.0f, 15.0f, -5.0f), Color(0.35f));
	//PointLight lightR(Point4(5.0f, 2.0f, -5.0f), Color(0.35f));
	w.lights.push_back(lightM);
	//w.lights.push_back(lightL);
	//w.lights.push_back(lightR);

	// setup objects
	{
		Color checkerColor1(0.99f);
		Color checkerColor2(0.95f);
		Color babyBlue = rgb(137, 207, 240);


		{
			Plane floor;
			CheckerPattern floorPattern(checkerColor1, checkerColor2);
			floor.material.pattern = &floorPattern;
			floor.material.ambient = 0.1f;
			floor.material.reflective = 0.0f;
			w.objects.push_back(&floor);

			Plane ceiling;
			ceiling.setTransform(translation(0.0f, 20.0f, 0.0f) * xRotation4x4(PI));
			ceiling.material.color = Color(1.0f);
			ceiling.material.ambient = 0.1f;
			ceiling.material.reflective = 0.0f;
			w.objects.push_back(&ceiling);

			Plane backWall;
			backWall.setTransform(translation(1.0f, 0.0f, 15.0f) * xRotation4x4(PI / 2.0f));
			CheckerPattern backWallPattern(checkerColor1, checkerColor2);
			backWall.material.pattern = &backWallPattern;
			backWall.material.ambient = 0.1f;
			backWall.material.reflective = 0.0f;
			backWall.material.specular = 0;
			w.objects.push_back(&backWall);

			Plane behindWall;
			behindWall.setTransform(translation(1.0f, 0.0f, -25.0f) * xRotation4x4(-PI / 2.0f));
			behindWall.material.color = Color(1.0f);
			behindWall.material.ambient = 0.1f;
			behindWall.material.reflective = 0.0f;
			behindWall.material.specular = 0;
			w.objects.push_back(&behindWall);
		}

		Cylinder glassSphere(0.0f, 3.0f, true);
		glassSphere.material = glass(glassSphere.material);
		glassSphere.setTransform(translation(-6.0f, 0.0f, 3.0f));
		w.objects.push_back(&glassSphere);

		Cylinder glassSphereInside(0.0f, 3.0f, true);
		glassSphereInside.material = glass(glassSphereInside.material);
		glassSphereInside.setTransform(translation(-6.0f, 0.0f, 3.0f) * scaling(0.99999f, 0.99999f, 0.99999f));
		w.objects.push_back(&glassSphereInside);

		Cylinder matteSphere(0.0f, 3.0f, true);
		matteSphere.material = matte(matteSphere.material, babyBlue);
		matteSphere.setTransform(translation(-2.0f, 0.0f, 5.0f));
		w.objects.push_back(&matteSphere);

		Cylinder reflectiveMetalSphere(0.0f, 1.0f);
		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
		reflectiveMetalSphere.material.reflective = 0.8f;
		reflectiveMetalSphere.setTransform(translation(0.0f, 0.0f, 5.0f) * scaling(4.5f, 1.0f, 4.5f));
		w.objects.push_back(&reflectiveMetalSphere);

		Cylinder glossySphere(0.0f, 3.0f, true);
		glossySphere.material = gloss(glossySphere.material, babyBlue);
		glossySphere.setTransform(translation(2.0f, 0.0f, 5.0f));
		w.objects.push_back(&glossySphere);

		Cylinder flatMetalSphere(0.0f, 3.0f, true);
		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
		flatMetalSphere.setTransform(translation(6.0f, 0.0f, 3.0f));
		w.objects.push_back(&flatMetalSphere);
	}


	// run the ray tracer...
	auto start = std::chrono::high_resolution_clock::now();

	Canvas image = renderMultiThread(camera, w, 16);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\n\nRay Tracer Completed in " << duration.count() << "ms.\n";

	// save the image to disk
	std::string filename = "images/cylinders_" + std::to_string(hsize) + "x" + std::to_string(vsize) + ".ppm";
	image.toPPM(filename);
}
*/
//	} // end namespace Scenes
//} // end namespace RayTracer
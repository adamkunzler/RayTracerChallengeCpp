#include "src/Headers.h"

using namespace RayTracer;

void RayTraceScene_Benchmark();
void spheres(const int sizeScale);
void cubes(const int sizeScale);
void cylinders(const int sizeScale);
void cubeOfSpheres(const int sizeScale);
void simpleGroup(int sizeScale);

int main()
{
	//Tests::RunTests();

	//RayTraceScene_Benchmark();
	//spheres(2);
	//cubes(2);
	//cylinders(2);
	cubeOfSpheres(10);
	//simpleGroup(1);

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
	return 0;
}

// -----------------------------------------------------------------------

void RayTraceScene_Benchmark()
{
	SceneConfig config;

	// dimensions and fov
	config.width = 3000;
	config.height = 1600;
	config.fov = 1.152f;

	// camera
	config.from = Point4(-2.6f, 1.5f, -3.9f);
	config.to = Point4(-0.6f, 1.0f, -0.8f);
	config.up = Vector4(0.0f, 1.0f, 0.0f);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-4.9f, 4.9f, -1.0f),
		Color(1.0f)
	));

	// add the shapes
	{
		//
		// floors, ceiling, and walls
		//
		Plane* floor = new Plane();
		floor->setTransform(yRotation4x4(0.31415f));
		CheckerPattern* floorPattern = new CheckerPattern(Color(0.35f, 0.35f, 0.35f), Color(0.65f, 0.65f, 0.65f));
		floor->material.pattern = floorPattern;
		floor->material.specular = 0.0f;
		floor->material.reflective = 0.4f;
		scene.addShape(floor);

		Plane* westWall = new Plane();
		westWall->setTransform(translation(-5, 0, 0)
			* zRotation4x4(1.5708f)
			* yRotation4x4(1.5708f));
		StripePattern* stripePatternWW = new StripePattern(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternWW->setTransform(yRotation4x4(-1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		westWall->material.pattern = stripePatternWW;
		westWall->material.ambient = 0;
		westWall->material.diffuse = 0.4f;
		westWall->material.specular = 0;
		westWall->material.reflective = 0.3f;
		scene.addShape(westWall);

		Plane* eastWall = new Plane();
		eastWall->setTransform(translation(5, 0, 0)
			* zRotation4x4(1.5708f)
			* yRotation4x4(1.5708f));
		StripePattern* stripePatternEW = new StripePattern(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternEW->setTransform(yRotation4x4(1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		eastWall->material.pattern = stripePatternEW;
		eastWall->material.ambient = 0;
		eastWall->material.diffuse = 0.4f;
		eastWall->material.specular = 0;
		eastWall->material.reflective = 0.3f;
		scene.addShape(eastWall);

		Plane* northWall = new Plane();
		northWall->setTransform(translation(0, 0, 5)
			* xRotation4x4(-1.5708f));
		StripePattern* stripePatternNW = new StripePattern(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternNW->setTransform(yRotation4x4(1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		northWall->material.pattern = stripePatternNW;
		northWall->material.ambient = 0;
		northWall->material.diffuse = 0.4f;
		northWall->material.specular = 0;
		northWall->material.reflective = 0.3f;
		scene.addShape(northWall);

		Plane* southWall = new Plane();
		southWall->setTransform(translation(0, 0, -5)
			* xRotation4x4(1.5708f));
		StripePattern* stripePatternSW = new StripePattern(Color(0.45f, 0.45f, 0.45f), Color(0.55f, 0.55f, 0.55f));
		stripePatternSW->setTransform(yRotation4x4(1.5708f)
			* scaling(0.25f, 0.25f, 0.25f));
		southWall->material.pattern = stripePatternSW;
		southWall->material.ambient = 0;
		southWall->material.diffuse = 0.4f;
		southWall->material.specular = 0;
		southWall->material.reflective = 0.3f;
		scene.addShape(southWall);

		//
		// Big Red Ball
		//
		Sphere* redSphere = new Sphere();
		redSphere->setTransform(translation(-0.6f, 1.0f, 0.6f));
		redSphere->material.color = Color(1.0f, 0.3f, 0.2f);
		redSphere->material.specular = 0.4f;
		redSphere->material.shininess = 5;
		scene.addShape(redSphere);

		//
		// Glass Marbles
		// 

		Sphere* blueMarble = new Sphere();
		blueMarble->setTransform(translation(0.6f, 0.7f, -0.6f)
			* scaling(0.7f, 0.7f, 0.7f));
		blueMarble->material.color = Color(0, 0, 0.2f);
		blueMarble->material.ambient = 0.0f;
		blueMarble->material.diffuse = 0.4f;
		blueMarble->material.specular = 0.9f;
		blueMarble->material.shininess = 300;
		blueMarble->material.reflective = 0.4f;
		blueMarble->material.transparency = 0.9f;
		blueMarble->material.refractiveIndex = 1.5f;
		scene.addShape(blueMarble);

		Sphere* greenMarble = new Sphere();
		greenMarble->setTransform(translation(-0.7f, 0.5f, -0.8f)
			* scaling(0.5f, 0.5f, 0.5f));
		greenMarble->material.color = Color(0, 0.2f, 0);
		greenMarble->material.ambient = 0.0f;
		greenMarble->material.diffuse = 0.4f;
		greenMarble->material.specular = 0.9f;
		greenMarble->material.shininess = 300;
		greenMarble->material.reflective = 0.9f;
		greenMarble->material.transparency = 0.9f;
		greenMarble->material.refractiveIndex = 1.5f;
		scene.addShape(greenMarble);

		//
		// Background balls
		//
		Sphere* s1 = new Sphere();
		s1->setTransform(translation(4.6f, 0.4f, 1)
			* scaling(0.4f, 0.4f, 0.4f));
		s1->material.color = Color(0.8f, 0.5f, 0.3f);
		s1->material.shininess = 50;
		scene.addShape(s1);

		Sphere* s2 = new Sphere();
		s2->setTransform(translation(4.7f, 0.3f, 0.4f)
			* scaling(0.3f, 0.3f, 0.3f));
		s2->material.color = Color(0.9f, 0.4f, 0.5f);
		s2->material.shininess = 50;
		scene.addShape(s2);

		Sphere* s3 = new Sphere();
		s3->setTransform(translation(-1.0f, 0.5f, 4.5f)
			* scaling(0.5f, 0.5f, 0.5f));
		s3->material.color = Color(0.4f, 0.9f, 0.6f);
		s3->material.shininess = 50;
		scene.addShape(s3);

		Sphere* s4 = new Sphere();
		s4->setTransform(translation(-1.7f, 0.3f, 4.7f)
			* scaling(0.3f, 0.3f, 0.3f));
		s4->material.color = Color(0.4f, 0.6f, 0.9f);
		s4->material.shininess = 50;
		scene.addShape(s4);
	}

	scene.renderToPPM("rayTraceScene_benchmark", 32);
}

// -----------------------------------------------------------------------

//void spheres(const int sizeScale)
//{
//	SceneConfig config;
//
//	// dimensions and fov
//	config.width = 800 * sizeScale;
//	config.height = 300 * sizeScale;
//	config.fov = PI / 2.7f;
//
//	// camera
//	config.from = Point4(0.0f, 5.0f, -6.0f);
//	config.to = Point4(0.0f, 1.0f, 5.0f);
//	config.up = Vector4(0.0f, 1.0f, 0.0f);
//
//	Scene scene(config);
//
//	// add the lights
//	scene.addLight(PointLight(
//		Point4(0.0f, 7.0f, 0.0f),
//		Color(0.9f)
//	));
//
//	// add the shapes	
//	{
//		Color checkerColor1(0.99f);
//		Color checkerColor2(0.95f);
//		Color babyBlue = rgb(137, 207, 240);
//
//		{
//			Plane floor;
//			CheckerPattern floorPattern(checkerColor1, checkerColor2);
//			floor.material.pattern = &floorPattern;
//			floor.material.ambient = 0.1f;
//			floor.material.reflective = 0.0f;
//			scene.addShape(floor);
//
//			Plane ceiling;
//			ceiling.setTransform(translation(0.0f, 20.0f, 0.0f) * xRotation4x4(PI));
//			ceiling.material.color = Color(1.0f);
//			ceiling.material.ambient = 0.1f;
//			ceiling.material.reflective = 0.0f;
//			scene.addShape(ceiling);
//
//			Plane backWall;
//			backWall.setTransform(translation(1.0f, 0.0f, 15.0f) * xRotation4x4(PI / 2.0f));
//			CheckerPattern backWallPattern(checkerColor1, checkerColor2);
//			backWall.material.pattern = &backWallPattern;
//			backWall.material.ambient = 0.1f;
//			backWall.material.reflective = 0.0f;
//			backWall.material.specular = 0;
//			scene.addShape(backWall);
//
//			Plane behindWall;
//			behindWall.setTransform(translation(1.0f, 0.0f, -25.0f) * xRotation4x4(-PI / 2.0f));
//			behindWall.material.color = Color(1.0f);
//			behindWall.material.ambient = 0.1f;
//			behindWall.material.reflective = 0.0f;
//			behindWall.material.specular = 0;
//			scene.addShape(behindWall);
//		}
//
//		Sphere glassSphere;
//		glassSphere.material = glass(glassSphere.material);
//		glassSphere.setTransform(translation(-6.0f, 1.0f, 4.0f));
//		scene.addShape(glassSphere);
//
//		Sphere glassSphereInside;
//		glassSphereInside.material = glass(glassSphereInside.material);
//		glassSphereInside.setTransform(translation(-6.0f, 1.0f, 4.0f) * scaling(0.9f, 0.9f, 0.9f));
//		scene.addShape(glassSphereInside);
//
//		Sphere matteSphere;
//		matteSphere.material = matte(matteSphere.material, babyBlue);
//		matteSphere.setTransform(translation(-3.0f, 1.0f, 5.0f));
//		scene.addShape(matteSphere);
//
//		Sphere reflectiveMetalSphere;
//		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
//		reflectiveMetalSphere.setTransform(translation(0.0f, 1.0f, 6.0f));
//		scene.addShape(reflectiveMetalSphere);
//
//		Sphere glossySphere;
//		glossySphere.material = gloss(glossySphere.material, babyBlue);
//		glossySphere.setTransform(translation(3.0f, 1.0f, 5.0f));
//		scene.addShape(glossySphere);
//
//		Sphere flatMetalSphere;
//		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
//		flatMetalSphere.setTransform(translation(6.0f, 1.0f, 4.0f));
//		scene.addShape(flatMetalSphere);
//	}
//
//	scene.renderToPPM("spheres");
//}
//
//// -----------------------------------------------------------------------
//
//void cubes(const int sizeScale)
//{
//	SceneConfig config;
//
//	// dimensions and fov
//	config.width = 800 * sizeScale;
//	config.height = 300 * sizeScale;
//	config.fov = PI / 2.3f;
//
//	// camera
//	config.from = Point4(0.0f, 5.0f, -6.0f);
//	config.to = Point4(0.0f, 1.0f, 5.0f);
//	config.up = Vector4(0.0f, 1.0f, 0.0f);
//
//	Scene scene(config);
//
//	// add the lights
//	scene.addLight(PointLight(
//		Point4(0.0f, 7.0f, 0.0f),
//		Color(0.9f)
//	));
//
//	// add the shapes
//	{
//		Color checkerColor1(0.99f);
//		Color checkerColor2(0.95f);
//		Color babyBlue = rgb(137, 207, 240);
//
//
//		{
//			Plane floor;
//			CheckerPattern floorPattern(checkerColor1, checkerColor2);
//			floor.material.pattern = &floorPattern;
//			floor.material.ambient = 0.1f;
//			floor.material.reflective = 0.0f;
//			scene.addShape(floor);
//
//			Plane ceiling;
//			ceiling.setTransform(translation(0.0f, 20.0f, 0.0f) * xRotation4x4(PI));
//			ceiling.material.color = Color(1.0f);
//			ceiling.material.ambient = 0.1f;
//			ceiling.material.reflective = 0.0f;
//			scene.addShape(ceiling);
//
//			Plane backWall;
//			backWall.setTransform(translation(1.0f, 0.0f, 15.0f) * xRotation4x4(PI / 2.0f));
//			CheckerPattern backWallPattern(checkerColor1, checkerColor2);
//			backWall.material.pattern = &backWallPattern;
//			backWall.material.ambient = 0.1f;
//			backWall.material.reflective = 0.0f;
//			backWall.material.specular = 0;
//			scene.addShape(backWall);
//
//			Plane behindWall;
//			behindWall.setTransform(translation(1.0f, 0.0f, -25.0f) * xRotation4x4(-PI / 2.0f));
//			behindWall.material.color = Color(1.0f);
//			behindWall.material.ambient = 0.1f;
//			behindWall.material.reflective = 0.0f;
//			behindWall.material.specular = 0;
//			scene.addShape(behindWall);
//		}
//
//		Cube glassSphere;
//		glassSphere.material = glass(glassSphere.material);
//		glassSphere.setTransform(translation(-6.0f, 1.00001f, 4.0f));
//		scene.addShape(glassSphere);
//
//		/*Cube glassSphereInside;
//		glassSphereInside.material = glass(glassSphereInside.material);
//		glassSphereInside.setTransform(translation(-6.0f, 1.0f, 4.0f) * scaling(0.99999f, 0.99999f, 0.99999f));
//		scene.addShape(glassSphereInside);*/
//
//		Cube matteSphere;
//		matteSphere.material = matte(matteSphere.material, babyBlue);
//		matteSphere.setTransform(translation(-3.0f, 1.0f, 5.0f));
//		scene.addShape(matteSphere);
//
//		Cube reflectiveMetalSphere;
//		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
//		reflectiveMetalSphere.material.reflective = 0.8f;
//		reflectiveMetalSphere.setTransform(translation(0.0f, 1.0f, 6.0f) * yRotation4x4(PI / 4.0f));
//		scene.addShape(reflectiveMetalSphere);
//
//		Cube glossySphere;
//		glossySphere.material = gloss(glossySphere.material, babyBlue);
//		glossySphere.setTransform(translation(3.0f, 1.0f, 5.0f));
//		scene.addShape(glossySphere);
//
//		Cube flatMetalSphere;
//		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
//		flatMetalSphere.setTransform(translation(6.0f, 1.0f, 4.0f));
//		scene.addShape(flatMetalSphere);
//	}
//
//	scene.renderToPPM("cubes");
//}
//
//// -----------------------------------------------------------------------
//
//void cylinders(const int sizeScale)
//{
//	SceneConfig config;
//
//	// dimensions and fov
//	config.width = 800 * sizeScale;
//	config.height = 300 * sizeScale;
//	config.fov = PI / 2.3f;
//
//	// camera
//	config.from = Point4(0.0f, 5.0f, -6.0f);
//	config.to = Point4(0.0f, 1.0f, 5.0f);
//	config.up = Vector4(0.0f, 1.0f, 0.0f);
//
//	Scene scene(config);
//
//	// add the lights
//	scene.addLight(PointLight(
//		Point4(0.0f, 7.0f, 0.0f),
//		Color(0.9f)
//	));
//
//	// add the shapes
//	{
//		Color checkerColor1(0.99f);
//		Color checkerColor2(0.95f);
//		Color babyBlue = rgb(137, 207, 240);
//
//
//		{
//			Plane floor;
//			CheckerPattern floorPattern(checkerColor1, checkerColor2);
//			floor.material.pattern = &floorPattern;
//			floor.material.ambient = 0.1f;
//			floor.material.reflective = 0.0f;
//			scene.addShape(floor);
//
//			Plane ceiling;
//			ceiling.setTransform(translation(0.0f, 20.0f, 0.0f) * xRotation4x4(PI));
//			ceiling.material.color = Color(1.0f);
//			ceiling.material.ambient = 0.1f;
//			ceiling.material.reflective = 0.0f;
//			scene.addShape(ceiling);
//
//			Plane backWall;
//			backWall.setTransform(translation(1.0f, 0.0f, 15.0f) * xRotation4x4(PI / 2.0f));
//			CheckerPattern backWallPattern(checkerColor1, checkerColor2);
//			backWall.material.pattern = &backWallPattern;
//			backWall.material.ambient = 0.1f;
//			backWall.material.reflective = 0.0f;
//			backWall.material.specular = 0;
//			scene.addShape(backWall);
//
//			Plane behindWall;
//			behindWall.setTransform(translation(1.0f, 0.0f, -25.0f) * xRotation4x4(-PI / 2.0f));
//			behindWall.material.color = Color(1.0f);
//			behindWall.material.ambient = 0.1f;
//			behindWall.material.reflective = 0.0f;
//			behindWall.material.specular = 0;
//			scene.addShape(behindWall);
//		}
//
//		Cylinder glassSphere(0.0f, 3.0f, true);
//		glassSphere.material = glass(glassSphere.material);
//		glassSphere.setTransform(translation(-6.0f, 0.0f, 3.0f));
//		scene.addShape(glassSphere);
//
//		Cylinder glassSphereInside(0.0f, 3.0f, true);
//		glassSphereInside.material = glass(glassSphereInside.material);
//		glassSphereInside.setTransform(translation(-6.0f, 0.0f, 3.0f) * scaling(0.99999f, 0.99999f, 0.99999f));
//		scene.addShape(glassSphereInside);
//
//		Cylinder matteSphere(0.0f, 3.0f, true);
//		matteSphere.material = matte(matteSphere.material, babyBlue);
//		matteSphere.setTransform(translation(-2.0f, 0.0f, 5.0f));
//		scene.addShape(matteSphere);
//
//		Cylinder reflectiveMetalSphere(0.0f, 1.0f);
//		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
//		reflectiveMetalSphere.material.reflective = 0.8f;
//		reflectiveMetalSphere.setTransform(translation(0.0f, 0.0f, 5.0f) * scaling(4.5f, 1.0f, 4.5f));
//		scene.addShape(reflectiveMetalSphere);
//
//		Cylinder glossySphere(0.0f, 3.0f, true);
//		glossySphere.material = gloss(glossySphere.material, babyBlue);
//		glossySphere.setTransform(translation(2.0f, 0.0f, 5.0f));
//		scene.addShape(glossySphere);
//
//		Cylinder flatMetalSphere(0.0f, 3.0f, true);
//		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
//		flatMetalSphere.setTransform(translation(6.0f, 0.0f, 3.0f));
//		scene.addShape(flatMetalSphere);
//	}
//
//	scene.renderToPPM("cylinders");
//}

// -----------------------------------------------------------------------

void cubeOfSpheres(const int sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 96 * sizeScale;
	config.height = 54 * sizeScale;
	config.fov = PI / 3.5f;

	// camera
	config.from = Point4(-10.0f, 10.0f, -10.0f);
	//config.from = Point4(0.0f, 10.0f, -10.0f);
	config.to = Point4(0.0f, 2.0f, 2.0f);
	config.up = Vector4(0.0f, 1.0f, 0.0f);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-20.0f, 25.0f, -15.0f),
		Color(0.85f)
	));

	// add the shapes	
	{
		Color checkerColor1(0.99f);
		Color checkerColor2(0.95f);
		Color babyBlue = rgb(137, 207, 240);

		Plane* floor = new Plane();
		//floor.setTransform(translation(0, -3, 0));
		CheckerPattern* floorPattern = new CheckerPattern(checkerColor1, checkerColor2);
		floor->material.pattern = floorPattern;
		floor->material.ambient = 0.1f;
		//floor.material.reflective = 0.5f;
		floor->material.reflective = 0.2f;
		scene.addShape(floor);

		Group* g = new Group();
		g->setTransform(zRotation4x4(PI / 4.0f));
		scene.addShape(g);

		for (int z = 1; z < 6; z++)
		{
			for (int y = 1; y < 6; y++)
			{
				for (int x = -2; x < 3; x++)
				{
					Sphere* s = new Sphere();

					int r = rand() % 8;
					switch (r)
					{
					case 0:
						s->material = metallic(s->material, Color(0.525f, 0.5f, 0.5f));
						break;
					case 1:
						s->material = metallic(s->material, Color(0.5f, 0.525f, 0.5f));
						break;
					case 2:
						s->material = metallic(s->material, Color(0.5f, 0.5f, 0.525f));
						break;
					case 3:
						s->material = metallic(s->material, Color(0.525f, 0.525f, 0.5f));
						break;
					case 4:
						s->material = metallic(s->material, Color(0.525f, 0.5f, 0.525f));
						break;
					case 5:
						s->material = metallic(s->material, Color(0.5f, 0.525f, 0.525f));
						break;
					case 6:
						s->material = matte(s->material, babyBlue);
						break;
					case 7:
						s->material = gloss(s->material, babyBlue);
						break;
					}

					s->setTransform(
						translation((float)x, (float)y, (float)z) *
						scaling(0.5f, 0.5f, 0.5f));
					s->hasShadow = false;
					g->addChild(s);
					//scene.addShape(s);
				}
			}
		}
		/*Sphere glassSphere;
		glassSphere.material = glass(glassSphere.material);
		glassSphere.setTransform(translation(-6.0f, 1.0f, 4.0f));
		scene.addShape(glassSphere);

		Sphere matteSphere;
		matteSphere.material = matte(matteSphere.material, babyBlue);
		matteSphere.setTransform(translation(-3.0f, 1.0f, 5.0f));
		scene.addShape(matteSphere);

		Sphere reflectiveMetalSphere;
		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
		reflectiveMetalSphere.setTransform(translation(0.0f, 1.0f, 6.0f));
		scene.addShape(reflectiveMetalSphere);

		Sphere glossySphere;
		glossySphere.material = gloss(glossySphere.material, babyBlue);
		glossySphere.setTransform(translation(3.0f, 1.0f, 5.0f));
		scene.addShape(glossySphere);

		Sphere flatMetalSphere;
		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
		flatMetalSphere.setTransform(translation(6.0f, 1.0f, 4.0f));
		scene.addShape(flatMetalSphere);*/
	}

	scene.renderToPPM("cubeOfSpheres");
}

// -----------------------------------------------------------------------

void simpleGroup(int sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 100 * sizeScale;
	config.height = 100 * sizeScale;
	config.fov = PI / 3.5f;

	// camera
	config.from = Point4(-10.0f, 10.0f, -10.0f);
	config.to = Point4(0.0f, 2.0f, 2.0f);
	config.up = Vector4(0.0f, 1.0f, 0.0f);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-20.0f, 25.0f, -15.0f),
		Color(0.85f)
	));

	// add the shapes	
	{
		Group* g = new Group();
		//g->setTransform(scaling(2, 2, 2));
		scene.addShape(g);

		Sphere* s = new Sphere();
		s->setTransform(translation(0, 1, 3));
		s->material = gloss(s->material, rgb(20, 50, 200));
		//scene.addShape(s);
		g->addChild(s);
	}

	scene.renderToPPM("simpleGroup", 1);
}

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
#include "..\RayTracerChallengev3\src\Headers.h"

using namespace RayTracer;

void RayTraceScene_Benchmark(double sizeScale);
void spheres(const int sizeScale);
void cubes(const int sizeScale);
void cubeOfSpheres(const double sizeScale);
void simpleGroup();
void scatteredMarbles(int sizeScale, int numMarbles);
void testObjParser(std::string filename);
void utahTeapot(double sizeScale);
void dragon(double sizeScale);

int main()
{
	//Tests::RunTests();
	//testObjParser("assets/obj/gibberish.txt");
	//testObjParser("assets/obj/teapot-low.obj");

	//RayTraceScene_Benchmark(0.5);
	//spheres(2);
	//cubes(2);	
	//cubeOfSpheres(4);
	simpleGroup();
	//scatteredMarbles(10, 500);
	//utahTeapot(1);
	//dragon(4); // 725218ms 12.1m - 2560x1920 - 5 million pixels


	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
	return 0;
}

void testObjParser(std::string filename)
{
	ObjParser parser;
	ObjParseResult result = parser.parse(filename);
}

// -----------------------------------------------------------------------

void RayTraceScene_Benchmark(double sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 320 * sizeScale;
	config.height = 240 * sizeScale;
	config.fov = 1.152f;

	// camera
	config.from = Point4(-2.6f, 1.5f, -3.9f);
	config.to = Point4(-0.6f, 1.0, -0.8f);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-4.9f, 4.9f, -1.0),
		Color(1.0)
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
		floor->material.specular = 0.0;
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
		redSphere->setTransform(translation(-0.6f, 1.0, 0.6f));
		redSphere->material.color = Color(1.0, 0.3f, 0.2f);
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
		blueMarble->material.ambient = 0.0;
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
		greenMarble->material.ambient = 0.0;
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
		s3->setTransform(translation(-1.0, 0.5f, 4.5f)
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

void spheres(const int sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 800 * sizeScale;
	config.height = 300 * sizeScale;
	config.fov = PI / 2.7;

	// camera
	config.from = Point4(0.0, 5.0, -6.0);
	config.to = Point4(0.0, 1.0, 5.0);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(0.0, 7.0, 0.0),
		Color(0.9)
	));

	// add the shapes	
	{
		Color checkerColor1(0.99);
		Color checkerColor2(0.95);
		Color babyBlue = rgb(137, 207, 240);

		{
			Cube* bounding = new Cube();
			CheckerPattern* boundingPattern = new CheckerPattern(checkerColor1, checkerColor2);
			boundingPattern->setTransform(scaling(0.25, 1.0, 0.25));
			bounding->material.pattern = boundingPattern;
			bounding->setTransform(translation(0.0, 15.0, 0.0) * scaling(15.0, 15.0, 15.0));
			scene.addShape(bounding);
		}

		Sphere* glassSphere = new Sphere();
		glassSphere->material = glass(glassSphere->material);
		glassSphere->setTransform(translation(-6.0, 1.0, 4.0));
		scene.addShape(glassSphere);

		Sphere* glassSphereInside = new Sphere();
		glassSphereInside->material = glass(glassSphereInside->material);
		glassSphereInside->setTransform(translation(-6.0, 1.0, 4.0) * scaling(0.9, 0.9, 0.9));
		scene.addShape(glassSphereInside);

		Sphere* matteSphere = new Sphere();
		matteSphere->material = matte(matteSphere->material, babyBlue);
		matteSphere->setTransform(translation(-3.0, 1.0, 5.0));
		scene.addShape(matteSphere);

		Sphere* reflectiveMetalSphere = new Sphere();
		reflectiveMetalSphere->material = metal(reflectiveMetalSphere->material);
		reflectiveMetalSphere->setTransform(translation(0.0, 1.0, 6.0));
		scene.addShape(reflectiveMetalSphere);

		Sphere* glossySphere = new Sphere();
		glossySphere->material = gloss(glossySphere->material, babyBlue);
		glossySphere->setTransform(translation(3.0, 1.0, 5.0));
		scene.addShape(glossySphere);

		Sphere* flatMetalSphere = new Sphere();
		flatMetalSphere->material = metallic(flatMetalSphere->material, Color(0.5, 0.525, 0.5));
		flatMetalSphere->setTransform(translation(6.0, 1.0, 4.0));
		scene.addShape(flatMetalSphere);
	}

	scene.renderToPPM("spheres");
}

// -----------------------------------------------------------------------

void cubes(const int sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 800 * sizeScale;
	config.height = 300 * sizeScale;
	config.fov = PI / 2.3;

	// camera
	config.from = Point4(0.0, 5.0, -6.0);
	config.to = Point4(0.0, 1.0, 5.0);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(0.0, 7.0, 0.0),
		Color(0.9)
	));

	// add the shapes
	{
		Color checkerColor1(0.99);
		Color checkerColor2(0.95);
		Color babyBlue = rgb(137, 207, 240);


		{
			Cube* bounding = new Cube();
			CheckerPattern* boundingPattern = new CheckerPattern(checkerColor1, checkerColor2);
			boundingPattern->setTransform(scaling(0.25, 1.0, 0.25));
			bounding->material.pattern = boundingPattern;
			bounding->setTransform(translation(0.0, 15.0, 0.0) * scaling(15.0, 15.0, 15.0));
			scene.addShape(bounding);
		}

		Cube* glassSphere = new Cube();
		glassSphere->material = glass(glassSphere->material);
		glassSphere->setTransform(translation(-6.0, 1.00001, 4.0));
		scene.addShape(glassSphere);

		Cube* glassSphereInside = new Cube();
		glassSphereInside->material = glass(glassSphereInside->material);
		glassSphereInside->setTransform(translation(-6.0, 1.0, 4.0) * scaling(0.99999, 0.99999, 0.99999));
		scene.addShape(glassSphereInside);

		Cube* matteSphere = new Cube();
		matteSphere->material = matte(matteSphere->material, babyBlue);
		matteSphere->setTransform(translation(-3.0, 1.0, 5.0));
		scene.addShape(matteSphere);

		Cube* reflectiveMetalSphere = new Cube();
		reflectiveMetalSphere->material = metal(reflectiveMetalSphere->material);
		reflectiveMetalSphere->material.reflective = 0.8;
		reflectiveMetalSphere->setTransform(translation(0.0, 1.0, 6.0) * yRotation4x4(PI / 4.0));
		scene.addShape(reflectiveMetalSphere);

		Cube* glossySphere = new Cube();
		glossySphere->material = gloss(glossySphere->material, babyBlue);
		glossySphere->setTransform(translation(3.0, 1.0, 5.0));
		scene.addShape(glossySphere);

		Cube* flatMetalSphere = new Cube();
		flatMetalSphere->material = metallic(flatMetalSphere->material, Color(0.5, 0.525, 0.5));
		flatMetalSphere->setTransform(translation(6.0, 1.0, 4.0));
		scene.addShape(flatMetalSphere);
	}

	scene.renderToPPM("cubes");
}

// -----------------------------------------------------------------------

void cubeOfSpheres(const double sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 640 * sizeScale;
	config.height = 480 * sizeScale;
	config.fov = PI / 3.5f;

	// camera
	config.from = Point4(-12.0, 13.0, -15.0);
	//config.from = Point4(0.0, 10.0, -10.0);
	config.to = Point4(-2.0, 5.0f, 2.0f);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-20.0, 25.0f, -15.0f),
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
		//g->setTransform(zRotation4x4(PI / 4.0f));
		scene.addShape(g);

		for (int z = 1; z < 11; z++)
		{
			for (int y = 1; y < 11; y++)
			{
				for (int x = -5; x < 6; x++)
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
						translation((double)x, (double)y, (double)z) *
						scaling(0.5f, 0.5f, 0.5f));
					s->hasShadow = false;
					g->addChild(s);
					//scene.addShape(s);
				}
			}
		}

		g->divide(10);
	}

	scene.renderToPPM("cubeOfSpheres");
}

// -----------------------------------------------------------------------

void simpleGroup()
{
	RayTracer::SceneConfig config;

	// dimensions and fov
	config.width = 800;
	config.height = 600;
	config.fov = PI / 2.7;

	// camera
	config.from = RayTracer::Point4(0.0, 1.75, -2.75);
	config.to = RayTracer::Point4(0.0, 1.0, 0.0);
	config.up = RayTracer::Vector4(0.0, 1.0, 0.0);

	RayTracer::Scene scene(config);

	// add the lights
	scene.addLight(RayTracer::PointLight(
		RayTracer::Point4(-5.0, 10.0, -5.0),
		RayTracer::Color(0.9)
	));

	{
		RayTracer::Color checkerColor1(0.99);
		RayTracer::Color checkerColor2(0.95);

		// checkered plane
		RayTracer::Plane* floor = new RayTracer::Plane();
		RayTracer::CheckerPattern* floorPattern = new RayTracer::CheckerPattern(checkerColor1, checkerColor2);
		floor->material.pattern = floorPattern;
		floor->material.ambient = 0.1f;
		scene.addShape(floor);

		RayTracer::Plane* backWall = new RayTracer::Plane();
		backWall->material.color = checkerColor2;
		backWall->material.reflective = 0.0;
		backWall->material.ambient = 0.1f;
		backWall->material.specular = 0.0f;
		backWall->setTransform(RayTracer::translation(0.0, 0.0, 7.0) * RayTracer::xRotation4x4(-PI / 2));
		scene.addShape(backWall);

		RayTracer::Sphere* sphere = new RayTracer::Sphere();
		sphere->setTransform(RayTracer::translation(0.0, 1.0, 0.0));
		sphere->material.color = RayTracer::rgb(168, 137, 201);
		sphere->material.specular = 0.3;
		sphere->material.shininess = 50.0;
		sphere->material.diffuse = 0.9;
		sphere->material.ambient = 0.1;
		scene.addShape(sphere);
	}

	scene.renderToPPM("../_images/sfmlScene");
}

// -----------------------------------------------------------------------

void scatteredMarbles(int sizeScale, int numMarbles)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 96 * sizeScale;
	config.height = 54 * sizeScale;
	config.fov = PI / 3.5f;

	// camera
	config.from = Point4(0.0, 7.0f, -30.0);
	config.to = Point4(0.0, 0.0, -10.0);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-30.0, 55.0f, 10.0),
		Color(0.85f)
	));

	// add the shapes	
	{
		Plane* floor = new Plane();
		floor->material = matte(floor->material, rgb(223, 202, 160));
		scene.addShape(floor);

		for (int i = 0; i < numMarbles; i++)
		{
			double x = (double)((rand() % 75) - 25);
			double z = (double)((rand() % 75) - 25);

			double scale = 1.0;
			int rScale = rand() % 3;
			switch (rScale)
			{
			case 0:
				scale = 1.0;
				break;
			case 1:
				scale = 1.5f;
				break;
			case 2:
				scale = 0.5f;
				break;
			}

			Sphere* s = new Sphere();
			s->setTransform(translation(x, scale, z) * scaling(scale, scale, scale));
			//s->material = gloss(s->material, rgb(152, 188, 89));			

			int r = rand() % 5;
			switch (r)
			{
			case 0:
			case 1:
				s->material = glass(s->material);
				break;
			case 2:
			case 3:
				s->material = metallic(s->material, Color(0.5f, 0.525f, 0.5f));
				break;
			case 4:
				s->material = metal(s->material);
				break;
			}

			//s->material = matte(s->material, rgb(152, 188, 89));			
			scene.addShape(s);
		}
	}

	scene.renderToPPM("scatteredMarbles");
}

// -----------------------------------------------------------------------

void utahTeapot(double sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 320 * sizeScale;
	config.height = 240 * sizeScale;
	config.fov = PI / 3.5f;

	// camera
	config.from = Point4(0.0, 20.0f, -40.0);
	config.to = Point4(0.0, 8.0, 0.0);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-45.0, 35.0f, -35.0),
		Color(0.85f)
	));

	// add the shapes	
	{
		Color checkerColor1(0.99);
		Color checkerColor2(0.95);

		Plane* floor = new Plane();
		CheckerPattern* floorPattern = new CheckerPattern(checkerColor1, checkerColor2);
		floor->material.pattern = floorPattern;
		floor->material.ambient = 0.1;
		floor->material.reflective = 0.5;
		scene.addShape(floor);

		ObjParser parser(false);
		ObjParseResult result = parser.parse("../_3d Models/teapot.obj");
		//ObjParseResult result = parser.parse("assets/obj/teapot-low.obj");

		result.defaultGroup->divide(3);
		result.defaultGroup->setTransform(yRotation4x4(PI / 6) * xRotation4x4(-PI / 2));
		scene.addShape(result.defaultGroup);

		Material* m = new Material();
		m->color = rgb(46, 179, 59);
		result.defaultGroup->setMaterial(*m);
	}

	scene.renderToPPM("../_images/utahTeapot_high");
	//scene.renderToPPM("utahTeapot_low");
}

// -----------------------------------------------------------------------

void dragon(double sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 320 * sizeScale;
	config.height = 240 * sizeScale;
	config.fov = PI / 3.5f;

	// camera
	config.from = Point4(-15.0, 15.0f, -30.0);
	config.to = Point4(0.0, 5.0, 0.0);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-15.0, 15.0f, -15.0),
		Color(0.85f)
	));

	// add the shapes	
	{
		Color checkerColor1(0.99);
		Color checkerColor2(0.95);

		Plane* floor = new Plane();
		CheckerPattern* floorPattern = new CheckerPattern(checkerColor1, checkerColor2);
		floor->material.pattern = floorPattern;
		floor->material.ambient = 0.1;
		floor->material.reflective = 0.5;
		scene.addShape(floor);

		ObjParser parser;
		ObjParseResult result = parser.parse("assets/obj/dragon.obj");

		Group* g = new Group();
		g->setTransform(scaling(3.0, 3.0, 3.0));
		scene.addShape(g);

		for (auto dfIter = result.defaultGroup->children.begin(); dfIter != result.defaultGroup->children.end(); dfIter++)
		{
			(*dfIter)->material = gloss((*dfIter)->material, rgb(255, 0, 25));
			g->addChild(*dfIter);
		}

		g->divide(5);
	}

	scene.renderToPPM("dragon");
}

// -----------------------------------------------------------------------
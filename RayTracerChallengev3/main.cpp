#include "src/Headers.h"

using namespace RayTracer;

void RayTraceScene_Benchmark();
void spheres(const int sizeScale);
void cubes(const int sizeScale);
void cubeOfSpheres(const int sizeScale);
void simpleGroup(int sizeScale);
void scatteredMarbles(int sizeScale, int numMarbles);
void testObjParser(std::string filename);
void utahTeapot(double sizeScale);
void objCube(double sizeScale);

int main()
{
	//Tests::RunTests();
	//testObjParser("assets/obj/gibberish.txt");
	//testObjParser("assets/obj/teapot-low.obj");

	//RayTraceScene_Benchmark();
	//spheres(2);
	//cubes(2);	
	//cubeOfSpheres(10);
	//simpleGroup(10);
	//scatteredMarbles(10, 500);
	utahTeapot(6);
	//objCube(1);


	// PASSES
	// Scenario: Querying a shape's bounding box in its parent's space 
	/*Sphere* shape = new Sphere();
	shape->setTransform(translation(1.0, -3.0, 5.0) * scaling(0.5, 2.0, 4.0));
	BoundingBox bb;
	BoundingBox box = bb.parentSpaceBoundsOf(*shape);
	int i = 0;*/



	// Scenario: A group has a bounding box that contains its children
	/*Sphere* s = new Sphere();
	s->setTransform(translation(2.0, 5.0, -3.0) * scaling(2.0, 2.0, 2.0));
	Cylinder *c = new Cylinder();
	c->minimum = -2.0;
	c->maximum = 2.0;
	c->setTransform(translation(-4.0, -1.0, 4.0) * scaling(0.5, 1.0, 0.5));
	Group* shape = new Group();
	shape->addChild(s);
	shape->addChild(c);
	BoundingBox box = shape->localBounds();*/










	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
	return 0;
}

void testObjParser(std::string filename)
{
	ObjParser parser;
	ObjParseResult result = parser.parse(filename);	
}

// -----------------------------------------------------------------------

void RayTraceScene_Benchmark()
{
	SceneConfig config;

	// dimensions and fov
	config.width = 3840;
	config.height = 2160;
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
			boundingPattern->setTransform(scaling(0.25, 1.0 , 0.25));
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

void cubeOfSpheres(const int sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 96 * sizeScale;
	config.height = 54 * sizeScale;
	config.fov = PI / 3.5f;

	// camera
	config.from = Point4(-10.0, 10.0, -10.0);
	//config.from = Point4(0.0, 10.0, -10.0);
	config.to = Point4(0.0, 2.0f, 2.0f);
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
						translation((double)x, (double)y, (double)z) *
						scaling(0.5f, 0.5f, 0.5f));
					s->hasShadow = false;
					g->addChild(s);
					//scene.addShape(s);
				}
			}
		}
		/*Sphere glassSphere;
		glassSphere.material = glass(glassSphere.material);
		glassSphere.setTransform(translation(-6.0f, 1.0, 4.0f));
		scene.addShape(glassSphere);

		Sphere matteSphere;
		matteSphere.material = matte(matteSphere.material, babyBlue);
		matteSphere.setTransform(translation(-3.0f, 1.0, 5.0f));
		scene.addShape(matteSphere);

		Sphere reflectiveMetalSphere;
		reflectiveMetalSphere.material = metal(reflectiveMetalSphere.material);
		reflectiveMetalSphere.setTransform(translation(0.0, 1.0, 6.0f));
		scene.addShape(reflectiveMetalSphere);

		Sphere glossySphere;
		glossySphere.material = gloss(glossySphere.material, babyBlue);
		glossySphere.setTransform(translation(3.0f, 1.0, 5.0f));
		scene.addShape(glossySphere);

		Sphere flatMetalSphere;
		flatMetalSphere.material = metallic(flatMetalSphere.material, Color(0.5f, 0.525f, 0.5f));
		flatMetalSphere.setTransform(translation(6.0f, 1.0, 4.0f));
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
	config.from = Point4(-10.0, 10.0, -10.0);
	config.to = Point4(0.0, 2.0f, 2.0f);
	config.up = Vector4(0.0, 1.0, 0.0);

	Scene scene(config);

	// add the lights
	scene.addLight(PointLight(
		Point4(-20.0, 25.0f, -15.0f),
		Color(0.85f)
	));

	// add the shapes	
	{
		Group* g = new Group();
		g->setTransform(scaling(4, 3, 4));
		scene.addShape(g);
				
		Point4 p1(-1.0, -1.0, -1.0);
		Point4 p2(1.0, -1.0, -1.0);
		Point4 p3(0.0, -1.0, 1.0);
		Point4 p4(0.0, 1.0, 0.0);

		Triangle* t1 = new Triangle(p1, p2, p4);
		t1->material.color = rgb(255, 0, 0);
		//scene.addShape(t1);

		Triangle* t2 = new Triangle(p2, p3, p4);
		t2->material.color = rgb(0, 255, 0);
		//scene.addShape(t2);

		Triangle* t3 = new Triangle(p3, p1, p4);
		t3->material.color = rgb(0, 0, 255);
		//scene.addShape(t3);

		Triangle* t4 = new Triangle(p1, p2, p3);
		t4->material.color = rgb(255, 255, 255);
		//scene.addShape(t4);

		g->addChild(t1);
		g->addChild(t2);
		g->addChild(t3);
		g->addChild(t4);
	}

	scene.renderToPPM("triangles", 1);
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

		ObjParser parser;
		ObjParseResult result = parser.parse("assets/obj/teapot.obj");
		//ObjParseResult result = parser.parse("assets/obj/teapot.obj");
				
		for (auto dfIter = result.defaultGroup->children.begin(); dfIter != result.defaultGroup->children.end(); dfIter++)
		{			
			int numTriangles = 0;
			int maxPerGroup = 10;
			Group* g = 0;
			for (auto gIter = ((Group*)*dfIter)->children.begin(); gIter != ((Group*)*dfIter)->children.end(); gIter++)
			{
				if (numTriangles % maxPerGroup == 0)
				{
					if(g != 0) scene.addShape(g);

					g = new Group();
					g->setTransform(xRotation4x4(-PI / 2));
				}
				
				(*gIter)->material.color = rgb(46, 179, 59);				
				g->addChild(*gIter);

				numTriangles++;
			}
			scene.addShape(g);
		}

		//result.defaultGroup->setTransform(xRotation4x4(-PI / 2));
		//scene.addShape(result.defaultGroup);
	}

	scene.renderToPPM("utahTeapot_high");
}

// -----------------------------------------------------------------------

void objCube(double sizeScale)
{
	SceneConfig config;

	// dimensions and fov
	config.width = 640 * sizeScale;
	config.height = 480 * sizeScale;
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
		floor->material.reflective = 0.0;
		scene.addShape(floor);

		ObjParser parser;
		ObjParseResult result = parser.parse("assets/obj/cube.txt");
		
		for (auto dfIter = result.defaultGroup->children.begin(); dfIter != result.defaultGroup->children.end(); dfIter++)
		{			
			for (auto gIter = ((Group*)*dfIter)->children.begin(); gIter != ((Group*)*dfIter)->children.end(); gIter++)
			{				
				(*gIter)->material = matte((*gIter)->material, rgb(50, 180, 75));
			}			

			(*dfIter)->setTransform(translation(0.0, 5.0000000001, 0.0) * scaling(5.0, 5.0, 5.0));
			scene.addShape(*dfIter);
		}		
	}

	scene.renderToPPM("triangleCube");
}

// -----------------------------------------------------------------------
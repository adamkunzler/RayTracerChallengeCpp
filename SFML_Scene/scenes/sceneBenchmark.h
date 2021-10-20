#pragma once

using namespace RayTracer;

RayTracer::Scene& sceneBenchmark(int width, int height);

// width = 640, height = 480
RayTracer::Scene& sceneBenchmark(int width, int height)
{
	SceneConfig config;

	// dimensions and fov
	config.width = width;
	config.height = height;
	config.fov = 1.152f;

	// camera
	config.from = Point4(-2.6f, 1.5f, -3.9f);
	config.to = Point4(-0.6f, 1.0, -0.8f);
	config.up = Vector4(0.0, 1.0, 0.0);

	RayTracer::Scene* scene = new RayTracer::Scene(config);

	// add the lights	
	if (false)
	{
		PointLight* light = new PointLight(
			Point4(-4.9f, 4.9f, -1.0),
			Color(1.0)
		);
		scene->addLight(light);
	}
	else
	{
		AreaLight* light = new AreaLight(
			RayTracer::Point4(-6, 6, -1),
			RayTracer::Vector4(2, 0, 0), 10,
			RayTracer::Vector4(0, 2, 0), 10,
			RayTracer::Color(1.5, 1.5, 1.5)
		);
		scene->addLight(light);
	}

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
		scene->addShape(floor);

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
		scene->addShape(westWall);

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
		scene->addShape(eastWall);

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
		scene->addShape(northWall);

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
		scene->addShape(southWall);

		//
		// Big Red Ball
		//
		Sphere* redSphere = new Sphere();
		redSphere->setTransform(translation(-0.6f, 1.0, 0.6f));
		redSphere->material.color = Color(1.0, 0.3f, 0.2f);
		redSphere->material.specular = 0.4f;
		redSphere->material.shininess = 5;
		scene->addShape(redSphere);

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
		scene->addShape(blueMarble);

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
		scene->addShape(greenMarble);

		//
		// Background balls
		//
		Sphere* s1 = new Sphere();
		s1->setTransform(translation(4.6f, 0.4f, 1)
			* scaling(0.4f, 0.4f, 0.4f));
		s1->material.color = Color(0.8f, 0.5f, 0.3f);
		s1->material.shininess = 50;
		scene->addShape(s1);

		Sphere* s2 = new Sphere();
		s2->setTransform(translation(4.7f, 0.3f, 0.4f)
			* scaling(0.3f, 0.3f, 0.3f));
		s2->material.color = Color(0.9f, 0.4f, 0.5f);
		s2->material.shininess = 50;
		scene->addShape(s2);

		Sphere* s3 = new Sphere();
		s3->setTransform(translation(-1.0, 0.5f, 4.5f)
			* scaling(0.5f, 0.5f, 0.5f));
		s3->material.color = Color(0.4f, 0.9f, 0.6f);
		s3->material.shininess = 50;
		scene->addShape(s3);

		Sphere* s4 = new Sphere();
		s4->setTransform(translation(-1.7f, 0.3f, 4.7f)
			* scaling(0.3f, 0.3f, 0.3f));
		s4->material.color = Color(0.4f, 0.6f, 0.9f);
		s4->material.shininess = 50;
		scene->addShape(s4);
	}

	return *scene;
}
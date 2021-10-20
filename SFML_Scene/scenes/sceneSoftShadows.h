#pragma once

RayTracer::Scene& sceneSoftShadows(int width, int height);

// width = 640, height = 288 
RayTracer::Scene& sceneSoftShadows(int width, int height)
{
	RayTracer::SceneConfig config;

	// dimensions and fov
	config.width = width; // 400
	config.height = height; // 160
	config.fov = 0.7854;

	// camera
	config.from = RayTracer::Point4(-3.0, 1.0, 2.5);
	config.to = RayTracer::Point4(0, 0.5, 0.0);
	config.up = RayTracer::Vector4(0.0, 1.0, 0.0);

	RayTracer::Scene* scene = new RayTracer::Scene(config);
		
	RayTracer::AreaLight* light = new RayTracer::AreaLight(
		RayTracer::Point4(-1, 2, 4),
		RayTracer::Vector4(5, 0, 0), 8,
		RayTracer::Vector4(0, 5, 0), 8,
		RayTracer::Color(1.5, 1.5, 1.5));
	//light->shouldJitter = false;
	scene->addLight(light);	

	{
		RayTracer::Cube* theLight = new RayTracer::Cube();
		theLight->material.color = RayTracer::Color(1.5, 1.5, 1.5);
		theLight->material.ambient = 1;
		theLight->material.diffuse = 0;
		theLight->material.specular = 0;
		theLight->setTransform(RayTracer::translation(0, 3, 4) * RayTracer::scaling(1, 1, 0.01));
		theLight->hasShadow = false;
		scene->addShape(theLight);

		RayTracer::Plane* floor = new RayTracer::Plane();
		floor->material.color = RayTracer::Color(1, 1, 1);
		floor->material.ambient = 0.025;
		floor->material.diffuse = 0.67;
		floor->material.specular = 0;
		scene->addShape(floor);

		RayTracer::Sphere* bigSphere = new RayTracer::Sphere();
		bigSphere->material.color = RayTracer::Color(1, 0, 0);
		bigSphere->material.ambient = 0.1;
		bigSphere->material.diffuse = 0.6;
		bigSphere->material.reflective = 0.3;
		bigSphere->material.specular = 0;
		bigSphere->setTransform(RayTracer::translation(0.5, 0.5, 0) * RayTracer::scaling(0.5, 0.5, 0.5));
		scene->addShape(bigSphere);

		RayTracer::Sphere* smallSphere = new RayTracer::Sphere();
		smallSphere->material.color = RayTracer::Color(0.5, 0.5, 1);
		smallSphere->material.ambient = 0.1;
		smallSphere->material.diffuse = 0.6;
		smallSphere->material.reflective = 0.3;
		smallSphere->material.specular = 0;
		smallSphere->setTransform(RayTracer::translation(-0.25, 0.33, 0) * RayTracer::scaling(0.33, 0.33, 0.33));
		//smallSphere->hasShadow = false;
		scene->addShape(smallSphere);
	}

	return *scene;
}
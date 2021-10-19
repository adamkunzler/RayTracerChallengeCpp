#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{

	Scene::Scene(const SceneConfig& config)
	{
		world = new World();
		camera = new Camera(config.width, config.height, config.fov);
		camera->setTransform(viewTransform(config.from, config.to, config.up));
	}

	Scene::~Scene()
	{
		delete world;
		delete camera;
	}

	void Scene::addLight(ILight* light) const
	{
		world->lights.push_back(light);
	}

	void Scene::addShape(IShape* shape) const
	{
		world->objects.push_back(shape);
	}

	void Scene::render(std::vector<Color>& pixels, const int numThreads)
	{
		//std::cout << "\nRendering scene...\n\n";
		//auto start = std::chrono::high_resolution_clock::now();

		// -----
		std::vector<Color*> datas = RayTracer::renderMultiThread(*camera, *world, false, numThreads);
		// -----
		
		Canvas image((int)camera->hSize, (int)camera->vSize);
		int index = 0;
		int yStep = (int)camera->vSize / numThreads;
		for (int i = 0; i < datas.size(); i++) // each threads data
		{
			for (int j = 0; j < camera->hSize * yStep; j++) // each color in each data
			{
				image.setPixel(index, datas[i][j]);				
				index++;
			}
		}
		pixels = image.pixels;

		for (auto& p : datas) {
			delete[] p;
		}

		//auto stop = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		//long long durationCount = duration.count();
		//std::cout << "\n\nScene completed in " << durationCount << "ms (" << (durationCount / 1000) << "s)\n";		
	}

	void Scene::renderToPPM(const std::string baseFilename, const int numThreads)
	{
		std::cout << "\nRendering scene...\n\n";
		auto start = std::chrono::high_resolution_clock::now();

		// -----
		std::vector<Color*> datas = RayTracer::renderMultiThread(*camera, *world, true, numThreads);
		// -----

		// create canvas from color vector
		Canvas image((int)camera->hSize, (int)camera->vSize);
		int index = 0;
		int yStep = (int)camera->vSize / numThreads;
		for (int i = 0; i < datas.size(); i++) // each threads data
		{
			for (int j = 0; j < camera->hSize * yStep; j++) // each color in each data
			{
				image.setPixel(index, datas[i][j]);
				index++;
			}
		}

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		long long durationCount = duration.count();
		std::cout << "\n\nScene completed in " << durationCount << "ms (" << (durationCount / 1000) << "s)\n";

		// save the image to disk
		std::string filename = baseFilename + "_" + std::to_string(camera->hSize) + "x" + std::to_string(camera->vSize) + ".ppm";
		image.toPPM(filename);
	}
}
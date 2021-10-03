#pragma once

namespace RayTracer
{
	struct SceneConfig
	{
		int width;
		int height;
		float fov;

		Vector4 from;
		Vector4 to;
		Vector4 up;

		SceneConfig() { }
	};

	class Scene
	{	
	private:
		World* world;
		Camera* camera;

	public:
		Scene(const SceneConfig& config) 
		{
			world = new World();
			camera = new Camera(config.width, config.height, config.fov);
			camera->setTransform(viewTransform(config.from, config.to, config.up));
		}

		~Scene() 
		{
			delete world;
			delete camera;
		}

		void addLight(const PointLight& light) const
		{
			world->lights.push_back(light);
		}

		void addShape(IShape& shape) const
		{
			world->objects.push_back(&shape);
		}

		void renderToPPM(const std::string baseFilename)
		{			
			std::cout << "\nRendering scene...\n\n";
			auto start = std::chrono::high_resolution_clock::now();

			// -----
			RayTracer::Canvas image = RayTracer::renderMultiThread(*camera, *world, 32);
			// -----

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			long long durationCount = duration.count();
			std::cout << "\n\nScene completed in " << durationCount << "ms (" << (durationCount / 1000) << "s)\n";

			// save the image to disk
			std::string filename = "images/" + baseFilename + "_" + std::to_string(camera->hSize) + "x" + std::to_string(camera->vSize) + ".ppm";
			image.toPPM(filename);
		}
	};
}
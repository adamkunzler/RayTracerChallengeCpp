#pragma once

namespace RayTracer
{	
	class Scene
	{	
	public:
		World* world;
		Camera* camera;

	public:
		Scene(const SceneConfig& config);

		~Scene();

		void addLight(ILight* light) const;

		void addShape(IShape* shape) const;

		void render(std::vector<Color>& pixels, const int numThreads = 32);

		void renderToPPM(const std::string baseFilename, const int numThreads = 32);
	};
}

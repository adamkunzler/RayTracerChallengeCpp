#ifndef SCENE_H
#define SCENE_H

namespace RayTracer
{	
	class Scene
	{	
	private:
		World* world;
		Camera* camera;

	public:
		Scene(const SceneConfig& config);

		~Scene();

		void addLight(const PointLight& light) const;

		void addShape(IShape* shape) const;

		void renderToPPM(const std::string baseFilename, const int numThreads = 32);
	};
}

#endif
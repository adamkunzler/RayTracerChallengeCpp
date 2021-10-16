#pragma once

namespace RayTracer
{				
	struct World
	{	
		std::vector<IShape*> objects;
		std::vector<PointLight> lights; // TODO ILight interface to support different types of lights

		World();
		~World();
						
		void intersectBy(const Ray& r, std::vector<std::shared_ptr<Intersection>>& intersections) const;

		Computation prepareComputations(const Intersection& i, const Ray& r, const std::vector<std::shared_ptr<Intersection>>& intersections) const;

		Color shadeHit(const Computation& c, const int remaining, std::vector<std::shared_ptr<Intersection>>& intersections) const;

		Color colorAt(const Ray& ray, const int remaining, std::vector<std::shared_ptr<Intersection>>& intersections) const;

		Color reflectedColor(const Computation& comps, const int remaining) const;

		Color refractedColor(const Computation& comps, const int remaining) const;

		double schlick(const Computation& comps) const;

		bool isShadowed(const PointLight& light, const Vector4& p) const;
	};	
	
}


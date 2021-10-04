#ifndef WORLD_H
#define WORLD_H

namespace RayTracer
{				
	struct World
	{	
		std::vector<IShape*> objects;
		std::vector<PointLight> lights; // TODO ILight interface to support different types of lights

		World() { }		
						
		void intersectBy(const Ray& r, std::vector<Intersection>& intersections) const;

		Computation prepareComputations(const Intersection& i, const Ray& r, const std::vector<Intersection>& intersections) const;

		Color shadeHit(const Computation& c, const int remaining, std::vector<Intersection>& intersections) const;

		Color colorAt(const Ray& ray, const int remaining, std::vector<Intersection>& intersections) const;

		Color reflectedColor(const Computation& comps, const int remaining) const;

		Color refractedColor(const Computation& comps, const int remaining) const;

		float schlick(const Computation& comps) const;

		bool isShadowed(const PointLight& light, const Vector4& p) const;
	};	
	
}

#endif
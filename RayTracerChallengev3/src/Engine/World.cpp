#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	World::World()
	{ 
		objects.reserve(500);
		lights.reserve(10);
	}

	World::~World()
	{
		for (auto obj : objects) delete obj;
		objects.clear();
	}

	void World::intersectBy(const Ray& r, std::vector<std::shared_ptr<Intersection>>& intersections) const
	{
		for (std::vector<IShape*>::const_iterator iter = objects.begin(); iter != objects.end(); iter++)
		{				
			(*iter)->intersectBy(r, intersections);
		}
	}

	Computation World::prepareComputations(const Intersection& i, const Ray& r, const std::vector<std::shared_ptr<Intersection>>& intersections) const
	{
		Computation c;

		Vector4 dir(r.direction);

		//
		// calculate n1, n2
		//			
		std::vector<IShape*> container;

		for (std::vector<std::shared_ptr<Intersection>>::const_iterator iter = intersections.begin(); iter != intersections.end(); iter++)
		{
			if (*(*iter) == i)
			{
				if (container.size() == 0)
				{
					c.n1 = 1.0;
				}
				else
				{
					c.n1 = container[container.size() - 1]->material.refractiveIndex;
				}
			}

			std::vector<IShape*>::iterator found = std::find(container.begin(), container.end(), (*iter)->object);
			if (found != container.end())
			{
				container.erase(found);
			}
			else
			{
				container.push_back((*iter)->object);
			}

			if (*(*iter) == i)
			{
				if (container.size() == 0)
				{
					c.n2 = 1.0;
				}
				else
				{
					c.n2 = container[container.size() - 1]->material.refractiveIndex;
				}

				break;
			}
		} // end for

		//
		// calculate everything else
		//
		c.t = i.t;
		c.object = i.object;
		c.point = r.position(i.t);
		c.eyeV = -dir;
		c.normalV = i.object->normalAt(c.point, i);
		c.isInside = false;

		double d = dot(c.normalV, c.eyeV);
		if (d < 0)
		{
			c.isInside = true;
			c.normalV = -c.normalV;
		}

		c.reflectV = dir.reflect(c.normalV);
		c.overPoint = c.point + (c.normalV * 0.0001);
		c.farOverPoint = c.point + (c.normalV * DBL_EPSILON);
		c.underPoint = c.point - (c.normalV * 0.0001);

		return c;
	}

	Color World::shadeHit(const Computation& c, const int remaining, std::vector<std::shared_ptr<Intersection>>& intersections) const
	{
		Color finalColor;
		for (std::vector<ILight*>::const_iterator iter = lights.begin(); iter != lights.end(); iter++)
		{
			//bool isInShadow = isShadowed((*iter)->position, c.overPoint);
			//double lightIntensity = isInShadow ? (*iter)->intensityAt(c.overPoint, *this) : 1.0;
			double lightIntensity = (*iter)->intensityAt(c.overPoint, *this);

			Color surface = phong(*iter, c.object->material, *c.object, c.farOverPoint, c.eyeV, c.normalV, lightIntensity);
			Color reflected = reflectedColor(c, remaining);
			Color refracted = refractedColor(c, remaining);

			Material m(c.object->material);
			if (m.reflective > 0.0 && m.transparency > 0.0)
			{
				double reflectance = schlick(c);
				finalColor = finalColor + surface
					+ reflected * reflectance
					+ refracted * (1.0 - reflectance);
			}
			else
			{
				finalColor = finalColor + surface + reflected + refracted;
			}			
		}		
		
		return finalColor;
	}

	Color World::colorAt(const Ray& ray, const int remaining, std::vector<std::shared_ptr<Intersection>>& intersections) const
	{
		Ray rayCopy(ray);

		// get all the intersections for this ray
		intersectBy(rayCopy, intersections);

		// get the closest intersection and return black if no hit
		std::shared_ptr<Intersection> hitXs = hit(intersections);
		if (hitXs->isNull()) return Color(0.0, 0.0, 0.0);

		// get the compuations for the hit to calculate lighting
		Computation comp = prepareComputations(*hitXs, rayCopy, intersections);

		Color color = shadeHit(comp, remaining, intersections);
		return color;
	}

	Color World::reflectedColor(const Computation& comps, const int remaining) const
	{
		if (comps.object->material.reflective == 0.0 || remaining < 1)
		{
			return Color(0.0);
		}

		Ray reflectRay(comps.overPoint, comps.reflectV);

		std::vector<std::shared_ptr<Intersection>> intersections{};
		Color c = colorAt(reflectRay, remaining - 1, intersections);

		/*for (auto p : intersections) delete p;
		intersections.clear();*/

		return c * comps.object->material.reflective;
	}

	Color World::refractedColor(const Computation& comps, const int remaining) const
	{
		if (comps.object->material.transparency == 0.0 || remaining < 1)
		{
			return Color(0.0);
		}

		double ratio = comps.n1 / comps.n2;
		double cos_i = dot(comps.eyeV, comps.normalV);
		double sin2_t = (ratio * ratio) * (1.0 - (cos_i * cos_i));
		if (sin2_t > 1.0) {
			// total internal reflection!!
			return Color(0.0);
		}

		double cost_t = std::sqrt(1.0 - sin2_t);
		Vector4 direction = comps.normalV * (ratio * cos_i - cost_t) - comps.eyeV * ratio;
		Ray refractRay(comps.underPoint, direction);

		std::vector<std::shared_ptr<Intersection>> intersections{};
		Color c = colorAt(refractRay, remaining - 1, intersections) * comps.object->material.transparency;
		
		//for (auto p : intersections) delete p;
		//intersections.clear();

		return c;
	}

	double World::schlick(const Computation& comps) const
	{
		// find cos of angle between eye and normal
		double cos = dot(comps.eyeV, comps.normalV);

		// total internal reflection if n1 > n2
		if (comps.n1 > comps.n2)
		{
			double n = comps.n1 / comps.n2;
			double sin2_t = (n * n) * (1.0 - (cos * cos));
			if (sin2_t > 1.0) return 1.0;

			// compute cos of thetaT  using trig identity
			double cos_t = std::sqrt(1.0 - sin2_t);

			// when n1 > n2, use cos of thetaT
			cos = cos_t;
		}

		double r0 = ((comps.n1 - comps.n2) / (comps.n1 + comps.n2)) * ((comps.n1 - comps.n2) / (comps.n1 + comps.n2));
		double oneMinusCosPower5 = (1.0 - cos) * (1.0 - cos) * (1.0 - cos) * (1.0 - cos) * (1.0 - cos);
		return r0 + ((1.0 - r0) * oneMinusCosPower5);
	}
	
	bool World::isShadowed(const Point4& lightPosition, const Vector4& p) const
	{
		Vector4 v = lightPosition - p;
		double distance = magnitude(v);
		Vector4 direction = normalize(v);

		Ray r(p, direction);
		std::vector<std::shared_ptr<Intersection>> intersections{};
		intersectBy(r, intersections);

		std::shared_ptr<Intersection> hitXs = hit(intersections);
		bool result = false;
		if (!hitXs->isNull() && hitXs->object->hasShadow && hitXs->t < distance) result = true;
		
		return result;
	}

	World defaultWorld()
	{
		World w;
		
		PointLight* light = new PointLight(Point4(-10, 10, -10), Color(1, 1, 1));
		w.lights.push_back(light);

		Sphere* s1 = new Sphere();
		s1->material.color = Color(0.8, 1.0, 0.6);
		s1->material.diffuse = 0.7;
		s1->material.specular = 0.2;
		w.objects.push_back(s1);
		
		Sphere* s2 = new Sphere();		
		s2->setTransform(scaling(0.5, 0.5, 0.5));
		w.objects.push_back(s2);

		return w;
	}
}
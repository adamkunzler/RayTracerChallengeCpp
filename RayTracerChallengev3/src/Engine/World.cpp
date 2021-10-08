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

	void World::intersectBy(const Ray& r, std::vector<Intersection>& intersections) const
	{
		for (std::vector<IShape*>::const_iterator iter = objects.begin(); iter != objects.end(); iter++)
		{				
			(*iter)->intersectBy(r, intersections);
		}
	}

	Computation World::prepareComputations(const Intersection& i, const Ray& r, const std::vector<Intersection>& intersections) const
	{
		Computation c;

		Vector4 dir(r.direction);

		//
		// calculate n1, n2
		//			
		std::vector<IShape*> container;

		for (std::vector<Intersection>::const_iterator iter = intersections.begin(); iter != intersections.end(); iter++)
		{
			if (*iter == i)
			{
				if (container.size() == 0)
				{
					c.n1 = 1.0f;
				}
				else
				{
					c.n1 = container[container.size() - 1]->material.refractiveIndex;
				}
			}

			std::vector<IShape*>::iterator found = std::find(container.begin(), container.end(), iter->object);
			if (found != container.end())
			{
				container.erase(found);
			}
			else
			{
				container.push_back(iter->object);
			}

			if (*iter == i)
			{
				if (container.size() == 0)
				{
					c.n2 = 1.0f;
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
		c.normalV = i.object->normalAt(c.point);
		c.isInside = false;

		float d = dot(c.normalV, c.eyeV);
		if (d < 0)
		{
			c.isInside = true;
			c.normalV = -c.normalV;
		}

		c.reflectV = dir.reflect(c.normalV);
		c.overPoint = c.point + (c.normalV * 0.0001f);
		c.farOverPoint = c.point + (c.normalV * FLT_EPSILON);
		c.underPoint = c.point - (c.normalV * 0.0001f);

		return c;
	}

	Color World::shadeHit(const Computation& c, const int remaining, std::vector<Intersection>& intersections) const
	{
		Color finalColor;
		for (std::vector<PointLight>::const_iterator iter = lights.begin(); iter != lights.end(); iter++)
		{
			bool isInShadow = isShadowed(*iter, c.overPoint);
			
			Color surface = phong(*iter, c.object->material, *c.object, c.farOverPoint, c.eyeV, c.normalV, isInShadow);
			Color reflected = reflectedColor(c, remaining);
			Color refracted = refractedColor(c, remaining);

			Material m(c.object->material);
			if (m.reflective > 0.0f && m.transparency > 0.0f)
			{
				float reflectance = schlick(c);
				finalColor = finalColor + surface
					+ reflected * reflectance
					+ refracted * (1.0f - reflectance);
			}
			else
			{
				finalColor = finalColor + surface + reflected + refracted;
			}			
		}		
		
		return finalColor;
	}

	Color World::colorAt(const Ray& ray, const int remaining, std::vector<Intersection>& intersections) const
	{
		Ray rayCopy(ray);

		// get all the intersections for this ray
		intersectBy(rayCopy, intersections);

		// get the closest intersection and return black if no hit
		Intersection hitXs = hit(intersections);
		if (hitXs.isNull()) return Color(0, 0, 0);

		// get the compuations for the hit to calculate lighting
		Computation comp = prepareComputations(hitXs, rayCopy, intersections);

		Color color = shadeHit(comp, remaining, intersections);
		return color;
	}

	Color World::reflectedColor(const Computation& comps, const int remaining) const
	{
		if (comps.object->material.reflective == 0.0f || remaining < 1)
		{
			return Color(0.0f);
		}

		Ray reflectRay(comps.overPoint, comps.reflectV);

		std::vector<Intersection> intersections;
		Color c = colorAt(reflectRay, remaining - 1, intersections);

		return c * comps.object->material.reflective;
	}

	Color World::refractedColor(const Computation& comps, const int remaining) const
	{
		if (comps.object->material.transparency == 0.0f || remaining < 1)
		{
			return Color(0.0f);
		}

		float ratio = comps.n1 / comps.n2;
		float cos_i = dot(comps.eyeV, comps.normalV);
		float sin2_t = (ratio * ratio) * (1.0f - (cos_i * cos_i));
		if (sin2_t > 1.0f) {
			// total internal reflection!!
			return Color(0.0f);
		}

		float cost_t = std::sqrtf(1.0f - sin2_t);
		Vector4 direction = comps.normalV * (ratio * cos_i - cost_t) - comps.eyeV * ratio;
		Ray refractRay(comps.underPoint, direction);

		std::vector<Intersection> intersections;
		return colorAt(refractRay, remaining - 1, intersections) * comps.object->material.transparency;
	}

	float World::schlick(const Computation& comps) const
	{
		// find cos of angle between eye and normal
		float cos = dot(comps.eyeV, comps.normalV);

		// total internal reflection if n1 > n2
		if (comps.n1 > comps.n2)
		{
			float n = comps.n1 / comps.n2;
			float sin2_t = (n * n) * (1.0f - (cos * cos));
			if (sin2_t > 1.0f) return 1.0f;

			// compute cos of thetaT  using trig identity
			float cos_t = std::sqrtf(1.0f - sin2_t);

			// when n1 > n2, use cos of thetaT
			cos = cos_t;
		}

		float r0 = ((comps.n1 - comps.n2) / (comps.n1 + comps.n2)) * ((comps.n1 - comps.n2) / (comps.n1 + comps.n2));
		float oneMinusCosPower5 = (1.0f - cos) * (1.0f - cos) * (1.0f - cos) * (1.0f - cos) * (1.0f - cos);
		return r0 + ((1.0f - r0) * oneMinusCosPower5);
	}

	bool World::isShadowed(const PointLight& light, const Vector4& p) const
	{
		Vector4 v = light.position - p;
		float distance = magnitude(v);
		Vector4 direction = normalize(v);

		Ray r(p, direction);
		std::vector<Intersection> intersections;
		intersectBy(r, intersections);
		
		Intersection hitXs = hit(intersections);
		if (!hitXs.isNull() && hitXs.object->hasShadow && hitXs.t < distance)
		{
			return true;
		}

		return false;
	}
}
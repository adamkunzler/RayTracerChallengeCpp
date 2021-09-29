#pragma once

#include <vector>

#include "..\DataStructs\Point.h"
#include "..\DataStructs\Color.h"
#include "..\DataStructs\Matrix.h"
#include "..\Geometry\IShape.h"
#include "..\Geometry\Sphere.h"
#include "..\Geometry\PointLight.h"
#include "..\Geometry\Computation.h"

namespace RayTracer
{
	class IShape;
	class PointLight;
	class Computation;

	class World
	{
	public:
		std::vector<IShape*> objects;
		std::vector<PointLight> lights; // TODO ILight interface to support different types of lights

		World()
		{
		}

		/*World(World& other)
		{
			for (std::vector<IShape*>::iterator iter = other.objects.begin(); iter != other.objects.end(); iter++)
			{
				other.objects.push_back(*iter);
			}

			for (std::vector<PointLight>::iterator iter1 = other.lights.begin(); iter1 != other.lights.end(); iter1++)
			{
				other.lights.push_back(*iter1);
			}
		}*/

		~World()
		{
			objects.clear();
		}

		static World defaultWorld()
		{
			World w;

			w.lights.push_back(PointLight(Point(-10, 10, -10), Color(1, 1, 1)));

			Sphere* s1 = new Sphere();
			s1->material.color = Color(0.8f, 1.0f, 0.6f);
			s1->material.diffuse = 0.7f;
			s1->material.specular = 0.2f;

			Sphere* s2 = new Sphere();
			s2->transform = Matrix::get4x4ScalingMatrix(0.5f, 0.5f, 0.5f);

			w.objects.push_back(s1);
			w.objects.push_back(s2);

			return w;
		}

		static Matrix viewTransform(const Point& from, const Point& to, const Vector& up)
		{
			Vector forward = Vector::normalize(to - from);
			Vector nUp = Vector::normalize(up);
			Vector left = Vector::cross(forward, nUp);
			Vector trueUp = Vector::cross(left, forward);

			Matrix orientation(4, 4, std::unique_ptr<float[]>(new float[] {
				left.x, left.y, left.z, 0,
					trueUp.x, trueUp.y, trueUp.z, 0,
					-forward.x, -forward.y, -forward.z, 0,
					0, 0, 0, 1
			}));

			Matrix translation = Matrix::get4x4TranslationMatrix(-from.x, -from.y, -from.z);
			Matrix vt = orientation * translation;

			return vt;
		}

		std::vector<Intersection> intersectBy(const Ray& r) const
		{
			std::vector<Intersection> intersections;

			for (std::vector<IShape*>::const_iterator iter = objects.begin(); iter != objects.end(); iter++)
			{
				std::vector<Intersection> shapeIntersects = (*iter)->intersectBy(r);
				intersections.insert(intersections.end(), shapeIntersects.begin(), shapeIntersects.end());
			}

			std::sort(intersections.begin(), intersections.end(), Intersection::comparer);

			return intersections;
		}

		Computation prepareComputations(const Intersection& i, const Ray& r, const std::vector<Intersection>& intersections) const
		{
			Computation c;

			Vector dir(r.direction);

			//
			// calculate n1, n2
			//			
			std::vector<IShape*> container;

			for (std::vector<Intersection>::const_iterator iter = intersections.begin(); iter != intersections.end(); iter++)
			{
				if (Intersection::areEqual(*iter, i))
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

				if (Intersection::areEqual(*iter, i))
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

			float d = Vector::dot(c.normalV, c.eyeV);
			if (d < 0)
			{
				c.isInside = true;
				c.normalV = -c.normalV;
				//c.reflectV = -c.reflectV;
			}

			c.reflectV = dir.reflect(c.normalV);
			c.overPoint = c.point + (c.normalV * EPSILON);
			c.underPoint = c.point - (c.normalV * EPSILON);

			return c;
		}

		Color shadeHit(const Computation& c, const int remaining) const
		{
			Color finalColor;
			for (std::vector<PointLight>::const_iterator iter = lights.begin(); iter != lights.end(); iter++)
			{
				bool isInShadow = isShadowed(*iter, c.overPoint);

				Color surface = iter->phong(c.object->material, *c.object, c.overPoint, c.eyeV, c.normalV, isInShadow);
				Color reflected = reflectedColor(c, remaining);
				Color refracted = refractedColor(c, remaining);

				Material m(c.object->material);
				if (m.reflective > 0 && m.transparency > 0)
				{
					float reflectance = schlick(c);
					finalColor = finalColor + surface
						+ (reflected * reflectance)
						+ (refracted * (1 - reflectance));
				}
				else
				{
					finalColor = finalColor + surface + reflected + refracted;
				}
			}

			return finalColor;
		}

		Color colorAt(const Ray& ray, const int remaining) const
		{
			Ray rayCopy(ray);

			// get all the intersections for this ray
			std::vector<Intersection> intersections = intersectBy(rayCopy);

			// get the closest intersection and return black if no hit
			Intersection hit = Intersection::hit(intersections);
			if (hit.isNull()) return Color(0, 0, 0);

			// get the compuations for the hit to calculate lighting
			Computation comp = prepareComputations(hit, rayCopy, intersections);

			Color color = shadeHit(comp, remaining);
			return color;
		}

		Color reflectedColor(const Computation& comps, const int remaining) const
		{
			if (FloatEquals(comps.object->material.reflective, 0.0f) || remaining < 1)
			{
				return Color::black();
			}

			Ray reflectRay(comps.overPoint, comps.reflectV);
			Color c = colorAt(reflectRay, remaining - 1);

			return c * comps.object->material.reflective;
		}

		Color refractedColor(const Computation& comps, const int remaining) const
		{
			if (FloatEquals(comps.object->material.transparency, 0) || remaining < 1)
			{
				return Color::black();
			}

			float ratio = comps.n1 / comps.n2;
			float cos_i = Vector::dot(comps.eyeV, comps.normalV);
			float sin2_t = (ratio * ratio) * (1 - (cos_i * cos_i));
			if (sin2_t > 1) {
				// total internal reflection!!
				return Color::black();
			}

			float cost_t = std::sqrtf(1.0f - sin2_t);
			Vector direction = comps.normalV * (ratio * cos_i - cost_t) - comps.eyeV * ratio;
			Ray refractRay(comps.underPoint, direction);

			Color c = colorAt(refractRay, remaining - 1) * comps.object->material.transparency;
			return c;
		}

		float schlick(const Computation& comps) const
		{
			// find cos of angle between eye and normal
			float cos = Vector::dot(comps.eyeV, comps.normalV);

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
			float oneMinusCosPower5 = (1 - cos) * (1 - cos) * (1 - cos) * (1 - cos) * (1 - cos);
			return r0 + (1 - r0) * oneMinusCosPower5;
		}

		bool isShadowed(const PointLight& light, const Point& p) const
		{
			Vector v = light.position - p;
			float distance = Vector::magnitude(v);
			Vector direction = Vector::normalize(v);

			Ray r(p, direction);
			std::vector<Intersection> intersections = intersectBy(r);

			Intersection hit = Intersection::hit(intersections);
			if (!hit.isNull() && hit.t < distance)
			{
				return true;
			}

			return false;
		}

		Canvas render(const Camera& camera)
		{
			auto start1 = std::chrono::high_resolution_clock::now();

			Canvas image((int)camera.hSize, (int)camera.vSize);

			int totalPixels = (int)(camera.vSize * camera.hSize);
			int processedPixels = 0;

			for (int y = 0; y < camera.vSize; y++)
			{
				for (int x = 0; x < camera.hSize; x++)
				{
					Ray r = camera.rayForPixel(x, y);
					Color c = colorAt(r, MAX_RECURSION);
					image.setPixel(x, y, c);

					processedPixels++;
					//if (x % 80 == 0)showProgressBar((float)processedPixels / (float)totalPixels);
				}				
				showProgressBar((float)processedPixels / (float)totalPixels);				
			}
			showProgressBar(1);

			auto stop1 = std::chrono::high_resolution_clock::now();
			auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
			std::cout << "\nrender() completed in " << duration1.count() << "ms.";

			return image;
		}		
	};			
}
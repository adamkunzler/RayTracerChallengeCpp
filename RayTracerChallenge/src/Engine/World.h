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
			Vector left = forward.cross(nUp);
			Vector trueUp = left.cross(forward);
			
			Matrix orientation(4, 4, std::unique_ptr<float[]>(new float[] {
				 left.x,      left.y,     left.z,    0,
				 trueUp.x,    trueUp.y,   trueUp.z,  0,
				-forward.x,  -forward.y, -forward.z, 0,
				 0,           0,          0,         1
			}));

			Matrix translation = Matrix::get4x4TranslationMatrix(-from.x, -from.y, -from.z);
			Matrix vt = orientation * translation;

			return vt;
		}

		std::vector<Intersection> intersectBy(const Ray& r)
		{
			std::vector<Intersection> intersections;

			for (std::vector<IShape*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
			{															
				std::vector<Intersection> shapeIntersects = (*iter)->intersectBy(r);
				intersections.insert(intersections.end(), shapeIntersects.begin(), shapeIntersects.end());
			}
			
			std::sort(intersections.begin(), intersections.end(), Intersection::comparer);

			return intersections;
		}
		
		Computation prepareComputations(const Intersection& i, const Ray& r)
		{
			Computation c;

			Vector dir(r.direction);

			c.t = i.t;
			c.object = i.object;
			c.point = r.position(i.t);
			c.eyeV = -dir;
			c.normalV = i.object->normalAt(c.point);
			c.isInside = false;
			c.overPoint = c.point + (c.normalV * EPSILON);

			float d = c.normalV.dot(c.eyeV);
			if (d < 0)
			{
				c.isInside = true;
				c.normalV = -c.normalV;
			}

			return c;
		}

		Color shadeHit(const Computation& c)
		{
			Color finalColor;
			for (std::vector<PointLight>::iterator iter = lights.begin(); iter != lights.end(); iter++)
			{
				bool isInShadow = isShadowed(*iter, c.overPoint);
				Color color = iter->phong(c.object->material, *c.object, c.overPoint, c.eyeV, c.normalV, isInShadow);
				finalColor = finalColor + color;
			}
						
			return finalColor;
		}

		Color colorAt(const Ray& ray)
		{
			// get all the intersections for this ray
			std::vector<Intersection> intersections = intersectBy(ray);
			
			// get the closest intersection and return black if no hit
			Intersection hit = Intersection::hit(intersections);
			if (hit.isNull()) return Color(0, 0, 0);

			// get the compuations for the hit to calculate lighting
			Computation comp = prepareComputations(hit, ray);

			Color color = shadeHit(comp);
			return color;
		}

		Canvas render(const Camera& camera)
		{
			std::cout << "\n";
			auto start1 = std::chrono::high_resolution_clock::now();

			Canvas image((int)camera.hSize, (int)camera.vSize);
						
			int totalPixels = camera.vSize * camera.hSize;
			int processedPixels = 0;

			for (int y = 0; y < camera.vSize; y++)
			{
				for (int x = 0; x < camera.hSize; x++)
				{
					Ray r = camera.rayForPixel(x, y);
					Color c = colorAt(r);
					image.setPixel(x, y, c);					

					processedPixels++;
				}

				showProgressBar((float)processedPixels / (float)totalPixels);
			}

			auto stop1 = std::chrono::high_resolution_clock::now();
			auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
			std::cout << "\nrender() completed in " << duration1.count() << "ms.";

			return image;
		}
		
		void showProgressBar(float progress)
		{
			int barWidth = 70;

			std::cout << "[";
			int pos = barWidth * progress;
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) std::cout << "=";
				else if (i == pos) std::cout << ">";
				else std::cout << " ";
			}
			std::cout << "] " << int(progress * 100.0) << " %\r";
			std::cout.flush();
		}

		bool isShadowed(const PointLight& light, const Point& p)
		{
			Vector v = light.position - p;
			float distance = v.magnitude();
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
	};
}
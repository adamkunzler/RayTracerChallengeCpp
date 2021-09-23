#pragma once

namespace RayTracer
{
	class IShape;
	class Intersection;
	
	class Ray
	{
	public:
		Point origin;
		Vector direction;

		Ray(const Point& lOrigin, const Vector& lDirection) : origin(lOrigin), direction(lDirection)
		{
		}

		Ray(const Ray& r)
		{
			origin = Point(r.origin);
			direction = Vector(r.direction);
		}

		Point position(const float t) const
		{
			Point p = origin + (direction * t);
			return p;
		}
		
		Ray transform(Matrix& matrix)
		{
			Point newOrigin = (matrix * origin).toPoint();
			Vector newDirection = (matrix * direction).toVector();

			Ray r(newOrigin, newDirection);
			return r;
		}

		//std::vector<Intersection> intersectWorld(const World& w)
		//{
		//	std::vector<Intersection> intersections;

		//	for (std::vector<IShape>::const_iterator iter = w.objects.begin(); iter != w.objects.end(); iter++)
		//	{							
		//		//IShape ishape = *iter;
		//		//Sphere s = (Sphere)ishape;
		//		//std::vector<Intersection> shapeIntersects = intersects(s);
		//	}

		//	std::sort(intersections.begin(), intersections.end(), Intersection::comparer);

		//	return intersections;			
		//}
	};
}
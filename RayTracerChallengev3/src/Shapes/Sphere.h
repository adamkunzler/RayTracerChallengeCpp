
namespace RayTracer
{
	struct Sphere : public IShape
	{
		Point4 origin;
		double radius;

		Sphere() : origin(Vector4(0.0, 0.0, 0.0, 1.0)), radius(1.0) { }
		Sphere(const Point4& lOrigin, const double lRadius) : origin(lOrigin), radius(lRadius) { }
		
		Vector4 localNormalAt(const Point4& localPoint, const Intersection& i) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection*>& intersections) const;

		BoundingBox localBounds() const;
	};

	Sphere GlassSphere();
}

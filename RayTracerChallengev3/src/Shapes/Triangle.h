
namespace RayTracer
{
	struct Triangle : public IShape
	{
		Point4 p1;
		Point4 p2;
		Point4 p3;
		Vector4 e1;
		Vector4 e2;
		Vector4 normal;

		Triangle() = delete;
		Triangle(const Point4& lp1, const Point4& lp2, const Point4& lp3);

		Vector4 localNormalAt(const Point4& localPoint) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const;
	};	

	std::ostream& operator<<(std::ostream& os, const RayTracer::Triangle& t);
}

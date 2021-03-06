#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Triangle::Triangle(const Point4& lp1, const Point4& lp2, const Point4& lp3) : p1(lp1), p2(lp2), p3(lp3)
	{
		e1 = p2 - p1;
		e2 = p3 - p1;
		normal = normalize(cross(e1, e2));
	}

	Vector4 Triangle::localNormalAt(const Point4& localPoint, const Intersection& i) const
	{
		return normal;
	}

	void Triangle::localIntersectBy(const Ray& localRay, std::vector<std::shared_ptr<Intersection>>& intersections) const
	{
		// moller-trumbore algorithm

		Vector4 dirCrossE2 = cross(localRay.direction, e2);
		double determinant = dot(e1, dirCrossE2);
		if (std::abs(determinant) < DBL_EPSILON) return;

		double invDet = 1.0 / determinant;
		Point4 p1ToOrigin = localRay.origin - p1;
		double u = invDet * dot(p1ToOrigin, dirCrossE2);
		if (u < 0 or u > 1) return;

		Vector4 originCrossE1 = cross(p1ToOrigin, e1);
		double v = invDet * dot(localRay.direction, originCrossE1);
		if (v < 0 or (u + v) > 1) return;

		double t = invDet * dot(e2, originCrossE1);
		intersections.push_back(std::shared_ptr<Intersection>(new Intersection(t, (IShape*)this)));
	}	

	BoundingBox Triangle::localBounds() const
	{
		BoundingBox bb;
		bb.addPoint(p1);
		bb.addPoint(p2);
		bb.addPoint(p3);

		return BoundingBox(bb.min, bb.max);
	}


	SmoothTriangle::SmoothTriangle(
		const Point4& lp1, const Point4& lp2, const Point4& lp3, 
		const Vector4& ln1, const Vector4& ln2, const Vector4& ln3) : p1(lp1), p2(lp2), p3(lp3), n1(ln1), n2(ln2), n3(ln3)
	{
		e1 = p2 - p1;
		e2 = p3 - p1;		
	}

	Vector4 SmoothTriangle::localNormalAt(const Point4& localPoint, const Intersection& i) const
	{
		return n2 * i.u 
			+ n3 * i.v 
			+ n1 * (1 - i.u - i.v);
	}

	void SmoothTriangle::localIntersectBy(const Ray& localRay, std::vector<std::shared_ptr<Intersection>>& intersections) const
	{
		// moller-trumbore algorithm

		Vector4 dirCrossE2 = cross(localRay.direction, e2);
		double determinant = dot(e1, dirCrossE2);
		if (std::abs(determinant) < DBL_EPSILON) return;

		double invDet = 1.0 / determinant;
		Point4 p1ToOrigin = localRay.origin - p1;
		double u = invDet * dot(p1ToOrigin, dirCrossE2);
		if (u < 0 or u > 1) return;

		Vector4 originCrossE1 = cross(p1ToOrigin, e1);
		double v = invDet * dot(localRay.direction, originCrossE1);
		if (v < 0 or (u + v) > 1) return;

		double t = invDet * dot(e2, originCrossE1);
		intersections.push_back(std::shared_ptr<Intersection>(new Intersection(t, (IShape*)this, u, v)));
	}

	BoundingBox SmoothTriangle::localBounds() const
	{
		BoundingBox bb;
		bb.addPoint(p1);
		bb.addPoint(p2);
		bb.addPoint(p3);

		return BoundingBox(bb.min, bb.max);
	}

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Triangle& t)
	{
		os << "p1 => (" << t.p1.x << ", " << t.p1.y << ", " << t.p1.z << ")";
		os << "\tp2 => (" << t.p2.x << ", " << t.p2.y << ", " << t.p2.z << ")";
		os << "\tp3 => (" << t.p3.x << ", " << t.p3.y << ", " << t.p3.z << ")";
		return os;
	}
}
#pragma once

namespace RayTracer
{
	/// <summary>
	/// Represents an XZ plane
	/// </summary>
	struct Cylinder : public IShape
	{
		float minimum;
		float maximum;
		bool isClosed;

		Cylinder() : minimum(-INFINITY), maximum(INFINITY), isClosed(false) { }
		Cylinder(const float& min, const float& max, const bool& lIsClosed = false) : minimum(min), maximum(max), isClosed(lIsClosed) { }

		Vector4 localNormalAt(const Point4& localPoint) const
		{
			// compute the square of the distance from the y axis
			float dist = localPoint.x * localPoint.x + localPoint.z * localPoint.z;

			if ((dist < 1.0f) && (localPoint.y >= (maximum - EPSILON)))
			{
				return Vector4(0.0f, 1.0f, 0.0f);
			}
			else if ((dist < 1.0f) && (localPoint.y <= (minimum + EPSILON)))
			{
				return Vector4(0.0f, -1.0f, 0.0f);
			}

			return Vector4(localPoint.x, 0.0f, localPoint.z);
		}

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
		{						
			float a = localRay.direction.x * localRay.direction.x 
				+ localRay.direction.z * localRay.direction.z;
			if (a < EPSILON) return;

			float b = 2.0f * localRay.origin.x * localRay.direction.x
				+ 2.0f * localRay.origin.z * localRay.direction.z;

			float c = localRay.origin.x * localRay.origin.x 
				+ localRay.origin.z * localRay.origin.z - 1.0f;

			float discriminant = (b * b) - (4 * a * c);
			if (discriminant < 0.0f) return;
			
			float sqrtDisc = sqrtf(discriminant);
			float t0 = (-b - sqrtDisc) / (2 * a);
			float t1 = (-b + sqrtDisc) / (2 * a);
			if (t0 > t1) std::swap(t0, t1);

			float y0 = localRay.origin.y + t0 * localRay.direction.y;
			if (minimum < y0 && y0 < maximum)
			{
				intersections.push_back(Intersection(t0, (IShape*)this));
			}

			float y1 = localRay.origin.y + t1 * localRay.direction.y;
			if (minimum < y1 && y1 < maximum)
			{
				intersections.push_back(Intersection(t1, (IShape*)this));
			}

			intersectCaps(intersections, localRay);			
		}

		bool checkCap(const Ray& localRay, const float& t) const
		{
			float x = localRay.origin.x + (t * localRay.direction.x);
			float z = localRay.origin.z + (t * localRay.direction.z);
			return (x * x + z * z) <= 1.0f;
		}

		void intersectCaps(std::vector<Intersection>& xs, const Ray& localRay) const
		{
			// caps only matter if the cylinder is closed and might possibly be intersected by the ray
			if (!isClosed || (localRay.direction.y < EPSILON && localRay.direction.y > -EPSILON)) return;

			// check for an intersection with the lower end cap by intersecting
			// the ray with the plane at y = cylinder.minimum
			float t0 = (minimum - localRay.origin.y) / localRay.direction.y;
			if (checkCap(localRay, t0))
			{
				xs.push_back(Intersection(t0, (IShape*)this));
			}

			// check for an intersection with the upper end cap by intersecting
			// the ray with the plane at y = cylinder.maximum
			float t1 = (maximum - localRay.origin.y) / localRay.direction.y;
			if (checkCap(localRay, t1))
			{
				xs.push_back(Intersection(t1, (IShape*)this));
			}
		}
	};
}
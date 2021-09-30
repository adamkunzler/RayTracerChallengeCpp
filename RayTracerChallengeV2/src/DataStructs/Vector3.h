#pragma once

#include <ostream>

namespace RayTracer
{
	struct Vector3
	{
		float x;
		float y;
		float z;
		
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float lx, float ly, float lz) : x(lx), y(ly), z(lz) { }
		Vector3(const Vector3& copy) : x(copy.x), y(copy.y), z(copy.z) { }

		// assignment
		Vector3& operator=(const Vector3& rhs)
		{
			x = rhs.x; y = rhs.y; z = rhs.z;
			return *this;
		}

		// equality
		bool operator==(const Vector3& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		// inequality
		bool operator!=(const Vector3& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		// addition
		Vector3 operator+(const Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		// subtraction
		Vector3 operator-(const Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		// negation
		Vector3 operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		// multiply by scalar
		Vector3 operator*(const float& scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		// divide by scalar 
		Vector3 operator/(const float& scalar) const
		{
			float inverseScalar = 1.0f / scalar;
			return Vector3(x * inverseScalar, y * inverseScalar, z * inverseScalar);
		}

		// addition - modify lhs
		Vector3& operator+=(const Vector3& rhs)
		{
			x += rhs.x; y += rhs.y; z += rhs.z;
			return *this;
		}

		// subtraction - modify lhs
		Vector3& operator-=(const Vector3& rhs)
		{
			x -= rhs.x; y -= rhs.y; z -= rhs.z;
			return *this;
		}

		// multiple by scalar - modify lhs
		Vector3& operator*=(const float& scalar)
		{
			x *= scalar; y *= scalar; z *= scalar;
			return *this;
		}

		// divide by scalar - modify lhs
		Vector3& operator/=(const float& scalar)
		{
			float inverseScalar = 1.0f / scalar;
			x *= inverseScalar; y *= inverseScalar; z *= inverseScalar;
			return *this;
		}

		// zero
		void zero()
		{
			x = y = z = 0.0f;
		}

		void normalize()
		{
			float magnitudeSquared = x * x + y * y + z * z;
			if (magnitudeSquared > 0.0f)
			{
				float inverseMagnitude = 1.0f / std::sqrt(magnitudeSquared);
				x *= inverseMagnitude;
				y *= inverseMagnitude;
				z *= inverseMagnitude;
			}
		}

		float dot(const Vector3& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}
	};

	extern const Vector3 ZeroVector3(0.0f, 0.0f, 0.0f);

	// magnitude
	inline float magnitude(const Vector3& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// normalize
	inline Vector3 normalize(const Vector3& v)
	{
		float magnitudeSquared = v.x * v.x + v.y * v.y + v.z * v.z;
		if (magnitudeSquared > 0.0f)
		{
			float inverseMagnitude = 1.0f / std::sqrt(magnitudeSquared);
			
			return Vector3(
				v.x * inverseMagnitude,
				v.y * inverseMagnitude,
				v.z * inverseMagnitude
			);
		}
		return Vector3();
	}

	// dot
	inline float dot(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	// cross
	inline Vector3 cross(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	// scalar multiplaction (scalar on left for symmetry)
	inline Vector3 operator*(float k, const Vector3& rhs)
	{
		return Vector3(k * rhs.x, k * rhs.y, k * rhs.z);
	}

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Vector3& v)
	{
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}
}
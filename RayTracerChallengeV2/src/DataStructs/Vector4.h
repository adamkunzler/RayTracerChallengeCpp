#pragma once

namespace RayTracer
{
	// TODO better way to do this?
	//---
	struct Vector4;
	float dot(const Vector4& lhs, const Vector4& rhs);
	//---

	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;
		
		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4(float lx, float ly, float lz, float lw = 0.0f) : x(lx), y(ly), z(lz), w(lw) { }
		Vector4(const Vector4& copy) : x(copy.x), y(copy.y), z(copy.z), w(copy.w) { }

		// assignment
		Vector4& operator=(const Vector4& rhs)
		{
			x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
			return *this;
		}

		// equality
		bool operator==(const Vector4& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		// inequality
		bool operator!=(const Vector4& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
		}

		// addition
		Vector4 operator+(const Vector4& rhs) const
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		// subtraction
		Vector4 operator-(const Vector4& rhs) const
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		// negation
		Vector4 operator-() const
		{
			return Vector4(-x, -y, -z, -w);
		}

		// multiply by scalar
		Vector4 operator*(const float& scalar) const
		{
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		// divide by scalar 
		Vector4 operator/(const float& scalar) const
		{
			float inverseScalar = 1.0f / scalar;
			return Vector4(
				x * inverseScalar, 
				y * inverseScalar, 
				z * inverseScalar,
				w * inverseScalar);
		}

		// addition - modify lhs
		Vector4& operator+=(const Vector4& rhs)
		{
			x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
			return *this;
		}

		// subtraction - modify lhs
		Vector4& operator-=(const Vector4& rhs)
		{
			x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
			return *this;
		}

		// multiple by scalar - modify lhs
		Vector4& operator*=(const float& scalar)
		{
			x *= scalar; y *= scalar; z *= scalar; w *= scalar;
			return *this;
		}

		// divide by scalar - modify lhs
		Vector4& operator/=(const float& scalar)
		{
			float inverseScalar = 1.0f / scalar;
			x *= inverseScalar; y *= inverseScalar; z *= inverseScalar; w *= inverseScalar;
			return *this;
		}

		// zero
		void zero()
		{
			x = y = z = w = 0.0f;
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

		float dot(const Vector4& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}

		// reflect vector around another vector
		Vector4 reflect(const Vector4& v) const
		{
			return (*this) - v * 2 * RayTracer::dot(*this, v);
		}
	};
	
	// magnitude
	inline float magnitude(const Vector4& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// normalize
	inline Vector4 normalize(const Vector4& v)
	{
		float magnitudeSquared = v.x * v.x + v.y * v.y + v.z * v.z;
		if (magnitudeSquared > 0.0f)
		{
			float inverseMagnitude = 1.0f / std::sqrt(magnitudeSquared);
			
			return Vector4(
				v.x * inverseMagnitude,
				v.y * inverseMagnitude,
				v.z * inverseMagnitude
			);
		}
		return Vector4();
	}

	// dot
	inline float dot(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	// cross
	inline Vector4 cross(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	// scalar multiplaction (scalar on left for symmetry)
	inline Vector4 operator*(float k, const Vector4& rhs)
	{
		return Vector4(k * rhs.x, k * rhs.y, k * rhs.z, k * rhs.w);
	}

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Vector4& v)
	{
		os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return os;
	}
}
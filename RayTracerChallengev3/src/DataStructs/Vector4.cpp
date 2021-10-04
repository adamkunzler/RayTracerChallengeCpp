#include "../Headers.h"

namespace RayTracer
{			 
	// assignment
	Vector4& Vector4::operator=(const Vector4& rhs)
	{
		x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
		return *this;
	}

	// equality
	bool Vector4::operator==(const Vector4& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z; //&& w == rhs.w;
	}

	// approximate equality
	bool Vector4::equals(const Vector4& rhs) const
	{
		return feq(x, rhs.x) && feq(y, rhs.y) && feq(z, rhs.z); //&& feq(w, rhs.w);
	}

	// inequality
	bool Vector4::operator!=(const Vector4& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z; // || w != rhs.w;
	}

	// addition
	Vector4 Vector4::operator+(const Vector4& rhs) const
	{
		return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	// subtraction
	Vector4 Vector4::operator-(const Vector4& rhs) const
	{
		return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	// negation
	Vector4 Vector4::operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	// multiply by scalar
	Vector4 Vector4::operator*(const float& scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	// divide by scalar 
	Vector4 Vector4::operator/(const float& scalar) const
	{
		float inverseScalar = 1.0f / scalar;
		return Vector4(
			x * inverseScalar,
			y * inverseScalar,
			z * inverseScalar,
			w * inverseScalar);
	}

	// addition - modify lhs
	Vector4& Vector4::operator+=(const Vector4& rhs)
	{
		x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
		return *this;
	}

	// subtraction - modify lhs
	Vector4& Vector4::operator-=(const Vector4& rhs)
	{
		x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
		return *this;
	}

	// multiple by scalar - modify lhs
	Vector4& Vector4::operator*=(const float& scalar)
	{
		x *= scalar; y *= scalar; z *= scalar; w *= scalar;
		return *this;
	}

	// divide by scalar - modify lhs
	Vector4& Vector4::operator/=(const float& scalar)
	{
		float inverseScalar = 1.0f / scalar;
		x *= inverseScalar; y *= inverseScalar; z *= inverseScalar; w *= inverseScalar;
		return *this;
	}

	// zero
	void Vector4::zero()
	{
		x = y = z = w = 0.0f;
	}

	void Vector4::normalize()
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

	float Vector4::dot(const Vector4& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	// reflect vector around another vector
	Vector4 Vector4::reflect(const Vector4& v) const
	{
		return (*this) - v * 2 * RayTracer::dot(*this, v);
	}

	// ---------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------

	// magnitude
	float magnitude(const Vector4& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// normalize
	Vector4 normalize(const Vector4& v)
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
	float dot(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	// cross
	Vector4 cross(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	// scalar multiplaction (scalar on left for symmetry)
	Vector4 operator*(float k, const Vector4& rhs)
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
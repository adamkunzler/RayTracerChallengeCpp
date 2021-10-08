#ifndef HEADERS_H
#include "../Headers.h"
#endif

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
	Vector4 Vector4::operator*(const double& scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	// divide by scalar 
	Vector4 Vector4::operator/(const double& scalar) const
	{
		double inverseScalar = 1.0 / scalar;
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
	Vector4& Vector4::operator*=(const double& scalar)
	{
		x *= scalar; y *= scalar; z *= scalar; w *= scalar;
		return *this;
	}

	// divide by scalar - modify lhs
	Vector4& Vector4::operator/=(const double& scalar)
	{
		double inverseScalar = 1.0 / scalar;
		x *= inverseScalar; y *= inverseScalar; z *= inverseScalar; w *= inverseScalar;
		return *this;
	}

	// zero
	void Vector4::zero()
	{
		x = y = z = w = 0.0;
	}

	void Vector4::normalize()
	{
		double magnitudeSquared = x * x + y * y + z * z;
		if (magnitudeSquared > 0.0)
		{
			double inverseMagnitude = 1.0 / std::sqrt(magnitudeSquared);
			x *= inverseMagnitude;
			y *= inverseMagnitude;
			z *= inverseMagnitude;
		}
	}

	double Vector4::dot(const Vector4& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	// reflect vector around another vector
	Vector4 Vector4::reflect(const Vector4& v) const
	{
		return (*this) - v * 2.0 * RayTracer::dot(*this, v);
	}

	// ---------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------

	// magnitude
	double magnitude(const Vector4& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// normalize
	Vector4 normalize(const Vector4& v)
	{
		double magnitudeSquared = v.x * v.x + v.y * v.y + v.z * v.z;
		if (magnitudeSquared > 0.0)
		{
			double inverseMagnitude = 1.0 / std::sqrt(magnitudeSquared);

			return Vector4(
				v.x * inverseMagnitude,
				v.y * inverseMagnitude,
				v.z * inverseMagnitude
			);
		}
		return Vector4();
	}

	// dot
	double dot(const Vector4& lhs, const Vector4& rhs)
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
	Vector4 operator*(double k, const Vector4& rhs)
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
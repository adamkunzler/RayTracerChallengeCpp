#pragma once

namespace RayTracer
{	
	struct Vector4
	{
		double x;
		double y;
		double z;
		double w;

		Vector4() : x(0.0), y(0.0), z(0.0), w(0.0) {}
		Vector4(double lx, double ly, double lz, double lw = 0.0) : x(lx), y(ly), z(lz), w(lw) { }
		Vector4(const Vector4& copy) : x(copy.x), y(copy.y), z(copy.z), w(copy.w) { }

		// assignment
		Vector4& operator=(const Vector4& rhs);

		// equality
		bool operator==(const Vector4& rhs) const;

		// approximate equality
		bool equals(const Vector4& rhs) const;

		// inequality
		bool operator!=(const Vector4& rhs) const;

		// addition
		Vector4 operator+(const Vector4& rhs) const;

		// subtraction
		Vector4 operator-(const Vector4& rhs) const;

		// negation
		Vector4 operator-() const;

		// multiply by scalar
		Vector4 operator*(const double& scalar) const;

		// divide by scalar 
		Vector4 operator/(const double& scalar) const;

		// addition - modify lhs
		Vector4& operator+=(const Vector4& rhs);

		// subtraction - modify lhs
		Vector4& operator-=(const Vector4& rhs);

		// multiple by scalar - modify lhs
		Vector4& operator*=(const double& scalar);

		// divide by scalar - modify lhs
		Vector4& operator/=(const double& scalar);

		// zero
		void zero();

		void normalize();

		double dot(const Vector4& rhs) const;

		// reflect vector around another vector
		Vector4 reflect(const Vector4& v) const;
	};	

	// magnitude
	double magnitude(const Vector4& v);

	// normalize
	Vector4 normalize(const Vector4& v);

	// dot
	double dot(const Vector4& lhs, const Vector4& rhs);

	// cross
	Vector4 cross(const Vector4& lhs, const Vector4& rhs);

	// scalar multiplaction (scalar on left for symmetry)
	Vector4 operator*(double k, const Vector4& rhs);

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Vector4& v);
}

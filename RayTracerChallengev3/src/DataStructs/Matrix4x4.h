#pragma once

namespace RayTracer
{					
	// 4x4 matrix in row x column form (e.g. m31 is row 3 column 1)
	struct Matrix4x4
	{
		double m00, m01, m02, m03;
		double m10, m11, m12, m13;
		double m20, m21, m22, m23;
		double m30, m31, m32, m33;

		Matrix4x4();

		Matrix4x4(
			double _m00, double _m01, double _m02, double _m03,
			double _m10, double _m11, double _m12, double _m13,
			double _m20, double _m21, double _m22, double _m23,
			double _m30, double _m31, double _m32, double _m33
		);

		Matrix4x4(const Matrix4x4& copy);

		// assigment
		Matrix4x4& operator=(const Matrix4x4& rhs);

		// equality
		bool operator==(const Matrix4x4& m);

		// approximate equality
		bool equals(const Matrix4x4& m) const;

		// inequality
		bool operator!=(const Matrix4x4& m);
	};

	//
	// NON-MEMBER FUNCTIONS -------------------------------------------------------------
	//
		
	Matrix4x4 identity4x4();

	// transpose
	Matrix4x4 transpose4x4(const Matrix4x4& m);

	// determinant
	// TODO

	// inverse (https://stackoverflow.com/a/44446912) thank you god
	Matrix4x4 inverse(const Matrix4x4& m);

	// multiply Vector4 by matrix4x4
	Vector4 operator*(const Vector4& v, const Matrix4x4& m);

	// multiply Vector4 by matrix4x4
	Vector4 operator*(const Matrix4x4& m, const Vector4& v);

	// multiply matrix4x4 by matrix4x4
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);

	// multiply Vector4 by matrix4x4 (modify lhs)
	Vector4& operator*=(Vector4& v, const Matrix4x4& m);

	// multiply matrix4x4 by matrix4x4 (modify lhs)
	Matrix4x4& operator*=(Matrix4x4& a, const Matrix4x4& b);

	// translation
	Matrix4x4 translation(const double& x, const double& y, const double& z);

	// scaling
	Matrix4x4 scaling(const double& x, const double& y, const double& z);

	// rotation x
	Matrix4x4 xRotation4x4(const double& r);

	// rotation y
	Matrix4x4 yRotation4x4(const double& r);

	// rotation z
	Matrix4x4 zRotation4x4(const double& r);

	// shearing
	Matrix4x4 shearing(
		const double& xy, const double& xz,
		const double& yx, const double& yz,
		const double& zx, const double& zy);

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Matrix4x4& m);
}

#pragma once

namespace RayTracer
{	
	// 4x4 matrix in row x column form (e.g. m31 is row 3 column 1)
	struct Matrix4x4
	{
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;

		Matrix4x4();

		Matrix4x4(
			float _m00, float _m01, float _m02, float _m03,
			float _m10, float _m11, float _m12, float _m13,
			float _m20, float _m21, float _m22, float _m23,
			float _m30, float _m31, float _m32, float _m33
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

	// identity
	Matrix4x4 identity4x4();

	// transpose
	Matrix4x4 transpose4x4(const Matrix4x4& m);
			
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
	Matrix4x4 translation(const float& x, const float& y, const float& z);

	// scaling
	Matrix4x4 scaling(const float& x, const float& y, const float& z);

	// rotation x
	Matrix4x4 xRotation4x4(const float& r);

	// rotation y
	Matrix4x4 yRotation4x4(const float& r);

	// rotation z
	Matrix4x4 zRotation4x4(const float& r);

	// shearing
	Matrix4x4 shearing(
		const float& xy, const float& xz,
		const float& yx, const float& yz,
		const float& zx, const float& zy);

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Matrix4x4& m);
}
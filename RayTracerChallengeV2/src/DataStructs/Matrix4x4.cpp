#include <ostream>
#include <iomanip>

#include "../Utils.h"
#include "Matrix4x4.h"
#include "Vector4.h"

namespace RayTracer
{
	// 4x4 matrix in row x column form (e.g. m31 is row 3 column 1)
	Matrix4x4::Matrix4x4()
	{
		m00 = m01 = m02 = m03 = 0.0f;
		m10 = m11 = m12 = m13 = 0.0f;
		m20 = m21 = m22 = m23 = 0.0f;
		m30 = m31 = m32 = m33 = 0.0f;
	}

	Matrix4x4::Matrix4x4(
		float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33
	)
	{
		m00 = _m00; m01 = _m01; m02 = _m02; m03 = _m03;
		m10 = _m10; m11 = _m11; m12 = _m12; m13 = _m13;
		m20 = _m20; m21 = _m21; m22 = _m22; m23 = _m23;
		m30 = _m30; m31 = _m31; m32 = _m32; m33 = _m33;
	}

	Matrix4x4::Matrix4x4(const Matrix4x4& copy)
	{
		m00 = copy.m00; m01 = copy.m01; m02 = copy.m02; m03 = copy.m03;
		m10 = copy.m10; m11 = copy.m11; m12 = copy.m12; m13 = copy.m13;
		m20 = copy.m20; m21 = copy.m21; m22 = copy.m22; m23 = copy.m23;
		m30 = copy.m30; m31 = copy.m31; m32 = copy.m32; m33 = copy.m33;
	}

	// assigment
	Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs)
	{
		m00 = rhs.m00; m01 = rhs.m01; m02 = rhs.m02; m03 = rhs.m03;
		m10 = rhs.m10; m11 = rhs.m11; m12 = rhs.m12; m13 = rhs.m13;
		m20 = rhs.m20; m21 = rhs.m21; m22 = rhs.m22; m23 = rhs.m23;
		m30 = rhs.m30; m31 = rhs.m31; m32 = rhs.m32; m33 = rhs.m33;
		return *this;
	}

	// equality
	bool Matrix4x4::operator==(const Matrix4x4& m)
	{
		return m00 == m.m00 && m01 == m.m01 && m02 == m.m02 && m03 == m.m03
			&& m10 == m.m10 && m11 == m.m11 && m12 == m.m12 && m13 == m.m13
			&& m20 == m.m20 && m21 == m.m21 && m22 == m.m22 && m23 == m.m23
			&& m30 == m.m30 && m31 == m.m31 && m32 == m.m32 && m33 == m.m33;
	}

	// approximate equality
	bool Matrix4x4::equals(const Matrix4x4& m) const
	{
		return feq(m00, m.m00) && feq(m01, m.m01) && feq(m02, m.m02) && feq(m03, m.m03)
			&& feq(m10, m.m10) && feq(m11, m.m11) && feq(m12, m.m12) && feq(m13, m.m13)
			&& feq(m20, m.m20) && feq(m21, m.m21) && feq(m22, m.m22) && feq(m23, m.m23)
			&& feq(m30, m.m30) && feq(m31, m.m31) && feq(m32, m.m32) && feq(m33, m.m33);
	}

	// inequality
	bool Matrix4x4::operator!=(const Matrix4x4& m)
	{
		return m00 != m.m00 || m01 != m.m01 || m02 != m.m02 || m03 != m.m03
			|| m10 != m.m10 || m11 != m.m11 || m12 != m.m12 || m13 != m.m13
			|| m20 != m.m20 || m21 != m.m21 || m22 != m.m22 || m23 != m.m23
			|| m30 != m.m30 || m31 != m.m31 || m32 != m.m32 || m33 != m.m33;
	}


	// identity
	Matrix4x4 identity4x4()
	{
		return Matrix4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// transpose
	Matrix4x4 transpose4x4(const Matrix4x4& m)
	{
		return Matrix4x4(
			m.m00, m.m10, m.m20, m.m30,
			m.m01, m.m11, m.m21, m.m31,
			m.m02, m.m12, m.m22, m.m32,
			m.m03, m.m13, m.m23, m.m33
		);
	}

	// determinant


	// inverse (https://stackoverflow.com/a/44446912) thank you god
	Matrix4x4 inverse(const Matrix4x4& m)
	{

		float A2323 = m.m22 * m.m33 - m.m23 * m.m32;
		float A1323 = m.m21 * m.m33 - m.m23 * m.m31;
		float A1223 = m.m21 * m.m32 - m.m22 * m.m31;
		float A0323 = m.m20 * m.m33 - m.m23 * m.m30;
		float A0223 = m.m20 * m.m32 - m.m22 * m.m30;
		float A0123 = m.m20 * m.m31 - m.m21 * m.m30;
		float A2313 = m.m12 * m.m33 - m.m13 * m.m32;
		float A1313 = m.m11 * m.m33 - m.m13 * m.m31;
		float A1213 = m.m11 * m.m32 - m.m12 * m.m31;
		float A2312 = m.m12 * m.m23 - m.m13 * m.m22;
		float A1312 = m.m11 * m.m23 - m.m13 * m.m21;
		float A1212 = m.m11 * m.m22 - m.m12 * m.m21;
		float A0313 = m.m10 * m.m33 - m.m13 * m.m30;
		float A0213 = m.m10 * m.m32 - m.m12 * m.m30;
		float A0312 = m.m10 * m.m23 - m.m13 * m.m20;
		float A0212 = m.m10 * m.m22 - m.m12 * m.m20;
		float A0113 = m.m10 * m.m31 - m.m11 * m.m30;
		float A0112 = m.m10 * m.m21 - m.m11 * m.m20;

		float det = m.m00 * (m.m11 * A2323 - m.m12 * A1323 + m.m13 * A1223)
			- m.m01 * (m.m10 * A2323 - m.m12 * A0323 + m.m13 * A0223)
			+ m.m02 * (m.m10 * A1323 - m.m11 * A0323 + m.m13 * A0123)
			- m.m03 * (m.m10 * A1223 - m.m11 * A0223 + m.m12 * A0123);
		det = 1 / det;

		return Matrix4x4(
			det * (m.m11 * A2323 - m.m12 * A1323 + m.m13 * A1223),  // m00
			det * -(m.m01 * A2323 - m.m02 * A1323 + m.m03 * A1223), // m01
			det * (m.m01 * A2313 - m.m02 * A1313 + m.m03 * A1213),  // m02
			det * -(m.m01 * A2312 - m.m02 * A1312 + m.m03 * A1212), // m03
			det * -(m.m10 * A2323 - m.m12 * A0323 + m.m13 * A0223), // m10
			det * (m.m00 * A2323 - m.m02 * A0323 + m.m03 * A0223),  // m11
			det * -(m.m00 * A2313 - m.m02 * A0313 + m.m03 * A0213), // m12
			det * (m.m00 * A2312 - m.m02 * A0312 + m.m03 * A0212),  // m13
			det * (m.m10 * A1323 - m.m11 * A0323 + m.m13 * A0123),  // m20
			det * -(m.m00 * A1323 - m.m01 * A0323 + m.m03 * A0123), // m21
			det * (m.m00 * A1313 - m.m01 * A0313 + m.m03 * A0113),  // m22
			det * -(m.m00 * A1312 - m.m01 * A0312 + m.m03 * A0112), // m23
			det * -(m.m10 * A1223 - m.m11 * A0223 + m.m12 * A0123), // m30
			det * (m.m00 * A1223 - m.m01 * A0223 + m.m02 * A0123),  // m31
			det * -(m.m00 * A1213 - m.m01 * A0213 + m.m02 * A0113), // m32
			det * (m.m00 * A1212 - m.m01 * A0212 + m.m02 * A0112)   // m33
		);
	}

	// multiply Vector4 by matrix4x4
	Vector4 operator*(const Vector4& v, const Matrix4x4& m)
	{
		return Vector4(
			v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03,
			v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13,
			v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23,
			v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33
		);
	}

	// multiply Vector4 by matrix4x4
	Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		return v * m;
	}

	// multiply matrix4x4 by matrix4x4
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
	{
		return Matrix4x4(
			a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30,
			a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31,
			a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32,
			a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,

			a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30,
			a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
			a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
			a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,

			a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30,
			a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
			a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
			a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,

			a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30,
			a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
			a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
			a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33
		);
	}

	// multiply Vector4 by matrix4x4 (modify lhs)
	Vector4& operator*=(Vector4& v, const Matrix4x4& m)
	{
		v = v * m;
		return v;
	}

	// multiply matrix4x4 by matrix4x4 (modify lhs)
	Matrix4x4& operator*=(Matrix4x4& a, const Matrix4x4& b)
	{
		a = a * b;
		return a;
	}

	// translation
	Matrix4x4 translation(const float& x, const float& y, const float& z)
	{
		return Matrix4x4(
			1.0f, 0.0f, 0.0f, x,
			0.0f, 1.0f, 0.0f, y,
			0.0f, 0.0f, 1.0f, z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// scaling
	Matrix4x4 scaling(const float& x, const float& y, const float& z)
	{
		return Matrix4x4(
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// rotation x
	Matrix4x4 xRotation4x4(const float& r)
	{
		float cosr = std::cos(r);
		float sinr = std::sin(r);

		return Matrix4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosr, -sinr, 0.0f,
			0.0f, sinr, cosr, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// rotation y
	Matrix4x4 yRotation4x4(const float& r)
	{
		float cosr = std::cos(r);
		float sinr = std::sin(r);

		return Matrix4x4(
			cosr, 0.0f, sinr, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-sinr, 0.0f, cosr, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// rotation z
	Matrix4x4 zRotation4x4(const float& r)
	{
		float cosr = std::cos(r);
		float sinr = std::sin(r);

		return Matrix4x4(
			cosr, -sinr, 0.0f, 0.0f,
			sinr, cosr, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// shearing
	Matrix4x4 shearing(
		const float& xy, const float& xz,
		const float& yx, const float& yz,
		const float& zx, const float& zy)
	{
		return Matrix4x4(
			1.0f, xy, xz, 0.0f,
			yx, 1.0f, yz, 0.0f,
			zx, zy, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	// ostream
	std::ostream& operator<<(std::ostream& os, const RayTracer::Matrix4x4& m)
	{
		os << "\n";
		os << std::fixed << std::setprecision(2);
		os << "   |" << std::setw(8) << m.m00 << "   |" << std::setw(8) << m.m01 << "   |" << std::setw(8) << m.m02 << "   |" << std::setw(8) << m.m03 << "   |\n";
		os << "   |" << std::setw(8) << m.m10 << "   |" << std::setw(8) << m.m11 << "   |" << std::setw(8) << m.m12 << "   |" << std::setw(8) << m.m13 << "   |\n";
		os << "   |" << std::setw(8) << m.m20 << "   |" << std::setw(8) << m.m21 << "   |" << std::setw(8) << m.m22 << "   |" << std::setw(8) << m.m23 << "   |\n";
		os << "   |" << std::setw(8) << m.m30 << "   |" << std::setw(8) << m.m31 << "   |" << std::setw(8) << m.m32 << "   |" << std::setw(8) << m.m33 << "   |\n";
		os << "\n";
		os.unsetf(std::ios::fixed);
		return os;
	}
}
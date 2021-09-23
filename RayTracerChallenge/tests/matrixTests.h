#pragma once

namespace RayTracer
{
	namespace Tests
	{
		bool MatrixConstructor_Default()
		{				
			Matrix m;

			bool result = m.getNumRows() == 4 && m.getNumColumns() == 4 && m.isZeroMatrix();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixConstructor_Default\n";

			return result;
		}

		bool MatrixConstructor_ParametersNoValues()
		{
			Matrix m(3, 3);

			bool result = m.getNumRows() == 3 && m.getNumColumns() == 3 && m.isZeroMatrix();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixConstructor_ParametersNoValues\n";

			return result;
		}

		bool MatrixConstructor_ParametersWithValues()
		{
			Matrix m(2, 2, new float[4]{ 
				1, 2, 
				3, 4
			});

			bool result = m.getNumRows() == 2 && m.getNumColumns() == 2 
				&& FloatEquals(m(0, 0), 1)
				&& FloatEquals(m(0, 1), 3)
				&& FloatEquals(m(1, 0), 2)
				&& FloatEquals(m(1, 1), 4);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixConstructor_ParametersWithValues\n";

			return result;
		}
		
		bool MatrixConstructor_Copy()
		{
			Matrix m1(2, 2, new float[4]{
				1, 2,
				3, 4
				});

			Matrix m(m1);

			bool result = m.getNumRows() == 2 && m.getNumColumns() == 2
				&& FloatEquals(m(0, 0), 1)
				&& FloatEquals(m(0, 1), 3)
				&& FloatEquals(m(1, 0), 2)
				&& FloatEquals(m(1, 1), 4);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixConstructor_Copy\n";

			return result;
		}

		bool MatrixOperator_Assignment()
		{
			Matrix m1(2, 2, new float[4]{
				1, 2,
				3, 4
				});

			Matrix m = m1;

			m1(0, 1, 115.0f);
			
			bool result = m.getNumRows() == 2 && m.getNumColumns() == 2
				&& FloatEquals(m(0, 0), 1)
				&& FloatEquals(m(0, 1), 3)
				&& FloatEquals(m(1, 0), 2)
				&& FloatEquals(m(1, 1), 4)
				&& FloatEquals(m1(0, 1), 115);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_Assignment\n";

			return result;
		}		

		bool MatrixOperator_Equality()
		{
			Matrix m1(2, 2, new float[4]{
				1, 2,
				3, 4
			});

			Matrix m2(2, 2, new float[4]{
				1, 2,
				3, 4
			});			

			bool result = m1 == m2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_Equality\n";

			return result;
		}

		bool MatrixOperator_Inequality()
		{
			Matrix m1(2, 2, new float[4]{
				1, 2,
				3, 4
				});

			Matrix m2(2, 2, new float[4]{
				4, 5,
				6, 7
				});

			bool result = m1 != m2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_Inequality\n";

			return result;
		}

		bool MatrixOperator_InequalityDifferentDimensions()
		{
			Matrix m1(3, 3, new float[9]{
				1, 2, 7,
				3, 4, 9,
				5, 6, 8
				});

			Matrix m2(2, 2, new float[4]{
				4, 5,
				6, 7
				});

			bool result = m1 != m2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_InequalityDifferentDimensions\n";

			return result;
		}

		bool MatrixOperator_MultiplyByEquals_4x4()
		{
			Matrix m1(4, 4, new float[16]{
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2
				});

			Matrix m2(4, 4, new float[16]{
				-2, 1, 2, 3,
				3, 2, 1, -1,
				4, 3, 6, 5,
				1, 2, 7, 8
				});

			Matrix m3(4, 4, new float[16]{
				20,22,50,48,
				44,54,114,108,
				40,58,110,102,
				16,26,46,42
				});

			m1 *= m2;
			
			bool result = m1 == m3;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyByEquals_4x4\n";

			return result;
		}

		bool MatrixOperator_MultiplyBy_4x4()
		{
			Matrix m1(4, 4, new float[16]{
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2
				});

			Matrix m2(4, 4, new float[16]{
				-2, 1, 2, 3,
				3, 2, 1, -1,
				4, 3, 6, 5,
				1, 2, 7, 8
				});

			Matrix m3(4, 4, new float[16]{
				20,22,50,48,
				44,54,114,108,
				40,58,110,102,
				16,26,46,42
				});

			Matrix m4 = m1 * m2;
			
			bool result = m4 == m3;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyBy_4x4\n";

			return result;
		}

		bool MatrixOperator_MultiplyByEquals_3x3()
		{
			Matrix m1(3, 3, new float[9]{
				1, 2, 3,
				5, 6, 7,
				9, 8, 7
				});

			Matrix m2(3, 3, new float[9]{
				-2, 1, 2,
				3, 2, 1,
				4, 3, 6
				});

			Matrix m3(3, 3, new float[9]{
				16, 14, 22,
				36, 38, 58,
				34, 46, 68
				});

			m1 *= m2;

			bool result = m1 == m3;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyByEquals_3x3\n";

			return result;
		}

		bool MatrixOperator_MultiplyBy_3x3()
		{
			Matrix m1(3, 3, new float[9]{
				1, 2, 3,
				5, 6, 7,
				9, 8, 7				
				});

			Matrix m2(3, 3, new float[9]{
				-2, 1, 2,
				3, 2, 1,
				4, 3, 6				
				});

			Matrix m3(3, 3, new float[9]{
				16, 14, 22, 
				36, 38, 58, 
				34, 46, 68
				});

			Matrix m4 = m1 * m2;

			bool result = m4 == m3;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyBy_3x3\n";

			return result;
		}

		bool MatrixOperator_MultiplyByIdentity_4x4()
		{
			Matrix m1(4, 4, new float[16]{
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2
				});

			Matrix m2(4, 4, new float[16]{
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2
				});

			Matrix identity = Matrix::get4x4IdentityMatrix();
			
			m1 *= identity;

			Matrix m3 = m1 * identity;

			bool result = m3 == m2;
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyByIdentity_4x4\n";

			return result;
		}

		bool MatrixOperator_MultiplyBy_Tuple()
		{
			Matrix m1(4, 4, new float[16]{
				1, 2, 3, 4,
				2, 4, 4, 2,
				8, 6, 4, 1,
				0, 0, 0, 1
				});

			Tuple t(1, 2, 3, 1);

			Matrix r(1, 4, new float[4]{
				18,
				24,
				33,
				1
				});
						
			Matrix m2 = m1 * t;								

			bool result = m2 == r;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyBy_Tuple\n";

			return result;
		}

		bool MatrixOperator_MultiplyByEquals_Tuple()
		{
			Matrix m1(4, 4, new float[16]{
				1, 2, 3, 4,
				2, 4, 4, 2,
				8, 6, 4, 1,
				0, 0, 0, 1
				});

			Tuple t(1, 2, 3, 1);

			Matrix r(1, 4, new float[4]{
				18,
				24,
				33,
				1
				});			

			m1 *= t;
			
			bool result = m1 == r;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyByEquals_Tuple\n";

			return result;
		}

		bool MatrixConstructor_Tuple()
		{			
			Tuple t(1, 2, 3, 4);

			Matrix m(t);

			Matrix r(1, 4, new float[4]{
				1,
				2,
				3,
				4
				});
						
			bool result = m == r;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixConstructor_Tuple\n";

			return result;
		}

		bool MatrixConstructor_Vector()
		{
			Vector t(1, 2, 3);

			Matrix m(t);

			Matrix r(1, 4, new float[4]{
				1,
				2,
				3,
				0
				});

			bool result = m == r;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixConstructor_Vector\n";

			return result;
		}

		bool MatrixOperator_MultiplyBy_Vector()
		{
			Matrix m1(4, 4, new float[16]{
				1, 2, 3, 4,
				2, 4, 4, 2,
				8, 6, 4, 1,
				0, 0, 0, 1
				});

			Vector t(1, 2, 3);

			Matrix r(1, 4, new float[4]{
				14,
				22,
				32,
				0
				});

			Matrix m2 = m1 * t;

			bool result = m2 == r;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyBy_Vector\n";

			return result;
		}

		bool MatrixOperator_MultiplyByEquals_Vector()
		{
			Matrix m1(4, 4, new float[16]{
				1, 2, 3, 4,
				2, 4, 4, 2,
				8, 6, 4, 1,
				0, 0, 0, 1
				});

			Vector t(1, 2, 3);

			Matrix r(1, 4, new float[4]{
				14,
				22,
				32,
				0
				});

			m1 *= t;

			bool result = m1 == r;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixOperator_MultiplyByEquals_Vector\n";

			return result;
		}

		bool Matrix_Transpose_4x4()
		{
			Matrix m1(4, 4, new float[16]{
				0,9,3,0,
				9,8,0,8,
				1,8,5,3,
				0,0,5,8
				});

			Matrix m2(4, 4, new float[16]{
				0,9,1,0,
				9,8,8,0,
				3,0,5,5,
				0,8,3,8
				});

			Matrix m3 = m1.transpose();
			
			bool result = m2 == m3;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transpose_4x4\n";

			return result;
		}

		bool Matrix_Transpose_Identity()
		{			
			Matrix m2 = Matrix::get4x4IdentityMatrix();

			Matrix m3 = m2.transpose();

			bool result = m2 == m3;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transpose_Identity\n";

			return result;
		}

		bool Matrix_Determinant_2x2()
		{
			Matrix m(2, 2, new float[4]{
				1, 5,
				-3, 2
			});

			float d = m.determinant();

			bool result = FloatEquals(d, 17);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Determinant_2x2\n";

			return result;
		}

		bool Matrix_Submatrix_3x3()
		{
			Matrix m(3, 3, new float[9]{
				1, 5, 0,
				-3, 2, 7,
				0, 6, -3
			});

			Matrix sub = m.submatrix(0, 2);
			
			Matrix expected(2, 2, new float[4]{
				-3, 2,
				0, 6
				});

			bool result = sub == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Submatrix_3x3\n";

			return result;
		}

		bool Matrix_Submatrix_4x4()
		{
			Matrix m(4, 4, new float[16]{
				-6,1,1,6,
				-8,5,8,6,
				-1,0,8,2,
				-7,1,-1,1
				});

			Matrix sub = m.submatrix(2, 1);
			
			Matrix expected(3, 3, new float[9]{
				-6,1,6,
				-8,8,6,
				-7,-1,1
				});

			bool result = sub == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Submatrix_4x4\n";

			return result;
		}

		bool Matrix_Minor_3x3()
		{
			Matrix m(3, 3, new float[9]{
				3, 5, 0,
				2, -1, -7,
				6, -1, 5
				});

			float minor = m.minor(1, 0);

			bool result = minor == 25;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Minor_3x3\n";

			return result;
		}

		bool Matrix_Cofactor_3x3_1()
		{
			Matrix m(3, 3, new float[9]{
				3, 5, 0,
				2, -1, -7,
				6, -1, 5
				});

			float cofactor = m.cofactor(0, 0);

			bool result = cofactor == -12;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Cofactor_3x3_1\n";

			return result;
		}

		bool Matrix_Cofactor_3x3_2()
		{
			Matrix m(3, 3, new float[9]{
				3, 5, 0,
				2, -1, -7,
				6, -1, 5
				});

			float cofactor = m.cofactor(1, 0);

			bool result = cofactor == -25;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Cofactor_3x3_2\n";

			return result;
		}

		bool Matrix_Determinant_3x3()
		{
			Matrix m(3, 3, new float[9]{
				1,2,6,
				-5,8,-4,
				2,6,4
				});

			float c1 = m.cofactor(0, 0);
			float c2 = m.cofactor(0, 1);
			float c3 = m.cofactor(0, 2);
			float d = m.determinant();

			bool result = FloatEquals(d, -196)
				&& FloatEquals(c1, 56)
				&& FloatEquals(c2, 12)
				&& FloatEquals(c3, -46);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Determinant_3x3\n";

			return result;
		}

		bool Matrix_Determinant_4x4()
		{
			Matrix m(4, 4, new float[16]{
				-2,-8,3,5,
				-3,1,7,3,
				1,2,-9,6,
				-6,7,7,-9
				});

			float c1 = m.cofactor(0, 0);
			float c2 = m.cofactor(0, 1);
			float c3 = m.cofactor(0, 2);
			float c4 = m.cofactor(0, 3);
			float d = m.determinant();

			bool result = FloatEquals(d, -4071)
				&& FloatEquals(c1, 690)
				&& FloatEquals(c2, 447)
				&& FloatEquals(c3, 210)
				&& FloatEquals(c4, 51);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Determinant_4x4\n";

			return result;
		}

		bool Matrix_IsInvertible()
		{
			Matrix m(4, 4, new float[16]{
				6,4,4,4,
				5,5,7,6,
				4,-9,3,-7,
				9,1,7,-6
				});
			
			float d = m.determinant();

			bool result = FloatEquals(d, -2120);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_IsInvertible\n";

			return result;
		}

		bool Matrix_IsNotInvertible()
		{
			Matrix m(4, 4, new float[16]{
				-4,2,-2,-3,
				9,6,2,6,
				0,-5,1,-5,
				0,0,0,0
				});

			float d = m.determinant();

			bool result = FloatEquals(d, 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_IsNotInvertible\n";

			return result;
		}

		bool Matrix_Inverse_1()
		{
			Matrix m(4, 4, new float[16]{
				-5,2,6,-8,
				1,-5,1,8,
				7,7,-6,-7,
				1,-3,7,4
			});

			Matrix expected(4, 4, new float[16]{
				0.21805f,  0.45113f, 0.24060f,-0.04511f,
				-0.80827f,-1.45677f,-0.44361f, 0.52068f,
				-0.07895f,-0.22368f,-0.05263f, 0.19737f,
				-0.52256f,-0.81391f,-0.30075f, 0.30639f
			});

			Matrix b = m.inverse();

			float d = m.determinant();
			float cof1 = m.cofactor(2, 3);
			float cof2 = m.cofactor(3, 2);
			float v1 = b(2, 3);
			float v2 = b(3, 2);
						
			bool result =
				FloatEquals(d, 532)
				&& FloatEquals(cof1, -160)
				&& FloatEquals(cof2, 105)
				&& FloatEquals(v1, -0.30075f)
				&& FloatEquals(v2, 0.19737f)
				&& b == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Inverse_1\n";

			return result;
		}

		bool Matrix_Inverse_2()
		{
			Matrix m(4, 4, new float[16]{
				8,-5,9,2,
				7,5,6,1,
				-6,0,9,6,
				-3,0,-9,-4
			});

			Matrix expected(4, 4, new float[16]{
				-0.15385f, -0.15385f, -0.28205f, -0.53846f,
				-0.07692f,  0.12308f,  0.02564f,  0.03077f,
				 0.35897f,  0.35897f,  0.43590f,  0.92308f,
				-0.69231f, -0.69231f, -0.76923f, -1.92308f
			});

			Matrix b = m.inverse();
			
			bool result = b == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Inverse_2\n";

			return result;
		}

		bool Matrix_Inverse_3()
		{
			Matrix m(4, 4, new float[16]{
				9,3,0,9,
				-5,-2,-6,-3,
				-4,9,6,4,
				-7,6,6,2	
			});

			Matrix expected(4, 4, new float[16]{
				-0.04074f, -0.07778f,  0.14444f, -0.22222f,
				-0.07778f,  0.03333f,  0.36667f, -0.33333f,
				-0.02901f, -0.14630f, -0.10926f,  0.12963f,
				 0.17778f,  0.06667f, -0.26667f,  0.33333f
			});

			Matrix b = m.inverse();
			
			bool result = b == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Inverse_3\n";

			return result;
		}

		bool Matrix_Inverse_Proof()
		{
			Matrix a(4, 4, new float[16]{
				3,-9,7,3,
				3,-8,2,-9,
				-4,4,4,1,
				-6,5,-1,1	
			});
			
			Matrix b(4, 4, new float[16]{
				8,2,2,2,
				3,-1,7,0,
				7,0,5,4,
				6,-2,0,5	
			});
						
			Matrix c = a * b;					

			Matrix d = c * b.inverse();
						
			bool result = a == d;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Inverse_Proof\n";

			return result;
		}

		bool Matrix_Inverse_Test()
		{
			Matrix a(4, 4, new float[16]{
				3,-9,7,3,
				3,-8,2,-9,
				-4,4,4,1,
				-6,5,-1,1
				});
			
			Matrix b = a.inverse();

			Matrix c = a * b;
			
			bool result = c == Matrix::get4x4IdentityMatrix();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Inverse_Test\n";

			return result;
		}

		// -------------------------------------------------------------------------------------------------------------------------------

		bool Matrix_Transformations_Translation()
		{
			Matrix transform = Matrix::get4x4TranslationMatrix(5, -3, 2);
			Point p(-3, 4, 5);

			Point expected(2, 1, 7);

			Point p1 = (transform * p).toPoint();					

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Translation\n";

			return result;
		}

		bool Matrix_Transformations_Translation_Inverse()
		{
			Matrix transform = Matrix::get4x4TranslationMatrix(5, -3, 2);
			Matrix inv = transform.inverse();
			Point p(-3, 4, 5);

			Point expected(-8, 7, 3);

			Point p1 = (inv * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Translation_Inverse\n";

			return result;
		}

		bool Matrix_Transformations_Translation_Vector()
		{
			Matrix transform = Matrix::get4x4TranslationMatrix(5, -3, 2);
			Vector v(-3, 4, 5);

			Vector v1 = (transform * v).toVector();

			bool result = v1 == v;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Translation_Vector\n";

			return result;
		}

		bool Matrix_Transformations_Scaling_Point()
		{
			Matrix transform = Matrix::get4x4ScalingMatrix(2, 3, 4);
			Point p(-4, 6, 8);
			Point expected(-8, 18, 32);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Scaling_Point\n";

			return result;
		}

		bool Matrix_Transformations_Scaling_Vector()
		{
			Matrix transform = Matrix::get4x4ScalingMatrix(2, 3, 4);
			Vector v(-4, 6, 8);
			Vector expected(-8, 18, 32);

			Vector v1 = (transform * v).toVector();

			bool result = v1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Scaling_Vector\n";

			return result;
		}

		bool Matrix_Transformations_Scaling_VectorInverse()
		{
			Matrix transform = Matrix::get4x4ScalingMatrix(2, 3, 4);
			Matrix inv = transform.inverse();
			Vector v(-4, 6, 8);
			Vector expected(-2, 2, 2);

			Vector v1 = (inv * v).toVector();

			bool result = v1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Scaling_VectorInverse\n";

			return result;
		}

		bool Matrix_Transformations_Scaling_NegativeValue()
		{
			Matrix transform = Matrix::get4x4ScalingMatrix(-1, 1, 1);
			Point p(2, 3, 4);
			Point expected(-2, 3, 4);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Scaling_NegativeValue\n";

			return result;
		}

		bool Matrix_Transformations_Rotation_X()
		{
			Point p(0, 1, 0);
			Matrix halfQuarter = Matrix::get4x4RotationMatrix_X(PI / 4);
			Matrix fullQuarter = Matrix::get4x4RotationMatrix_X(PI / 2);

			Point ep1(0, std::sqrtf(2) / 2, std::sqrtf(2) / 2);
			Point ep2(0, 0, 1);

			Point p1 = (halfQuarter * p).toPoint();
			Point p2 = (fullQuarter * p).toPoint();

			bool result = (p1 == ep1) && (p2 == ep2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Rotation_X\n";

			return result;
		}

		bool Matrix_Transformations_Rotation_XInverse()
		{
			Point p(0, 1, 0);
			Matrix halfQuarter = Matrix::get4x4RotationMatrix_X(PI / 4);
			Matrix inv = halfQuarter.inverse();
			
			Point ep1(0, std::sqrtf(2) / 2, -std::sqrtf(2) / 2);
			
			Point p1 = (inv * p).toPoint();
			
			bool result = (p1 == ep1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Rotation_XInverse\n";

			return result;
		}

		bool Matrix_Transformations_Rotation_Y()
		{
			Point p(0, 0, 1);
			Matrix halfQuarter = Matrix::get4x4RotationMatrix_Y(PI / 4);
			Matrix fullQuarter = Matrix::get4x4RotationMatrix_Y(PI / 2);

			Point ep1(std::sqrtf(2) / 2, 0, std::sqrtf(2) / 2);
			Point ep2(1, 0, 0);

			Point p1 = (halfQuarter * p).toPoint();
			Point p2 = (fullQuarter * p).toPoint();

			bool result = (p1 == ep1) && (p2 == ep2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Rotation_Y\n";

			return result;
		}

		bool Matrix_Transformations_Rotation_Z()
		{
			Point p(0, 1, 0);
			Matrix halfQuarter = Matrix::get4x4RotationMatrix_Z(PI / 4);
			Matrix fullQuarter = Matrix::get4x4RotationMatrix_Z(PI / 2);

			Point ep1(-std::sqrtf(2) / 2, std::sqrtf(2) / 2, 0);
			Point ep2(-1, 0, 0);

			Point p1 = (halfQuarter * p).toPoint();
			Point p2 = (fullQuarter * p).toPoint();

			bool result = (p1 == ep1) && (p2 == ep2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Rotation_Z\n";

			return result;
		}

		bool Matrix_Transformations_Shearing_XY()
		{
			Matrix transform = Matrix::get4x4ShearingMatrix(1, 0, 0, 0, 0, 0);
			Point p(2, 3, 4);
			Point expected(5, 3, 4);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Shearing_XY\n";

			return result;
		}

		bool Matrix_Transformations_Shearing_XZ()
		{
			Matrix transform = Matrix::get4x4ShearingMatrix(0, 1, 0, 0, 0, 0);
			Point p(2, 3, 4);
			Point expected(6, 3, 4);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Shearing_XZ\n";

			return result;
		}

		bool Matrix_Transformations_Shearing_YX()
		{
			Matrix transform = Matrix::get4x4ShearingMatrix(0, 0, 1, 0, 0, 0);
			Point p(2, 3, 4);
			Point expected(2, 5, 4);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Shearing_YX\n";

			return result;
		}

		bool Matrix_Transformations_Shearing_YZ()
		{
			Matrix transform = Matrix::get4x4ShearingMatrix(0, 0, 0, 1, 0, 0);
			Point p(2, 3, 4);
			Point expected(2, 7, 4);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Shearing_YZ\n";

			return result;
		}

		bool Matrix_Transformations_Shearing_ZX()
		{
			Matrix transform = Matrix::get4x4ShearingMatrix(0, 0, 0, 0, 1, 0);
			Point p(2, 3, 4);
			Point expected(2, 3, 6);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Shearing_ZX\n";

			return result;
		}

		bool Matrix_Transformations_Shearing_ZY()
		{
			Matrix transform = Matrix::get4x4ShearingMatrix(0, 0, 0, 0, 0, 1);
			Point p(2, 3, 4);
			Point expected(2, 3, 7);

			Point p1 = (transform * p).toPoint();

			bool result = p1 == expected;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Shearing_ZY\n";

			return result;
		}

		bool Matrix_Transformations_Sequenced()
		{
			Point p(1, 0, 1);
			Matrix a = Matrix::get4x4RotationMatrix_X(PI / 2);
			Matrix b = Matrix::get4x4ScalingMatrix(5, 5, 5);
			Matrix c = Matrix::get4x4TranslationMatrix(10, 5, 7);

			Point p2 = (a * p).toPoint();
			Point p2e(1, -1, 0);

			Point p3 = (b * p2).toPoint();
			Point p3e(5, -5, 0);

			Point p4 = (c * p3).toPoint();
			Point p4e(15, 0, 7);

			bool result = (p2 == p2e) && (p3 == p3e) && (p4 == p4e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Sequenced\n";

			return result;
		}

		bool Matrix_Transformations_Chained()
		{
			Point p(1, 0, 1);
			Matrix a = Matrix::get4x4RotationMatrix_X(PI / 2);
			Matrix b = Matrix::get4x4ScalingMatrix(5, 5, 5);
			Matrix c = Matrix::get4x4TranslationMatrix(10, 5, 7);

			Matrix t = c * b * a;

			Point p2 = (t * p).toPoint();
			Point p2e(15, 0, 7);

			bool result = p2 == p2e;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Transformations_Chained\n";

			return result;
		}
	}
}
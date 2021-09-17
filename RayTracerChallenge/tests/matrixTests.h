#pragma once

#include <iostream>
#include <string>
#include "../src/Matrix.h"
#include "../src/Utils.h"
#include "..\src\Vector.h"

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

			Matrix identity = Matrix::get4x4IdentiyMatrix();
			
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
			Matrix m2 = Matrix::get4x4IdentiyMatrix();

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
				0.21805,  0.45113, 0.24060,-0.04511,
				-0.80827,-1.45677,-0.44361, 0.52068,
				-0.07895,-0.22368,-0.05263, 0.19737,
				-0.52256,-0.81391,-0.30075, 0.30639
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
				&& FloatEquals(v1, -0.30075)
				&& FloatEquals(v2, 0.19737)
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
				-0.15385, -0.15385, -0.28205, -0.53846,
				-0.07692,  0.12308,  0.02564,  0.03077,
				 0.35897,  0.35897,  0.43590,  0.92308,
				-0.69231, -0.69231, -0.76923, -1.92308
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
				-0.04074, -0.07778,  0.14444, -0.22222,
				-0.07778,  0.03333,  0.36667, -0.33333,
				-0.02901, -0.14630, -0.10926,  0.12963,
				 0.17778,  0.06667, -0.26667,  0.33333
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
			
			bool result = c == Matrix::get4x4IdentiyMatrix();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t Matrix_Inverse_Test\n";

			return result;
		}
	}
}
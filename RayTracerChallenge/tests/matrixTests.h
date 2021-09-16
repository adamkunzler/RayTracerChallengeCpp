#pragma once

#include <iostream>
#include <string>
#include "../src/Matrix.h"
#include "../src/Utils.h"

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
	}
}
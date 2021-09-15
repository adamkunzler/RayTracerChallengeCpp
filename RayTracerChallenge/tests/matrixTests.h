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

			bool result = m.getHeight() == 4 && m.getWidth() == 4 && m.isZeroMatrix();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t MatrixConstructor_Default\n";

			return result;
		}

		bool MatrixConstructor_ParametersNoValues()
		{
			Matrix m(3, 3);

			bool result = m.getHeight() == 3 && m.getWidth() == 3 && m.isZeroMatrix();

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

			bool result = m.getHeight() == 2 && m.getWidth() == 2 
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

			bool result = m.getHeight() == 2 && m.getWidth() == 2
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
			
			bool result = m.getHeight() == 2 && m.getWidth() == 2
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
	}
}
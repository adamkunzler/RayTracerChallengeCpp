#pragma once


namespace RayTracer
{
	namespace Tests
	{
		bool LightShading_Normal_XAxis()
		{			
			Sphere s;
			Vector v = s.normalAt(Point(1, 0, 0));

			Vector e(1, 0, 0);

			bool result = (v == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Normal_XAxis\n";

			return result;
		}

		bool LightShading_Normal_YAxis()
		{
			Sphere s;
			Vector v = s.normalAt(Point(0, 1, 0));

			Vector e(0, 1, 0);

			bool result = (v == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Normal_YAxis\n";

			return result;
		}

		bool LightShading_Normal_ZAxis()
		{
			Sphere s;
			Vector v = s.normalAt(Point(0, 0, 1));

			Vector e(0, 0, 1);

			bool result = (v == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Normal_ZAxis\n";

			return result;
		}

		bool LightShading_Normal_NonAxial()
		{
			float sqrt3Div3 = std::sqrtf(3) / 3.0f;
			Sphere s;
			Vector v = s.normalAt(Point(sqrt3Div3, sqrt3Div3, sqrt3Div3));

			Vector e(sqrt3Div3, sqrt3Div3, sqrt3Div3);

			bool result = (v == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Normal_NonAxial\n";

			return result;
		}

		bool LightShading_Normal_Normalized()
		{
			float sqrt3Div3 = std::sqrtf(3) / 3.0f;
			Sphere s;
			Vector v = s.normalAt(Point(sqrt3Div3, sqrt3Div3, sqrt3Div3));

			Vector e = Vector::normalize(v);

			bool result = (v == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Normal_Normalized\n";

			return result;
		}

		bool LightShading_Normal_Sphere_Translated()
		{
			Sphere s;
			s.transform = Matrix::get4x4TranslationMatrix(0, 1, 0);
			Vector n = s.normalAt(Point(0, 1.70711f, -0.70711f));

			Vector e(0, 0.70711f, -0.70711f);
			bool result = (n == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Normal_Sphere_Translated\n";

			return result;
		}

		bool LightShading_Normal_Sphere_Transformed()
		{
			Sphere s;
			Matrix ts = Matrix::get4x4ScalingMatrix(1, 0.5, 1);
			Matrix trz = Matrix::get4x4RotationMatrix_Z(RayTracer::PI / 5.0f);
			s.transform = (ts * trz);
			
			float sqrt2Over2 = std::sqrtf(2) / 2.0f;
			Vector n = s.normalAt(Point(0, sqrt2Over2, -sqrt2Over2));

			Vector e(0, 0.97014f, -0.24254f);
			bool result = (n == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Normal_Sphere_Transformed\n";

			return result;
		}

		bool LightShading_Reflect_45()
		{
			Vector v(1, -1, 0);
			Vector n(0, 1, 0);

			Vector e(1, 1, 0);

			Vector r = v.reflect(n);

			bool result = (r == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Reflect_45\n";

			return result;
		}

		bool LightShading_Reflect_Slanted()
		{
			Vector v(0, -1, 0);
			
			float sqrt2Over2 = std::sqrtf(2) / 2.0f;
			Vector n(sqrt2Over2, sqrt2Over2, 0);

			Vector e(1, 0, 0);

			Vector r = v.reflect(n);

			bool result = (r == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Reflect_Slanted\n";

			return result;
		}

		bool LightShading_PointLight()
		{
			Color c(1, 1, 1);
			Point p(0, 0, 0);

			PointLight light(p, c);

			bool result = (light.position == p) && (light.intensity == c);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_PointLight\n";

			return result;
		}

		bool LightShading_Material_Default()
		{
			Material m;

			bool result = (m.color == Color(1,1,1)) 
				&& FloatEquals(m.ambient, 0.1f) 
				&& FloatEquals(m.diffuse, 0.9f) 
				&& FloatEquals(m.specular, 0.9f) 
				&& FloatEquals(m.shininess, 200.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Material_Default\n";

			return result;
		}

		bool LightShading_Material_SphereDefault()
		{
			Sphere s;
			Material m;

			bool result = (s.material == m);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Material_SphereDefault\n";

			return result;
		}

		bool LightShading_Material_SphereAssigned()
		{
			Sphere s;
			Material m;
			m.ambient = 1.0f;

			s.material = m;

			bool result = (s.material == m);
			

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Material_SphereAssigned\n";

			return result;
		}

		bool LightShading_Light_EyeBetweenLightAndSurface()
		{
			Material m;
			Point position(0, 0, 0);

			Vector eye(0, 0, -1);
			Vector normalV(0, 0, -1);
			PointLight light(Point(0, 0, -10), Color(1, 1, 1));

			Sphere s;
			Color r = light.phong(m, s, position, eye, normalV, false);

			Color expected(1.9f, 1.9f, 1.9f);

			bool result = (r == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Light_EyeBetweenLightAndSurface\n";

			return result;
		}

		bool LightShading_Light_EyeBetweenLightAndSurface45()
		{
			float sqrt2over2 = std::sqrtf(2) / 2.0f;

			Material m;
			Point position(0, 0, 0);

			Vector eye(0, sqrt2over2, -sqrt2over2);
			Vector normalV(0, 0, -1);
			PointLight light(Point(0, 0, -10), Color(1, 1, 1));
			
			Sphere s;
			Color r = light.phong(m, s, position, eye, normalV, false);

			Color expected(1.0f, 1.0f, 1.0f);

			bool result = (r == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Light_EyeBetweenLightAndSurface45\n";

			return result;
		}

		bool LightShading_Light_EyeOppositeSurface()
		{
			Material m;
			Point position(0, 0, 0);

			Vector eye(0, 0, -1);
			Vector normalV(0, 0, -1);
			PointLight light(Point(0, 10, -10), Color(1, 1, 1));

			Sphere s;
			Color r = light.phong(m, s, position, eye, normalV, false);

			Color expected(0.7364f, 0.7364f, 0.7364f);

			bool result = (r == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Light_EyeOppositeSurface\n";

			return result;
		}

		bool LightShading_Light_EyeInPath()
		{
			float sqrt2over2 = std::sqrtf(2) / 2.0f;

			Material m;
			Point position(0, 0, 0);

			Vector eye(0, -sqrt2over2, -sqrt2over2);
			Vector normalV(0, 0, -1);
			PointLight light(Point(0, 10, -10), Color(1, 1, 1));

			Sphere s;
			Color r = light.phong(m, s, position, eye, normalV, false);

			Color expected(1.63639f, 1.63639f, 1.63639f);
			
			bool result = (r == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Light_EyeInPath\n";

			return result;
		}

		bool LightShading_Light_BehindSurface()
		{
			Material m;
			Point position(0, 0, 0);

			Vector eye(0, 0, -1);
			Vector normalV(0, 0, -1);
			PointLight light(Point(0, 0, 10), Color(1, 1, 1));

			Sphere s;
			Color r = light.phong(m, s, position, eye, normalV, false);

			Color expected(0.1f, 0.1f, 0.1f);

			bool result = (r == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t LightShading_Light_BehindSurface\n";

			return result;
		}

	}
}
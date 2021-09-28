#pragma once

namespace RayTracer
{
	namespace Tests
	{
		//
		// Reflection
		//

		bool Reflection_DefaultMaterial()
		{
			Material m;
			bool result = FloatEquals(m.reflective, 0.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_DefaultMaterial()\n";

			return result;
		}

		bool Reflection_PrecomputeReflectionVector()
		{			
			float sqrt2 = std::sqrtf(2);
			float sqrt2over2 = std::sqrtf(2) / 2;
			World w;
			Plane p;
			Ray r(Point(0, 1, -1), Vector(0, -sqrt2over2, sqrt2over2));
			Intersection i(sqrt2, &p);
			Computation comps = w.prepareComputations(i, r);

			Vector expected(0, sqrt2over2, sqrt2over2);

			bool result = (comps.reflectV == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_PrecomputeReflectionVector()\n";

			return result;
		}

		bool Reflection_ReflectedColorForNonReflectiveMaterial()
		{
			World w = World::defaultWorld();			
			Ray r(Point(0, 0, 0), Vector(0, 0, 1));
			Sphere* s = (Sphere*)w.objects[1];
			s->material.ambient = 1;
			Intersection i(1, s);
			Computation comps = w.prepareComputations(i, r);
			Color c = w.reflectedColor(comps, 0);

			Color expected(0, 0, 0);

			bool result = (c == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_ReflectedColorForNonReflectiveMaterial()\n";

			return result;
		}

		bool Reflection_ReflectedColorForReflectiveMaterial()
		{
			float sqrt2 = std::sqrtf(2);
			float sqrt2over2 = std::sqrtf(2) / 2;

			World w = World::defaultWorld();
			Plane shape;
			shape.material.reflective = 0.5f;
			shape.transform = Matrix::get4x4TranslationMatrix(0, -1, 0);
			w.objects.push_back(&shape);
			Ray r(Point(0, 0, -3), Vector(0, -sqrt2over2, sqrt2over2));
			Intersection i(sqrt2, &shape);
			Computation comps = w.prepareComputations(i, r);
			Color c = w.reflectedColor(comps, MAX_RECURSION);

			Color expected(0.19032f, 0.2379f, 0.14274f);

			bool result = (c == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_ReflectedColorForReflectiveMaterial()\n";

			return result;
		}

		bool Reflection_ShadeHitWithReflectiveMaterial()
		{
			float sqrt2 = std::sqrtf(2);
			float sqrt2over2 = std::sqrtf(2) / 2;

			World w = World::defaultWorld();
			Plane shape;
			shape.material.reflective = 0.5f;
			shape.transform = Matrix::get4x4TranslationMatrix(0, -1, 0);
			w.objects.push_back(&shape);
			Ray r(Point(0, 0, -3), Vector(0, -sqrt2over2, sqrt2over2));
			Intersection i(sqrt2, &shape);
			Computation comps = w.prepareComputations(i, r);
			Color c = w.shadeHit(comps, MAX_RECURSION);

			Color expected(0.87677f, 0.92436f, 0.82918f);

			bool result = (c == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_ShadeHitWithReflectiveMaterial()\n";

			return result;
		}

		bool Reflection_ColorAtWithMutuallyReflectiveSurfaces()
		{
			World w;
			PointLight light(Point(0, 0, 0), Color(1, 1, 1));
			w.lights.push_back(light);

			Plane lower;
			lower.material.reflective = 1;
			lower.transform = Matrix::get4x4TranslationMatrix(0, -1, 0);
			w.objects.push_back(&lower);

			Plane upper;
			upper.material.reflective = 1;
			upper.transform = Matrix::get4x4TranslationMatrix(0, 1, 0);
			w.objects.push_back(&upper);

			Ray r(Point(0, 0, 0), Vector(0, 1, 0));

			Color c = w.colorAt(r, 0);

			// isn't recursive???
			bool result = true;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_ColorAtWithMutuallyReflectiveSurfaces()\n";

			return result;
		}

		bool Reflection_ReflectedColorAtMaximumRecursiveDepth()
		{
			float sqrt2 = std::sqrtf(2);
			float sqrt2over2 = std::sqrtf(2) / 2;

			World w = World::defaultWorld();
			Plane shape;
			shape.material.reflective = 0.5f;
			shape.transform = Matrix::get4x4TranslationMatrix(0, -1, 0);
			w.objects.push_back(&shape);

			Ray r(Point(0, 0, -3), Vector(0, -sqrt2over2, sqrt2over2));
			Intersection i(sqrt2, &shape);
			Computation comps = w.prepareComputations(i, r);
			Color c = w.reflectedColor(comps, 0);

			Color expected(0, 0, 0);

			bool result = (c == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_ReflectedColorAtMaximumRecursiveDepth()\n";

			return result;
		}

		//
		// Refraction
		//

		bool Refraction_DefaultMaterial()
		{
			Material m;

			bool result = FloatEquals(m.transparency, 0)
				&& FloatEquals(m.refractiveIndex, 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_DefaultMaterial()\n";

			return result;
		}

		bool Refraction_GlassSphere()
		{
			Sphere s = Sphere::GlassSphere();

			bool result = FloatEquals(s.material.transparency, 1)
				&& FloatEquals(s.material.refractiveIndex, 1.5)
				&& (s.transform == Matrix::get4x4IdentityMatrix());

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_GlassSphere()\n";

			return result;
		}

		bool Refraction_N1_N2()
		{
			Sphere a = Sphere::GlassSphere();
			a.transform = Matrix::get4x4ScalingMatrix(2, 2, 2);
			a.material.refractiveIndex = 1.5f;

			Sphere b = Sphere::GlassSphere();
			b.transform = Matrix::get4x4TranslationMatrix(0, 0, -0.25);
			b.material.refractiveIndex = 2.0f;

			Sphere c = Sphere::GlassSphere();
			c.transform = Matrix::get4x4TranslationMatrix(0, 0, 0.25f);
			c.material.refractiveIndex = 2.5f;

			Ray r(Point(0, 0, -4), Vector(0, 0, 1));
			
			std::vector<Intersection> intersections;
			intersections.push_back(Intersection(2, &a));
			intersections.push_back(Intersection(2.75f, &b));
			intersections.push_back(Intersection(3.25f, &c));
			intersections.push_back(Intersection(4.75f, &b));
			intersections.push_back(Intersection(5.25f, &c));
			intersections.push_back(Intersection(6, &a));

			World w;			
			Computation c0 = w.prepareComputations(intersections[0], r, intersections);
			Computation c1 = w.prepareComputations(intersections[1], r, intersections);
			Computation c2 = w.prepareComputations(intersections[2], r, intersections);
			Computation c3 = w.prepareComputations(intersections[3], r, intersections);
			Computation c4 = w.prepareComputations(intersections[4], r, intersections);
			Computation c5 = w.prepareComputations(intersections[5], r, intersections);

			bool result = FloatEquals(c0.n1, 1.0f) && FloatEquals(c0.n2, 1.5f)
				&& FloatEquals(c0.n1, 1.5f) && FloatEquals(c0.n2, 2.0f)
				&& FloatEquals(c0.n1, 2.0f) && FloatEquals(c0.n2, 2.5f)
				&& FloatEquals(c0.n1, 2.5f) && FloatEquals(c0.n2, 2.5f)
				&& FloatEquals(c0.n1, 2.5f) && FloatEquals(c0.n2, 1.5f)
				&& FloatEquals(c0.n1, 1.5f) && FloatEquals(c0.n2, 1.0f);
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_N1_N2()\n";

			return result;
		}

		bool Refraction_ComputeUnderPoint()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_ComputeUnderPoint()\n";

			return result;
		}

		bool Refraction_RefractedColor_Opaque()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_RefractedColor_Opaque()\n";

			return result;
		}

		bool Refraction_RefractedColor_MaximumRecursiveDepth()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_RefractedColor_MaximumRecursiveDepth()\n";

			return result;
		}

		bool Refraction_RefractedColor_TotalInternalReflection()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_RefractedColor_TotalInternalReflection()\n";

			return result;
		}

		bool Refraction_RefractedColorWithARefractedRay()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_RefractedColorWithARefractedRay()\n";

			return result;
		}

		bool Refraction_ShadeHit_TransparentMaterial()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Refraction_ShadeHit_TransparentMaterial()\n";

			return result;
		}
	}
}
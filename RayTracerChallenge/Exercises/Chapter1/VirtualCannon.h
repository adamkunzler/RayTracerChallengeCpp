#pragma once

#include <iostream>
#include "../../src/Tuple.h"

namespace Exercises
{
	namespace Chapter1
	{
		class Projectile
		{
		public:
			Projectile(RayTracer::Point lPosition, RayTracer::Vector lVelocity) : position(lPosition), velocity(lVelocity)
			{}
		
			RayTracer::Point position;
			RayTracer::Vector velocity;
		};

		class Environment
		{
		public:
			Environment(RayTracer::Vector lGravity, RayTracer::Vector lWind) : gravity(lGravity), wind(lWind)
			{}
			
			RayTracer::Vector gravity;
			RayTracer::Vector wind;
		};

		Projectile& Tick(Environment& env, Projectile& proj)
		{
			RayTracer::Point position = proj.position + proj.velocity;
			RayTracer::Vector velocity = proj.velocity + env.gravity + env.wind;
			
			Projectile p(position, RayTracer::Tuple::normalize(velocity));
			return p;
		}

		void FireCannon()
		{	
			Projectile p(
				RayTracer::Point(0, 1, 0),
				RayTracer::Tuple::normalize(RayTracer::Vector(0, 1, 0)));

			Environment e(
				RayTracer::Vector(0, -0.05, 0),
				RayTracer::Vector(0, 0, 0));

			std::cout << "Initial position: " << p.position << std::endl;
			int numTicks = 0;
			while (p.position.y > 0)
			{				
				p = Tick(e, p);
				std::cout << "\nTick #" << ++numTicks << ": " << p.position << std::endl;
			}
			std::cout << "\nHit ground! " << p.position << std::endl;

		}
	}
}
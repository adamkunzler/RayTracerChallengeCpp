#pragma once

#include <iostream>
#include "../../src/Tuple.h"
#include "../../src/Point.h"
#include "../../src/Vector.h"

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

		Projectile Tick(Environment& env, Projectile& proj)
		{			
			RayTracer::Point position = proj.position + proj.velocity;
			RayTracer::Vector velocity = proj.velocity + env.gravity + env.wind;
			
			Projectile p(position, velocity);
			return p;
		}

		void FireCannon()
		{	
			Projectile p(
				RayTracer::Point(0.0f, 10.0f, 0.0f),
				//RayTracer::Vector(0.0f, 1.0f, 0.0f));
				RayTracer::Vector(2, 3, 0).normalize());

			Environment e(
				RayTracer::Vector(0.0f, -0.08f, 0.0f),
				RayTracer::Vector(-0.05f, 0.0f, 0.0f));
				
			int i = 0;
			while(p.position.y > 0)
			//for(int i = 0; i < 10; i++)
			{
				std::cout << "Tick #" << i++;
				p = Tick(e, p);
				std::cout << "\tposition => " << p.position << std::endl;
				
			}
			std::cout << "\nHit ground! " << p.position << std::endl;

		}
	}
}
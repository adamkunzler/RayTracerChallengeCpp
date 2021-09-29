#pragma once

namespace RayTracer
{	
	/// <summary>
	/// Represents an Ordered List of values (x, y, z, w)
	/// </summary>
	class Tuple
	{		
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Tuple() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
		Tuple(float lx, float ly, float lz, float lw) : x(lx), y(ly), z(lz), w(lw) { }
		Tuple(const Tuple& other) : x(other.x), y(other.y), z(other.z), w(other.w) { }
		
		// assignment operator
		Tuple& operator=(const Tuple& other)
		{
			if (this == &other)
				return *this;

			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;

			return *this;
		}
		
		inline bool isPoint() const { return FloatEquals(w, 1.0f); }
		bool isVector() const { return FloatEquals(w, 0.0f); }
						
		// Computes the magnitude of a Tuple		
		inline static float magnitude(const Tuple& t)
		{
			return std::sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
		}
						
		// Normalize a tuple so that it has a magnitude of 1.0.		
		inline static Tuple normalize(const Tuple& t)
		{			
			float m = magnitude(t);			
			Tuple tn(t.x / m, t.y / m, t.z / m, t.w / m);
			return tn;
		}
				
		// Calculates Dot product of two tuples (the cosine of the angle between 2 unit vectors)
		// 
		// Given a unit vector (magnitude of 1):
		//	-1 = pointing in opposite directions
		//   1 = identical vectors		
		inline static float dot(const Tuple& a, const Tuple& b)
		{			
			return a.x * b.x +
				   a.y * b.y +
				   a.z * b.z +
				   a.w * b.w;
		}
		
		// Calculate Cross Product between two Vectors.		
		//		The Cross Product is a Vector that is perpendicular to both input Vectors
		inline static Tuple cross(const Tuple& a, const Tuple& b)
		{			
			Tuple t(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x,
				0);
			return t;
		}
				
		inline bool operator==(const Tuple& other) const
		{									
			return FloatEquals(x, other.x) && 
				   FloatEquals(y, other.y) && 
				   FloatEquals(z, other.z) && 
				   FloatEquals(w, other.w);
		}
				
		inline bool operator!=(const Tuple& other) const
		{						
			return !(*this == other);
		}						

		inline Tuple operator+(const Tuple& other) const
		{ 
			Tuple t(x + other.x, y + other.y, z + other.z, w + other.w);
			return t;
		}
		
		inline Tuple operator-(const Tuple& other) const
		{ 
			Tuple t(x - other.x, y - other.y, z - other.z, w - other.w);
			return t;
		}
		
		inline Tuple operator-() const
		{
			Tuple t(-x, -y, -z, -w);
			return t;
		}
						
		inline Tuple operator*(const float& scalar) const
		{ 
			Tuple t(x * scalar, y * scalar, z * scalar, w * scalar);
			return t;
		}

		inline Tuple operator/(const float& scalar) const
		{ 
			Tuple t(x / scalar, y / scalar, z / scalar, w / scalar);			
			return t;
		}
	};
	
} // end namespace

// -------------------------------------------------------------------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream& os, const RayTracer::Tuple& tuple)
{
	os << "(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ")";
	return os;
}
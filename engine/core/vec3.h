#pragma once
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept> // for std out of range. 
using namespace std; 

constexpr float PI = 3.14159265359f; 

// convert degrees to radians
inline float radians(float degrees) 
{
	return degrees * (PI / 180.0f); 

}



class vec3 {
public: 
	float x, y, z; 
	
	// constructors
	// ini... vector to 0, 0, 0, 
	vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	// ini.. vector with specifict x,y,x values. 
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	// ini.... the vector by copying anothers vec3
	vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

	// operators 
	inline vec3 operator=(const vec3& rhs) // copies values from another vec3
	{
		if (this != &rhs) 
		{
			x = rhs.x; 
			y = rhs.y; 
			z = rhs.z; 
		}
		return *this; 
	}
	inline vec3 operator-() const // return the negative of the vector. 
	{
		return vec3(-x, -y, -z); 
	}

	inline vec3 operator+(const vec3& rhs) const // adds two vec3 vectors return result. 
	{
		return vec3(x + rhs.x, y + rhs.y, z + rhs.z); 
	}

	inline vec3 operator+=(const vec3& rhs)// adds another vector to the current one
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this; 
		
	}

	inline vec3 operator-(const vec3& rhs) const // subtracts one vec3 from another. 
	{
		return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	inline vec3 operator-=(const vec3& rhs) // subtracts another vector from the current one
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;

	}

	inline vec3 operator*=(const float scalar)// multiple scalar the vector by a scalar. 
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	inline vec3 operator* (const float scalar) const // multiple the vector by a scalar return the result 
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	inline bool operator==(const vec3& rhs) const // check if two vec3 vectors are equal 
	{
		return x == rhs.x && y == rhs.y && z == rhs.z; 
	}

	inline bool operator!=(const vec3& rhs) const//  check if two vec3 vectors are not equal. 
	{
		return !(*this == rhs); 
	}
	// provides access to x,y,z by i    i= index 
	inline float& operator[](const uint32_t i)
	{

		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		
		throw std::out_of_range("Index out of range. Valid ranga is [0 , 2");

		/*switch (i)
		{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: assert(false && "out of range");
		}*/
	}
	 
	// provides const access to x,y,x by i
	inline const float& operator[](const uint32_t i) const
	{

		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		
		throw std::out_of_range("Index out of range. Valid ranga is [0 , 2");
		/*switch (i)
		{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: assert(false && "out of range");
		}
			*/


	}
	

};



// to calculate the dot product of two vev3 vectors 
inline float dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z; 

}

// calculate the length of a vec2 
inline float length(const vec3& v)
{
	return std::sqrt(dot(v, v)); 

}

// calculate the cross procuct of two vec3 vector 
inline vec3 cross(const vec3& a, const vec3& b)
{
	return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); 

}

// normalize vec3 

inline vec3 normalize(const vec3 v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0.0f) return vec3(0.0f, 0.0f, 0.0f);
	return vec3(v.x / length, v.y / length, v.z / length);
}



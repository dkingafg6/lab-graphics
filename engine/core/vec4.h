
#pragma once
#include "vec3.h"
#include "vec4.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;


class vec4 {
public:
	float x;
	float y;
	float z;
	float w; 


	//constructors 
	vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {} // all vectors to 0 
	// all vectors with specific x, y, z,and w values. 
	vec4(float _x, float _y, float _z, float _w = 1.0f) : x(_x), y(_y), z(_z), w(_w) {} // all vectors with
	// copying another vec4 
	vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}


	//vecetor operations 
	vec4& operator=(const vec4& rhs) // copying values 
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w; 
		}
		return *this;
	}

	// return negative of the vector. 
	vec4 operator-() const
	{
		return vec4(-x, -y, -z, -w);
	}

	// add two vectors and return result. 
	vec4 operator+(const vec4& rhs) const
	{
		return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	// subtracts another vector from the currect one
	vec4 operator+=(const vec4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w; 
		return *this;

	}

	//subtracts one vec4 from another
	vec4 operator-(const vec4& rhs) const
	{
		return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}


	//subtracts anothers vetors from the current one 
	vec4 operator-=(const vec4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w; 
		return *this;

	}

	// multiple scales the vector by a scalar
	vec4 operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar; 
		return *this;
	}

	//multiple vector by  scalar and return result. 
	vec4 operator*(const float scalar) const
	{
		return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	// check if two vectors are equal. 
	bool operator==(const vec4& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	// ckech if not aqual. 

	bool operator!=(const vec4& rhs) const
	{
		//return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w; // add later 
		return !(*this == rhs);
	}



	// provides access to x,y,z,w by [i] = (0,1,2,3) , 
	float& operator[](const uint32_t i)
	{
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		if (i == 3) return w;
		throw std::out_of_range("Index out of range. Valid ranga is [0 , 3"); 
	}

	// provides const access to x,y,z,w, 

	const float& operator[](const uint32_t i) const
	{

		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		if (i == 3) return w;
		throw std::out_of_range("Index out of range. Valid ranga is [0 , 3");

		//switch (i)
		//{
		//case 0: return x;
		//case 1: return y;
		//case 2: return z;
		//case 3: return w;
		//default: assert(false && "out of range");
		//}

	}

	// normalize vec3 

	vec4 normalize(const vec4 v) {
		float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
		if (length == 0.0f) return vec4(0.0f, 0.0f, 0.0f, 0.0f);
		return vec4(v.x / length, v.y / length, v.z / length, v.w / length);
	}
	// normalize vec4 to use on camera calculation. 
	//vec4 normalize() const 
	//{
	//	float len = std::sqrt(x * x + y * y + z * z + w * w); 
	//	if (len > 0.0f) 
	//	{
	//		return vec4(x / len, y / len, z / len, w / len); 

	//	}
	//	// if the lenth = 0, return ziro. 
	//	return vec4(0.0f, 0.0f, 0.0f, 0.0f); 

	//}
	// overload the operator for printing a vec4 object to the ou
	friend std::ostream& operator<<(std::ostream& os, const vec4& v) 
	{
		os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w; ")";
		return os; 

	}


};

// calculate the dot product for vectors 
float dot(const vec4& a, const vec4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

}

// calculate the length of vectors 
float length(const vec4& v)
{
	return std::sqrt(dot(v, v));

}

// normalize vector each one 
//vec4 normalize(const vec4& v)
//{
//	float len = length(v);
//	if (len > 0.0f)
//	{
//		return vec4(v.x / len, v.y / len, v.z / len, v.w / len);
//	}
//	return vec4(0.0f, 0.0f, 0.0f, 0.0f); // if length is 0 return the vector is 0.
//
//
//}


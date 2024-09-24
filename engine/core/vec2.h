
#pragma once
//#include "vec3.h"
//#include "vec4.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;


class vec2 {
public:
	float x;
	float y;
	
	//constructors 
	vec2() : x(0.0f), y(0.0f) {} // all vectors to 0 
	// all vectors with specific x, y, values. 
	vec2(float _x, float _y = 1.0f) : x(_x), y(_y) {} // all vectors with
	// copying another vec4 
	vec2(const vec2& v) : x(v.x), y(v.y) {}


	//vecetor operations 
	vec2& operator=(const vec2& rhs) // copying values 
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			
		}
		return *this;
	}

	// return negative of the vector. 
	vec2 operator-() const
	{
		return vec2(-x, -y );
	}

	// add two vectors and return result. 
	vec2 operator+(const vec2& rhs) const
	{
		return vec2(x + rhs.x, y + rhs.y);
	}

	// subtracts another vector from the currect one
	vec2 operator+=(const vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		
		return *this;

	}

	//subtracts one vec4 from another
	vec2 operator-(const vec2& rhs) const
	{
		return vec2(x - rhs.x, y - rhs.y);
	}


	//subtracts anothers vetors from the current one 
	vec2 operator-=(const vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		
		return *this;

	}

	// multiple scales the vector by a scalar
	vec2 operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		
		return *this;
	}

	//multiple vector by  scalar and return result. 
	vec2 operator*(const float scalar) const
	{
		return vec2(x * scalar, y * scalar);
	}

	// check if two vectors are equal. 
	bool operator==(const vec2& rhs) const
	{
		return x == rhs.x && y == rhs.y ;
	}

	// ckech if not aqual. 

	bool operator!=(const vec2& rhs) const
	{
		//return x != rhs.x || y != rhs.y add later 
		return !(*this == rhs);
	}



	// provides access to x,y,z,w by [i] = (0,1)  
	float& operator[](const uint32_t i)
	{
		if (i == 0) return x;
		if (i == 1) return y;
	
		throw std::out_of_range("Index out of range. Valid ranga is [0 , 1");
	}

	// provides const access to x,y,z,w, 

	const float& operator[](const uint32_t i) const
	{

		if (i == 0) return x;
		if (i == 1) return y;
	
		throw std::out_of_range("Index out of range. Valid ranga is [0 , 1");

	}

	// normalize vec3 

	vec2 normalize(const vec2 v) {
		float length = std::sqrt(v.x * v.x + v.y * v.y);
		if (length == 0.0f) return vec2(0.0f, 0.0f);
		return vec2(v.x / length, v.y / length);
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
	friend std::ostream& operator<<(std::ostream& os, const vec2& v)
	{
		os << "(" << v.x << "," << v.y << ")";
		return os;

	}


};

// calculate the dot product for vectors 
float dot(const vec2& a, const vec2& b)
{
	return a.x * b.x + a.y * b.y;

}

// calculate the length of vectors 
float length(const vec2& v)
{
	return std::sqrt(dot(v, v));

}

// normalize vector each one 
//vec2 normalize(const vec2& v)
//{
//	float len = length(v);
//	if (len > 0.0f)
//	{
//		return vec4(v.x / len, v.y );
//	}
//	return vec4(0.0f, 0.0f); // if length is 0 return the vector is 0.
//
//
//}7777777



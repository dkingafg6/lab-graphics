#pragma once
#include <iostream>
#include <cassert>
using namespace std; 



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
	vec3 operator=(const vec3& rhs) // copies values from another vec3
	{
		if (this != &rhs) 
		{
			x = rhs.x; 
			y = rhs.y; 
			z = rhs.z; 
		}
		return *this; 
	}
	vec3 operator-() const // return the negative of the vector. 
	{
		return vec3(-x, -y, -z); 
	}

	vec3 operator+(const vec3& rhs) const // adds two vec3 vectors return result. 
	{
		return vec3(x + rhs.x, y + rhs.y, z + rhs.z); 
	}

	vec3 operator+=(const vec3& rhs)// adds another vector to the current one
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this; 
		
	}

	vec3 operator-(const vec3& rhs) const // subtracts one vec3 from another. 
	{
		return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	vec3 operator-=(const vec3& rhs) // subtracts another vector from the current one
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;

	}

	vec3 operator*=(const float scalar)// multiple scalar the vector by a scalar. 
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	vec3 operator* (const float scalar) const // multiple the vector by a scalar return the result 
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	bool operator==(const vec3& rhs) const // check if two vec3 vectors are equal 
	{
		return x == rhs.x && y == rhs.y && z == rhs.z; 
	}

	bool operator!=(const vec3& rhs) const//  check if two vec3 vectors are not equal. 
	{
		return !(*this == rhs); 
	}
	// provides access to x,y,z by i    i= index 
	float& operator[](const uint32_t i)
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
	const float& operator[](const uint32_t i) const
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

// normalize vec3 

vec3 normalize(const vec3 v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0.0f) return vec3(0.0f, 0.0f, 0.0f);
	return vec3(v.x / length, v.y / length, v.z / length);
}
//
//vec3 cross(const vec3& a, const vec3& b) {
//	return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * a.x);
//}
//
//
//
//// normalize vec3 
//vec3 Normalizevec3(const vec3& v)
//{
//	float len = length(v);
//	if (len > 0.0f)
//	{
//		return vec3(v.x / len, v.y / len, v.z / len);
//	}
//	return vec3(0.0f, 0.0f, 0.0f); // if length is 0 return the vector is 0.
//
//}

// to calculate the dot product of two vev3 vectors 
float dot(const vec3& a, const vec3& b) 
{
	return a.x * b.x + a.y * b.y + a.z * b.z; 

}

// calculate the length of a vec2 
float length(const vec3& v) 
{
	return std::sqrt(dot(v, v)); 

}

// calculate the cross procuct of two vec3 vector 
vec3 cross(const vec3& a, const vec3& b) 
{
	return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); 

}

//// normalize vec3 
//vec3 Normalizevec3(const vec3& v)
//{
//	float len = length(v);
//	if (len > 0.0f)
//	{
//		return vec3(v.x / len, v.y / len, v.z / len);
//	}
//	return vec3(0.0f, 0.0f, 0.0f); // if length is 0 return the vector is 0.
//
//}



//vec2 implement 

//
//#pragma once
////#include "vec3.h"
////#include "vec4.h"
//#include <stdexcept>
//#include <cmath>
//#include <iostream>
//#include <cassert>
//
//using namespace std;
//
//
//class vec2 {
//public:
//	float x;
//	float y;
//
//	//constructors 
//	vec2() : x(0.0f), y(0.0f) {} // all vectors to 0 
//	// all vectors with specific x, y, values. 
//	vec2(float _x, float _y = 1.0f) : x(_x), y(_y) {} // all vectors with
//	// copying another vec4 
//	vec2(const vec2& v) : x(v.x), y(v.y) {}
//
//
//	//vecetor operations 
//	vec2& operator=(const vec2& rhs) // copying values 
//	{
//		if (this != &rhs)
//		{
//			x = rhs.x;
//			y = rhs.y;
//
//		}
//		return *this;
//	}
//
//	// return negative of the vector. 
//	vec2 operator-() const
//	{
//		return vec2(-x, -y);
//	}
//
//	// add two vectors and return result. 
//	vec2 operator+(const vec2& rhs) const
//	{
//		return vec2(x + rhs.x, y + rhs.y);
//	}
//
//	// subtracts another vector from the currect one
//	vec2 operator+=(const vec2& rhs)
//	{
//		x += rhs.x;
//		y += rhs.y;
//
//		return *this;
//
//	}
//
//	//subtracts one vec4 from another
//	vec2 operator-(const vec2& rhs) const
//	{
//		return vec2(x - rhs.x, y - rhs.y);
//	}
//
//
//	//subtracts anothers vetors from the current one 
//	vec2 operator-=(const vec2& rhs)
//	{
//		x -= rhs.x;
//		y -= rhs.y;
//
//		return *this;
//
//	}
//
//	// multiple scales the vector by a scalar
//	vec2 operator*=(const float scalar)
//	{
//		x *= scalar;
//		y *= scalar;
//
//		return *this;
//	}
//
//	//multiple vector by  scalar and return result. 
//	vec2 operator*(const float scalar) const
//	{
//		return vec2(x * scalar, y * scalar);
//	}
//
//	// check if two vectors are equal. 
//	bool operator==(const vec2& rhs) const
//	{
//		return x == rhs.x && y == rhs.y;
//	}
//
//	// ckech if not aqual. 
//
//	bool operator!=(const vec2& rhs) const
//	{
//		//return x != rhs.x || y != rhs.y add later 
//		return !(*this == rhs);
//	}
//
//
//
//	// provides access to x,y,z,w by [i] = (0,1)  
//	float& operator[](const uint32_t i)
//	{
//		if (i == 0) return x;
//		if (i == 1) return y;
//
//		throw std::out_of_range("Index out of range. Valid ranga is [0 , 1");
//	}
//
//	// provides const access to x,y,z,w, 
//
//	const float& operator[](const uint32_t i) const
//	{
//
//		if (i == 0) return x;
//		if (i == 1) return y;
//
//		throw std::out_of_range("Index out of range. Valid ranga is [0 , 1");
//
//	}
//
//	// normalize vec3 
//
//	vec2 normalize(const vec2 v) {
//		float length = std::sqrt(v.x * v.x + v.y * v.y);
//		if (length == 0.0f) return vec2(0.0f, 0.0f);
//		return vec2(v.x / length, v.y / length);
//	}
//	// normalize vec4 to use on camera calculation. 
//	//vec4 normalize() const 
//	//{
//	//	float len = std::sqrt(x * x + y * y + z * z + w * w); 
//	//	if (len > 0.0f) 
//	//	{
//	//		return vec4(x / len, y / len, z / len, w / len); 
//
//	//	}
//	//	// if the lenth = 0, return ziro. 
//	//	return vec4(0.0f, 0.0f, 0.0f, 0.0f); 
//
//	//}
//	// overload the operator for printing a vec4 object to the ou
//	friend std::ostream& operator<<(std::ostream& os, const vec2& v)
//	{
//		os << "(" << v.x << "," << v.y << ")";
//		return os;
//
//	}
//
//
//};
//
//// calculate the dot product for vectors 
//float dot(const vec2& a, const vec2& b)
//{
//	return a.x * b.x + a.y * b.y;
//
//}
//
//// calculate the length of vectors 
//float length(const vec2& v)
//{
//	return std::sqrt(dot(v, v));
//
//}
//
//// normalize vector each one 
////vec2 normalize(const vec2& v)
////{
////	float len = length(v);
////	if (len > 0.0f)
////	{
////		return vec4(v.x / len, v.y );
////	}
////	return vec4(0.0f, 0.0f); // if length is 0 return the vector is 0.
////
////
////}7777777



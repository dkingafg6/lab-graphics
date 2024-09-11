  
#include <iostream>
#pragma once
#include "vec3.h"
#include "vec4.h"
#include <cmath> 
#include "util.h"
#include <stdexcept>

using namespace std; 





// matrix operations 
// 
// Product, product with vector
// nitialization functions for rotation matrices around the x, y, z axis and an arbitrary vector.
// Transpose and inverse.
// 
// 
// class a matrix 4*4
class mat4 {
public:
	vec4 m[4]; // matrix by 4 vec4 columns. 

	// constructor with identity matrix. all columns 
	
	mat4() 
	{
		m[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
		m[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
		m[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
		m[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		

	}
	 // ini...matrix with 4 vec4 rows. 
	mat4(const vec4& c0, const vec4& c1, const vec4& c2, const vec4& c3)
	{
		m[0] = c0;
		m[1] = c1;
		m[2] = c2;
		m[3] = c3;


	}
	mat4(const mat4& rhs) // copy the constructor 
	{
		for (int i = 0; i < 4; ++i) 
		{
			m[i] = rhs.m[i]; 
		}
	}

	// copies values from another mat4
	mat4& operator=(const mat4& rhs) 
	{
		if (this != &rhs) 
		{
			for (int i = 0; i < 4; ++i) 
			{
				m[i] = rhs.m[i]; 

			}
		}
		return *this; 
	}
	// check if two mat4 matrices are equal.
	bool operator==(const mat4& rhs) const 
	{
		for (int i = 0; i < 4; ++i)
		{
			if(m[i] != rhs.m[i]) return false; 
		}
		return true; 
	}

	// check if two mat4 matrices are not equal 
	bool operator!=(const mat4& rhs) const 
	{
		return !(*this == rhs); 
	}

	// provides access to matrix columns bu i 0 to 3
	vec4& operator[](const uint32_t i) 
	{
		if (i < 4) return m[i]; 
		throw std::out_of_range("Index out of range. valid range is [0, 3],");
	}

	// provides const access to matrix columns bu i 0 to 3
	const vec4& operator[](const uint32_t i) const
	{
		if (i < 4) return m[i];
		throw std::out_of_range("Index out of range. valid range is [0, 3],");
	}

	// multiples two mat4 matrices 
	mat4 operator*(const mat4& rhs) const 
	{
		std::cout << " Matrix A:\n" << this->m[0][0] << std::endl; 
		std::cout << " Matrix B:\n"; for (int i = 0; i < 4; ++i)
			std::cout << rhs.m[i] << std::endl;
		mat4 result = mat4(); 
		int counter = 0; 
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				result[i][j] = 0; 
				for (int k = 0; k < 4; k++) 
				{
					result[i][j] += this->m[k][j] * rhs[i][k];

				}

			}

		}
		/*mat4 thisTrans;*/
	/*	for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				thisTrans[i][j] = this->m[j][i];
			}
		}*/

		//for (int i = 0; i < 4; i++) 
		//{
		//	
		//	for (int j = 0; j < 4; j++) 
		//	{
		//		result[i][j] = 0.0f; // ini... result to zero. 
		//		for (int k = 0; k < 4; k++)
		//		{
		//			result[i][j] += this->m[i][k] * rhs.m[k][j];

		//		}
		//			
		//	}

		//}

		
		return result; 

	}

	// multiples the matrix by vec4; 
	vec4 operator*(const vec4& rhs) const 
	{
		vec4 result = vec4();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result[i] += this->m[j][i] * rhs[j];
			}
		}

		/*for (int i = 0; i < 4; i++)
		{
			result[i] = dot(m[i], rhs);
		}*/
		return result;
		//return vec4(
		//	dot(m[0], rhs), // 1a row of the matrix dot product with vector
		//	dot(m[1], rhs), // 2a row of the matrix dot product with vector
		//	dot(m[2], rhs), // 3a row of the matrix dot product with vector
		//	dot(m[3], rhs) // 4a row of the matrix dot product with vector
		//);

	}

	
	public: 
		mat4 operator*(float scalar) const // scalar multication 
		{
			return mat4(
				m[0] * scalar,
				m[1] * scalar,
				m[2] * scalar,
				m[3] * scalar
			); 

		}
		friend std::ostream& operator<<(std::ostream& os, const mat4& mat) 
		{
			for (int i = 0; i < 4; ++i) 
			{
				os << mat.m[i] << std::endl;

			}
			return os; 

		}

};




// return the transpese of a mat4 swapping rows and columns 
static mat4 transpose(const mat4& mat) // transpose matrix
{
	return mat4(
		vec4(mat.m[0].x, mat.m[1].x, mat.m[2].x, mat.m[3].x),
		vec4(mat.m[0].y, mat.m[1].y, mat.m[2].y, mat.m[3].y),
		vec4(mat.m[0].z, mat.m[1].z, mat.m[2].z, mat.m[3].z),
		vec4(mat.m[0].w, mat.m[1].w, mat.m[2].w, mat.m[3].w)


	);
}




// static fun to create a rotation matrix for a rotation around the x axis. 
static mat4 rotationx(float radians)
{
	float c = std::cos(radians);
	float s = std::sin(radians);
	return mat4(
		vec4(1.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, c, s, 0.0f),
		vec4(0.0f, -s, c, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)


	);
	//std::cout << "Rotation X Matrix:\n" << result << std::endl;

}

// static fun to create a rotation matrix for a rotation around the y axis. 
static mat4 rotationy(float radians)
{
	float c = std::cos(radians);
	float s = std::sin(radians);
	return mat4(
		vec4(c, 0.0f, -s, 0.0f),
		vec4(0.0f, 1.0f, 0.0f, 0.0f),
		vec4(s, 0.0f, c, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

}


// static fun to create a rotation matrix for a rotation around the z axis. 
static mat4 rotationz(float radians)
{
	float c = std::cos(radians);
	float s = std::sin(radians);
	return mat4(
		vec4(c, s, 0.0f, 0.0f),
		vec4(-s, c, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 1.0f, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

}

// static fun.. create a rotation matrix around an arbitrary axis, 
static mat4 rotationaxis(const vec3& axis, float radians)
{
	float c = std::cos(radians);
	float s = std::sin(radians);
	float x = axis.x, y = axis.y, z = axis.z;
	float t = 1.0f - c;
	return mat4(
		vec4(t * x * x + c, t * x * y + s * z, t * x * z - s * y, 0.0f),
		vec4(t * x * y - s * z, t * y * y + c, t * y * z + s * x, 0.0f),
		vec4(t * x * z + s * y, t * y * z - s * x, t * z * z + c, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

}


// calculate the confactor of the matrix. 
static float cofactor(const mat4& mat, int row, int col)
{
	mat4 submatrix;
	int sub_i = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (i == row) continue;
		int sub_k = 0;
		for (int k = 0; k < 4; ++k)
		{
			if (k == col) continue; 
			submatrix.m[sub_i][sub_k] = mat.m[i][k]; 
			++sub_k; 

		//	if (k == col) continue; // accessing matrix components, assign each ideividual component.
		//	if (sub_k == 0) submatrix.m[sub_i].x = mat.m[i][k];
		//	if (sub_k == 1) submatrix.m[sub_i].y = mat.m[i][k];
		//	if (sub_k == 2) submatrix.m[sub_i].z = mat.m[i][k];
		//	if (sub_k == 3) submatrix.m[sub_i].w = mat.m[i][k];
		//	submatrix.m[sub_i][sub_k] = mat.m[i][k];
		//	++sub_k;

		}
		++sub_i;

	}

	// determinant of 3*3 submatrix. 
	float det_submatrix =
		submatrix.m[0][0] * (submatrix.m[1][1] * submatrix.m[2][2] - submatrix.m[1][2] * submatrix.m[2][1]) -
		submatrix.m[0][1] * (submatrix.m[1][0] * submatrix.m[2][2] - submatrix.m[1][2] * submatrix.m[2][0]) +
		submatrix.m[0][2] * (submatrix.m[1][0] * submatrix.m[2][1] - submatrix.m[1][1] * submatrix.m[2][0]);
	
	return ((row + col) % 2 == 0) ? det_submatrix : -det_submatrix; 


	/*float det_submatrix =
		submatrix.m[0].x * (submatrix.m[1].y * submatrix.m[2].z - submatrix.m[1].z * submatrix.m[2].y) -
		submatrix.m[0].y * (submatrix.m[1].x * submatrix.m[2].z - submatrix.m[1].z * submatrix.m[2].x) +
		submatrix.m[0].z * (submatrix.m[1].x * submatrix.m[2].y - submatrix.m[1].y * submatrix.m[2].x);
	if ((row + col) % 2 == 1) det_submatrix = -det_submatrix;
	return det_submatrix;*/

	// with this function can calculate cofactor matriz given row and col in both 3*3 and 4*4 marix 
	// 
	//return 1.0f;  // plaaceholder return value

}


// that fun.. to compute adjugate matrix 
static mat4 adjoint(const mat4& mat)
{
	mat4 adj;
	for (int i = 0; i < 4; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			adj.m[i][k] = cofactor(mat, i, k);

		}

	}
	return transpose(adj);
	// compute the adjugate means transpose of the cofactor matrix 
	//return mat4(); // placeholder return value. 

}

// compute the determinant of a mat4
static float determinant(const mat4& mat)
{
	return mat.m[0][0] * cofactor(mat, 0, 0) -
		mat.m[0][1] * cofactor(mat, 0, 1) +
		mat.m[0][2] * cofactor(mat, 0, 2) -
		mat.m[0][3] * cofactor(mat, 0, 3);
	//float det = 0.0f; // calculate for a 4*4 matrix. 

	//det += mat.m[0].x * cofactor(mat, 0, 0);
	//det -= mat.m[1].x * cofactor(mat, 0, 1);
	//det += mat.m[2].x * cofactor(mat, 0, 2);
	//det -= mat.m[3].x * cofactor(mat, 0, 3);
	//return det;

}

// static fun to returns the invers of  mat4 or identify if not invertible. 
static mat4 inverse(const mat4& mat)
{
	float det = determinant(mat);
	if (std::abs(det) < 1e-6f)
	{
		throw std::runtime_error("Matrix is not invertiable"); // return identify matrix if the determinant is 0 or not invers
		//return mat4(); // return identify matrix if the determinant is 0 or not invers

	}
	mat4 adjugate = adjoint(mat);
	return adjugate * (1.0f / det);

}

//// fun.. to calculate matrix 
//float dot(const vec4& a, const vec4& b) {
//	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
//}

//
//// matnearequal fun... check if two matrics a and b are approximitly within specified tolerance. 
bool nearequal(const vec4& a, const vec4& b, float epsilon)
{
	return std::fabs(a.x - b.x) < epsilon &&
		std::fabs(a.y - b.y) < epsilon &&
		std::fabs(a.z - b.z) < epsilon && 
		std::fabs(a.w - b.w) < epsilon;


}
// check if  two mat4 vectors a and b are approximately equal within a specified torelransce.
// epsilon is the tolaerance value within which two cectors are concidered equal. 
bool matnearequal(const mat4& a, const mat4& b, float epsilon) 
{
	for (int i = 0; i < 4; ++i) 
	{
		if (!nearequal(a.m[i], b.m[i], epsilon))
		{
			return false; 

		}
		
	}
	return true; 

}
// function after the mat4 class definition. 
//extern float dot(const vec4& a, const vec4& b) 
//{
//	return(a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w); 
//
//}



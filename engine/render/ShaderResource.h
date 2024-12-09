#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <core/vec4.h>
#include <core/vec3.h>
#include <core/mat4.h>

#include <math.h>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include <string>
#include <stdexcept>
#define CAPACITY 600 // Hash table size


using namespace std;

// take the files convert to the text file
string get_file_contents(const char* filename); 

// ShaderResource class handles loading, compiling, for those using OpenGL shader programs. 
class ShaderResource
{
public:
	
	// constructor
	ShaderResource(); 
	
	
	
	// destructor
	~ShaderResource(); 
	

	
	//// Load shader source file, compiles and vertex shader plus fragment shader after compile links them into a shader program. 
	void loadShaderResource(const string& FilePath, GLenum TYPENAME);

	// compiles one single shader return its ID. 
	//GLint compileShader(GLenum shaderType, const char* shadersource);

	void LinkProgram(); 
	// connect this shader program for use in rendering. 
	// OBS this function (UseProgram()) should call before any object render. 
	// be sour that correct shaders are used. 
	// in example.cpp should be in right order. 
	void UseProgram(); 

	//Add functions to modify uniform variables of at least the type Matrix4fv .
	// use a 4x4 matrix uniform in the shader.
	// helping transformation to be used
	void SetUniformMatrix4fv(const string& name, const	mat4& matrix);

	//Add functions to modify uniform variables of at least the type Vector4f (or Vector4fv).
	//use 4D vector uniform in the shader used for colors position. 
	void SetUniformVector4fv(const string& name, const	vec4& vector);

	void setUniform1f(const string& name, float value); 
	void setUniform1I(const string& name, float value); 
	void setUniform3fv(const string& name, const vec3& vector); 

	// false = 0    and true = 1. 
	void setBool(const string& name, int statement); 



	// load shader source code from file returns as a string. 
	//string loadShaderSource(const char* filePath);

	// get location of the uniform's variable from the shader program. 
	// can use it later. 
	GLint getUniformLocation(const string& name);



private:
	// Hashtabel
	unsigned long hashFunction(const string& str); 
	void insertIntoHashTable(const string& name, GLint location); 
	GLint findInHashTable(const string& name); 

	GLuint vertexShader;
	GLuint pixelShader;
	GLuint program = 0; 
	// ID linked the shader program in OpneGL
	GLuint programID;


	// define hashtable 
	struct HashItem
	{
		string key; 
		GLint value; 
		HashItem* next; 

	};
	// for cach uniforms
	vector<HashItem*> uniformHashTable; 

	// (optional add ) Do the reducing the overhead of multiple lookup.  
	//unordered_map<string, GLint> uniformLocationas; // cache for uniform location. 

	
};

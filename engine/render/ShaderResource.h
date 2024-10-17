#pragma once
#include <config.h>
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <stdexcept>


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
	
	GLuint vertexShader; 
	GLuint indexShader; 
	GLuint fragmentShader; 

	// ID linked the shader program in OpneGL
	GLuint programID; 

	// (optional add ) Do the reducing the overhead of multiple lookup.  
	unordered_map<string, GLint> uniformLocationas; // cache for uniform location. 
	
	//// Load shader source file, compiles and vertex shader plus fragment shader after compile links them into a shader program. 
	void loadFromFiles(const string& vertexFilePath, GLenum fregmentFilePath);

	// compiles one single shader return its ID. 
	GLint compileShader(GLenum shaderType, const char* shadersource);


	// connect this shader program for use in rendering. 
	// OBS this function (UseProgram()) should call before any object render. 
	// be sour that correct shaders are used. 
	void UseProgram(); 

	//Add functions to modify uniform variables of at least the type Matrix4fv .
	// use a 4x4 matrix uniform in the shader.
	// helping transformation to be used
	void SetUniformMatrix4fv(const char* name, const GLfloat* value);

	//Add functions to modify uniform variables of at least the type Vector4f (or Vector4fv).
	//use 4D vector uniform in the shader used for colors position. 
	void SetUniformVector4fv(const char* name, const GLfloat* value);


	// load shader source code from file returns as a string. 
	string loadShaderSource(const char* filePath);

	// get location of the uniform's variable from the shader program. 
	// can use it later. 
	GLint getUniformLocation(const char* name);



private:
	
};

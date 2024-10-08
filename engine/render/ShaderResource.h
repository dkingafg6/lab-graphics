#pragma once
#include <config.h>
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <string>


using namespace std;

// take the file convert to text file
//string get_file_contents(const char* filename); 

// ShaderResource class handles loading, compiling, for those using OpenGL shader programs. 
class ShaderRsource
{
public:
	
	ShaderRsource()
	{
	}
	
	// constructor
	~ShaderRsource(); // Destructor

	// ID linked the shader program in OpneGL
	GLuint programID; 

	unordered_map<string, GLint> uniformLocationas; 
	
	//// Load shader source file, compiles and vertex shader plus fragment shader after compile links them into a shader program. 
	void loadfromFiles(const string& vertexShaderPath, const string& fragmentShaderPath); 

	// compiles shader 
	GLint copileShader(GLenum shaderType, const string& shadersource);
	// connect this shader program for use in rendering. 
	void Use(); 

	// use a 4x4 matrix uniform in the shader.
	void SetUniformMatrix4fv(const string& name, const GLfloat* value); 

	//use 4D vector uniform in the shader. 
	void SetUniformVector4fv(const string& name, const GLfloat* value);

	

	// load shader source from file. 
	string loadShaderSource(const string& filePath); 

	// get location of the uniform's variable from the shader program. 
	GLint getUniformLocation(const string& name); 

	// active 
	void Active(); 
	// delete. 
	void Delete(); 



private:
	// to check for shader compilation and linked errors. 
	void compileErrors(unsigned shader, const char* type); 

};

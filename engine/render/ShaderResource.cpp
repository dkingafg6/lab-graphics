
#pragma once
#include <config.h>
#include "ShaderResource.h"
#include <stdexcept>

using namespace std;



ShaderRsource::~ShaderRsource()
{
}




void ShaderRsource::loadfromFiles(const string& vertexShaderPath, const string& fragmentShaderPath)
{
	
}

// compiles shader 
GLint ShaderRsource::copileShader(GLenum shaderType, const string& shadersource)
{
	return GLint();
}

// connect ths shader program for use in renderingl. 
void ShaderRsource::Use()
{
}

// use a 4x4 matrix uniform in the shader.
void ShaderRsource::SetUniformMatrix4fv(const string& name, const GLfloat* value)
{
}

//use 4D vector uniform in the shader. 
void ShaderRsource::SetUniformVector4fv(const string& name, const GLfloat* value)
{
}

// load shader source from file. 
string ShaderRsource::loadShaderSource(const string& filePath)
{
	return string();
}

// get location of the uniform's variable from the shader program. 
GLint ShaderRsource::getUniformLocation(const string& name)
{
	return GLint();
}

// active 
void ShaderRsource::Active()
{

}

// delete 
void ShaderRsource::Delete()
{
}

void ShaderRsource::compileErrors(unsigned shader, const char* type)
{
}

//void ShaderRsource::compileErrors(unsigned shader, const char* type)
//{
//}


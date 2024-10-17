
#pragma once
#include <config.h>
#include "ShaderResource.h"

using namespace std;



ShaderResource::ShaderResource()
{
	// initialize to the 0 
	programID = 0;
	 
}

ShaderResource::~ShaderResource()
{
	//Delete();
	
	 // clean the shader resource. 
	 
}

// convert file to string  after reading the file. 
string get_file_contents(const char* filename)
{
	return string();
}

// compile and linking Process
// 1. load Shader Resource Code. 
// 2. compile individual Shader. 
// 3. link the Shader into a Program. 
// compiles shader 
GLint ShaderResource::compileShader(GLenum shaderType, const char* shadersource)
{
	// store statuse of compilation 
	GLint shader = glCreateShader(shaderType);

	// shader source code. 
	glShaderSource(shader, 1, &shadersource, nullptr);

	// compile shader. 
	glCompileShader(shader);

	// check for shader's compile error
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint LogSize;

		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &LogSize);

		vector<char> errolog(LogSize);

		glGetShaderInfoLog(shader, LogSize, nullptr, errolog.data());
		cerr << "[SHADER COMPILE ERROR]:" << errolog.data() << endl;

		// cleanup 
		glDeleteShader(shader);
		throw runtime_error("shader compilation failed:");
	}

	return shader;
}


// what should have inside loadfromFile
//.Either use an argument per shader type(vertex + fragment) or load them separately.
//.After loading the file, compile and link the shader and write any errors to the console.
//.Use proper error handling.Do not silently fail if there are errors while opening the files or compiling.
// 1. compile each shader vertex or fragment must be compiled independently using (glCompileShader() ) 
// 2. link After compilaion 
void ShaderResource::loadFromFiles(const string& vertexFilePath, GLenum fregmentFilePath)
{
	// ckeck if there is program if not create it. 
	if (this->programID == 0) 
	{
		this->programID = glCreateProgram();
	}

	// load the source code of vertex shader. 
	string vertexShaderSource = get_file_contents(vertexFilePath.c_str()); 
	GLint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str()); 


	// attach the compiled shader to the program 
	glAttachShader(this->programID, vertexShader);
	glAttachShader(this->programID, fragmentShader);

	// link program
	glLinkProgram(programID); 

	// checking errors for linking. 

	GLint success;
	// checking shader compilation.
	glGetShaderiv(programID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint LogSize;

		glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &LogSize);

		// print the error log.
		vector<char> errorLog(LogSize);

		glGetShaderInfoLog(programID, LogSize, nullptr, errorLog.data());
		cerr << "[SHADER COMPILE ERROR]:" << errorLog.data() << endl;

		// cleanup 
		glDeleteShader(programID);
		throw runtime_error("shader compiling failed:");

	}

	// cleanup individual shaders after linking 
	glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader);






	//string shaderString = ""; 
	//ifstream shaderFile(vertexFilePath); 

	//if (!shaderFile) 
	//{
	//	std::cerr << "Error file cannot open " << std::endl;
	//	throw runtime_error("Failed to open shader file"); 
	//	// reading  shader file as string 
	//	
	//}
	//
	//shaderString.assign(istreambuf_iterator<char>(shaderFile), istreambuf_iterator<char>());

	//shaderFile.close(); 

	//
	//const GLchar* shaderChar = shaderString.c_str();      

	//GLint shaderlength = static_cast<GLint>(shaderString.length()); 

	//
	//GLint shaderID = glCreateShader(fregmentFilePath);

	//glShaderSource(shaderID, 1, &shaderChar, &shaderlength);
	//glCompileShader(shaderID);
	//// check compilation for vertex shader. 


	//
	//// attach the compiled shader to the program 
	//glAttachShader(this->programID, shaderID); 

	//if (fregmentFilePath == GL_FRAGMENT_SHADER)
	//{
	//	glLinkProgram(this->programID);

	//	//// check compilation for vertex shader. 
	//	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	//	if (success == GL_FALSE)
	//	{
	//		GLint LogSize;
	//		
	//		glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &LogSize);

	//		vector<char> errolog(LogSize); 
	//		
	//		glGetShaderInfoLog(this->programID, LogSize, nullptr, errolog.data());
	//		cerr << "[PROGRAG LINK ERROR]:" << errolog.data() << endl;

	//		// cleanup 
	//		glDeleteShader(shaderID);
	//		throw runtime_error("program linking failed:");
	//	}

	//}
	//glDeleteShader(shaderID); 
	//

	////// 
	////	string vertexSoruce = get_file_contents(vertexFilePath);
	////	string vertexSoruce = get_file_contents(fragmentFilePath);
	//
}


// connect the shader program for use in rendering. 
// or active the shader program for use in rendering. 
// OBS this function (Use() = Active) should call before any object render. 
void ShaderResource::UseProgram()
{
	glUseProgram(programID); 
}

// use a 4x4 matrix uniform in the shader.
void ShaderResource::SetUniformMatrix4fv(const char* name, const GLfloat* value)
{
	GLint location = getUniformLocation(name); 
	// set the uniform 
	glUniformMatrix4fv(location, 1, GL_FALSE, value); 
}

//use 4D vector uniform in the shader. 
void ShaderResource::SetUniformVector4fv(const char* name, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	// set the uniform 
	glUniform4fv(location, 1, value);
}

// load shader source from file. 
string ShaderResource::loadShaderSource(const char*  filePath)
{
	return get_file_contents(filePath);
}

// get location of a uniform variable takes a parameter. 
GLint ShaderResource::getUniformLocation(const char* name)
{
	// sheck cach first
	if(uniformLocationas.find(name) != uniformLocationas.end()) 
	{
		return uniformLocationas[name]; 

	}

	// if not get the location store in in cache
	GLint location = glGetUniformLocation(programID, name); 
	if (location == -1) 
	{
		cerr << "[uniform location error]: uniform '" << name << "' not found " << endl;
	}

	// cach location 
	uniformLocationas[name] = location; 

	//return the location. 
	return location; 
}


#pragma once
#include <config.h>
#include "ShaderResource.h"

using namespace std;



ShaderRsource::ShaderRsource()
{
	// initialize to the 0 
	programID = 0;
	 
}

ShaderRsource::~ShaderRsource()
{
	//Delete();
	
	 // clean the shader resource. 
	 
}

// convert file to string  after reading the file. 
string get_file_contents(const char* filename)
{
	return string();
}




// what should have inside loadfromFile
//.Either use an argument per shader type(vertex + fragment) or load them separately.
//.After loading the file, compile and link the shader and write any errors to the console.
//.Use proper error handling.Do not silently fail if there are errors while opening the files or compiling.
void ShaderRsource::loadfromFiles(const string& FilePath, GLenum Typename)
{
	if (this->programID == 0) 
	{
		this->programID = glCreateProgram();
	}
	string shaderString = ""; 
	ifstream shaderFile(FilePath); 

	if (!shaderFile) 
	{
		std::cerr << "Error file cannot open " << std::endl;
		throw runtime_error("Failed to open shader file"); 
		// reading  shader file as string 
		
	}
	
	shaderString.assign(istreambuf_iterator<char>(shaderFile), istreambuf_iterator<char>());

	shaderFile.close(); 

	
	const GLchar* shaderChar = shaderString.c_str();      

	GLint shaderlength = static_cast<GLint>(shaderString.length()); 

	
	GLint shaderID = glCreateShader(Typename); 

	glShaderSource(shaderID, 1, &shaderChar, &shaderlength);
	glCompileShader(shaderID);
	// check compilation for vertex shader. 


	 //get error log
	GLint success; 
	// checking shader compilation.
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint LogSize;
	
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &LogSize);

		// print the error log.
		vector<char> errorLog(LogSize); 
	
		glGetShaderInfoLog(shaderID, LogSize, nullptr, errorLog.data());
		cerr << "[SHADER COMPILE ERROR]:" << errorLog.data() << endl; 

		// cleanup 
		glDeleteShader(shaderID);
		throw runtime_error("shader compiling failed:"); 
		
	}

	
	// attach the compiled shader to the program 
	glAttachShader(this->programID, shaderID); 

	if (Typename == GL_FRAGMENT_SHADER) 
	{
		glLinkProgram(this->programID);

		//// check compilation for vertex shader. 
		glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint LogSize;
			
			glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &LogSize);

			vector<char> errolog(LogSize); 
			
			glGetShaderInfoLog(this->programID, LogSize, nullptr, errolog.data());
			cerr << "[PROGRAG LINK ERROR]:" << errolog.data() << endl;

			// cleanup 
			glDeleteShader(shaderID);
			throw runtime_error("program linking failed:");
		}

	}
	glDeleteShader(shaderID); 
	

	//// 
	//	string vertexSoruce = get_file_contents(vertexFilePath);
	//	string vertexSoruce = get_file_contents(fragmentFilePath);
	
}

// compiles shader 
GLint ShaderRsource::compileShader(GLenum shaderType, const char* shadersource)
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

// connect the shader program for use in rendering. 
// or active the shader program for use in rendering. 
// OBS this function (Use() = Active) should call before any object render. 
void ShaderRsource::Use()
{
	glUseProgram(programID); 
}

// use a 4x4 matrix uniform in the shader.
void ShaderRsource::SetUniformMatrix4fv(const char* name, const GLfloat* value)
{
	GLint location = getUniformLocation(name); 
	// set the uniform 
	glUniformMatrix4fv(location, 1, GL_FALSE, value); 
}

//use 4D vector uniform in the shader. 
void ShaderRsource::SetUniformVector4fv(const char* name, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	// set the uniform 
	glUniform4fv(location, 1, value);
}

// load shader source from file. 
string ShaderRsource::loadShaderSource(const char*  filePath)
{
	return get_file_contents(filePath);
}

// get location of a uniform variable takes a parameter. 
GLint ShaderRsource::getUniformLocation(const char* name)
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

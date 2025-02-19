
#pragma once
#include <config.h>
#include "ShaderResource.h"

ShaderResource::ShaderResource()
{

	this->pixelShader = 0; 
	this->vertexShader = 0; 
	uniformHashTable.resize(CAPACITY, nullptr); 
	// initialize to the 0 
	//programID = 0;
	 
}

ShaderResource::~ShaderResource()
{
	if (this->program != 0) 
	{
		glDeleteProgram(this->program); 
	}

	for (auto& item : uniformHashTable) 
	{
		while (item) 
		{
			HashItem* temp = item; 
			item = item->next; 
			delete temp; 
		}
	}
	
	
	   
}

// compile and linking Process
// 1. load Shader Resource Code. 
// 2. compile individual Shader. 
// 3. link the Shader into a Program. 
// compiles shader 

void ShaderResource::loadShaderResource(const string& FilePath, GLenum TYPENAME)
{
	if (this->program == 0)
	{
		this->program = glCreateProgram();
	}
	string shaderString = "";
	std::ifstream shaderFile(FilePath);
	if (!shaderFile.is_open())
	{
		// convert shader file to string for read. 
		//shaderString.assign(istreambuf_iterator<char>(shaderFile), istreambuf_iterator<char>());
		throw std::runtime_error("Fialed to open shader file: " + FilePath); 
	}
	/*else
	{
		printf(" Error file couldent't open ");
	}*/
	std::stringstream buffer; 
	buffer << shaderFile.rdbuf(); 
	std::string shaderSource = buffer.str(); 
	shaderFile.close();

	// debuging shader source 
	std::cout << " Loaded shader source from " << FilePath << ":\n" << shaderSource << endl;

	// create shader object  and  Error log
	GLint shader = glCreateShader(TYPENAME);

	// compile shader
	const GLchar* shaderChar = shaderSource.c_str();
	//GLuint shader = glCreateShader(TYPENAME); 
	GLint length = static_cast<GLint>(strlen(shaderChar));
	glShaderSource(shader, 1, &shaderChar, &length);
	glCompileShader(shader);

	GLint compileStatues; 
	// check compilation errors
	//GLint shaderLogSize;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatues);
	if (compileStatues != GL_TRUE)
	{
		GLint logSize; 

		//GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH,&logSize);
		std::vector<GLchar> log(logSize); 
		glGetShaderInfoLog(shader, logSize, nullptr, log.data()); 
		throw std::runtime_error(" shader compilation failed" + std::string(log.begin(), log.end())); 
		//printf("[SHADER COMPILE ERROR]: %s ", buf);
		//delete[] buf;
	}
	

	// create program object  
	glAttachShader(this->program, shader);
	glDeleteShader(shader); 
	//glLinkProgram(this->program);

	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &compileStatues);

	if (compileStatues > 0)
	{
		GLchar* buf = new GLchar[compileStatues];
		glGetProgramInfoLog(this->program, compileStatues, NULL, buf);
		printf("[PROGRAM LINK ERROR]: %s ", buf);
		delete[] buf;
	}
	LinkProgram();
	glDeleteShader(shader);

}

void ShaderResource::LinkProgram()
{
	glLinkProgram(this->program); 

	// check linking error
	GLint linkStatus; 
	glGetProgramiv(this->program, GL_LINK_STATUS, &linkStatus);

	if(linkStatus != GL_TRUE)
	{
		GLint logLength; 
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &logLength);
		
		std::vector<GLchar> log(logLength); 
		glGetProgramInfoLog(this->program, logLength, nullptr, log.data());
		throw runtime_error("Program linking failed." + std::string(log.begin(), log.end())); 
	}

	glValidateProgram(this->program);

	// check linking error
	GLint validateStatus;
	glGetProgramiv(this->program, GL_VALIDATE_STATUS, &validateStatus);

	if (validateStatus != GL_TRUE)
	{
		GLint logLength;
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> log(logLength);
		glGetProgramInfoLog(this->program, logLength, nullptr, log.data());
		throw runtime_error("Program linking failed." + std::string(log.begin(), log.end()));
	}


}


	// connect the shader program for use in rendering. 
	// or active the shader program for use in rendering. 
	// OBS this function (Use() = Active) should call before any object render. 
	void ShaderResource::UseProgram()
	{
		if (this->program != 0)
		{
			glUseProgram(this->program);
		}
		else 
		{


			assert(false && " Shader Program is not Exist "); 
		}
		
	}

	// get location of a uniform variable takes a parameter. 
	GLint ShaderResource::getUniformLocation(const string& name)
	{
		GLint location = findInHashTable(name); 
		// sheck cach first
		if (location!= -1)
		{
			return location; 

		}

		// if not get the location store in in cache
		location = glGetUniformLocation(this->program, name.c_str()); 
		if (location == -1) 
		{
			cout << "UNIFORM ERROR: could not find Uniform " << name << endl; 

		}
		else 
		{
			insertIntoHashTable(name, location); 
		}
		
		//return the location. 
		return location;
	}

	

	// use a 4x4 matrix uniform in the shader.
	void ShaderResource::SetUniformMatrix4fv(const string& name, const mat4& matrix )
	{
		GLint location = getUniformLocation(name);
		// set the uniform 
		if (location != -1) 
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&matrix);

		}
		
	}

	//use 4D vector uniform in the shader. 
	void ShaderResource::SetUniformVector4fv(const string& name, const	vec4& vector)
	{
		GLint location = getUniformLocation(name);
		// set the uniform 
		if (location != -1)
		{
			glUniform4fv(location, 1, (GLfloat*)&vector);

		}

	}

	// get the uniform location for the given name for all get and set the uniform with right value, the same with boolfunction 
	void ShaderResource::setUniform1f(const string& name, float value)
	{
		GLint location = getUniformLocation(name);
		// set the uniform 
		if (location != -1)
		{
			glUniform1f(location, value);

		}

	}

	void ShaderResource::setUniform1I(const string& name, float value)
	{
		GLint location = getUniformLocation(name);
		// set the uniform 
		if (location != -1)
		{
			glUniform1i(location, value);

		}

	}

	void ShaderResource::setUniform3fv(const string& name, const vec3& vector)
	{
		GLint location = getUniformLocation(name);
		// set the uniform 
		if (location != -1)
		{
			glUniform3fv(location, 1, (GLfloat*)&vector);

		}

	}
	 // 
	void ShaderResource::setBool(const string& name, int statement)
	{
		GLint location = getUniformLocation(name);
		// set the uniform 
		if (location != -1)
		{
			glUniform1i(location, statement);

		}

	}

	// Initilize a hash table to ziro and itrate through each char of the str. 
	unsigned long ShaderResource::hashFunction(const string& str)
	{
		unsigned long hash = 0; 
		for (char c : str) 
		{
			hash = hash * 31 + c;// accumulate hash value using a multiplier. 
		}
		return hash % CAPACITY; // return a hash value modulate by table campacity. 
	}

	// calculate the hash index for the given uniform name then create a new item to store the uniforme name and location. 
	void ShaderResource::insertIntoHashTable(const string& name, GLint location)
	{
		unsigned long index = hashFunction(name); 
		// create hash item 
		HashItem* newItem = new HashItem(); 
		newItem->key = name; 
		newItem->value = location; 
		newItem->next = nullptr; 

		if (!uniformHashTable[index]) 
		{
			uniformHashTable[index] = newItem; 
		}
		else 
		{
			HashItem* current = uniformHashTable[index]; 
			while (current->next) 
			{
				current = current->next; 
			}
			current->next = newItem; 
		}
	}

	GLint ShaderResource::findInHashTable(const string& name)
	{
		unsigned long index = hashFunction(name); 
		HashItem* current = uniformHashTable[index]; 
		while (current)
		{
			if(current->key == name)
			{
				return current->value; 
			}
			current = current->next; 
		}
		// 
		return -1; 
	}


	

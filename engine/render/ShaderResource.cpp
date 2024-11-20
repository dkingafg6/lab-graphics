
#pragma once
#include <config.h>
#include "ShaderResource.h"

using namespace std;



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
	ifstream shaderFile(FilePath);
	if (shaderFile)
	{
		// convert shader file to string for read. 
		shaderString.assign(istreambuf_iterator<char>(shaderFile), istreambuf_iterator<char>());
	}
	else
	{
		printf(" Error file couldent't open ");
	}
	shaderFile.close();

	// create shader object  and  Error log
	GLint shader = glCreateShader(TYPENAME);
	const GLchar* shaderChar = shaderString.c_str();
	GLint length = static_cast<GLint>(strlen(shaderChar));
	glShaderSource(shader, 1, &shaderChar, &length);
	glCompileShader(shader);

	GLint shaderLogSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(shader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s ", buf);
		delete[] buf;
	}


	// create program object  
	glAttachShader(this->program, shader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);

	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		printf("[PROGRAM LINK ERROR]: %s ", buf);
		delete[] buf;
	}
	glDeleteShader(shader);

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


	


//
//
//
//
//	void ShaderResource::SetUniformVector4fv(const char* name, const GLfloat * value)
//	{
//		GLint location = getUniformLocation(name);
//		// set the uniform 
//		glUniform4fv(location, 1, value);
//	}
//
//	// load shader source from file. 
//	string ShaderResource::loadShaderSource(const char* filePath)
//	{
//		return get_file_contents(filePath);
//	}
//
//	// get location of a uniform variable takes a parameter. 
//	GLint ShaderResource::getUniformLocation(const char* name)
//	{
//		// sheck cach first
//		if (uniformLocationas.find(name) != uniformLocationas.end())
//		{
//			return uniformLocationas[name];
//
//		}
//
//		// if not get the location store in in cache
//		GLint location = glGetUniformLocation(programID, name);
//		if (location == -1)
//		{
//			cerr << "[uniform location error]: uniform '" << name << "' not found " << endl;
//		}
//
//		// cach location 
//		uniformLocationas[name] = location;
//
//		//return the location. 
//		return location;
//	}
//
//
//
//
//
//
//
//
//	// store statuse of compilation 
//	GLint shader = glCreateShader(shaderType);
//
//	// shader source code. 
//	glShaderSource(shader, 1, &shadersource, nullptr);
//
//	// compile shader. 
//	glCompileShader(shader);
//
//	// check for shader's compile error
//	GLint success;
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//
//	if (success == GL_FALSE)
//	{
//		GLint LogSize;
//
//		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &LogSize);
//
//		vector<char> errolog(LogSize);
//
//		glGetShaderInfoLog(shader, LogSize, nullptr, errolog.data());
//		cerr << "[SHADER COMPILE ERROR]:" << errolog.data() << endl;
//
//		// cleanup 
//		glDeleteShader(shader);
//		throw runtime_error("shader compilation failed:");
//	}
//
//	return shader;
//}
//
//// convert file to string  after reading the file. 
//string get_file_contents(const char* filename)
//{
//	return string();
//}
//
//
//// what should have inside loadfromFile
////.Either use an argument per shader type(vertex + fragment) or load them separately.
////.After loading the file, compile and link the shader and write any errors to the console.
////.Use proper error handling.Do not silently fail if there are errors while opening the files or compiling.
//// 1. compile each shader vertex or fragment must be compiled independently using (glCompileShader() ) 
//// 2. link After compilaion 
//void ShaderResource::loadFromFiles(const string& vertexFilePath, GLenum fregmentFilePath)
//{
//	// ckeck if there is program if not create it. 
//	if (this->programID == 0) 
//	{
//		this->programID = glCreateProgram();
//	}
//
//	// load the source code of vertex shader. 
//	string vertexShaderSource = get_file_contents(vertexFilePath.c_str()); 
//	GLint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str()); 
//
//
//	// attach the compiled shader to the program 
//	glAttachShader(this->programID, vertexShader);
//	glAttachShader(this->programID, fragmentShader);
//
//	// link program
//	glLinkProgram(programID); 
//
//	// checking errors for linking. 
//
//	GLint success;
//	// checking shader compilation.
//	glGetShaderiv(programID, GL_COMPILE_STATUS, &success);
//	if (success == GL_FALSE)
//	{
//		GLint LogSize;
//
//		glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &LogSize);
//
//		// print the error log.
//		vector<char> errorLog(LogSize);
//
//		glGetShaderInfoLog(programID, LogSize, nullptr, errorLog.data());
//		cerr << "[SHADER COMPILE ERROR]:" << errorLog.data() << endl;
//
//		// cleanup 
//		glDeleteShader(programID);
//		throw runtime_error("shader compiling failed:");
//
//	}
//
//	// cleanup individual shaders after linking 
//	glDeleteShader(vertexShader); 
//	glDeleteShader(fragmentShader);
//
//	
//		// Initialize shaders. 
//		GLint success;
//
//		// setup vertex shader
//		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
//		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
//		// 
//		GLint length = static_cast<GLint>(std::strlen(vs));
//		glShaderSource(this->vertexShader, 1, &vs, &length);
//		glCompileShader(this->vertexShader);
//		// check compilation for vertex shader. 
//		
//		
//		 //get error log
//		// checking shader compilation.
//		glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
//		if (success ==	GL_FALSE)
//		{
//			GLint shaderLogSize;
//			//GLchar* buf = new GLchar[shaderLogSize];
//			glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
//			if (shaderLogSize > 0) 
//			{
//				GLchar* buf = new GLchar[shaderLogSize];
//				glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
//				printf("[SHADER COMPILE ERROR]: %s \n", buf);
//				delete[] buf;
//
//			}
//			return false; 
//			
//		}
//
//		// setup pixel shader
//		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
//		length = static_cast<GLint>(std::strlen(ps));
//		glShaderSource(this->pixelShader, 1, &ps, &length);
//		glCompileShader(this->pixelShader);  
//		// check compilation for vertex shader. 
//		glGetShaderiv(this->pixelShader, GL_COMPILE_STATUS, &success);
//		if (success == GL_FALSE)
//		{
//			GLint shaderLogSize;
//			//GLchar* buf = new GLchar[shaderLogSize];
//			glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
//			if (shaderLogSize > 0)
//			{
//				GLchar* buf = new GLchar[shaderLogSize];
//				glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
//				printf("[SHADER COMPILE ERROR]: %s \n", buf);
//				delete[] buf;
//
//			}
//			return false;
//
//		}
//
//		//window->SetKeyPressFunction([this](int key, int scancode, int action, int mods) {
//		//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		//	{
//		//		this->Close();
//		//	}
//
//		//}
//		// 
//		// 
//		// create a shader program object
//		this->program = glCreateProgram();
//		glAttachShader(this->program, this->vertexShader);
//		glAttachShader(this->program, this->pixelShader);
//		glLinkProgram(this->program);
//
//		 
//		//// check compilation for vertex shader. 
//		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
//		if (success == GL_FALSE)
//		{
//			GLint shaderLogSize;
//			//GLchar* buf = new GLchar[shaderLogSize];
//			glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
//			if (shaderLogSize > 0)
//			{
//				GLchar* buf = new GLchar[shaderLogSize];
//				glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
//				printf("[PROGRAM LINK ERROR]: %s \n", buf);
//				delete[] buf;
//
//			}
//			return false;
//
//		// Initialize shaders. 
//		GLint success;
//
//		// setup vertex shader
//		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
//		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
//		// 
//		GLint length = static_cast<GLint>(std::strlen(vs));
//		glShaderSource(this->vertexShader, 1, &vs, &length);
//		glCompileShader(this->vertexShader);
//		// check compilation for vertex shader. 
//		
//		
//		 //get error log
//		// checking shader compilation.
//		glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
//		if (success ==	GL_FALSE)
//		{
//			GLint shaderLogSize;
//			//GLchar* buf = new GLchar[shaderLogSize];
//			glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
//			if (shaderLogSize > 0) 
//			{
//				GLchar* buf = new GLchar[shaderLogSize];
//				glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
//				printf("[SHADER COMPILE ERROR]: %s \n", buf);
//				delete[] buf;
//
//			}
//			return false; 
//			
//		}
//
//		// setup pixel shader
//		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
//		length = static_cast<GLint>(std::strlen(ps));
//		glShaderSource(this->pixelShader, 1, &ps, &length);
//		glCompileShader(this->pixelShader);  
//		// check compilation for vertex shader. 
//		glGetShaderiv(this->pixelShader, GL_COMPILE_STATUS, &success);
//		if (success == GL_FALSE)
//		{
//			GLint shaderLogSize;
//			//GLchar* buf = new GLchar[shaderLogSize];
//			glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
//			if (shaderLogSize > 0)
//			{
//				GLchar* buf = new GLchar[shaderLogSize];
//				glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
//				printf("[SHADER COMPILE ERROR]: %s \n", buf);
//				delete[] buf;
//
//			}
//			return false;
//
//		}
//
//		//window->SetKeyPressFunction([this](int key, int scancode, int action, int mods) {
//		//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		//	{
//		//		this->Close();
//		//	}
//
//		//}
//		// 
//		// 
//		// create a shader program object
//		this->program = glCreateProgram();
//		glAttachShader(this->program, this->vertexShader);
//		glAttachShader(this->program, this->pixelShader);
//		glLinkProgram(this->program);
//
//		 
//		//// check compilation for vertex shader. 
//		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
//		if (success == GL_FALSE)
//		{
//			GLint shaderLogSize;
//			//GLchar* buf = new GLchar[shaderLogSize];
//			glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
//			if (shaderLogSize > 0)
//			{
//				GLchar* buf = new GLchar[shaderLogSize];
//				glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
//				printf("[PROGRAM LINK ERROR]: %s \n", buf);
//				delete[] buf;
//
//			}
//			return false;
//
//
//
//}
//
//
//// connect the shader program for use in rendering. 
//// or active the shader program for use in rendering. 
//// OBS this function (Use() = Active) should call before any object render. 
//void ShaderResource::UseProgram()
//{
//	glUseProgram(programID); 
//}
//
//// use a 4x4 matrix uniform in the shader.
//void ShaderResource::SetUniformMatrix4fv(const char* name, const GLfloat* value)
//{
//	GLint location = getUniformLocation(name); 
//	// set the uniform 
//	glUniformMatrix4fv(location, 1, GL_FALSE, value); 
//}
//
////use 4D vector uniform in the shader. 
//void ShaderResource::SetUniformVector4fv(const char* name, const GLfloat* value)
//{
//	GLint location = getUniformLocation(name);
//	// set the uniform 
//	glUniform4fv(location, 1, value);
//}
//
//// load shader source from file. 
//string ShaderResource::loadShaderSource(const char*  filePath)
//{
//	return get_file_contents(filePath);
//}
//
//// get location of a uniform variable takes a parameter. 
//GLint ShaderResource::getUniformLocation(const char* name)
//{
//	// sheck cach first
//	if(uniformLocationas.find(name) != uniformLocationas.end()) 
//	{
//		return uniformLocationas[name]; 
//
//	}
//
//	// if not get the location store in in cache
//	GLint location = glGetUniformLocation(programID, name); 
//	if (location == -1) 
//	{
//		cerr << "[uniform location error]: uniform '" << name << "' not found " << endl;
//	}
//
//	// cach location 
//	uniformLocationas[name] = location; 
//
//	//return the location. 
//	return location; 
//}

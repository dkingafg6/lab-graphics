//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "MeshResource.h"
#include "core/mat4.h"

// vertex shader vs
const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"

"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"uniform mat4 rotation;\n"

"void main()\n"
"{\n"
"	gl_Position = vec4(pos, 1) * rotation;\n"
"	Color = color;\n"
"}\n";

// Fragment Shader. 
const GLchar* ps =
"#version 430\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"}\n";


using namespace Display;
namespace Example
{

//------------------------------------------------------------------------------
/**
*/
	ExampleApp::ExampleApp()
	
	{
		// empty
	}

//------------------------------------------------------------------------------
/**
*/
	ExampleApp::~ExampleApp()
	{
		// empty
	}

//------------------------------------------------------------------------------
/**
*/
	bool ExampleApp::Open()
	{
		App::Open();
		this->window = new Display::Window;
		/*window->SetKeyPressFunction([this](int32, int32, int32, int32)
		{
			this->window->Close();
		});*/

		//GLfloat buf[] =
		//{
		//	-0.5f,	-0.5f,	-1,			// pos 0
		//	1,		0,		0,		1,	// color 0
		//	0,		0.5f,	-1,			// pos 1
		//	0,		1,		0,		1,	// color 0 
		//	0.5f,	-0.5f,	-1,			// pos 2
		//	0,		0,		1,		1	// color 0
		//};

		if (this->window->Open())
		{
			// ...inial   the MeshResource object, 
			// set clear color to gray
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// setup vertex shader
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLint length = static_cast<GLint>(std::strlen(vs));
			glShaderSource(vertexShader, 1, &vs, &length);
			glCompileShader(vertexShader);

			// get error log
			GLint shaderLogSize;
			glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}

			// setup pixel shader
			pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
			length = static_cast<GLint>(std::strlen(ps));
			glShaderSource(pixelShader, 1, &ps, &length);
			glCompileShader(pixelShader);

			// get error log
			shaderLogSize;
			glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}

			// create a program object link
			program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, pixelShader);
			glLinkProgram(program);



			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
				printf("[PROGRAM LINK ERROR]: %s", buf);
				delete[] buf;
			}

			// setup vbo
			/*glGenBuffers(1, &this->triangle);
			glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			*/
			return true;

		}
		return false;
	}


//------------------------------------------------------------------------------
/**
*/
	void ExampleApp::Close()
	{
		//if(this->meshResource != nullptr)
		//{
		//		this->meshResource->cleanup(); 
		//		delete this->meshResource; 
		//		// cleanup 
		//		this->meshResource = nullptr; 

		//}

		//if (this->window->IsOpen()) 
		//{
		//	this->window->Close();
		//}
		
		Core::App::Close();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void ExampleApp::Run()
	{
		glEnable(GL_DEPTH_TEST);
		meshResource = MeshResource::CreatCube(1.0f, 1.0f, 1.0f);

		GLint rotation = glGetUniformLocation(this->program, "rotation");

		float time = 0;
		while (this->window->IsOpen())
		{
			time += 0.002;

			mat4 matrix4x4;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();



			meshResource->bindVBO();
			meshResource->bindIBO();



			// use the the shader for rendering. 
			glUseProgram(this->program);

			matrix4x4 = rotationz(time) * rotationx(time);

			//	// attributes 
			

			glUniformMatrix4fv(rotation, 1, GL_TRUE, (GLfloat*)&matrix4x4);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			//swap buffers to display the rendered frame. 
			this->window->SwapBuffers();

#ifdef CI_TEST
			// if we're running CI, we want to return and exit the application after one frame
			// break the loop and hopefully exit gracefully
			break;
		}
#endif

		}
	}

};


 // namespace Example
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
#include "render/MeshResource.h"
#include "core/mat4.h"
#include "render/Camera.h"
#include "render/Window.h"
#include "render/Grid.h"
#include "../../../exts/glfw/src/win32_platform.h"




// vertex shader vs
const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"

"layout(location=1) in vec4 color;\n"
"uniform mat4 rotation;\n"
"uniform mat4 camMatrix;\n" // for activat the camera 
"out vec4 Color;\n"

"void main()\n"
"{\n"
//"	gl_Position = vec4(pos, 1) * rotation;\n"
"	gl_Position = vec4(pos, 1) * rotation * camMatrix;\n" // just for camera. combine rotation and camera.
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

		if(!App::Open()) return false;
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32, int32, int32, int32)
			{
				this->window->Close();
			});
		// hello
		//GLfloat buf[] =
		//{
		//	-0.5f,	-0.5f,	-1,			// pos 0
		//	1,		0,		0,		1,	// color 0
		//	0,		0.5f,	-1,			// pos 1
		//	0,		1,		0,		1,	// color 0
		//	0.5f,	-0.5f,	-1,			// pos 2
		//	0,		0,		1,		1	// color 0
		//};

		if (!this->window->Open())
		{
			return false; // to be sure window opened successfully. 
		}

		// camera initialize 
		this->camera = Camera(vec3(0.0f, 0.0f, 3.0f),// position 
			vec3(0.0f, 0.0f, 0.0f),            // target position 

			vec3(0.0f, 1.0f, 3.0f),            // up vector 
			45.0f,                             // field of v
			static_cast<float>(width) / static_cast<float>(height),
			0.1f,           // near plan and far clipping 
			100.0f);
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLint length = static_cast<GLint>(std::strlen(vs));
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);

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
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = static_cast<GLint>(std::strlen(ps));
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);

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

		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		GLfloat buf[] =
		{
			-0.5f, -0.5f, -1, 1, 0, 0, 1, // vertex 0
			0,      0.5f, -1, 0, 1, 0, 1, // vertex 1
			0.5f, -0.5f, -1, 0, 0, 1, 1, // vertex 0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// initialize the grid 
		grid = Render::Grid();
		return true;

	}
	void ExampleApp::Close()
	{
		//if (this->window->IsOpen())
			//this->window->Close();

		if(this->window != nullptr)
		{
				this->window->Close(); 
				delete this->window; 
				// cleanup 
				this->window = nullptr; 

		}

		if (this->vertexShader != 0)
		{
			glDeleteShader(this->vertexShader); 
			this->vertexShader = 0; 
		}

		if (this->pixelShader != 0)
		{
			glDeleteShader(this->pixelShader);
			this->pixelShader = 0;
		}

		if (this->program != 0)
		{
			glDeleteProgram(this->program);
			this->program = 0;
		}

		
		Core::App::Close();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		ExampleApp::Run()
	{
		glEnable(GL_DEPTH_TEST); 
		meshResource = MeshResource::CreatCube(1.0f, 1.0f, 1.0f);


		// get the location in the shader. 
		GLint camMatrixLoc = glGetUniformLocation(this->program, "camMatrix");

		// get location form shader program 
		GLint rotation = glGetUniformLocation(this->program, "rotation");

		float time = 0; 

		while (this->window->IsOpen())
		{


			time += 0.009f; // increment time on eahc iteration. 

			// define a 4x4 matrix used for transformation some scaling and ratation.
			//mat4 matrix4x4; 
			mat4 matrix4x4 = rotationz(time) * rotationx(time); // rotation matrix


			// clear depth buffer and color buffer be ready for new frame. 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// get ned dimenstions 


			// update the window 
			this->window->Update();


			// binding vertex and index buffer object of the meshresource  be ready vertex and index data to be used in rendering. 
			meshResource->bindVBO();
			meshResource->bindIBO();

			glUseProgram(this->program); // it use shader program. 

			// porojectin and view matrix combined from the camera. 
			mat4 projectionMatrix = camera.getProjectionMatrix();
			mat4 viewMatrix = camera.getViewMatrix();
			mat4 viewProjectionMatrix = projectionMatrix * viewMatrix; // combined matrix

			//	// attributes 
			glUniformMatrix4fv(camMatrixLoc, 1, GL_TRUE, (GLfloat*)&viewProjectionMatrix);
			glUniformMatrix4fv(rotation, 1, GL_TRUE, (GLfloat*)&matrix4x4);


			// draw a 3D grid and mesh
			grid.Draw((GLfloat*)&viewProjectionMatrix); // call the grid's draw function with combined matrix 

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);// draw the cube.
			glBindBuffer(GL_ARRAY_BUFFER, 0); // UNbind vbo
			this->window->SwapBuffers(); // swap buffers. 


			// binding vertex and index buffer object of the meshresource  be ready vertex and index data to be used in rendering. 
			//meshResource->bindVBO();
			//meshResource->bindIBO();

			//glUniformMatrix4fv(rotation, 1, GL_TRUE, (GLfloat*)&matrix4x4);


			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);












			// use for depth testl to show rander 3D in obj in front of or behind  each other. 
			//glEnable(GL_DEPTH_TEST);
			// create a cube mesh resource with dimensions. 
			/*meshResource = MeshResource::CreatCube(1.0f, 1.0f, 1.0f);

			int width = 800;
			int height = 600; */


			// get the location in the shader. 
			//GLint camMatrixLoc = glGetUniformLocation(this->program, "camMatrix");

			// get location form shader program 
			//GLint rotation = glGetUniformLocation(this->program, "rotation");

			// camera object 
			/*Camera camera(vec3(0.0f, 0.0f, .0f),
				vec3(0.0f, 0.0f, 0.0f),
				vec3(0.0f, 0.0f, 0.0f),
				45.0f, (float)width / (float)height, 0.1f, 100.0f);*/

			

#ifdef CI_TEST
			// if we're running CI, we want to return and exit the application after one frame
			// break the loop and hopefully exit gracefully
			break;
#endif
		}
	}

} // namespace Example

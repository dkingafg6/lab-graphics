//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "exampleapp.h"
#include <cstring>
#include "render/MeshResource.h"
#include "core/mat4.h"
#include "render/Camera.h"
#include "render/window.h"




// vertex shader vs
const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=2) in vec2 texCoord;\n"

"uniform mat4 rotation;\n"
"uniform mat4 camMatrix;\n" // for activate the camera 

"out vec4 Color;\n"
"out vec2 TexCoord;\n"


"void main()\n"
"{\n"
"	gl_Position = vec4(pos, 1) * rotation * camMatrix;\n" // just for camera. combine rotation and camera.
"	Color = color;\n"
"	TexCoord = texCoord;\n"
"}\n";

// Fragment Shader. 
const GLchar* ps =
"#version 430\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D texture1;\n"

"out vec4 FragColor;\n"
//"out vec4 Color;\n"
"void main()\n"
"{\n"
"	FragColor = texture(texture1, TexCoord) * color;\n"
//"	Color = color;\n"
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
		//test.loadFromFile(); 
		if(!App::Open()) return false;

		this->window = new Display::Window;
		if (!this->window->Open()) return false; 

		

		// load texture


		// camera initialize 
		this->camera = Camera(vec3(0.0f, 0.0f, 3.0f),// position 
			vec3(0.0f, 0.0f, 0.0f),            // target position 

			vec3(0.0f, 1.0f, 0.0f),            // up vector 
			45.0f,                             // field of v
			static_cast<float>(width) / static_cast<float>(height),
			0.1f,           // near plan and far clipping 
			100.0f);

		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


		//set up shaders. 
		GLint success;

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		// 
		GLint length = static_cast<GLint>(std::strlen(vs));
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);
		// check compilation for vertex shader. 
		
		// change with new ErrorLog if it's not work can undo it
		 //get error log
		
		glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
		if (success ==	GL_FALSE)
		{
			GLint shaderLogSize;
			//GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0) 
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s \n", buf);
				delete[] buf;

			}
			return false; 
			
		}

		// setup pixel shader
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = static_cast<GLint>(std::strlen(ps));
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);  
		// check compilation for vertex shader. 
		glGetShaderiv(this->pixelShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint shaderLogSize;
			//GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s \n", buf);
				delete[] buf;

			}
			return false;

		}
		
		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);

		 
		//// check compilation for vertex shader. 
		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint shaderLogSize;
			//GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->program, shaderLogSize, NULL, buf);
				printf("[PROGRAM LINK ERROR]: %s \n", buf);
				delete[] buf;

			}
			return false;

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

		/// load file pics 
		if (!texture.loadFromFile("../engine/texture/lizard.png"))
		{
			std::cerr << "Failed to load texture " << std::endl; 
			return false; 

		}
	
		//grid = Render::Grid();
		return true;

	}
	void ExampleApp::Close()
	{
		

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
		// cleanup mesh resource
		//delete meshResource; 

		
		Core::App::Close();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
	ExampleApp::Run()
	{
		glEnable(GL_DEPTH_TEST);

		// create a cube 
		//MeshResource* meshResource = new MeshResource();
		MeshResource* meshResource = MeshResource::CreateCube(1.0f, 1.0f, 1.0f);
		//load texture
		texture.loadFromFile("../engine/texture/lizard.png");
		// bind texture
		texture.Bind(); 

		
		
		
		// get the location of texture uniform. 
		GLint textureLoc = glGetUniformLocation(this->program, "texture1");


		// bind texture to uniform 
		//glUniform1i(textureLoc, 0);


		// get the location in the shader. 
		GLint camMatrixLoc = glGetUniformLocation(this->program, "camMatrix");

		// get location form shader program 
		GLint rotationLoc = glGetUniformLocation(this->program, "rotation");

		if (textureLoc == -1 || camMatrixLoc == -1 || rotationLoc == -1) 
		{
			std::cerr << "Failed to retrive uniform location " << std::endl;
			return; 

		}

		float time = 0; 

		while (this->window->IsOpen())
		{


			time += 0.009f; // increment time on iteration. 

			// define a 4x4 matrix used for transformation some scaling and rotation.
			//mat4 matrix4x4; 
			mat4 matrix4x4 = rotationz(time) * rotationx(time); // rotation matrix


			// clear depth buffer and color buffer be ready for new frame. 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// get ned dimenstions 


			// update the window 
			this->window->Update();


			// binding vertex and index buffer object of the mesh resource  be ready vertex and index data to be used in rendering. 
			meshResource->BindVBO();
			meshResource->BindIBO();

			glUseProgram(this->program); // it use shader program. 

			// comute view projection matrix. 
			mat4 viewProjectionMatrix = camera.getProjectionMatrix() * camera.getViewMatrix(); // combined matrix


			// projection and view matrix combined from the camera. 
			mat4 projectionMatrix = camera.getProjectionMatrix();
			mat4 viewMatrix = camera.getViewMatrix();
			

			//	// attributes 
			glUniformMatrix4fv(camMatrixLoc, 1, GL_TRUE, (GLfloat*)&viewProjectionMatrix);
			glUniformMatrix4fv(rotationLoc, 1, GL_TRUE, (GLfloat*)&matrix4x4);

			// bind texture to uniform 
			glUniform1i(textureLoc, 0); 


			// draw a 3D grid and mesh
			//grid.Draw((GLfloat*)&viewProjectionMatrix); // call the grid's draw function with combined matrix 

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);// render and draw the cube.
			glBindBuffer(GL_ARRAY_BUFFER, 0); // UNbind vbo

			// render the grid to draw 
			//grid.Draw((float*)&viewProjectionMatrix);  
			this->window->SwapBuffers(); // swap buffers. 


		
#ifdef CI_TEST
			// if we're running CI, we want to return and exit the application after one frame
			// break the loop and hopefully exit gracefully
			break;
#endif
		}
	}

} // namespace Example

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
#include "render/grid.h"





// vertex shader vs
const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=2) in vec2 texCoord;\n"

"uniform mat4 rotation;\n"
"uniform mat4 camMatrix;\n" // for activate the camera 

//"out vec4 projection;\n"
"out vec4 Color;\n"
"out vec2 TexCoord;\n"


"void main()\n"
"{\n"
"	gl_Position = camMatrix * rotation * vec4(pos, 1);\n" // just for camera. combine rotation and camera.
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
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	FragColor = texture(texture1, TexCoord);\n"
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
		window->SetMousePressFunction([this](int32 button, int32 action, int32 mods)
			{
				if (button == GLFW_MOUSE_BUTTON_LEFT)
				{
					this->mouseLeftPressed = (action == GLFW_PRESS);
				}
				else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				{
					this->mouseRightPressed = (action == GLFW_PRESS);
				}
				
			});

		
		

		

		// load texture


		// camera initialize 
		this->camera = Camera(
			vec3(0.0f, 0.0f, 3.0f),// position 
			vec3(0.0f, 0.0f, 0.0f),            // target position 
			vec3(0.0f, 1.0f, 0.0f),            // up vector 
			45.0f,                             // field of v
			static_cast<float>(width) / static_cast<float>(height),
			// near plan and far clipping 
			0.1f,           
			100.0f);       

		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		//// Enable debugs output
		//glEnable(GL_DEBUG_OUTPUT); 
		//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		//// Register the callback function for
		//glDebugMessageCallback(MessageCallback, nullptr); 

		// optionally filter out 
		//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 9, nullptr, GL_FALSE); 
	


		// Initialize shaders. 
		GLint success;

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		// 
		GLint length = static_cast<GLint>(std::strlen(vs));
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);
		// check compilation for vertex shader. 
		
		
		 //get error log
		// checking shader compilation.
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

		//window->SetKeyPressFunction([this](int key, int scancode, int action, int mods) {
		//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		//	{
		//		this->Close();
		//	}

		//}
		// 
		// 
		// create a shader program object
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
			glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
				printf("[PROGRAM LINK ERROR]: %s \n", buf);
				delete[] buf;

			}
			return false;

		}
		
		// setup vbo (initialize) 

		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		GLfloat buf[] =
		{
			-0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // vertex 0
			0,      0.5f, -1, 0, 1, 0, 1, // vertex 1
			0.5f, -0.5f, -1, 0, 0, 1, 1, // vertex 0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//initialize th grid
		/*if (!grid.Init()) 
		{
			std::cerr << "Failed to initialize the grid from grid class" << std::endl;
			return false;

		}
		return true; */


		// active for taking the information from the window class here right for movement the cameras with mouse and keys. 
		window->SetKeyPressFunction([this](int key, int scancode, int action, int mods)
			{
				//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				//{
				//	this->Close();
				//}

			});

		
	
		//;
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

	/*void GLAPIENTRY ExampleApp::MessageCallback(GLenum, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		
		printf("GL CALLBACK: %s Type: 0x%x, Severity: 0x%x, ID:  %d, Message: %s\n", (type == GL_DEBUG_TYPE_ERROR ? "* GL ERROR *" : ""), type, severity, id, message);
		
	}*/

	//------------------------------------------------------------------------------
	/**
	*/
	void ExampleApp::Run()
	{
		glEnable(GL_DEPTH_TEST);

		// the camera's pussibily during setup 
		Render::Grid grid;
	
		// create a cube 
		//MeshResource* meshResource = new MeshResource();
		MeshResource* meshResource = MeshResource::CreateCube(1.0f, 1.0f, 1.0f);

		//load texture
		texture.loadFromFile("../engine/texture/lizard1.png");
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
			printf("Failed to retrieve uniform location \n");
			return; 

		}

		float time = 0; 

		//initialize mouse callback for camera. 
		GLFWwindow* glfwwindow = this->window->GetGLFWwindow(); 
		

		while (this->window->IsOpen())
		{


			time += 0.009f; // increment time on iteration. 


			// clear depth buffer and color buffer be ready for new frame. 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// update the window 
			this->window->Update();

			// handle the camera movement. 
			camera.processInput(this->window->GetGLFWwindow()); 

			// compute view projection matrix. 
			mat4 viewProjectionMatrix = camera.getProjectionMatrix(); // combined matrix

			// define a 4x4 matrix used for transformation some scaling and rotation.
			//mat4 matrix4x4; 
			mat4 matrix4x4 = mat4::rotationz(time) * mat4::rotationx(time); // rotation matrix

			
			// binding vertex and index buffer object of the mesh resource  be ready vertex and index data to be used in rendering. 
			

			glUseProgram(this->program); // it use shader program. 


			//	// attributes 
			glUniformMatrix4fv(camMatrixLoc, 1, GL_FALSE, (GLfloat*)&viewProjectionMatrix);
			glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, (GLfloat*)&matrix4x4);

			// bind texture to uniform 
			glUniform1i(textureLoc, 0); 


			// draw a 3D grid and mesh
			//grid.Draw((GLfloat*)&viewProjectionMatrix); // call the grid's draw function with combined matrix 
			meshResource->BindVBO();
			meshResource->BindIBO();// update the camera based on mouse mouvement. 
		
			double xpos;
			double ypos;

			if (this->mouseRightPressed)
			{
				glfwGetCursorPos(glfwwindow, &xpos, &ypos);

				camera.mouse_callback(xpos, ypos);
			}
			

	

			// render the grid to draw 
			grid.Draw((GLfloat*)&viewProjectionMatrix);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);// render and draw the cube.
			glBindBuffer(GL_ARRAY_BUFFER, 0); // UNbind vbo
			  
			this->window->SwapBuffers(); // swap buffers. 


		
#ifdef CI_TEST
			// if we're running CI, we want to return and exit the application after one frame
			// break the loop and hopefully exit gracefully
			break;
#endif
		}
		delete meshResource;
	}

} // namespace Example

//
//
//
//window->SetKeyPressFunction([this](int key, int scancode, int action, int mods) {
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		this->Close();
//	}
//
//	}
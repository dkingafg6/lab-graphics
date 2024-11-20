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








//// vertex shader vs
//const GLchar* vs =
//"#version 430\n"
//"layout(location=0) in vec3 pos;\n"
//"layout(location=1) in vec4 color;\n"
//"layout(location=2) in vec2 texCoord;\n"
//
//"uniform mat4 rotation;\n"
//"uniform mat4 camMatrix;\n" // for activate the camera 
//
////"out vec4 projection;\n"
//"out vec4 Color;\n"
//"out vec2 TexCoord;\n"
//
//
//"void main()\n"
//"{\n"
//"	gl_Position = camMatrix * rotation * vec4(pos, 1);\n" // just for camera. combine rotation and camera.
//"	Color = color;\n"
//"	TexCoord = texCoord;\n"
//"}\n";

// Fragment Shader. 
//const GLchar* ps =
//"#version 430\n"
//"in vec4 color;\n"
//"in vec2 TexCoord;\n"
//
//"uniform sampler2D texture1;\n"
//
//"out vec4 FragColor;\n"
//"out vec4 Color;\n"
//"void main()\n"
//"{\n"
//"	FragColor = texture(texture1, TexCoord);\n"
////"	Color = color;\n"
//"}\n";


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

		if (this->window->Open())
		{
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
			return true;
		}

		// camera initialize 
		this->camera = Camera(
			vec3(0.0f, 0.0f, 3.0f),				// position 
			vec3(0.0f, 0.0f, 0.0f),            // target position 
			vec3(0.0f, 1.0f, 0.0f),            // up vector 
			45.0f,                             // field of v
			static_cast<float>(width) / static_cast<float>(height),
			// near plan and far clipping 
			0.1f,           
			100.0f);       

		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	

		return false;
		}

	void ExampleApp::Close()
	{
		if (this->window->IsOpen())
			this->window->Close();

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
		glEnable(GL_DEPTH_TEST); // enable depth testing for 3D rendering. 

		// the camera's pussibily during setup 
		Render::Grid grid;
		
		// create a cube from graphicsNode

		std::shared_ptr<ShaderResource> shaderResource = std::make_shared<ShaderResource>();

		shaderResource->loadShaderResource("../engine/shaders/vertexShader.vert", GL_VERTEX_SHADER);
		shaderResource->loadShaderResource("../engine/shaders/fragmentShader.frag", GL_FRAGMENT_SHADER);

		std::shared_ptr<TextureResource> textureResource = std::make_shared<TextureResource>();
		//load texture
		textureResource->loadFromFile("../engine/texture/lizard2.png");

		std::shared_ptr<MeshResource> meshResource = std::make_shared<MeshResource>();
		meshResource->CreateCube(1.0f, 1.0f, 1.0f);
		// bind texture

		GraphicsNode graphicsNode(meshResource, shaderResource, textureResource);
		
		// get the location of texture uniform. 
		GLint textureLoc = glGetUniformLocation(this->program, "texture1");

		// bind texture to uniform 
		//glUniform1i(textureLoc, 0);

		// get the location in the shader. 
		GLint camMatrixLoc = glGetUniformLocation(this->program, "camMatrix");

		// get location form shader program 
		GLint rotationLoc = glGetUniformLocation(this->program, "rotation");

	


		float time = 0; 

		//initialize mouse callback for camera. 
		GLFWwindow* glfwwindow = this->window->GetGLFWwindow(); 
		

		while (this->window->IsOpen())
		{

			// connect this shader program for use in rendering. 
			// OBS this function (UseProgram()) should call before any object render. 
			// be sour that correct shaders are used. 
			// used in shaderResource or called. 
			glUseProgram(this->program); // avtive the shader program. 


			time += 0.009f; // increment time on iteration. 


			// clear depth buffer and color buffer be ready for new frame. 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// update the window 
			this->window->Update();

			//set texture uniform and the unit is 0 
			glUniform1i(textureLoc, 0); 

			// handle the camera movement. 
			camera.processInput(this->window->GetGLFWwindow()); 

			// compute view projection matrix. 
			mat4 viewProjectionMatrix = camera.getProjectionMatrix(); // combined matrix

			mat4 matrix4x4 = mat4::rotationz(time) * mat4::rotationx(time); // rotation matrix



			//	// attributes set the uniform when shader program avtivate. 
			glUniformMatrix4fv(camMatrixLoc, 1, GL_FALSE, (GLfloat*)&viewProjectionMatrix);
			glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, (GLfloat*)&matrix4x4);

			// bind texture to uniform 
			glUniform1i(textureLoc, 0); 

			GLuint TextureID = graphicsNode.GetTextureResource()->getTextureID();
			// draw a 3D grid and mesh
			//grid.Draw((GLfloat*)&viewProjectionMatrix); // call the grid's draw function with combined matrix 
			graphicsNode.Draw(viewProjectionMatrix,camMatrixLoc, rotationLoc, matrix4x4, textureLoc, TextureID);

			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);// render and draw the cube.
			//glBindVertexArray(0); 
		
			double xpos;
			double ypos;

			if (this->mouseRightPressed)
			{
				glfwGetCursorPos(glfwwindow, &xpos, &ypos);

				camera.mouse_callback(xpos, ypos);
			}
			

	

			// render the grid to draw 
			grid.Draw((GLfloat*)&viewProjectionMatrix);
			//meshResource->Draw(this->program); 
			
			glBindBuffer(GL_ARRAY_BUFFER, 0); // UNbind vbo
			  
			this->window->SwapBuffers(); // swap buffers. 


		
#ifdef CI_TEST
			// if we're running CI, we want to return and exit the application after one frame
			// break the loop and hopefully exit gracefully
			break;
#endif
		}
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
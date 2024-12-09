
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
		window->SetMousePressFunction([this](int32 button, int32 action, int32 mods)
			{
				if (button == GLFW_MOUSE_BUTTON_LEFT)
				{
					this->mouseLeftPressed = (action == GLFW_PRESS);
				}
				if (button == GLFW_MOUSE_BUTTON_RIGHT)
				{
					this->mouseRightPressed = (action == GLFW_PRESS);
				}
				if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				{
					this->mouseMiddlePressed = (action == GLFW_PRESS);
				}
			});
		window->SetMouseMoveFunction([this](float64 z, float64 y)
			{
				if (this->mouseLeftPressed)
				{
					float deltaY = static_cast<float>(y - this->lastMouseY);
					float deltaZ = static_cast<float>(z - this->lastMouseZ);

					this->translationMatrix[3].y -= deltaY * 0.01f;
					this->translationMatrix[3].z -= deltaZ * 0.01f;
				}


				else if (this->mouseMiddlePressed)
				{
					float deltaY = static_cast<float>(y - this->lastMouseY);
					float deltaZ = static_cast<float>(z - this->lastMouseZ);

					this->translationMatrix[2].y -= deltaY * 0.01f;
					this->translationMatrix[2].z -= deltaZ * 0.01f;
				}
				this->lastMouseZ = z;
				this->lastMouseY = y;
			});



		if (this->window->Open())
		{
			// set clear color to gray
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// initi... the light source
			


			return true;
		}
		return false;
	}

	void ExampleApp::Close()
	{
		if (this->window->IsOpen())
			this->window->Close();

		Core::App::Close();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void ExampleApp::Run()
	{
		
		glEnable(GL_DEPTH_TEST); // enable depth testing for 3D rendering. 

		// camera initialize 
		this->cameraObject = Camera(
			vec3(0.0f, 0.0f, 3.0f),				// position 
			vec3(0.0f, 0.0f, 0.0f),            // target position 
			vec3(0.0f, 1.0f, 0.0f),            // up vector 
			45.0f,                             // field of v
			static_cast<float>(width) / static_cast<float>(height),
			// near plan and far clipping 
			0.1f,
			100.0f);

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
		meshResource->LoadOBJFiles("../engine/OBJFiles/cube.obj");

		this->graphicsNode = GraphicsNode(meshResource, shaderResource, textureResource);

		std::shared_ptr<ShaderResource> shaderResource2 = std::make_shared<ShaderResource>();
		shaderResource2->loadShaderResource("../engine/shaders/vertexShader.vert", GL_VERTEX_SHADER);
		shaderResource2->loadShaderResource("../engine/shaders/fragmentShader.frag", GL_FRAGMENT_SHADER);

		std::shared_ptr<TextureResource> textureResource2 = std::make_shared<TextureResource>();
		//load texture
		textureResource2->loadFromFile("../engine/texture/lizard1.png");

		std::shared_ptr<MeshResource> meshResource2 = std::make_shared<MeshResource>();
		meshResource2->LoadOBJFiles("../engine/OBJFiles/cube.obj");

		this->graphicsNode2 = GraphicsNode(meshResource2, shaderResource2, textureResource2);

		mat4 viewMatrix = cameraObject.getViewMatrix();
		mat4 projectionMatrix = cameraObject.getPerspectiveMatrix();

		float time = 0;

		//initialize mouse callback for camera. 
		GLFWwindow* glfwwindow = this->window->GetGLFWwindow();

		this->pointLight.setPointlightPosition(vec3(graphicsNode2.transform[3].x, graphicsNode2.transform[3].y, graphicsNode2.transform[3].z));


		while (this->window->IsOpen())
		{
			// clear depth buffer and color buffer be ready for new frame. 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// update the window 
			this->window->Update();


			time += 0.009f; // increment time on iteration. 

			mat4 translationMat = mat4::translation(this->translationMatrix[3][0], this->translationMatrix[3][1], this->translationMatrix[3][2]);
			mat4 rotationMat = mat4::rotationy(this->translationMatrix[2][1]) * mat4::rotationz(this->translationMatrix[2][2]);
			mat4 automaticRotation = mat4::rotationy(time);
			mat4 ofsetMat;
			ofsetMat.m[3] = vec4(mat4().m[3].x + 2.0f, mat4().m[3].y, mat4().m[3].z, mat4().m[3].w);
			mat4 modelMatrix = translationMat * rotationMat;
			mat4 modelMatrix2 = ofsetMat * automaticRotation;


			// set transformation matrices for shader.
			// render the grid to draw 
			
			mat4 gridMatrix = projectionMatrix * viewMatrix;
			grid.Draw((GLfloat*)&gridMatrix);

			this->graphicsNode.SetTransform(modelMatrix);
			this->graphicsNode2.SetTransform(modelMatrix2);

			this->graphicsNode.Draw(cameraObject, pointLight);
			this->graphicsNode2.Draw(cameraObject, pointLight); 
			
			
			// handle the camera movement. 
			cameraObject.processInput(this->window->GetGLFWwindow());



			GLuint TextureID = graphicsNode.GetTextureResource()->getTextureID();


			double xpos;
			double ypos;

			if (this->mouseRightPressed)
			{
				glfwGetCursorPos(glfwwindow, &xpos, &ypos);

				cameraObject.mouse_callback(xpos, ypos);
			}




			// render the grid to draw 
			//grid.Draw((GLfloat*)&gridMatrix);
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


//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "math.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "render/TextureResource.h"
#include "exampleapp.h"
#include <cstring>
#include "render/Camera.h"
#include "render/MeshResource.h"
#include "core/mat4.h"

// vertex shader vs
const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec2 texCoord;\n"
"out vec2 TexCoor;\n"
//"layout(location=0) out vec2 TexCoord;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(pos, 1.0);;\n"
"	TexCoord = texCoord;\n"
"}\n";

 //Fragment shader ps
const GLchar* ps =
"#version 430\n"
"in vec2 TexCoord;\n"
"out vec4 Color;\n"
//"uniform sampler2D texture; \n"
"uniform sampler2D textureSampler; \n" // texture sampler. 

"void main()\n"
"{\n"
"	Color = texture(textureSampler, TexCoord);\n" // fix the color from the texture.
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
	bool
		ExampleApp::Open()
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
			//this->meshResource = new MeshResource(); 
			// set clear color to gray
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// setup vertex shader
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLint length = static_cast<GLint>(std::strlen(vs));
			glShaderSource(vertexShader, 1, &vs, &length);
			glCompileShader(vertexShader);

			// get error log
			GLint vertexshaderLogSize;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &vertexshaderLogSize);
			if (vertexshaderLogSize > 0)
			{
				GLchar* buf = new GLchar[vertexshaderLogSize];
				glGetShaderInfoLog(vertexShader, vertexshaderLogSize, NULL, buf);
				printf("[VERTEX SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}


			// setup pixel shader
			pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
			length = static_cast<GLint>(std::strlen(ps));
			glShaderSource(pixelShader, 1, &ps, &length);
			glCompileShader(pixelShader);

			// get error log
			//shaderLogSize;
			GLint fragmentShaderLogSize;
			glGetShaderiv(pixelShader, GL_INFO_LOG_LENGTH, &fragmentShaderLogSize);
			if (fragmentShaderLogSize > 0)
			{
				GLchar* buf = new GLchar[fragmentShaderLogSize];
				glGetShaderInfoLog(pixelShader, fragmentShaderLogSize, NULL, buf);
				printf("[FRAGMENT SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}

			// create a program object link
			program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, pixelShader);
			glLinkProgram(program);

			GLint programLogSize;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &programLogSize);
			if (programLogSize > 0)
			{
				GLchar* buf = new GLchar[programLogSize];
				glGetShaderInfoLog(this->program, programLogSize, NULL, buf);
				printf("[PROGRAM ERROR]: %s", buf);
				delete[] buf;
			}


			mesh = MeshResource::CreatCube(1.0f, 1.0f, 1.0f);
			mesh->createVBO();
			mesh->createIBO();

			texture.loadFromFile("path_to_texture.png");

			camera.SetPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
			camera.SetView(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));

			GLuint texLoc = glGetUniformLocation(program, "textureSamler");
			GLuint modelLoc = glGetUniformLocation(program, "model");
			GLuint viewLoc = glGetUniformLocation(program, "view");
			GLuint projLoc = glGetUniformLocation(program, "projection");


			// checking for all uniform location. 
			if (texLoc == -1) {
				printf(" textureSampler uniform no found in shader program. \n");
			}
			if (modelLoc == -1) {
				printf(" model uniform not found in shader program. \n");
			}

			if (viewLoc == -1) {
				printf(" view uniform no found in shader program. \n");
			}
			if (projLoc == -1) {
				printf(" projection uniform no found in shader program. \n");
			}

			return true;

		}
		return false;


	}


	void
		ExampleApp::Close()
	{
		mesh->cleanup();
		texture.Cleanup();

		if (this->window->IsOpen())
		{
			this->window->Close();
		}

		Core::App::Close();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		ExampleApp::Run()
	{
		glUseProgram(program);
		while (this->window->IsOpen())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

			mat4 model = mat4::rotationz(glfwGetTime());  // Rotate the cube over time
			glUniformMatrix4fv(modelLoc, 1, GL_TRUE, (GLfloat*)&model);
			glUniformMatrix4fv(viewLoc, 1, GL_TRUE, (GLfloat*)&camera.viewMatrix);
			glUniformMatrix4fv(projLoc, 1, GL_TRUE, (GLfloat*)&camera.projectionMatrix);

			texture.Bind(0);
			glUniform1i(texLoc, 0);

			mesh->bindVBO();
			mesh->bindIBO();
			mesh->draw();

			this->window->SwapBuffers();




#ifdef CI_TEST
			// if we're running CI, we want to return and exit the application after one frame
			// break the loop and hopefully exit gracefully
			break;

#endif

		}
	}
}
 // namespace Example
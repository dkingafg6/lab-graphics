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
#include "core/vec2.h"

// vertex shader vs
const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n" // attribute for pos
"layout(location=1) in vec2 texCoord;\n" // attribute for texture coordinates
"out vec2 TexCoord;\n" // pass texture to shader. 
//"layout(location=0) out vec2 TexCoord;\n"

"uniform mat4 model;\n" // model 
"uniform mat4 view;\n" // view
"uniform mat4 projection;\n"// projection matrix. 

"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(pos, 1.0);;\n" // calculate pos 
"	TexCoord = texCoord;\n" // pass texture to shader
"}\n";

 //Fragment shader ps
const GLchar* ps =
"#version 430\n"
"in vec2 TexCoord;\n" // texture coordinates from vertex shader. 
"out vec4 Color;\n" // color 
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

			// enable openGl debug output. 
			glEnable(GL_DEBUG_OUTPUT); 
			glDebugMessageCallback(MessageCallback, 0); // register the callback function. 

			// setup vertex shader
			vertexShader = glCreateShader(GL_VERTEX_SHADER); // create  shader object 
			GLint length = static_cast<GLint>(std::strlen(vs)); // source length. 
			glShaderSource(vertexShader, 1, &vs, &length); // set source 
			glCompileShader(vertexShader); // compile shader 

			// check for vertex shader compile errors 
			GLint vertexshaderLogSize;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &vertexshaderLogSize);
			if (vertexshaderLogSize > 0)
			{
				GLchar* buf = new GLchar[vertexshaderLogSize];
				glGetShaderInfoLog(vertexShader, vertexshaderLogSize, NULL, buf);
				printf("[VERTEX SHADER COMPILE ERROR]: %s\n", buf);
				delete[] buf; // 
				return false; // if there is not error ther program exit. 
			}


			// setup Fragment pixel shader
			pixelShader = glCreateShader(GL_FRAGMENT_SHADER); // create ...object. 
			length = static_cast<GLint>(std::strlen(ps)); // get source length
			glShaderSource(pixelShader, 1, &ps, &length); // set source
			glCompileShader(pixelShader); // compile 

			// check for fragment shader compile errors 
			//shaderLogSize;
			GLint fragmentShaderLogSize;
			glGetShaderiv(pixelShader, GL_INFO_LOG_LENGTH, &fragmentShaderLogSize);
			if (fragmentShaderLogSize > 0)
			{
				GLchar* buf = new GLchar[fragmentShaderLogSize];
				glGetShaderInfoLog(pixelShader, fragmentShaderLogSize, NULL, buf);
				printf("[FRAGMENT SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
				return false; // if there is not error ther program exit. 
			}

			// create a program object link shaders
			program = glCreateProgram(); // create object. 
			glAttachShader(program, vertexShader); // attach vertex
			glAttachShader(program, pixelShader); // attach fragment 
			glLinkProgram(program); // linke shader into program 

			// check for program's linking to errors. 
			GLint programLogSize;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &programLogSize);
			if (programLogSize > 0)
			{
				GLchar* buf = new GLchar[programLogSize];
				glGetShaderInfoLog(program, programLogSize, NULL, buf);
				printf("[PROGRAM LINKING ERROR]: %s\n", buf);
				delete[] buf;
				return false; // if there is not error ther program exit. 
			}

			// create cueb mesh and set up its buffers. 
			mesh = MeshResource::CreatCube(1.0f, 1.0f, 1.0f);
			mesh->createVBO();// create vbo 
			mesh->createIBO(); // create ibo 

			// load texture from file that we have it ready. 
			if (!texture.loadFromFile("valid_path_to_texture.png")) 
			{
				// check to see if the looding was successful.
				printf("Failed to load texture from file.\n"); 
				return false; // handeling the error. 
			}

			// set up camera projection and view matrices
			camera.SetPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // set perspective
			camera.SetView(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0)); // set view 

			//get unifor locations from shader program 
			GLuint texLoc = glGetUniformLocation(program, "textureSampler");
			GLuint modelLoc = glGetUniformLocation(program, "model");
			GLuint viewLoc = glGetUniformLocation(program, "view");
			GLuint projLoc = glGetUniformLocation(program, "projection");


			// checking for all uniform location. 
			if (texLoc == -1) {
				printf("Error: textureSampler uniform no found in shader program. \n");
			}
			if (modelLoc == -1) {
				printf("Error: model uniform not found in shader program. \n");
			}

			if (viewLoc == -1) {
				printf("Error: view uniform no found in shader program. \n");
			}
			if (projLoc == -1) {
				printf("Error: projection uniform no found in shader program. \n");
			}

			return true; // return doen when window and resource initialized. 

		}
		return false; // return fail if window cannat be openen. 


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
		//run time checking before using shader program to check if it's in a valid state. 
		if (program == 0) 
		{
			printf("Error: Program object is not valid. \n"); 
			return; // exit when program is invalid. 
		}
		glUseProgram(program); // shader program 
		// rendering loop 
		while (this->window->IsOpen())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// clear the screen. 
			this->window->Update(); // update 

			// Rotate the cube over time
			mat4 model = rotationz(glfwGetTime());  
			glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (GLfloat*)&model);
			glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (GLfloat*)&camera.viewMatrix);
			glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_TRUE, (GLfloat*)&camera.projectionMatrix);

			//bind and set texture uniform 
			texture.Bind(0);
			glUniform1i(glGetUniformLocation(program, "textureSampler"), 0);
			//glUniform1i(texLoc, 0);

			// bind and draw mesh. 
			mesh->bindVBO();
			mesh->bindIBO();
			mesh->draw();

			// swap the buffers and display rendered from that. 
			this->window->SwapBuffers();




#ifdef CI_TEST
			// if we're running CI, we want to return and exit the application after one frame
			// break the loop and hopefully exit gracefully
			break;

#endif

		}
	}
	// massage callback function be called when there is e debug message from opengl. 
	void GLAPIENTRY ExampleApp::MessageCallback(GLenum, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		printf("GL CALLBACK: %s Type: 0x%x, Severity: 0x%x, ID:  %d, Message: %s\n", (type == GL_DEBUG_TYPE_ERROR ? "* GL ERROR *" : ""), type, severity, id, message);
		
	}
}
 // namespace Example
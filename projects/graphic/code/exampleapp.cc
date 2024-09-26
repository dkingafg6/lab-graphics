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

// 
// vertex shader = generate direction (forwards, right, up)
const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"       // attribute for pos
"layout(location=1) in vec2 texCoord;\n"  // attribute for texture coordinates
"layout(location=2) in vec4 color;\n"     // color attribute 

"out vec2 TexCoord;\n"    // pass texture coordinate to the fragment shader. 
"out vec4 vertexColor;\n" // pass color to the fragment shader. 
//"layout(location=0) out vec2 TexCoord;\n"

//"layout(location=1) in vec4 color;\n"
//"layout(location=0) out vec4 Color;\n"

"uniform mat4 model;\n"       // model matrix
"uniform mat4 view;\n"        // view matrix
"uniform mat4 projection;\n"  // projection matrix. 

"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(pos, 1.0);;\n" // calculate pos in world space. 
"	TexCoord = texCoord;\n" // pass texture to shader
"	vertexColor = color;\n" // pass input color to fragment shader. 
"}\n";

 //Fragment shader  = generate color and cub map texture 
const GLchar* ps =
"#version 430\n"
//"layout(location=0) in vec4 color;\n"
//"out vec4 Color;\n"

"in vec2 TexCoord;\n"    // texture coordinates from vertex shader. 
"in vec4 vertexColor;\n" // color from vertex shader. 
"out vec4 Color;\n"      // output color

//"uniform sampler2D texture; \n"
"uniform sampler2D textureSampler; \n" // texture sampler. 

"void main()\n"
"{\n"
"	vec4 textureColor = texture(textureSampler, TexCoord);\n" // sampler the texture 
"	Color = textureColor * vertexColor;\n" // fix the color from the texture.
//"	Color = color;\n" if this line activate it will be overwritint for color 

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
		window->SetKeyPressFunction([this](int32, int32, int32, int32)
		{
		this->window->Close();
		});

		GLfloat buf[] =
		{
			-0.5f,	-0.5f,	-1,			// pos 0
			1,		0,		0,		1,	// color 0
			0,		0.5f,	-1,			// pos 1
			0,		1,		0,		1,	// color 0
			0.5f,	-0.5f,	-1,			// pos 2
			0,		0,		1,		1	// color 0
		};

		if (this->window->Open())
		{
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

			// create cueb mesh and set up its buffers. 
			mesh = MeshResource::CreatCube(1.0f, 1.0f, 1.0f);
			mesh->createVBO();// create vbo 
			mesh->createIBO(); // create ibo 

			texture.loadFromFile("../projects/graphic/texture/lizard.png");
			// load texture from file that we have it ready. 
			if (!texture.loadFromFile("../projects/graphic/texture/lizard.png")) 
			{
				// check to see if the looding was successful.
				printf("Failed to load texture from file.\n"); 
				return false; // handeling the error. 
			}

			// set up camera projection and view matrices
			camera.SetPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // set perspective
			camera.SetView(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0)); // set view 

			//get unifor locations from shader program 
			GLuint texLoc = glGetUniformLocation(this->program, "textureSampler");
			GLuint modelLoc = glGetUniformLocation(this->program, "model");
			GLuint viewLoc = glGetUniformLocation(this->program, "view");
			GLuint projLoc = glGetUniformLocation(this->program, "projection");


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
		if (this->program == 0)
		{
			printf("Error: Program object is not valid. \n"); 
			return; // exit when program is invalid. 
		}
		glUseProgram(this->program); // shader program 
		// rendering loop 
		while (this->window->IsOpen())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// clear the screen. 
			this->window->Update(); // update 


			//// do stuff
			//glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			//glUseProgram(this->program);
			//glEnableVertexAttribArray(0);
			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);
			//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);


			// here: model, view and projection matrix, biding to the texture smpler 
			// Rotate the cube over time
			mat4 model = rotationz(glfwGetTime());  
			glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_TRUE, (GLfloat*)&model);
			glUniformMatrix4fv(glGetUniformLocation(this->program, "view"), 1, GL_TRUE, (GLfloat*)&camera.viewMatrix);
			glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_TRUE, (GLfloat*)&camera.projectionMatrix);
			
			//bind and set texture uniform 
			texture.Bind(0);
			// assigned to the fragment shader.
			glUniform1i(glGetUniformLocation(this->program, "textureSampler"), 0);
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
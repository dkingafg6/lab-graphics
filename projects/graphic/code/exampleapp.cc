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
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

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
void
ExampleApp::Close()
{
	if (this->window->IsOpen())
		this->window->Close();

	Core::App::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{
	MeshResource mesresource;
	float time = 0.0f;
	//get the loacation of the rotation uniform variable in the shader program. 
	GLint rotation = glGetUniformLocation(this->program, "rotation");

	// create vertex buffer object vbo and index buffer object ibo for the mesh. 
	mesresource.createVBO();
	mesresource.createIBO();

	// 
	while (this->window->IsOpen())
	{
		mat4 mat4thingy; // decalre a matrix for transformations 
		time += 0.03f;//increment time for continuous rotation. 
		glClear(GL_COLOR_BUFFER_BIT);// clear the color buffer to propare for the frame. 
		this->window->Update(); // update the window 

		// do stuff
		//glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		//Bind the vbo and ibo for rendering. 
		mesresource.bindVBO();
		mesresource.bindIBO();

		// compute the rotation matrix bease on the elapsed time. 
		mat4thingy = rotationz(time); // roation matrix around the z-axis. 
		/*mat4thingy = rotationx(time);
		mat4thingy = rotationy(time);*/

		
		//mat4 rotationMat = mat4::rotationz(time);
		// compute the translation matrix for left-right movement. 
		//mat4 translationMat = mat4::translation(sinf(time) * 0.5f, 0.0f, 0.0f); 

		// combining transformation matrix to the shader. 
		//mat4 transformMat = translationMat * rotationMat;
		
		// send the rotatio matrix to the shader. 
		glUniformMatrix4fv(rotation, 1, GL_TRUE, (GLfloat*)&mat4thingy);

		// use the the shader for rendering. 
		glUseProgram(this->program);


		glEnableVertexAttribArray(0); // pos
		glEnableVertexAttribArray(1); // color

		// 0 = the position attribute in the vertex shader. 3 = each pos has 3 float(x,y,z) 
		// sizeof(floate 32 * 7 = says to openGL each vertex has total 7 floats. 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);

		// 1 = color atrebute   4 ) each color has 4 floats ( r, g, b, a) 
		// (GLvoid*)(sizeof(float32) * 3 = color data starts afoter the first 3 floats 
		// like x=0, y=1, z=2, r=3, g=4, b=5, a=6, 
		// 7 = shows the total number of float in a single vertex( 3 for position + 4 for color) 

		// 3 floats = (x,y,z) positon 
		// 4 floats = (r,g,b,a) color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//swap buffers to display the renderred frame. 
		this->window->SwapBuffers();

#ifdef CI_TEST
		// if we're running CI, we want to return and exit the application after one frame
		// break the loop and hopefully exit gracefully
		break;
#endif
	}
}

} // namespace Example
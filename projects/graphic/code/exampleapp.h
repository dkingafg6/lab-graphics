#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2022 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include <GL/glew.h>
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "render/MeshResource.h"
#include "core/mat4.h"
#include "render/Camera.h"
#include "render/WindowWrapper.h"
#include "render/grid.h"
#include "core/app.h"
#include "render/window.h"
#include "render/TextureResource.h"
namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();

	// hellp function for checking 
	//void handleShaderError(GLuint shader, GLenum type);


	bool Open(); 
	/// close app
	void Close();
	static void GLAPIENTRY MessageCallback(GLenum, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	/// run app
	void Run();
	// load picture 
	
	TextureResource texture;


private:

	Display::Window* window;

	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;


	
	Camera camera; // camera object



	// width and hieght of window
	const int width = 800;
	const int height = 600;
	
	// help function to get GLFW window.
	

	// Add the grid as a member variable
	//Render::Grid grid; 
	
};
} // namespace Example
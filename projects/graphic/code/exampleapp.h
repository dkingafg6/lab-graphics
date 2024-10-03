#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2022 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "render/MeshResource.h"
#include "core/mat4.h"
#include "render/Camera.h"

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

	// Add the grid as a member variable
	//Render::Grid grid; 
	
};
} // namespace Example
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
#include "render/Window.h"

#include "core/app.h"
#include "render/window.h"

namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();

	/// open app
	bool Open();
	/// close app
	void Close();
	/// run app
	void Run();
private:
	Display::Window* window;
	
	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;

	// member of meshresource,
	MeshResource* meshResource;

	Camera camera; // camera object
	
	

	// width and hieght of window
	const int width = 800; 
	const int height = 600; 

};
} // namespace Example
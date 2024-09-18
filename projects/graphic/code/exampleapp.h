#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2022 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "render/MeshResource.h"
#include "render/Camera.h"
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
	// adding member
	MeshResource* meshResource; 
	TextureResource texture; 
	
};
} // namespace Example
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
	//------------------------------------------------------------------------------
	/**
	*/
	bool Open();
	/// close app
	void Close();
	/// run app
	void Run();
private:

	// point to window 
	Display::Window* window{ nullptr };

	// all IDs 
	GLuint program{ 0 };
	GLuint vertexShader{ 0 };
	GLuint pixelShader{ 0 };
	GLuint triangle{ 0 };

	// point to meshrecsource
	MeshResource* mesh{ nullptr };
	TextureResource texture; // resource for texture. 
	Camera camera; 

	GLuint texLoc; 
	GLuint modelLoc; 
	GLuint viewLoc;
	GLuint projLoc; 



};
} // namespace Example

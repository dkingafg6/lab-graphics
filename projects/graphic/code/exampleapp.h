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
	// massage callback function be called when there is e debug message from opengl .
	static void GLAPIENTRY MessageCallback(GLenum, GLenum tpye, GLuint id, GLenum serverity, GLsizei length, const GLchar* message, const void* userParam); 
private:

	// point to window 
	Display::Window* window;

	// all IDs 
	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;

	// point to meshrecsource
	MeshResource* mesh;
	TextureResource texture; // resource for texture. 
	Camera camera; 
	GLuint texLoc; 
	GLuint modelLoc; 
	GLuint viewLoc;
	GLuint projLoc; 



};
} // namespace Example

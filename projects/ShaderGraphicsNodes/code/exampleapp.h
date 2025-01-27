#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2022 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include <GL/glew.h>
#include "config.h"
#include <cstring>
#include "render/MeshResource.h"
#include "core/mat4.h"
#include "core/vec2.h"
#include "core/vec3.h"
#include "core/vec4.h"
#include "render/Camera.h"
#include "render/WindowWrapper.h"
#include "render/grid.h"
#include "core/app.h"
#include "render/window.h"
#include "render/TextureResource.h"
#include "render/GraphicsNode.h"
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
	

	double lastMouseX, lastMouseY, lastMouseZ;


	// the cube's position
	mat4 translationMatrix;
	// cube' rotation angles around x,y and z axis. 
	float rotationX = 0.0f;
	float rotationY = 0.0f;
	float rotationZ = 0.0f;

private:

	Display::Window* window;

	Camera cameraObject; // camera object
	GraphicsNode graphicsNode;

	DirectionalLight sunLight;
	PointLightSourceNode pointLight;

	bool mouseLeftPressed = false;
	bool mouseRightPressed = false;
	bool mouseMiddlePressed = false;

	// width and hieght of window
	const int width = 800;
	const int height = 600;
	
};
} // namespace Examplewdss
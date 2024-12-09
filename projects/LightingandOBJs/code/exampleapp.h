#pragma once
#include <GL/glew.h>
#include "exampleapp.h"
#include <cstring>
#include "render/MeshResource.h"
#include "render/ShaderResource.h"
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
#include "render/PointLightSourceNode.h"
#include "render/GraphicsNode.h"
#include "render/DirectionalLight.h"

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
	float lastMouseY; // set mous function to control with mouse 
	float lastMouseZ;

	mat4 translationMatrix; 
	GraphicsNode graphicsNode; 
	GraphicsNode graphicsNode2;
	Camera cameraObject; // camera object

	PointLightSourceNode pointLight;

	bool pauseLightMovement = false; 
	float lastTime;  
	 

	bool mouseLeftPressed = false;
	bool mouseRightPressed = false;
	bool mouseMiddlePressed = false;
	// width and hieght of window
	const int width = 800;
	const int height = 600;
	
};
} // namespace Examplewdss
#pragma once
#include <config.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "core/mat4.h"
#include "core/vec4.h"
#include "core/vec3.h"
#include "render/window.h"

#include "math.h"

class Camera
{



public:
	Camera();
	// constructor for width, height and position. 
	Camera(int width, int height, vec3 position);

	// constructor with pos. target, and up vectors. 
	Camera(const vec3& pos, const vec3& target, const vec3& up, float fov = 45.0f, float aspect = 1.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

	// camera's properties, position, target, vector, field of view in degrees, ration ( width / height) clipping plans both near and far.
	vec3 position;
	vec3 target = vec3(0.0f, 0.0f, -1.0f); 
	vec3 up     = vec3(0.0f, 1.0f, 0.0f);


	// prevent the camera from jumping when clicking the first time. 
	bool firstClick = true; 

	// window's width and height. 
	int width;
	int height;

	// camera's angles for looking around.  
	float yaw = -90.0f; 
	float pitch = 0.0f; 

	// Field of view, aspect ratio, near plane and far clipping plane
	float fov, aspect, nearPlane, farPlane;

	// adjusting the speed of the camera. 
	float speed = 0.1f; 

	// adjusting the sensitivity of the camera. 
	float sensitivity = 0.10f; 

	// mouse position tracking. 
	float lastX; 
	float lastY;

	bool firstMouse; 
	
	


	
	// calculate the view matrix ( look up target ) 
	mat4 getViewMatrix() const;

	// calculate the perspective matrix 
	mat4 getPerspectiveMatrix() const;

	// calculate the combined projection ( perspective * view ) 
	mat4 getProjectionMatrix() const;

	// update and send the camera matrix to the shader. 
	void updateCameraMatrix(float FOVdeg, GLuint shaderProgram, const char* uniform); 
	


	// move the camera ( translate in world space) 
	void move(const vec3& delta); 

	// rotate the camera (yaw and pitch)  
	//void setFOV(float yaw, float pitch); 

	// setters for fov aspect ratio, and clipping plans. 
	void setFOV(float newFOV); 

	void setAspectRatio(float newAspect); 
	void setClippingPlanes(float newNear, float newFar); 

	////////////  testing for mouse control ///////////////


	/// set key press function callback
	void SetKeyPressFunction(const std::function<void(int32, int32, int32, int32)>& func);
	/// set mouse press function callback
	void SetMousePressFunction(const std::function<void(int32, int32, int32)>& func);
	/// set mouse move function callback
	void SetMouseMoveFunction(const std::function<void(float64, float64)>& func);
	


	////////////  testing for mouse control ///////////////
	


	// mouse callback for camera rotation. 
	void mouse_callback(float64 xpos, float64 ypos); 

	// handle keyboard and mouse inputs for camera movement. 
	void processInput(GLFWwindow* window);

	//// functions to rotation around axes. 
	//vec3 rotateX(const vec3& v, float angle) const; 
	//vec3 rotateY(const vec3& v, float angle) const;

	// calculate direction based on (pitch and yaw)
	void updateTarget(); 

private: 
	void clamPicth(); 


};


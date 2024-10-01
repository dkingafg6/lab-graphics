#pragma once
#include <config.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "core/mat4.h"
#include "core/vec4.h"
#include "core/vec3.h"
#include "math.h"

class Camera
{



public:

	// camera's properties, position, target, vector, field of view in degrees, ration ( width / height) clipping pland both near and far.
	vec3 position, target, up;
	float fov, aspect, nearPlane, farPlane;

	// camera's properties for mouse control 
	float yaw, pitch, sensitivity, lastX, lastY; 
	bool firstMouse; 


	// constructor. 
	Camera();
	Camera(const vec3& pos, const vec3& target, const vec3& up, float fov = 45.0f, float aspect = 1.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
		/*: position(pos), target(target), up(up), fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane),
		yaw(-90.0f), pitch(0.0f), sensitivity(0.1f), lastX(400), lastY(300), firstMouse(true);*/


	// calculate the view matrix
	// calculate the view matrix
	mat4 getViewMatrix() const;
	

	// Calculate the perspective matrix: 
	mat4 getPerspectiveMatrix() const; 


	// calculate the combined projection = perspective * view. 
	mat4 getProjectionMatrix() const; 

	// move the camera ( translate in world space) 
	void move(const vec3& delta); 

	// rotate the camera (yaw and pitch)  
	void setFOV(float yaw, float pitch); 

	// setters for fov aspect ratio, and clipping plans. 
	void setFOV(float newFOV); 
	void setAspectRatio(float newAspect); 
	void setClippingPlanes(float newNear, float newFar); 
	void mouse_callback(GLFWwindow* window, double xpos, double ypos); 
	void processInput(GLFWwindow* window, Camera& camera);

	// functions to ratete around axes. 
	vec3 rotateX(const vec3& v, float angle) const; 
	vec3 rotateY(const vec3& v, float angle) const;

	// caculate direction based on (pitch and yaw)
	void updateTarget(); 


};


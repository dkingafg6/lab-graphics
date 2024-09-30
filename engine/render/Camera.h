#pragma once
#include <config.h>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "core/mat4.h"
#include "core/vec4.h"
#include "core/vec3.h"

class Camera
{



public:

	// constructor. 
	Camera(const vec3& pos, const vec3& target, const vec3& up,
		float fov = 45.0f, float aspect = 1.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

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




	// camera's properties, position, target, vector, field of view in degrees, ration ( width / height) clipping pland both near and far.
	vec3 position, target, up; 
	float fov, aspect, nearPlane, farPlane;


	// functions to ratete around axes. 
	vec3 rotateX(const vec3& v, float angle) const; 
	vec3 rotateY(const vec3& v, float angle) const;

	



	//float fov = 45.0f;
	//float nearPlane = 0.1f, farPlane = 100.0f;
	//float radius;
	//float rotationSpeed = 1.0f; // per second 
	//float aspect; 
	//Camera(const vec3& position, const vec3& target, const vec3& up) : 
		//position(position), target(target), up(up), fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane) {};

	//mat4 getViewMatrix() const; 
	//mat4 getProjectionMatrix(); 

	//void orbit(); 

	//void update(); 
	//void setAspectRatio(float ratio); 
	//float fov = 45.0f; 
	//float nearPlane = 0.1f, farPlane = 100.0f; 
	//float radius; 
	//float rotationSpeed = 1.0f; // per second 
	//
	


};


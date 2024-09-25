#pragma once
#include"render/Camera.h"
#include "core/mat4.h"
#include "core/vec3.h"
#include "core/vec2.h"

class Camera
{
public:
	// the camera's view and projection matrices. 
	mat4 viewMatrix; // transforms wordl coordinates to camera coordinates. 
	mat4 projectionMatrix; // handles projection transformation. 

	// constructor 
	Camera();
	// distructor. 
	~Camera();

	// set up the camers's perspective projection 
	// fov = vieew in degrees. 
	// aspect = ratio width and height of viewport. 
	// nearplan = a distance to near cliping plan. 
	// farplan = a distance to far cliping plan. 
	void SetPerspective(float fov, float aspect, float nearPalne, float farPlane); 

	// camera position and orientation 
	// position = position in world space. 
	// target = looking the camera at. 
	// up = direction for camera. 
	void SetView(const vec3& positin, const vec3& target, const vec3& up);

	// a target point of the camera to arbit. 
	// radius = distance from target point 
	// angle = nagle rotation around target point. 
	void SetOrbit(float radius, float angle); 

	// getter for the view and projection matrices. 
	const mat4& GetViewMatrix() const; // currnet view matrix
	const mat4& GetProjectionMatrix() const; // current projection matrix

	
};


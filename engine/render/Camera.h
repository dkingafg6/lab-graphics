#pragma once
#include"render/Camera.h"
#include "core/mat4.h"
#include "core/vec3.h"
#include "core/vec2.h"

class Camera
{
public:
	Camera(); 
	Camera(const vec3& Position, const vec3& target, const vec3& up, float fov, float aspect, float nearPlan, float farPlan); 

	void update(float deltaTime); // use un update loop for rotate the camera. 
	void processInput(GLFWwindow* window, float deltaTime); // keyboard inpits. 

	// getter for the view and projection matrices. 
	mat4& GetViewMatrix() const; // currnet view matrix
	mat4& GetProjectionMatrix() const; // current projection matrix

	void setPosition(const vec3& position); 
	void setTarget(const vec3& target);
	void setUp(const vec3& up); 
	void setAspect(float newAspect); // updating the aspect ratio.
	void setFOV(float nedFOV); // updating 


	mutable mat4 viewMarix; 
	mutable mat4 projectionMatrix; 
	mutable bool isViewMatrixDirty; 

	vec3 position; // camera pos
	vec3 target; // camera perspective.
	vec3 up;  // direction up.
	vec3 front; 
	vec3 right;
	float fov; // aspect ratio
	float aspect; 
	float nearPlan; 
	float farPlan; 

	float movementSpeed; 
	float rotationSpeed; 
	// for rotation 
	float angle; // angle rotation 
	float radius; // how long the target are. 
	float rotationSpeed; // rotation's speed. 

};


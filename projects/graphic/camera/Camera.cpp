#include "Camera.h"
#include "mat4.h"



Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::SetPerspective(float fov, float aspect, float, float)
{
	this->projectionMatrix = perspective(fov, aspect, near, far); 
}

void Camera::SetView(const vec3& positin, const vec3& target, const vev3& up)
{
	this->viewMatrix = lookat(position, target, up); 
}
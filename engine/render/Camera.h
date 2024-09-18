#pragma once
#include "core/mat4.h"

class Camera
{
public:
	mat4 viewMatrix; 
	mat4 projectionMatrix; 
	Camera();
	~Camera();

	//void (testing https ://chatgpt.com/c/66e811d4-7440-8003-8846-6a0c379eb4a1)

private:

	void Camera::SetPerspective(float fov, float aspect, float, float);

	void Camera::SetView(const vec3& positin, const vec3& target, const vev3& up);

};


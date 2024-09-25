#pragma once
#include"render/Camera.h"
#include "core/mat4.h"
#include "core/vec3.h"
#include "core/vec2.h"

class Camera
{
public:
	mat4 viewMatrix;
	mat4 projectionMatrix;

	Camera();
	~Camera();


	void SetPerspective(float fov, float aspect, float nearPalne, float farPlane); 

	void SetView(const vec3& positin, const vec3& target, const vec3& up);
	void SetOrbit(float radius, float angle); 

	const mat4& GetViewMatrix() const;
	const mat4& GetProjectionMatrix() const; 

	
};


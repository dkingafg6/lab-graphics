#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "core/vec3.h"
#include "core/util.h"
#include "render/window.h"
#include "render/ShaderResource.h"
#include "math.h"

class DirectionalLight
{
public:


	vec3 direction;
	vec3 color;
	float intensity;


	// constructor.
	DirectionalLight();
	DirectionalLight(const vec3& direct, const vec3& col, float intens);
	~DirectionalLight();

	void ApplyToShader(std::shared_ptr<ShaderResource> shaderProgram);


	// Setters and Getters
	void setDirectionalLightDirection(const vec3& direct);
	vec3 getDirectionalLightDirection() const;

	void setDirectionalLightColor(const vec3& col);
	vec3 getDirectionalLightColor() const;

	float setDirectionalLightIntensity(float intens);
	float getDirectionalLightIntensity() const;

	


private:


};
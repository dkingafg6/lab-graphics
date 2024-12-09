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
	DirectionalLight(const vec3& direc, const vec3& col, float intens);
	~DirectionalLight();

	void ApplyToShader(std::shared_ptr<ShaderResource> shaderProgram);


	void setPointlightDirection(vec3& direction);
	vec3 getPointLightDirection();

	void setPointLightColor(vec3 color);
	vec3 getPointLightColor();

	void setPointLightIntensity(float lightIntensity);
	float getPointLightIntensity();



private:


};
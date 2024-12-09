#pragma once
#include <GL/glew.h>
#include <memory>
#include <cstring>
#include <core/vec3.h>
#include "render/ShaderResource.h"
#include "math.h"

class PointLightSourceNode
{
private:
	vec3 position; // pos for light in world space. 
	vec3 color; // color for the light. 
	float intensity;  // intencity of the light. 

public:
	// constructor.
	PointLightSourceNode();
	~PointLightSourceNode();

	void setPointlightPosition(vec3& position);
	vec3 getPointLightPosition();

	void setPointLightColor(vec3 color);
	vec3 getPointLightColor();

	void setPointLightIntensity(float lightIntensity);
	float getPointLightIntensity();

	void ApplyToShader(std::shared_ptr<ShaderResource> shaderProgram);

};
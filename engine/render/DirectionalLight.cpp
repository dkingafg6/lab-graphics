#include "config.h"
#include "render/DirectionalLight.h"



DirectionalLight::DirectionalLight(const vec3& direc, const vec3& col, float intens)
{

	direction = vec3(0.0f, 0.0f, 0.0f);
	color = vec3(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;

	
}

void DirectionalLight::ApplyToShader(std::shared_ptr<ShaderResource> shaderProgram)
{
	shaderProgram->UseProgram();
	shaderProgram->setUniform3fv("pointLight.position", getPointLightPosition());
	shaderProgram->setUniform3fv("pointLight.color", getPointLightColor());
	shaderProgram->setUniform1f("pointLight.intensity", getPointLightIntensity());

}


void DirectionalLight::setPointlightPosition(vec3& position)
{
}

vec3 DirectionalLight::getPointLightPosition()
{
	return vec3();
}

void DirectionalLight::setPointLightColor(vec3 color)
{
}

vec3 DirectionalLight::getPointLightColor()
{
	return vec3();
}

void DirectionalLight::setPointLightIntensity(float lightIntensity)
{
}

float DirectionalLight::getPointLightIntensity()
{
	return 0.0f;
}


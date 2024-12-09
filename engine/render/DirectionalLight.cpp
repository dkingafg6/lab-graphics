#include "config.h"
#include "render/DirectionalLight.h"


DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(const vec3& direc, const vec3& col, float intens)
{

	direction = vec3(0.0f, 0.0f, 0.0f);
	color = vec3(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;


}

DirectionalLight::~DirectionalLight()
{
}


void DirectionalLight::ApplyToShader(std::shared_ptr<ShaderResource> shaderProgram)
{
	shaderProgram->UseProgram();
	shaderProgram->setUniform3fv("pointLight.direction", getPointLightDirection());
	shaderProgram->setUniform3fv("pointLight.color", getPointLightColor());
	shaderProgram->setUniform1f("pointLight.intensity", getPointLightIntensity());

}


void DirectionalLight::setPointlightDirection(vec3& direction)
{
}

vec3 DirectionalLight::getPointLightDirection()
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


#include "config.h"
#include "render/DirectionalLight.h"


DirectionalLight::DirectionalLight()
{
	direction = vec3(-0.5f, -1.0f, -0.5f);
	color = vec3(1.0f, 0.9f, 0.8f);
	intensity = 1.0f;



}

DirectionalLight::DirectionalLight(const vec3& direct, const vec3& col, float intens)
{

	direction = direct;
	color = col;
	intensity = intens;

	
}

DirectionalLight::~DirectionalLight()
{
}


void DirectionalLight::ApplyToShader(std::shared_ptr<ShaderResource> shaderProgram)
{
	shaderProgram->UseProgram();
	shaderProgram->setUniform3fv("directionalLight.rotation", getDirectionalLightDirection());
	shaderProgram->setUniform3fv("directionalLight.color", getDirectionalLightColor());
	shaderProgram->setUniform1f("directionalLight.intensity", getDirectionalLightIntensity());

}

void DirectionalLight::setDirectionalLightDirection(const vec3& direct)
{
	this->direction = direct; 
}

vec3 DirectionalLight::getDirectionalLightDirection() const
{
	return this->direction; 
}

void DirectionalLight::setDirectionalLightColor(const vec3& col)
{
	this->color = col; 
}

vec3 DirectionalLight::getDirectionalLightColor() const
{
	return this->color; 
}
float DirectionalLight::setDirectionalLightIntensity(float intens)
{
	return this->intensity; 
}

float DirectionalLight::getDirectionalLightIntensity() const
{
	return 0.0f;
}

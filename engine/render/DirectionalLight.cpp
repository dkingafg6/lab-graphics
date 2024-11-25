#include "render/DirectionalLight.h"

DirectionalLight::DirectionalLight(const vec3& direc, const vec3& col, float intens)
{
	direction(direc.normalize()), color(col), intensity(intens)
}

void DirectionalLight::Apply(GLuint shaderProgram)
{
	GLint directionLoc = glGetUniformLocation(shaderProgram, " direcLight. direction"); 
	GLint colorLoc = glGetUniformLocation(shaderProgram, " directLight.color");
	GLint intensityLoc = glGetUniformLocation(shaderProgram, " direcLight.intensity ");
}

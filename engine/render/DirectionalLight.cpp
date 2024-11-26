#include "config.h"
#include "render/DirectionalLight.h"



DirectionalLight::DirectionalLight(const vec3& direc, const vec3& col, float intens)
	: direction(normalize(direc)), color(col), intensity(intens)
{
	// Constructor body (if needed)
}
DirectionalLight::~DirectionalLight()
{
}
void DirectionalLight::Apply(GLuint shaderProgram)
{
	GLint directionLoc = glGetUniformLocation(shaderProgram, "direcLight.direction"); 
	GLint colorLoc = glGetUniformLocation(shaderProgram, "directLight.color");
	GLint intensityLoc = glGetUniformLocation(shaderProgram, "direcLight.intensity");


	if (directionLoc == -1 || colorLoc == -1 || intensityLoc == -1)
	{
		std::cerr << "ERROR: Faild to find DirectionalLight uniform in shader." << std::endl; 
		return; 

	}






	glUniform3fv(directionLoc, 1, (GLfloat*)&direction);
	glUniform3fv(colorLoc, 1, (GLfloat*)&color);
	glUniform1f(intensityLoc, intensity);

}

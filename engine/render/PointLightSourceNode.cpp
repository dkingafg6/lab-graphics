#include "config.h"
#include "render/PointLightSourceNode.h"



PointLightSourceNode::PointLightSourceNode()
{
	// empty

}
PointLightSourceNode::~PointLightSourceNode()
{
	// empty
}
void PointLightSourceNode::Apply(GLuint shaderProgram)
{

	GLint positionLoc = glGetUniformLocation(shaderProgram, "pointLight.position");
	GLint colorLoc = glGetUniformLocation(shaderProgram, "pointlLightLight.color");
	GLint intensityLoc = glGetUniformLocation(shaderProgram, "pointLightLight.intensity");

	glUniform3fv(positionLoc, 1, (GLfloat*)&position); 
	glUniform3fv(colorLoc, 1, (GLfloat*)&color);
	glUniform1f(intensityLoc, intensity);

}

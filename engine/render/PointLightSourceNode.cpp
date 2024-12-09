#include "config.h"
#include "render/PointLightSourceNode.h"



PointLightSourceNode::PointLightSourceNode()
{
	position = vec3(0.0f, 0.0f, 0.0f);
	color = vec3(1.0f, 1.0f, 1.0f);
	intensity = 1.0f; 
	

}
PointLightSourceNode::~PointLightSourceNode()
{
	// empty
}
void PointLightSourceNode::setPointlightPosition(vec3 position)
{
	this->position = position;
}
vec3 PointLightSourceNode::getPointLightPosition()
{
	return this->position;
}
void PointLightSourceNode::setPointLightColor(vec3 color)
{
	this->color = color;
}

vec3 PointLightSourceNode::getPointLightColor()
{
	return this->color;
}

void PointLightSourceNode::setPointLightIntensity(float lightIntensity)
{
	this->intensity = intensity;
}

float PointLightSourceNode::getPointLightIntensity()
{
	return this->intensity;
}

void PointLightSourceNode::ApplyToShader(std::shared_ptr<ShaderResource> shaderProgram)
{
	shaderProgram->UseProgram();
	shaderProgram->setUniform3fv("pointLight.position", getPointLightPosition());
	shaderProgram->setUniform3fv("pointLight.color", getPointLightColor());
	shaderProgram->setUniform1f("pointLight.intensity", getPointLightIntensity());
}



























//
//void PointLightSourceNode::applyToShaderDeferred(std::shared_ptr<ShaderResource> shader)
//{
//	shader->setuniform1I("gPosition", 0);
//	shader->setuniform1I("gNormal", 1);
//	shader->setuniform1I("gAlbedoSpec", 2);
//}
//
//void PointLightSourceNode::generateRandomLights()
//{
//	// Ensure srand is called only once in your program, ideally in main()
//	static bool seeded = false;
//	if (!seeded)
//	{
//		srand(13);
//		seeded = true;
//	}
//
//	// Generate random colors in the range [0.5, 1.0]
//	float rColor = (rand() / (float)RAND_MAX);
//	float gColor = (rand() / (float)RAND_MAX);
//	float bColor = (rand() / (float)RAND_MAX);
//
//	// Push the color into the list of light colors
//	lightColors.push_back(vec3(rColor, gColor, bColor));
//
//}
//
//void PointLightSourceNode::sendLightRelevantUniforms(std::shared_ptr<ShaderResource> shader, float radius)
//{
//	for (int i = 0; i < lightPositions.size(); i++)
//	{
//		shader->setuniform3fv("light.Position", lightPositions[i]);
//		shader->setuniform3fv("light.Color", lightColors[i]);
//		shader->setUniform1f("light.Radius", radius);
//		// update attenuation parameters and calculate radius
//		const float linear = 0.1f;
//		const float quadratic = 30.0f;
//		shader->setUniform1f("light.Linear", linear);
//		shader->setUniform1f("light.Quadratic", quadratic);
//	}
//}
//
//
//
//
//void PointLightSourceNode::setLightTargetPosition(const vec3& target)
//{
//	this->lightTargetPosition = target;
//}
//void PointLightSourceNode::setLightPosition(int lightIndex, vec3& newPosition)
//{
//
//	if (lightIndex >= 0 && lightIndex < lightPositions.size())
//	{
//		lightPositions[lightIndex] = newPosition;
//	}
//
//}
//
//void PointLightSourceNode::setLightOwnPosition(const vec3& pos)
//{
//	this->LightOwnPosition = pos;
//}
//
//
//void PointLightSourceNode::setColor(const vec3& col)
//{
//	this->lightColor = col;
//}
//
//void PointLightSourceNode::setIntensity(float inten)
//{
//	this->lightIntensity = inten;
//}
//void PointLightSourceNode::PushBackLightPositions(vec3& positions)
//{
//	this->lightPositions.push_back(positions);
//}
//
//const vec3& PointLightSourceNode::getPosition() const
//{
//	return this->LightOwnPosition;
//}
//
//const vec3& PointLightSourceNode::getColor() const
//{
//	return this->lightColor;
//}
//
//float PointLightSourceNode::getIntenstity() const
//{
//	return this->lightIntensity;
//}
//
//void PointLightSourceNode::renderQuad()
//{
//	if (quadVAO == 0)
//	{
//		float quadVertices[] =
//		{
//			// positions        // texture Coords
//			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//		};
//		// setup plane VAO
//		glGenVertexArrays(1, &quadVAO);
//		glGenBuffers(1, &quadVBO);
//		glBindVertexArray(quadVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	}
//	glBindVertexArray(quadVAO);
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glBindVertexArray(0);
//
//
//

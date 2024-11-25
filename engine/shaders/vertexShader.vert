#version 430
layout(location=0) in vec3 pos;
layout(location=1) in vec4 color;
layout(location=2) in vec2 texCoord;
layout(location=3) in vec3 normal; 

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
//out vec4 projection;

out vec3 fragPos; // pos in world space. 
out vec3 fragNormal; // normalize in world space 

out vec4 Color;
out vec2 TexCoord;


void main()
{

	gl_Position = projectionMatrix * viewMatrix * modelMatrix *  vec4(pos, 1.0); // just for camera. combine rotation and camera.
	Color = color;
	TexCoord = texCoord;
	fragPos = vec3(modelMatrix * vec4(pos, 1.0)); 

	//fragNormal = normalize(normalMatrix * normal); 
	// there is no class mat3 bur can campute here in world space (upper left 3x3 modelMatrix; 
	mat3 normalMatrix = mat3(
	vec3(modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2]),
	vec3(modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2]), 
	vec3(modelMatrix[2][0], modelMatrix[2][1], modelMatrix[2][2])
	); 

	// transforming normal in world space then normalize it. 
	fragNormal = normalize(normalMatrix * normal); 
	
}

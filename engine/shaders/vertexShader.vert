#version 430
layout(location=0) in vec3 position;

layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;
//layout(location=3) in vec3 normal; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 model;
//out vec4 projection;


//out vec4 vertexColor; 
out vec3 fragPos; // pos in world space. 
out vec3 fragNormal; // normalize in world space 

//out vec4 Color;
out vec2 TexCoord;


void main()
{

	gl_Position = projection * view* model *  vec4(position, 1.0); // just for camera. combine rotation and camera.
	//Color = color;
	//TexCoord = texCoord;
	fragPos = vec3(model * vec4(position, 1.0)); 

	//fragNormal = normalize(normalMatrix * normal); 
	// there is no class mat3 bur can campute here in world space (upper left 3x3 modelMatrix; 
	mat3 normalMatrix = mat3(
	vec3(model[0][0], model[0][1], model[0][2]),
	vec3(model[1][0], model[1][1], model[1][2]), 
	vec3(model[2][0], model[2][1], model[2][2])
	); 

	// transforming normal in world space then normalize it. 
	fragNormal = normalize(normal * normal); 
	TexCoord = texCoord;

	
}

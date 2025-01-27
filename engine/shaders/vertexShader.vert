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
out vec3 fragNormal; 
//out vec4 Color;
out vec2 TexCoord;


void main()
{

	gl_Position = projection * view * model *  vec4(position, 1.0); // just for camera. combine rotation and camera.

	fragPos = vec3(model * vec4(position, 1.0)); 

	fragNormal = mat3(transpose(inverse(model))) * normal;

	TexCoord = texCoord; 
	
}

#version 430
layout(location=0) in vec3 pos;
layout(location=1) in vec4 color;
layout(location=2) in vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
//out vec4 projection;
out vec4 Color;
out vec2 TexCoord;


void main()
{
	gl_Position = projection * view * model *  vec4(pos, 1); // just for camera. combine rotation and camera.
	Color = color;
	TexCoord = texCoord;
}
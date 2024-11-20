#version 430
in vec4 color;
in vec2 TexCoord;

uniform sampler2D texture1;

out vec4 FragColor;
out vec4 Color;
void main()
{
	FragColor = texture(texture1, TexCoord);
}
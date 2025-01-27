#version 430


in vec3 fragPos;
in vec3 fragNormal;
in vec2 TexCoord;


uniform sampler2D texture1;
out vec4 FragColor;
void main()
{
vec4 texColor = texture(texture1, TexCoord);
    FragColor =  texColor;
}



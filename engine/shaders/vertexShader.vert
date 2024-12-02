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
	//Color = color;
	//TexCoord = texCoord;
	fragPos = vec3(model * vec4(position, 1.0)); 


	// the 3x3 normal matrix from the model matrix
    mat4 inverseModel = inverse(model);
    mat4 transposedModel = transpose(inverseModel);
    mat3 normalMatrix = mat3(
        transposedModel[0].xyz,
        transposedModel[1].xyz,
        transposedModel[2].xyz
    );

	fragNormal = mat3(transpose(inverse(model))) * normal;

	TexCoord = texCoord; 
	
}

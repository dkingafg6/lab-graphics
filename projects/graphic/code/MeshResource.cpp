#include "MeshResource.h"
#include <GL/eglew.h>
#include <cstring>
#include "config.h"



// vertex shader source code( GLSL) 
const GLchar* vs =
"#version 430\n"// specify openGL version 
"layout(location=0) in vec3 pos;\n" // input: vertex position ( 3D vectors) 
"layout(location=1) in vec4 color;\n" // input: vertex color ( 4D vector) 
"layout(location=0) out vec4 Color;\n" // output; color passed to the fragment shader. 
"void main()\n"
"{\n"
"	gl_Position = vec4(pos, 1);\n" // set vertex position, converting vec3 to vev4 by adding w = 1.0
"	Color = color;\n" // pass the vertex color to the fragment shader. 
"}\n";

const GLchar* ps =
"#version 430\n"                     // specify openGL version 4.3 
"layout(location=0) in vec4 color;\n" // input: color from vertex shader. 
"out vec4 Color;\n"                   // output: final pixel color. 
"void main()\n"
"{\n"
"	Color = color;\n" // set the final pixel color. 
"}\n";

using namespace std;

MeshResource::MeshResource()
{
	// generate the buffers.
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);

	//vertexBuffer = 0;
	//indexBuffer = 0;
}

MeshResource::~MeshResource()
{
	// cleaning the buffers.
	glDeleteBuffers(1, &VBO); 
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO); 

}
// VBO = vertex buffer object 
void MeshResource::createVBO(float x, float y)
{
	vertices = {
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // bottom-lft red
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, //bottom- right green
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 1.0f}}, // top- right blue
		{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}}, // top- left yellow


	}; 

	indices = { 0, 1, 2, 2, 3, 0 }; // should b two triangles to from a quad. 

	//float position[] =
	//{
	//	-x, y, // p1
	//	0.0f, 0.0f, 0.0f, 0.0f, // color red green blue alfa (alfa == transparency)
	//	x, y, // p2
	//	0.0f, 0.0f, 0.0f, 0.0f,// color RGBA
	//	x,-y, // p3
	//	0.0f, 0.0f, 0.0f, 0.0f, // color RGBA
	//	-x, -y, //p4
	//	0.0f, 0.0f, 0.0f, 0.0f, // color RGBA
	//};

	// generate buffer for binding vertex

	glGenBuffers(1, &vertexBuffer);
	// bind the openGL array data with vertex buffer. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// take the information from what type, what size and what position and draw. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


}
// IBO = index buffer object
void MeshResource::createIBO()
{
	// connecting the points to gather. 
	int indices[] =
	{
		0, 1, 2, // front 
		2, 3, 0,

	};
	// generate buffer for binding indexes. 
	glGenBuffers(1, &indexBuffer);
	// bind the openGL element array data with index buffer. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// take the information from what type, what size and what indexes and draw. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);  // position
	glEnableVertexAttribArray(1);  // color 

	glEnableVertexAttribArray(2); // uv

	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)(sizeof(float32) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)(sizeof(float32) * 7));*/

	//buffersCreated = true


}

inline void MeshResource::createVAO()
{
}

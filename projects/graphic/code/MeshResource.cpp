#include "MeshResource.h"
#include <GL/eglew.h>




const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(pos, 1);\n"
"	Color = color;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"}\n";


MeshResource::MeshResource()
{
	vertexBuffer = 0;
	indexBuffer = 0;
}

MeshResource::~MeshResource()
{

}
// VBO = vertex buffer object 
void MeshResource::createVBO(float x, float y)
{
	float position[] =
	{
		-x, y, // p1
		0.0f, 0.0f, 0.0f, 0.0f, // color red green blue alfa (alfa == transparency)
		x, y, // p2
		0.0f, 0.0f, 0.0f, 0.0f,// color RGBA
		x,-y, // p3
		0.0f, 0.0f, 0.0f, 0.0f, // color RGBA
		-x, -y, //p4
		0.0f, 0.0f, 0.0f, 0.0f, // color RGBA
	};

	// generate buffer for binding vertex

	glGenBuffers(1, &vertexBuffer);
	// bind the openGL array data with vertex buffer. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// take the information from what type, what size and what position and draw. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);


}
// IBO = index buffer object
void MeshResource::createIBO()
{
	// connecting the points to gather. 
	int indexes[] =
	{
		0, 1, 2, // front 
		2, 3, 0,

	};
	// generate buffer for binding indexes. 
	glGenBuffers(1, &indexBuffer);
	// bind the openGL element array data with index buffer. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// take the information from what type, what size and what indexes and draw. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

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

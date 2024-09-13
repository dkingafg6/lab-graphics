#pragma once
#include <GL/eglew.h>




class MeshResource
{
private: 
	GLuint vertexBuffer;
	GLuint indexBuffer;

public:

	MeshResource();
	~MeshResource(); 


	void createVBO(float x, float y); 
	void createIBO(); 


};

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
		0, 1, 2,
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
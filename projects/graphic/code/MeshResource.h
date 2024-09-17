#pragma once
#include <GL/glew.h>
#include <config.h>

using namespace std;

class MeshResource
{
private:
	// for vertex data like position and col0rs. 
	GLuint vertexBuffer;
	// show the order of vertices to form primitives like triangles. 
	GLuint indexBuffer;

public:
	// show the order of vertices to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	// vertex buffer object.
	void creatCube(float width, float height, float depth); 
	void createVBO();
	void createIBO();
	void bindVBO();
	void bindIBO();
	// draw the mesh 
	
	void draw(); 
	//static MeshResource* CreateSquare(float x, float y);
	/*void bind(unsigned int unit = 0);*/
};

MeshResource::MeshResource()
{
	vertexBuffer = 0;
	indexBuffer = 0;
}

MeshResource::~MeshResource()
{

}
inline void MeshResource::creatCube(float width, float height, float depth)
{
}
// VBO = vertex buffer object 
void MeshResource::createVBO()
{
	float position[] =
	{
		-0.5, 0.5, 0, // p1
		1.0f, 0.0f, 0.0f, 1.0f, // color red green blue alfa (alfa == trancparenci)
		0.5, 0.5, 0, // p2
		0.0f, 1.0f, 0.0f, 1.0f,// color RGBA
		0.5,-0.5, 0, // p3
		0.0f, 0.0f, 1.0f, 1.0f, // color RGBA
		-0.5, -0.5, 0, //p4
		0.0f, 1.0f, 0.0f, 1.0f, // color RGBA
	};

	// generate buffer for binding vertex

	glGenBuffers(1, &vertexBuffer);
	// bind the openGL array data with vertextbuffer. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// take the information from what type, what size and what position and draw. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

}
// IBO = index buffer object
void MeshResource::createIBO()
{
	// coneccting the points to gather. 
	int indexes[] =
	{
		0, 1, 2,
		2, 3, 0,

	};
	// generate buffer for binding indexes. 
	glGenBuffers(1, &indexBuffer);
	// bind the openGL element array data with indexbuffer. 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	// take the information from what type, what size and what indexes and draw. 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
}

void MeshResource::bindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
}
void MeshResource::bindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

inline void MeshResource::draw()
{
}

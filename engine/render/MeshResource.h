#pragma once
//#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <config.h>
#include <render/stb_image.h>

using namespace std;

class MeshResource
{
private:
	// for vertex data like position and col0rs. 
	GLuint vertexBuffer;
	// show the order of vertices to form primitives like triangles. 
	GLuint indexBuffer;
	// openGle textur indentifire. 
	//GLuint TextureID; 

	GLuint vertexarray; 

public:
	// show the order of vertices to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	// vertex buffer object.
	static MeshResource* CreatCube(float width, float height, float depth)
	{
		MeshResource* mesh = new MeshResource();
		// call function 
		mesh->createVBO();
		mesh->createIBO();
		return mesh;
	}
	void createVBO();
	void createIBO();
	void bindVBO();
	void bindIBO();
	// draw the mesh 
	
	void draw(); 
	void cleanup(); 
	
	//bool LaodFromFile(const char* filename); */
	//static MeshResource* CreateSquare(float x, float y);
	/*void bind(unsigned int unit = 0);*/
};

MeshResource::MeshResource()
{
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexarray = 0; 
}

MeshResource::~MeshResource()
{
	cleanup(); 

}

// VBO = vertex buffer object 
void MeshResource::createVBO()
{
	float position[] =
	{
		// texture and pos coordinate with x, y, z, u and v
		// Front face
		-0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,  0.0f, 1.0f,
		// Back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
	//	0.0f, 0.0f,  // lower-left corner  
	//	1.0f, 0.0f,  // lower-right corner
	//	0.5f, 1.0f   // top-center corner

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
	 unsigned int indices[] =
	{
		0, 1, 2, 2, 3, 0, // Front
		4, 5, 6, 6, 7, 4, // Back
		0, 4, 7, 7, 3, 0, // Left
		1, 5, 6, 6, 2, 1, // Right
		0, 1, 5, 5, 4, 0, // Bottom
		3, 2, 6, 6, 7, 3  // Top


		//0, 1, 2,
		//2, 3, 0,

	};
	// generate buffer for binding indexes. 
	glGenBuffers(1, &indexBuffer);
	// bind the openGL element array data with indexbuffer. 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	// take the information from what type, what size and what indexes and draw. 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void MeshResource::bindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
}
void MeshResource::bindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

void MeshResource::draw()
{
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

void MeshResource::cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}




#pragma once
#include <GL/glew.h>
#include <config.h>
#include "core/vec2.h"
#include "core/vec3.h"
#include <vector>



using namespace std;

class MeshResource
{
public:
	// for vertex data like position and col0rs. 
	GLuint vertexBuffer;
	// show the order of vertices to form primitives like triangles. 
	GLuint indexBuffer;
	// openGle textur indentifire. 
	//GLuint TextureID; 

	GLuint vertexArray; 
	std::vector<vec3> vertices; 
	//std::vector<vec2> vertices; // there is no vec2 in librery 

	//vector to stor texture coordinate in 2D
	std::vector<vec2> texCoords; 

	// vector to store indices for drawing triangles. 
	std::vector<unsigned int> indices; 

	// show the order of vertices to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	// create the vertices with pos and texture cooordinate for each face of the cube.
	static MeshResource* CreatCube(float width, float height, float depth);
	
	void createVBO();
	void createIBO();
	void bindVBO();
	void bindIBO();
	// draw the mesh 
	
	void draw(); 
	void cleanup(); 
	
	
};

inline MeshResource::MeshResource()
{
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexArray = 0; 
}

inline MeshResource::~MeshResource()
{
	cleanup(); 

}

inline MeshResource* MeshResource::CreatCube(float width, float height, float depth)
{
	// each face of the cube define with vertices. 
	MeshResource* cube = new MeshResource(); 

	cube->vertices =
	{
		// front face
		vec3(-width, -height, depth), vec3(width, -height, depth), vec3(width, height, depth), vec3(-width, height, depth),
		// back face.
		vec3(-width, -height, -depth), vec3(width, -height, -depth), vec3(width, height, -depth), vec3(-width, height, -depth),
		// left face
		vec3(-width, -height, -depth), vec3(-width, -height, depth), vec3(-width, height, depth), vec3(-width, height, -depth),
		// right face 
		vec3(width, -height, -depth), vec3(width, -height, depth), vec3(width, height, depth), vec3(width, height, -depth),
		// top face 
		vec3(-width, height, -depth), vec3(width, height, -depth), vec3(width, height, depth), vec3(-width, height, depth),
		// bottom face.
		vec3(-width, -height, -depth), vec3(width, -height, -depth), vec3(width, -height, depth), vec3(-width, -height, depth),


	}; 

	// texture coodinates for cube. 
	cube->texCoords =
	{
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f),// front 
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f),// back
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f), // left
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f),// right
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f),//top 
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f)// bottom 

	};

	//indices for the cube. each face = two triangle. 
	// cube->indexBuffer
	

	// indices for cube two triangles per face. 
	cube->indices =
	{
		// front face.
		0, 1, 2, 0, 2, 3,
		// back face
		4, 5, 6, 4, 6, 7,
		// left face
		8, 9, 10, 8, 10, 11,
		// right face
		12, 13, 14, 12, 14, 15,
		// top face 
		16, 17, 18, 16, 18, 19,
		// battom face
		20, 12, 22, 20, 22, 23


	}; 

	cube->createVBO(); 
	cube->createIBO(); 

	return cube; 
}

// VBO = vertex buffer object 
inline void MeshResource::createVBO()
{
	// generate buffer for binding vertex

	glGenBuffers(1, &vertexBuffer);
	// bind the openGL array data with vertextbuffer. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	std::vector<float> vboData; 
	for (size_t i = 0; i < vertices.size(); i++) 
	{
		vboData.push_back(vertices[i].x); 
		vboData.push_back(vertices[i].y);
		vboData.push_back(vertices[i].z);
		vboData.push_back(texCoords[i].x);
		vboData.push_back(texCoords[i].y);
		
	}

	glBufferData(GL_ARRAY_BUFFER, vboData.size() * sizeof(float), vboData.data(),GL_STATIC_DRAW);

}
// IBO = index buffer object
inline void MeshResource::createIBO()
{
	// generate buffer for binding indexes. 
	glGenBuffers(1, &indexBuffer);
	// bind the openGL element array data with indexbuffer. 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	// take the information from what type, what size and what indexes and draw. 
	glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


}

inline void MeshResource::bindVBO()
{
	// bind vertex buffer object to GL_ARRAY_BUFFER target. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// enable vertex attribute array fo position data. 
	glEnableVertexAttribArray(0); 

	// positaion be specify the layout of vertex. 
	// 3 float for pos no normailization 
	// 5 float stride starting at the beginning of the buffer. 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 *sizeof(float), (void*)0); 

	// the texture coordinate data be enable with attibiute array. 
	glEnableVertexAttribArray(1);

	// specify layout attribute array 
	// 2 float for texture coordinat. 
	// 5 float stride starting after pos data.. with 3 float. 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 *sizeof(float), (void*)(3 * sizeof(float)));
}


inline void MeshResource::bindIBO()
{
	// bind index buffer object to GL_ARRAY_BUFFER target.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

}

inline void MeshResource::draw()
{
	// draw elements like triangle from the bound  index buffer. 
	// the unsingned int specifies by indeces 
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

inline void MeshResource::cleanup()
{
	// delete the vertex buffer if that has been created. 
	if (vertexBuffer != 0) 
	{
		glDeleteBuffers(1, &vertexBuffer);

	}
	// delete the index buffer if that has been created. 
	if (indexBuffer != 0) {
		glDeleteBuffers(1, &indexBuffer);
	}
	// delete the vertex array object  if it has been created. 
	if (vertexArray != 0) {
		glDeleteBuffers(1, &vertexArray);
	}
	
}




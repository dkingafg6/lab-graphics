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
	//{
	//	// set texture coordinates for each vertex. 
	//	MeshResource* mesh = new MeshResource();
	//	// call function 
	//	mesh->createVBO();// create VBO for the cub's vertex data. 
	//	mesh->createIBO(); // create IBO for the cub's index data. 
	//	return mesh;
	//}
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
	MeshResource* cube = new MeshResource(); 

	cube->vertices =
	{
		// front face
		vec3(-width, -height, depth), vec3(width, -height, depth), vec3(width, height, depth), vec3(-width, height, depth),
		// back face.
		vec3(-width, -height, -depth), vec3(width, -height, -depth), vec3(width, height, -depth), vec3(-width, height, -depth)

	}; 

	// texture coodinates for cube. 
	cube->texCoords =
	{
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f),
		vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(0.0f, 1.0f)

	};

	//indices for the cube. each face = two triangle. 
	// cube->indexBuffer
	

	// indices for cube two triangles per face. 
	cube->indices =
	{
		// front face.
		0, 1, 2, 0, 2, 3,
		// back face
		4, 5, 6, 4, 6, 7
		// can draw more face down here!!!!!!!!!!!


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

	//float position[] =
	//{
	//	
	//

	//	// texture and pos coordinate with x, y, z, u and v
	//	// Front face
	//	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
	//	 0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
	//	 0.5f,  0.5f, 0.5f,  1.0f, 1.0f,
	//	-0.5f,  0.5f, 0.5f,  0.0f, 1.0f,
	//	// Back face
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
	////	0.0f, 0.0f,  // lower-left corner  
	////	1.0f, 0.0f,  // lower-right corner
	////	0.5f, 1.0f   // top-center corner

	//	//-0.5, 0.5, 0, // p1
	//	//1.0f, 0.0f, 0.0f, 1.0f, // color red green blue alfa (alfa == trancparenci)
	//	//0.5, 0.5, 0, // p2
	//	//0.0f, 1.0f, 0.0f, 1.0f,// color RGBA
	//	//0.5,-0.5, 0, // p3
	//	//0.0f, 0.0f, 1.0f, 1.0f, // color RGBA
	//	//-0.5, -0.5, 0, //p4
	//	//0.0f, 1.0f, 0.0f, 1.0f, // color RGBA
	//};

	// generate buffer for binding vertex

	//glGenBuffers(1, &vertexBuffer);
	// bind the openGL array data with vertextbuffer. 
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// take the information from what type, what size and what position and draw. 
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


	// unsigned int indices[] =
	//{
	//	0, 1, 2, 2, 3, 0, // Front
	//	4, 5, 6, 6, 7, 4, // Back
	//	0, 4, 7, 7, 3, 0, // Left
	//	1, 5, 6, 6, 2, 1, // Right
	//	0, 1, 5, 5, 4, 0, // Bottom
	//	3, 2, 6, 6, 7, 3  // Top


	//	//0, 1, 2,
	//	//2, 3, 0,

	//};
	//// generate buffer for binding indexes. 
	//glGenBuffers(1, &indexBuffer);
	//// bind the openGL element array data with indexbuffer. 
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	//// take the information from what type, what size and what indexes and draw. 
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

inline void MeshResource::bindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 *sizeof(float), (void*)0); 

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 *sizeof(float), (void*)(3 * sizeof(float)));
}


inline void MeshResource::bindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

}

inline void MeshResource::draw()
{
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

inline void MeshResource::cleanup()
{
	if (vertexBuffer != 0) 
	{
		glDeleteBuffers(1, &vertexBuffer);

	}
	if (indexBuffer != 0) {
		glDeleteBuffers(1, &indexBuffer);
	}
	if (vertexArray != 0) {
		glDeleteBuffers(1, &vertexArray);
	}
	//glDeleteBuffers(1, &vertexBuffer);
	//glDeleteBuffers(1, &indexBuffer);
}




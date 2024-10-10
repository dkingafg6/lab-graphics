#pragma once
#include <config.h>
#include <GL/glew.h>

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

	GLuint vertexArray; 

public:
	// show the order of vertices to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	// vertex buffer object.
	static MeshResource* CreatCube(float width, float height, float depth);
	void createVBO(float width, float height, float depth);
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
	MeshResource* mesh = new MeshResource();
	mesh->createVBO(width, height, depth);
	mesh->createIBO(); 

	glEnableVertexAttribArray(0); // pos
	glEnableVertexAttribArray(1); // color

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));
	return mesh;


}

// VBO = vertex buffer object 
inline void MeshResource::createVBO(float width, float height, float depth)
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float halfDepth = depth / 2.0f;

	float position[] =
	{
		// Front face
	   -halfWidth, -halfHeight, halfDepth, // 0
		05.0f, 0.0f, 1.0f, 0.0f,
		halfWidth, -halfHeight, halfDepth, // 1
		0.0f, 05.0f, 1.0f, 0.0f,
		halfWidth,  halfHeight, halfDepth, // 2
		1.0f, 0.0f, 0.0f, 0.0f,
	   -halfWidth,  halfHeight, halfDepth, // 3
		1.0f, 0.0f, 0.0f, 1.0f,
	   // Back face
	   -halfWidth, -halfHeight, -halfDepth, // 4
		1.0f, 1.0f, 0.0f, 1.0f,
		halfWidth, -halfHeight, -halfDepth, // 5
		1.0f, 0.0f, 0.0f, 0.0f,
		halfWidth,  halfHeight, -halfDepth, // 6
		1.0f, 0.0f, 1.0f, 0.0f,
	   -halfWidth,  halfHeight, -halfDepth, // 7

	 //  // Left face
	 //  halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f, // 4
		//halfWidth, -halfHeight, -halfDepth, 1.0f, 0.0f, // 5
		//halfWidth,  halfHeight, -halfDepth, 1.0f, 1.0f, // 6
	 //  -halfWidth,  halfHeight, -halfDepth, 0.0f, 1.0f, // 7

	 //  // Right face
	 //  -halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f, // 4
		//halfWidth, -halfHeight, -halfDepth, 1.0f, 0.0f, // 5
		//halfWidth,  halfHeight, -halfDepth, 1.0f, 1.0f, // 6
	 //  -halfWidth,  halfHeight, -halfDepth, 0.0f, 1.0f, // 7

	 //  //Top face
	 //  -halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f, // 4
		//halfWidth, -halfHeight, -halfDepth, 1.0f, 0.0f, // 5
		//halfWidth,  halfHeight, -halfDepth, 1.0f, 1.0f, // 6
	 //  -halfWidth,  halfHeight, -halfDepth, 0.0f, 1.0f, // 7

	 //  // Bottom face
	 //  -halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f, // 4
		//halfWidth, -halfHeight, -halfDepth, 1.0f, 0.0f, // 5
		//halfWidth,  halfHeight, -halfDepth, 1.0f, 1.0f, // 6
	 //  -halfWidth,  halfHeight, -halfDepth, 0.0f, 1.0f, // 7
	};

	// generate buffer for binding vertex

	glGenBuffers(1, &vertexBuffer);
	// bind the openGL array data with vertextbuffer. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// take the information from what type, what size and what position and draw. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

}
// IBO = index buffer object
inline void MeshResource::createIBO()
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

inline void MeshResource::bindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
}
inline void MeshResource::bindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

inline void MeshResource::draw()
{
	// bind vertex buffer. 
	bindVBO(); 
	// bind index buffer.
	bindIBO(); 

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

	// unbind both VBO and IBO 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

inline void MeshResource::cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}




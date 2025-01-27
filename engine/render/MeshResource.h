#pragma once
#include <GL/glew.h>
#include <render/MeshResource.h>
#include <core/vec4.h>
#include <core/mat4.h>
#include "core/vec3.h"
#include "core/vec2.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>





using namespace std;




class MeshResource
{
public:


	// sructure for vertices to create cube. 
	struct Vertex
	{
		vec3 position;   // position x,y,z, 
		vec4 color;      // color r,g,b,and a, 
		vec3 texCoord;   // texture coordinates u and v, 
		vec3 normal;

	};


	GLuint vao; 
	// for vertex data like position and col0rs.  
	GLuint vertexBuffer;
	// show the order of vertices to form primitives like triangles. 
	GLuint indexBuffer;

	unsigned int indexSize;




	// show the order of vertices's to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	

	// create the vertices with pos and texture cooordinate for each face of the cube.
	static MeshResource* CreateCube(float width, float height, float depth);
	shared_ptr<MeshResource> CreateCube_SharedPtr(float width, float height, float depth);



	void BindVBO();
	void BindIBO();

	// Stores vetex and index data for position, normal , texcoord and EBO
	// Can be in private also


	// data storage for vertices, normal texture coordinates and indices. 

	// obj file loader 
	void LoadOBJFiles(const std::string& filePath);
	//void loadFromOBJ(const std::string& filename, float scale); 
	// creat a cube. 
	void CreateVBO(float width, float height, float depth);
	void CreateIBO();
	void Draw();



	// method to rerurn the index count 
	GLsizei GetIndexCount() const; 
	GLsizei GetVertexCount()const;
	//void setupMesh(); 
	
	// clean up resource
	void Cleanup(); 

	
};


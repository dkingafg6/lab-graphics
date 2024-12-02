#pragma once

#include <config.h>
#include <GL/glew.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "core/vec3.h"
#include "core/vec2.h"
#include <UserConsentVerifierInterop.h>





using namespace std;




class MeshResource
{
public:


	// sructure for vertices to create cube. 
	struct Vertex
	{
		vec3 position;   // position x,y,z, 
		vec3 color;      // color r,g,b,and a, 
		vec2 texCoord;   // texture coordinates u and v, 
		vec3 normal;

	};
	struct Face
	{
		int vertexIndex;
		int textureIndex;
		int normalIndex;
	};

	std::vector<Vertex> verticies;
	std::vector<Face> faces;


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
	std::shared_ptr<MeshResource> CreateCube_SharedPtr(float width, float height, float depth);



	void BindVBO();
	void BindIBO();

	// Stores vetex and index data for position, normal , texcoord and EBO
	// Can be in private also

	std::vector<vec3>position; 
	std::vector<vec2> uvs;
	std::vector<unsigned int> indices;

	

	void setVertices(const std::vector<vec3>& position); 
	void setUVs(const std::vector<vec2>& uvs);
	void setIndices(const std::vector<unsigned int>& Indices);

	

	// obj file loader 
	void LoadOBJFiles(const std::string& filePath);
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


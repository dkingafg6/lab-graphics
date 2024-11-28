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

		float x, y, z;

	};


	// texture coordinates
	struct TextureCoord
	{
		float u, v;


	};


	struct Normal
	{
		vec3 x, y, z;

	};



	struct Face
	{
		std::vector<int> vertexIndices;
		std::vector<int> textureIndices;
		std::vector<int> normalIndices;


	};


	// for vertex data like position and col0rs.  
	GLuint vertexBuffer;
	// show the order of vertices to form primitives like triangles. 
	GLuint indexBuffer;

	unsigned int indexSize;



	// member variables 
	std::vector<Vertex> vertices;
	std::vector<TextureCoord> texturCoords;
	std::vector<Normal> normals;
	std::vector<Face> faces;


	// show the order of vertices's to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	//void createVBO();

		// OBJ loading methos
	//void LoadFromOBJ(const std::string& filePath); 


	//void setupMesh();
	//draw the mesh 
	

	// create the vertices with pos and texture cooordinate for each face of the cube.
	static MeshResource* CreateCube(float width, float height, float depth);
	std::shared_ptr<MeshResource> CreateCube_SharedPtr(float width, float height, float depth);



	void BindVBO();
	void BindIBO();

	// Stores vetex and index data for position, normal , texcoord and EBO
	// Can be in private also. 
	std::vector<vec3> vertices;
	std::vector<vec2> uvs;
	std::vector<unsigned int> indices;

	

	void setVertices(const std::vector<vec3>& vertices); 
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
	//void setupMesh(); 
	
	// clean up resource
	void Cleanup(); 

	
};

